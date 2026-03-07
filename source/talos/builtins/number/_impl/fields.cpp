/// Talos Modules
#include "talos/member/storage.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_FIELDS(Number::Tagged) {
    TALOS_XX_FIELDS_NUMBER(X)

   private:
    //  PRIVATE METHODS  //

    /// @brief Handles converting numerics to outputs.
    static Value::Any m_stringify(Runtime::Isolate*, const Function::Arguments&, const $::String::View&);
};
#undef X

//  PROPERTIES  //

#define X(N, ...) { #N, Field::N },
TALOS_BUILTIN_STORAGE(Number::Tagged) = Talos::Member::Storage(name(), { TALOS_XX_FIELDS_NUMBER(X) });
#undef X

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_FIELD(Number::Tagged, abs, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args.self());
    return Number::Tagged(std::abs(args.self<Number::Tagged>().value()));
}

TALOS_MM_BUILTIN_FIELD(Number::Tagged, sign, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args.self());
    auto value = args.self<Number::Tagged>().value();    // get value...
    return Number::Tagged(Number::Math::signum(value));  // ...and sign
}

TALOS_MM_BUILTIN_FIELD(Number::Tagged, ceil, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args.self());
    return Number::Tagged(std::ceil(args.self<Number::Tagged>().value()));
}

TALOS_MM_BUILTIN_FIELD(Number::Tagged, floor, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args.self());
    return Number::Tagged(std::floor(args.self<Number::Tagged>().value()));
}

TALOS_MM_BUILTIN_FIELD(Number::Tagged, round, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args.self());
    return Number::Tagged(std::round(args.self<Number::Tagged>().value()));
}

TALOS_MM_BUILTIN_FIELD(Number::Tagged, trunc, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args.self());
    return Number::Tagged(std::trunc(args.self<Number::Tagged>().value()));
}

TALOS_MM_BUILTIN_FIELD(Number::Tagged, clamp, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args.self());

    // get the baseline numeric to be used
    auto self = args.self<Number::Tagged>();

    // prepare the minimum and maximum values
    auto minimum = args.at(0, self), maximum = args.at(1, self);

    // update our values to be non-voidish now
    if (minimum.is<Value::Void>()) minimum = self;
    if (maximum.is<Value::Void>()) maximum = self;

    // ensure our values are now numerics
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, minimum);
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, maximum);

    // get the underlying left/right clamp values
    Number::Underlying left = minimum.as<Number::Tagged>();
    Number::Underlying right = maximum.as<Number::Tagged>();

    // finally handle our clamping as necessary
    return Number::Tagged(std::clamp(self.value(), left, right));
}

TALOS_MM_BUILTIN_FIELD(Number::Tagged, is_nan, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args.self());
    return Value::Boolean(std::isnan(args.self<Number::Tagged>().value()));
}

TALOS_MM_BUILTIN_FIELD(Number::Tagged, is_fin, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args.self());
    return Value::Boolean(std::isfinite(args.self<Number::Tagged>().value()));
}

TALOS_MM_BUILTIN_FIELD(Number::Tagged, is_inf, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args.self());
    return Value::Boolean(std::isinf(args.self<Number::Tagged>().value()));
}

TALOS_MM_BUILTIN_FIELD(Number::Tagged, to_precision, isolate, args) {
    return m_stringify(isolate, args, "to_precision");
}

TALOS_MM_BUILTIN_FIELD(Number::Tagged, to_scientific, isolate, args) {
    return m_stringify(isolate, args, "to_scientific");
}

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(Number::Tagged)::m_attributes(const Number::Tagged&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}

TALOS_MM_BUILTIN_FIELD(Number::Tagged, m_stringify, isolate, args, const $::String::View& method) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args.self());

    auto digits = args.at(0, Number::Tagged(0));  // fraction
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, digits);

    // should be able to resolve our fraction and value
    Number::Underlying value = args.self<Number::Tagged>();
    Number::Underlying fraction = digits.as<Number::Tagged>();

    // fail if the fraction is outside our expected bounds
    auto exceeds = fraction < 0 || fraction > Number::Limits::FRACTION;
    if (exceeds) return isolate->panic(6000600, fmt::format("Number.{0}", method));

    // format our output as necessary now
    auto format = fmt::runtime(method.ends_with("precision") ? "{0:.{1}F}" : "{0:.{1}G}");
    return String::Dynamic(isolate, fmt::format(format, value, static_cast<size_t>(fraction)));
}

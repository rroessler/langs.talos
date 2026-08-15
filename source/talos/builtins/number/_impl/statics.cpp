/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/number/_defines/statics.def"

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Static::parse(Isolate *isolate, const Args &args) {
  // ensure the total incoming arguments now
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args[0]);

  // pull out the necessary properties now
  auto input = args.at<String::Any>(0);
  auto radix = args.at(1, Value::Void());

  // attempt via a variety of options
  try {
    // if we have no-radix given (eg: undefined base), then revert to float
    if (radix.is<Value::Void>()) return Number::Tagged(std::stod(input.data()));

    // otherwise ensure we have a valid radix incoming
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, radix);

    // pull out the radix value to be used (eg: as a base)
    Number::Floating base = radix.as<Number::Tagged>();

    // and attempt conversion now using integral parsing
    return Number::Tagged(std::stoll(input.data(), nullptr, base));
  }

  // otherwise default exceptions to be "NAN"
  catch (...) {
    return Number::Invalid;
  }
}

//  PRIVATE METHODS  //

Talos::Value::Any
Talos::Builtins::Wrapper<Talos::Number::Tagged>::m_globals(Isolate *isolate, const Object::Class &self) {
#define TALOS_XX_STATICS_DEFINE(N, ...)                                                \
  self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/number/_defines/statics.def"

  // and return the resulting instance
  return self;
}

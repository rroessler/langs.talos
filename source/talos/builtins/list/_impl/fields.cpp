/// Talos Modules
#include "talos/member/storage.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"
#include "talos/builtins/_inline/defines.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_FIELDS(Iterable::List) {
#include "talos/builtins/list/_defines/fields.def"
};
#undef TALOS_XX_FIELDS_DEFINE

//  PROPERTIES  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) { #N, Field::N },
TALOS_BUILTIN_STORAGE(Iterable::List) = Talos::Member::Storage(name(), {
#include "talos/builtins/list/_defines/fields.def"
                                                                       });
#undef TALOS_XX_FIELDS_DEFINE

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_FIELD(Iterable::List, size, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());
    return Number::Tagged(args.self<Iterable::List>().size());
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, empty, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());
    return Value::Boolean(args.self<Iterable::List>().empty());
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, front, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());
    auto self = args.self<Iterable::List>();  // get the list to resolve
    return self.empty() ? isolate->panic(6000504, "front") : self.front();
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, back, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());
    auto self = args.self<Iterable::List>();  // get the list to resolve
    return self.empty() ? isolate->panic(6000504, "back") : self.back();
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, get, isolate, args) {
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

    // pull out our necessary items now
    auto self = args.self<Iterable::List>();
    auto numeric = args.at<Number::Tagged>(0);

    // attempt resolving a suitable index value now
    auto index = static_cast<int64_t>(numeric);
    auto size = static_cast<int64_t>(self.size());

    // attempt updating the index if negative at all
    if (index < 0) index += size;

    // fail if the index is out of the available bounds
    TALOS_MM_ASSERT_INDEX(isolate, size, index);

    // attempt resolving the necessary value now
    return self.get(index);
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, set, isolate, args) {
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 2);
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

    // pull out our necessary items now
    auto self = args.self<Iterable::List>();
    auto numeric = args.at<Number::Tagged>(0);

    // attempt resolving a suitable index value now
    auto index = static_cast<int64_t>(numeric);
    auto size = static_cast<int64_t>(self.size());

    // attempt updating the index if negative at all
    if (index < 0) index += size;

    // fail if the index is out of the available bounds
    TALOS_MM_ASSERT_INDEX(isolate, size, index);

    // attempt resolving the necessary value now
    return self.set(index, args.at(1));
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, map, isolate, args) {
    // ensure some conditions about the list
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[0]);

    // pull out our details now for handling
    auto values = args.self<Iterable::List>().span();
    auto callback = args.at<Function::Dynamic>(0);

    // prepare the outgoing arguments to be used
    auto passthrough = std::vector<Value::Any>(2);

    // prepare the filtered view of values now
    auto mapped = std::vector<Value::Any>(values.size());

    // iterate over the available values now
    for (size_t ii = 0; ii < values.size(); ++ii) {
        // prepare the outgoing passthrough arguments now
        passthrough[0] = values[ii], passthrough[1] = Number::Tagged(ii);
        auto result = isolate->invoke(callback, std::span(passthrough));

        // if the result failed, then pass onwards
        if (!result.traits().okay()) return result;
        else mapped[ii] = result;  // valid mapping
    }

    // construct the filtered list now
    return isolate->create<Iterable::List>(mapped);
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, fold, isolate, args) {
    // ensure some conditions about the list
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 2);
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[1]);

    // pull out our details now for handling
    auto result = args.at<Value::Any>(0);
    auto callback = args.at<Function::Dynamic>(1);
    auto self = args.self<Iterable::List>();

    // prepare the arguments to be passed on
    std::vector<Value::Any> passthrough = { result, Value::Void() };

    // iterate over the available values now
    for (const auto& value : self.span()) {
        passthrough[0] = result, passthrough[1] = value;
        result = isolate->invoke(callback, { passthrough });
        if (!result.traits().okay()) return result;  // exit
    }

    // construct the filtered list now
    return result;
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, erase, isolate, args) {
    // ensure some conditions about the function call
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

    // if no arguments are given, then clear the list
    if (args.empty()) return isolate->create<Iterable::List>();

    // pull out the incoming list now
    auto self = args.self<Iterable::List>();
    auto size = static_cast<int64_t>(self.size());

    // otherwise attempt pulling out our sections to be erased
    auto initial = args.at(0, Value::Void());
    auto secondary = args.at(1, Value::Void());

    // update our values with the correct details now
    if (initial.is<Value::Void>()) initial = Number::Tagged(0);
    if (secondary.is<Value::Void>()) secondary = Number::Tagged(-1);

    // prepare our starting and ending points now
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, initial);
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, secondary);

    // cast the incoming values now
    Number::Integral start = initial.as<Number::Tagged>();
    Number::Integral end = secondary.as<Number::Tagged>();

    // if the arguments are less than zero
    if (start < 0) start += size;
    if (end < 0) end += size;

    // validate the incoming values now
    TALOS_MM_ASSERT_INDEX(isolate, size, start);
    TALOS_MM_ASSERT_INDEX(isolate, size, end);

    // ignore if the start is equivalent to the end
    if (start == end) return isolate->create<Iterable::List>();

    // otherwise swap our values to ensure correct
    else if (start > end) std::swap(start, end);

    // attempt removing this section now
    auto values = std::vector(self.values());

    // erase the necessary values now
    values.erase(values.begin() + start, values.begin() + end + 1);

    // and finally construct the resulting list now
    return isolate->create<Iterable::List>(values);
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, slice, isolate, args) {
    // ensure some conditions about the function call
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

    // if no arguments are given, then clear the list
    if (args.empty()) return isolate->create<Iterable::List>();

    // pull out the incoming list now
    auto self = args.self<Iterable::List>();
    auto size = static_cast<int64_t>(self.size());

    // otherwise attempt pulling out our sections to be erased
    auto initial = args.at(0, Value::Void());
    auto secondary = args.at(1, Value::Void());

    // update our values with the correct details now
    if (initial.is<Value::Void>()) initial = Number::Tagged(0);
    if (secondary.is<Value::Void>()) secondary = Number::Tagged(-1);

    // prepare our starting and ending points now
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, initial);
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, secondary);

    // cast the incoming values now
    Number::Integral start = initial.as<Number::Tagged>();
    Number::Integral end = secondary.as<Number::Tagged>();

    // if the arguments are less than zero
    if (start < 0) start += size;
    if (end < 0) end += size;

    // validate the incoming values now
    TALOS_MM_ASSERT_INDEX(isolate, size, start);
    TALOS_MM_ASSERT_INDEX(isolate, size, end);

    // ignore if the start is equivalent to the end
    if (start == end) return isolate->create<Iterable::List>();

    // otherwise swap our values to ensure correct
    else if (start > end) std::swap(start, end);

    // and finally construct the resulting slice now
    return isolate->create<Iterable::List>(self.slice(start, end - start + 1));
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, filter, isolate, args) {
    // ensure some conditions about the list
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

    // pull out the incoming values to be assessed
    auto values = args.self<Iterable::List>().span();

    // filter by truthiness when given no arguments
    if (args.empty()) {
        static constexpr auto predicate = [](const Value::Any& value) { return value.truthiness(); };
        return isolate->create<Iterable::List>($::Ranges::To($::Filter(values, predicate)));  // view
    }

    // otherwise pull out the incoming callback as necessary
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[0]);
    auto callback = args.at<Function::Dynamic>(0);  // resolve

    // prepare the filtered view of values now
    auto filtered = std::vector<Value::Any>();
    filtered.reserve(values.size());  // max size

    // iterate over the available values now
    for (size_t ii = 0; ii < values.size(); ++ii) {
        auto span = values.subspan(ii, 1);
        auto result = isolate->invoke(callback, span);
        if (!result.traits().okay()) return result;
        else if (!result.truthiness()) continue;
        else filtered.emplace_back(span.front());
    }

    // construct the filtered list now
    return isolate->create<Iterable::List>(filtered);
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, reverse, isolate, args) {
    // ensure some conditions about the list
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

    // prepare the values to be reversed now
    auto self = args.self<Iterable::List>();
    auto reversed = self.values() | std::views::reverse;

    // and construct the resulting array now
    return isolate->create<Iterable::List>($::Ranges::To(reversed));
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, push_front, isolate, args) {
    // ensure some conditions about the list
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

    // pull out the necessary arguments
    auto& values = args.self<Iterable::List>().values();

    // attempt pushing the arguments to the front
    $::Ranges::Prepend(values, args.span());

    // return the resulting size of the list now
    return Number::Tagged(values.size());
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, push_back, isolate, args) {
    // ensure some conditions about the list
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

    // pull out the necessary arguments
    auto& values = args.self<Iterable::List>().values();

    // attempt pushing the arguments to the end
    $::Ranges::Append(values, args.span());

    // return the resulting size of the list now
    return Number::Tagged(values.size());
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, pop_front, isolate, args) {
    // ensure some conditions about the list
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

    // pull out the necessary arguments
    auto& values = args.self<Iterable::List>().values();

    // if the list is empty, the throw an exception
    if (values.empty()) return isolate->panic(6000505);

    // prepare the front-most item to be retrieved
    auto front = values.front();

    // erase and return now as necessary
    return values.erase(values.begin()), front;
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, pop_back, isolate, args) {
    // ensure some conditions about the list
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

    // pull out the necessary arguments
    auto values = args.self<Iterable::List>().values();

    // if the list is empty, the throw an exception
    if (values.empty()) return isolate->panic(6000505);

    // prepare the front-most item to be retrieved
    auto back = values.back();

    // erase and return now as necessary
    return values.pop_back(), back;
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, first_index_of, isolate, args) {
    // ensure some conditions about the list
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

    // pull out the incoming values now
    auto self = args.self<Iterable::List>();

    // prepare our search items now
    auto needle = args[0];
    auto haystack = self.span();

    // attempt finding the needle in the haystack
    auto iter = std::ranges::find(haystack, needle);

    // should be able to safely resolve the index of the value
    if (iter == haystack.end()) return Number::Tagged(-1);
    return Number::Tagged(std::distance(haystack.begin(), iter));
}

TALOS_MM_BUILTIN_FIELD(Iterable::List, last_index_of, isolate, args) {
    // ensure some conditions about the list
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

    // pull out the incoming values now
    auto self = args.self<Iterable::List>();

    // prepare our search items now
    auto needle = args[0];
    auto haystack = self.span();

    // attempt finding the needle in the haystack
    auto iter = std::ranges::find(haystack | std::views::reverse, needle);

    // should be able to safely resolve the index of the value
    if (iter == haystack.rend()) return Number::Tagged(-1);
    return Number::Tagged(std::distance(iter, haystack.rend()));
}

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(Iterable::List)::m_attributes(const Iterable::List&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}

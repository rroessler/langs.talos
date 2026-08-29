/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/list/_defines/fields.def"

//  PROPERTIES  //

static auto s_members = Talos::Builtins::Storage<Talos::Iterable::List>({
#define TALOS_XX_FIELDS_DEFINE(N, ...) {#N, Talos::Builtins::Field::N},
#include "talos/builtins/list/_defines/fields.def"
});

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Field::size(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());
  return Number::Tagged(args.self<Iterable::List>().size());
}

Talos::Value::Any Talos::Builtins::Field::empty(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());
  return Value::Boolean(args.self<Iterable::List>().empty());
}

Talos::Value::Any Talos::Builtins::Field::front(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());
  auto self = args.self<Iterable::List>(); // get the list to resolve
  return self.empty() ? isolate->panic(6000504, "front") : self.front();
}

Talos::Value::Any Talos::Builtins::Field::back(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());
  auto self = args.self<Iterable::List>(); // get the list to resolve
  return self.empty() ? isolate->panic(6000504, "back") : self.back();
}

Talos::Value::Any Talos::Builtins::Field::get(Isolate *isolate, const Args &args) {
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

Talos::Value::Any Talos::Builtins::Field::set(Isolate *isolate, const Args &args) {
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

Talos::Value::Any Talos::Builtins::Field::map(Isolate *isolate, const Args &args) {
  // ensure some conditions about the list
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, Function::Any, args[0]);
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

  // pull out our details now for handling
  auto values = args.self<Iterable::List>().span();
  auto callback = args.at<Function::Any>(0);

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
    if (!result.pointer().okay()) return result;
    else mapped[ii] = result; // valid mapping
  }

  // construct the filtered list now
  return isolate->create<Iterable::List>(mapped);
}

Talos::Value::Any Talos::Builtins::Field::fold(Isolate *isolate, const Args &args) {
  // ensure some conditions about the list
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 2);
  TALOS_MM_ASSERT_TYPEOF(isolate, Function::Any, args[1]);
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

  // pull out our details now for handling
  auto result = args.at<Value::Any>(0);
  auto callback = args.at<Function::Any>(1);
  auto self = args.self<Iterable::List>();

  // prepare the arguments to be passed on
  std::vector<Value::Any> passthrough = {result, Value::Void()};

  // iterate over the available values now
  for (const auto &value : self.span()) {
    passthrough[0] = result, passthrough[1] = value;
    result = isolate->invoke(callback, {passthrough});
    if (!result.pointer().okay()) return result;
  }

  // construct the filtered list now
  return result;
}

Talos::Value::Any Talos::Builtins::Field::clear(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());
  return args.self<Iterable::List>().clear(); // erase now
}

Talos::Value::Any Talos::Builtins::Field::drop(Isolate *isolate, const Args &args) {
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

  // and finally drop the resulting value
  auto dropped = self.get(index);
  auto &values = self.values();
  values.erase(values.begin() + index);
  return dropped; // return the value
}

Talos::Value::Any Talos::Builtins::Field::erase(Isolate *isolate, const Args &args) {
  // ensure some conditions about the function call
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 2);
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

  // pull out the incoming list now
  auto self = args.self<Iterable::List>();
  auto size = static_cast<int64_t>(self.size());

  // prepare our starting and ending points now
  TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);
  TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[1]);

  // cast the incoming values now
  Number::Integral start = args.at<Number::Tagged>(0);
  Number::Integral end = args.at<Number::Tagged>(1);

  // if the arguments are less than zero
  if (start < 0) start += size;
  if (end < 0) end += size;

  // validate the incoming values now
  TALOS_MM_ASSERT_INDEX(isolate, size, start);

  // ignore if the start is equivalent to the end
  if (start == end) return self;

  // otherwise swap our values to ensure correct
  else if (start > end) std::swap(start, end);

  // ensure the ending value can only be the maximum
  if (end > size) end = size;

  // attempt removing this section now
  auto &values = self.values();

  // handle removing our range of values as required
  values.erase(values.begin() + start, values.begin() + end);

  // and finally construct the resulting list now
  return self;
}

Talos::Value::Any Talos::Builtins::Field::slice(Isolate *isolate, const Args &args) {
  // ensure some conditions about the function call
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

  // pull out the incoming list now
  auto self = args.self<Iterable::List>();
  auto size = static_cast<int64_t>(self.size());

  // if no arguments are given, then clear the list
  if (args.empty()) return isolate->create<Iterable::List>(self.span());

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

Talos::Value::Any Talos::Builtins::Field::filter(Isolate *isolate, const Args &args) {
  // ensure some conditions about the list
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

  // pull out the incoming values to be assessed
  auto values = args.self<Iterable::List>().span();

  // filter by truthiness when given no arguments
  if (args.empty()) {
    static constexpr auto predicate = [](const Value::Any &value) { return value.truthiness(); };
    return isolate->create<Iterable::List>($::Ranges::To($::Ranges::Filter(values, predicate)));
  }

  // otherwise pull out the incoming callback as necessary
  TALOS_MM_ASSERT_TYPEOF(isolate, Function::Any, args[0]);
  auto callback = args.at<Function::Any>(0); // resolve

  // prepare the filtered view of values now
  auto filtered = std::vector<Value::Any>();
  filtered.reserve(values.size()); // max size

  // iterate over the available values now
  for (size_t ii = 0; ii < values.size(); ++ii) {
    auto span = values.subspan(ii, 1); // to invoke
    auto result = isolate->invoke(callback, span);
    if (!result.pointer().okay()) return result;
    else if (!result.truthiness()) continue;
    else filtered.emplace_back(span.front());
  }

  // construct the filtered list now
  return isolate->create<Iterable::List>(filtered);
}

Talos::Value::Any Talos::Builtins::Field::reverse(Isolate *isolate, const Args &args) {
  // ensure some conditions about the list
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

  // prepare the values to be reversed now
  auto self = args.self<Iterable::List>();
  auto reversed = self.values() | std::views::reverse;

  // and construct the resulting array now
  return isolate->create<Iterable::List>($::Ranges::To(reversed));
}

Talos::Value::Any Talos::Builtins::Field::push_front(Isolate *isolate, const Args &args) {
  // ensure some conditions about the list
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

  // pull out the necessary arguments
  auto &values = args.self<Iterable::List>().values();

  // attempt pushing the arguments to the front
  $::Ranges::Prepend(values, args.span());

  // return the resulting size of the list now
  return Number::Tagged(values.size());
}

Talos::Value::Any Talos::Builtins::Field::push_back(Isolate *isolate, const Args &args) {
  // ensure some conditions about the list
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

  // pull out the necessary arguments
  auto &values = args.self<Iterable::List>().values();

  // attempt pushing the arguments to the end
  $::Ranges::Append(values, args.span());

  // return the resulting size of the list now
  return Number::Tagged(values.size());
}

Talos::Value::Any Talos::Builtins::Field::pop_front(Isolate *isolate, const Args &args) {
  // ensure some conditions about the list
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

  // pull out the necessary arguments
  auto &values = args.self<Iterable::List>().values();

  // if the list is empty, the throw an exception
  if (values.empty()) return isolate->panic(6000505);

  // prepare the front-most item to be retrieved
  auto front = values.front();

  // erase and return now as necessary
  return values.erase(values.begin()), front;
}

Talos::Value::Any Talos::Builtins::Field::pop_back(Isolate *isolate, const Args &args) {
  // ensure some conditions about the list
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args.self());

  // pull out the necessary arguments
  auto &values = args.self<Iterable::List>().values();

  // if the list is empty, the throw an exception
  if (values.empty()) return isolate->panic(6000505);

  // prepare the front-most item to be retrieved
  auto back = values.back();

  // erase and return now as necessary
  return values.pop_back(), back;
}

Talos::Value::Any Talos::Builtins::Field::first_index_of(Isolate *isolate, const Args &args) {
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

Talos::Value::Any Talos::Builtins::Field::last_index_of(Isolate *isolate, const Args &args) {
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
  return Number::Tagged(std::distance(iter, haystack.rend()) - 1);
}

//  PRIVATE METHODS  //

Talos::Member::View
Talos::Builtins::Wrapper<Talos::Iterable::List>::m_attribute(const Iterable::List &, const Value::Symbol &symbol) {
  return s_members.retrieve(symbol);
}

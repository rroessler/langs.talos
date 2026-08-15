/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/string/_defines/fields.def"

//  PROPERTIES  //

static auto s_members = Talos::Builtins::Storage<Talos::String::Any>({
#define TALOS_XX_FIELDS_DEFINE(N, ...) {#N, Talos::Builtins::Field::N},
#include "talos/builtins/string/_defines/fields.def"
});

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Field::symbol(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());
  return args.self<String::Any>().symbol(); // get symbol
}

Talos::Value::Any Talos::Builtins::Field::size(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());
  return Number::Tagged(args.self<String::Any>().size());
}

Talos::Value::Any Talos::Builtins::Field::bytes(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());
  return Number::Tagged(args.self<String::Any>().bytes());
}

Talos::Value::Any Talos::Builtins::Field::empty(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());
  return Number::Tagged(args.self<String::Any>().size() == 0);
}

Talos::Value::Any Talos::Builtins::Field::at(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // prepare the underlying self and numeric
  auto self = args.self<String::Any>();
  auto numeric = args.at<Number::Tagged>(0);

  // prepare the incoming index and size values
  auto index = static_cast<int64_t>(numeric);
  auto size = static_cast<int64_t>(self.size());

  // attempt updating the index if negative at all
  if (index < 0) index += size;

  // fail if the index is out of the available bounds
  TALOS_MM_ASSERT_INDEX(isolate, size, index);

  // attempt resolving the necessary rune value
  return String::Small(self.rune(index));
}

Talos::Value::Any Talos::Builtins::Field::slice(Isolate *isolate, const Args &args) {
  // prepare the underlying assertions
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // get the value to be sliced
  auto self = args.self<String::Any>();
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
  if (start == end) return String::Any();

  // otherwise swap our values to ensure correct
  else if (start > end) std::swap(start, end);

  // resolve the base indices from the runes
  start = self.offset(start), end = self.offset(end);

  // and finally construct the resulting slice now
  return String::Any(isolate, self.view().substr(start, end - start + 1));
}

Talos::Value::Any Talos::Builtins::Field::compare(Isolate *isolate, const Args &args) {
  // prepare the underlying assertions
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args[0]);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // pull out our items in question now
  auto needle = args.at<String::Any>(0);
  auto haystack = args.self<String::Any>();

  // return the resulting comparison value now
  return Number::Tagged(haystack.compare(needle));
}

Talos::Value::Any Talos::Builtins::Field::contains(Isolate *isolate, const Args &args) {
  // prepare the underlying assertions
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args[0]);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // pull out our items in question now
  auto needle = args.at<String::Any>(0);
  auto haystack = args.self<String::Any>();

  // check if the haystack contains the needle
  return Value::Boolean(haystack.view().contains(needle.view()));
}

Talos::Value::Any Talos::Builtins::Field::starts_with(Isolate *isolate, const Args &args) {
  // prepare the underlying assertions
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args[0]);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // pull out our items in question now
  auto needle = args.at<String::Any>(0);
  auto haystack = args.self<String::Any>();

  // check if the haystack contains the needle
  return Value::Boolean(haystack.view().starts_with(needle.view()));
}

Talos::Value::Any Talos::Builtins::Field::ends_with(Isolate *isolate, const Args &args) {
  // prepare the underlying assertions
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args[0]);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // pull out our items in question now
  auto needle = args.at<String::Any>(0);
  auto haystack = args.self<String::Any>();

  // check if the haystack contains the needle
  return Value::Boolean(haystack.view().ends_with(needle.view()));
}

Talos::Value::Any Talos::Builtins::Field::to_upper(Isolate *isolate, const Args &args) {
  // ensure some incoming conditions now
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // pull out the incoming string to be modified
  auto self = args.self<String::Any>();

  // prepare a wide-string to conduct the conversion
  auto buffer = $::String::Buffer();

  // emplace each of the incoming characters with its equivalent
  for (size_t uu = 0; uu < self.size(); ++uu) {
    auto rune = self.rune(uu);
    rune = ::towupper(rune);
    buffer += $::Encoding::UTF8::from(rune);
  }

  // return the resulting upper-case result now
  return String::Any(isolate, buffer);
}

Talos::Value::Any Talos::Builtins::Field::to_lower(Isolate *isolate, const Args &args) {
  // ensure some incoming conditions now
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // pull out the incoming string to be modified
  auto self = args.self<String::Any>();

  // prepare a wide-string to conduct the conversion
  auto buffer = $::String::Buffer();

  // emplace each of the incoming characters with its equivalent
  for (size_t uu = 0; uu < self.size(); ++uu) {
    auto rune = self.rune(uu);
    rune = ::towlower(rune);
    buffer += $::Encoding::UTF8::from(rune);
  }

  // return the resulting upper-case result now
  return String::Any(isolate, buffer);
}

Talos::Value::Any Talos::Builtins::Field::trim_both(Isolate *isolate, const Args &args) {
  // ensure some incoming conditions now
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // pull out the incoming string to be modified
  auto self = args.self<String::Any>();

  // can safely trim as necessary
  return String::Any(isolate, $::Trim::both(self.view()));
}

Talos::Value::Any Talos::Builtins::Field::trim_leading(Isolate *isolate, const Args &args) {
  // ensure some incoming conditions now
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // pull out the incoming string to be modified
  auto self = args.self<String::Any>();

  // can safely trim as necessary
  return String::Any(isolate, $::Trim::leading(self.view()));
}

Talos::Value::Any Talos::Builtins::Field::trim_trailing(Isolate *isolate, const Args &args) {
  // ensure some incoming conditions now
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // pull out the incoming string to be modified
  auto self = args.self<String::Any>();

  // can safely trim as necessary
  return String::Any(isolate, $::Trim::trailing(self.view()));
}

Talos::Value::Any Talos::Builtins::Field::pad_leading(Isolate *isolate, const Args &args) {
  // ensure some incoming conditions now
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // pull out all the base values to be used
  auto self = args.self<String::Any>();
  auto maximum = static_cast<int64_t>(self.size());
  auto size = static_cast<int64_t>(args.at<Number::Tagged>(0));

  // resolve the padding string to be used
  String::Any padding = String::Small(" ");

  // we need to ensure we have the correct sizing
  if (args.size() > 1 && !args[1].is<Value::Void>()) {
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args[1]);
    padding = args.at<String::Any>(1); // and resolve
  }

  // if the size does not exceed the current maximum, then copy instead
  if (size <= maximum) return String::Any(isolate, self.view());

  // prepare a buffer to be used now for padding
  auto buffer = $::String::Buffer();

  // whilst we have remaining characters, we can print
  for (auto remaining = size - maximum; remaining > 0;) {
    for (size_t uu = 0; uu < padding.size(); ++uu) {
      buffer += $::Encoding::UTF8::from(padding.rune(uu));
      if (--remaining <= 0) break; // break when necessary
    }
  }

  // and prepend the buffer now
  return String::Any(isolate, buffer + $::String::Buffer(self.view()));
}

Talos::Value::Any Talos::Builtins::Field::pad_trailing(Isolate *isolate, const Args &args) {
  // ensure some incoming conditions now
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args.self());

  // pull out all the base values to be used
  auto self = args.self<String::Any>();
  auto maximum = static_cast<int64_t>(self.size());
  auto size = static_cast<int64_t>(args.at<Number::Tagged>(0));

  // resolve the padding string to be used
  String::Any padding = String::Small(" ");

  // we need to ensure we have the correct sizing
  if (args.size() > 1 && !args[1].is<Value::Void>()) {
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args[1]);
    padding = args.at<String::Any>(1); // and resolve
  }

  // if the size does not exceed the current maximum, then copy instead
  if (size <= maximum) return String::Any(isolate, self.view());

  // prepare a buffer to be used now for padding
  auto buffer = $::String::Buffer();

  // whilst we have remaining characters, we can print
  for (auto remaining = size - maximum; remaining > 0;) {
    for (size_t uu = 0; uu < padding.size(); ++uu) {
      buffer += $::Encoding::UTF8::from(padding.rune(uu));
      if (--remaining <= 0) break; // break when necessary
    }
  }

  // and prepend the buffer now
  return String::Any(isolate, $::String::Buffer(self.view()) + buffer);
}

Talos::Value::Any Talos::Builtins::Field::fmt(Isolate *isolate, const Args &args) {
  // get the self instance to be used
  auto self = args.self();

  // ensure we validate the incoming details
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, self);

  // return immediately if there are no arguments given
  if (args.empty()) return self;

  // and attempt writing our details now
  return String::Literal::style(isolate, self.as<String::Any>(), args);
}

//  PRIVATE METHODS  //

Talos::Member::View
Talos::Builtins::Wrapper<Talos::String::Any>::m_attribute(const String::Any &, const Value::Symbol &symbol) {
  return s_members.retrieve(symbol);
}

/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/boolean/_defines/statics.def"

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Static::from(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  return Value::Boolean(args.at(0).truthiness());
}

Talos::Value::Any Talos::Builtins::Static::parse(Isolate *isolate, const Args &args) {
  // ensure the incoming arguments are valid
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, String::Any, args[0]);

  // attempt resolving a suitable source and case-sensitivity
  auto input = args.at<String::Any>(0);
  auto sensitive = args.at(1, Value::False).truthiness();

  // the source requires a backing from the base input string
  auto source = input.view();

// define a specialized macro for exiting
#define MM_PARSE_FAILURE             \
  if (sensitive) goto _PARSE_FAILURE

// define a specialized macros for fast-delegation
#define MM_PARSE_CLOSE(...) }
#define MM_PARSE_OPEN(N, L, U, ...) \
  switch (source[N]) {              \
  case L: MM_PARSE_FAILURE;         \
  case U: __VA_ARGS__

#define XX_TRUE_CHAIN(X) \
  X(1, 'r', 'R')         \
  X(2, 'u', 'U')         \
  X(3, 'e', 'E')

#define XX_FALSE_CHAIN(X) \
  X(1, 'a', 'A')          \
  X(2, 'l', 'L')          \
  X(3, 's', 'S')          \
  X(4, 'e', 'E')

  // stop early if the sizing is invalid
  if (source.size() < 4 || source.size() > 5) goto _PARSE_FAILURE;

  // attempt handling with exactness now
  switch (source[0]) {
  case 't': MM_PARSE_FAILURE;
  case 'T':
    XX_TRUE_CHAIN(MM_PARSE_OPEN)
    return Value::True;
    XX_TRUE_CHAIN(MM_PARSE_CLOSE);

  case 'f': MM_PARSE_FAILURE;
  case 'F':
    XX_FALSE_CHAIN(MM_PARSE_OPEN)
    return Value::False;
    XX_FALSE_CHAIN(MM_PARSE_CLOSE);

  // otherwise break for failures
  default: break;
  }

#undef XX_TRUE_CHAIN
#undef XX_FALSE_CHAIN

#undef MM_PARSE_OPEN
#undef MM_PARSE_CLOSE
#undef MM_PARSE_FAILURE

_PARSE_FAILURE:
  return isolate->panic(6000404, Inspect<Value::Boolean>::name(), source);
}

//  PRIVATE METHODS  //

Talos::Value::Any
Talos::Builtins::Wrapper<Talos::Value::Boolean>::m_globals(Isolate *isolate, const Object::Class &self) {
#define TALOS_XX_STATICS_DEFINE(N, ...)                                                \
  self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/boolean/_defines/statics.def"

  // and return the resulting instance
  return self;
}

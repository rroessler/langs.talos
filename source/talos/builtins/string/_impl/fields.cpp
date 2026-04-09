/// C++ Modules
#include <cwctype>

/// Talos Modules
#include "talos/member/storage.hpp"
#include "talos/string/literal.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"
#include "talos/builtins/_inline/defines.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_FIELDS(String::Dynamic) {
#include "talos/builtins/string/_defines/fields.def"
};
#undef TALOS_XX_FIELDS_DEFINE

//  PROPERTIES  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) { #N, Field::N },
TALOS_BUILTIN_STORAGE(String::Dynamic) = Talos::Member::Storage(name(), {
#include "talos/builtins/string/_defines/fields.def"
                                                                        });
#undef TALOS_XX_FIELDS_DEFINE

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_FIELD(String::Dynamic, hash, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());
    return args.self<String::Dynamic>().symbol();  // get symbol
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, size, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());
    return Number::Tagged(args.self<String::Dynamic>().size());
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, bytes, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());
    return Number::Tagged(args.self<String::Dynamic>().bytes());
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, empty, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());
    return Number::Tagged(args.self<String::Dynamic>().size() == 0);
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, at, isolate, args) {
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // prepare the underlying self and numeric
    auto self = args.self<String::Dynamic>();
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

TALOS_MM_BUILTIN_FIELD(String::Dynamic, slice, isolate, args) {
    // prepare the underlying assertions
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // get the value to be sliced
    auto self = args.self<String::Dynamic>();
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
    if (start == end) return String::Dynamic();

    // otherwise swap our values to ensure correct
    else if (start > end) std::swap(start, end);

    // resolve the base indices from the runes
    start = self.offset(start), end = self.offset(end);

    // and finally construct the resulting slice now
    return String::Dynamic(isolate, self.view().substr(start, end - start + 1));
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, compare, isolate, args) {
    // prepare the underlying assertions
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // pull out our items in question now
    auto needle = args.at<String::Dynamic>(0);
    auto haystack = args.self<String::Dynamic>();

    // return the resulting comparison value now
    return Number::Tagged(haystack.compare(needle));
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, contains, isolate, args) {
    // prepare the underlying assertions
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // pull out our items in question now
    auto needle = args.at<String::Dynamic>(0);
    auto haystack = args.self<String::Dynamic>();

    // check if the haystack contains the needle
    return Value::Boolean(haystack.view().contains(needle.view()));
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, starts_with, isolate, args) {
    // prepare the underlying assertions
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // pull out our items in question now
    auto needle = args.at<String::Dynamic>(0);
    auto haystack = args.self<String::Dynamic>();

    // check if the haystack contains the needle
    return Value::Boolean(haystack.view().starts_with(needle.view()));
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, ends_with, isolate, args) {
    // prepare the underlying assertions
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // pull out our items in question now
    auto needle = args.at<String::Dynamic>(0);
    auto haystack = args.self<String::Dynamic>();

    // check if the haystack contains the needle
    return Value::Boolean(haystack.view().ends_with(needle.view()));
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, to_upper, isolate, args) {
    // ensure some incoming conditions now
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // pull out the incoming string to be modified
    auto self = args.self<String::Dynamic>();

    // prepare a wide-string to conduct the conversion
    auto buffer = $::String::Buffer();

    // emplace each of the incoming characters with its equivalent
    for (size_t uu = 0; uu < self.size(); ++uu) {
        auto rune = self.rune(uu);
        rune = ::towupper(rune);
        buffer += $::Encoding::UTF8::from(rune);
    }

    // return the resulting upper-case result now
    return String::Dynamic(isolate, buffer);
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, to_lower, isolate, args) {
    // ensure some incoming conditions now
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // pull out the incoming string to be modified
    auto self = args.self<String::Dynamic>();

    // prepare a wide-string to conduct the conversion
    auto buffer = $::String::Buffer();

    // emplace each of the incoming characters with its equivalent
    for (size_t uu = 0; uu < self.size(); ++uu) {
        auto rune = self.rune(uu);
        rune = ::towlower(rune);
        buffer += $::Encoding::UTF8::from(rune);
    }

    // return the resulting upper-case result now
    return String::Dynamic(isolate, buffer);
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, trim_both, isolate, args) {
    // ensure some incoming conditions now
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // pull out the incoming string to be modified
    auto self = args.self<String::Dynamic>();

    // can safely trim as necessary
    return String::Dynamic(isolate, $::Trim::both(self.view()));
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, trim_leading, isolate, args) {
    // ensure some incoming conditions now
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // pull out the incoming string to be modified
    auto self = args.self<String::Dynamic>();

    // can safely trim as necessary
    return String::Dynamic(isolate, $::Trim::leading(self.view()));
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, trim_trailing, isolate, args) {
    // ensure some incoming conditions now
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // pull out the incoming string to be modified
    auto self = args.self<String::Dynamic>();

    // can safely trim as necessary
    return String::Dynamic(isolate, $::Trim::trailing(self.view()));
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, pad_leading, isolate, args) {
    // ensure some incoming conditions now
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // pull out all the base values to be used
    auto self = args.self<String::Dynamic>();
    auto maximum = static_cast<int64_t>(self.size());
    auto size = static_cast<int64_t>(args.at<Number::Tagged>(0));

    // resolve the padding string to be used
    String::Dynamic padding = String::Small(" ");

    // we need to ensure we have the correct sizing
    if (args.size() > 1 && !args[1].is<Value::Void>()) {
        TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[1]);
        padding = args.at<String::Dynamic>(1);  // and resolve
    }

    // if the size does not exceed the current maximum, then copy instead
    if (size <= maximum) return String::Dynamic(isolate, self.view());

    // prepare a buffer to be used now for padding
    auto buffer = $::String::Buffer();

    // whilst we have remaining characters, we can print
    for (auto remaining = size - maximum; remaining > 0;) {
        for (size_t uu = 0; uu < padding.size(); ++uu) {
            buffer += $::Encoding::UTF8::from(padding.rune(uu));
            if (--remaining <= 0) break;  // break when necessary
        }
    }

    // and prepend the buffer now
    return String::Dynamic(isolate, buffer + $::String::Buffer(self.view()));
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, pad_trailing, isolate, args) {
    // ensure some incoming conditions now
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args.self());

    // pull out all the base values to be used
    auto self = args.self<String::Dynamic>();
    auto maximum = static_cast<int64_t>(self.size());
    auto size = static_cast<int64_t>(args.at<Number::Tagged>(0));

    // resolve the padding string to be used
    String::Dynamic padding = String::Small(" ");

    // we need to ensure we have the correct sizing
    if (args.size() > 1 && !args[1].is<Value::Void>()) {
        TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[1]);
        padding = args.at<String::Dynamic>(1);  // and resolve
    }

    // if the size does not exceed the current maximum, then copy instead
    if (size <= maximum) return String::Dynamic(isolate, self.view());

    // prepare a buffer to be used now for padding
    auto buffer = $::String::Buffer();

    // whilst we have remaining characters, we can print
    for (auto remaining = size - maximum; remaining > 0;) {
        for (size_t uu = 0; uu < padding.size(); ++uu) {
            buffer += $::Encoding::UTF8::from(padding.rune(uu));
            if (--remaining <= 0) break;  // break when necessary
        }
    }

    // and prepend the buffer now
    return String::Dynamic(isolate, $::String::Buffer(self.view()) + buffer);
}

TALOS_MM_BUILTIN_FIELD(String::Dynamic, fmt, isolate, args) {
    // get the self instance to be used
    auto self = args.self();

    // ensure we validate the incoming details
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, self);

    // return immediately if there are no arguments given
    if (args.empty()) return self;

    // and attempt writing our details now
    return String::Literal::style(isolate, self.as<String::Dynamic>(), args);
}

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(String::Dynamic)::m_attributes(const String::Dynamic&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}

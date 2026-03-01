#ifndef _FORGE_STRING_DYNAMIC_HPP
#define _FORGE_STRING_DYNAMIC_HPP

/// Forge Modules
#include "forge/string/large.hpp"
#include "forge/string/small.hpp"

namespace Forge::String {

    /// @brief Dynamic String Pointer.
    struct Dynamic : public Value::Any {
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted string instance.
        constexpr Dynamic() : Value::Any(Small()) {}

        /**
         * @brief Handles conversion from derived strings.
         * @param target                    Target to encapsulate.
         */
        constexpr Dynamic(Small target) : Value::Any(target) {}
        constexpr Dynamic(Large target) : Value::Any(target) {}

        /**
         * @brief Constructs any string.
         * @param isolate                   Runtime isolate.
         * @param intern                    Interned string.
         */
        explicit Dynamic(Runtime::Isolate* isolate, const Intern& intern);

        /**
         * @brief Constructs any string.
         * @param isolate                   Runtime isolate.
         * @param value                     String value to bind.
         */
        explicit Dynamic(Runtime::Isolate* isolate, const $::String::View& value);

        /**
         * @brief Constructs formatted strings.
         * @param isolate                   Runtime isolate.
         * @param fmt                       String format.
         * @param args                      Format arguments.
         */
        template <class... As>
        explicit Dynamic(Runtime::Isolate* isolate, const $::String::View& fmt, As&&... args) :
            Dynamic(isolate, fmt::format(fmt::runtime(fmt), std::forward<As>(args)...)) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the size of a string (code-points).
        inline constexpr size_t size() const noexcept {
            return Small::m_is(m_pointer) ? Small::m_size(m_pointer) : m_as<Large>().size();
        }

        /// @brief Gets the size of a string (bytes).
        inline constexpr size_t bytes() const noexcept {
            return Small::m_is(m_pointer) ? Small::m_bytes(m_pointer) : m_as<Large>().bytes();
        }

        /// @brief Gets the associated data to be used.
        inline constexpr const char* data() const noexcept {
            return Small::m_is(m_pointer) ? Small::m_decode(this) : m_as<Large>().data();
        }

        /// @brief Gets the view of the string.
        inline constexpr $::String::View view() const noexcept { return { data(), bytes() }; }

        /// @brief Gets the symbol value of the string.
        inline constexpr Value::Symbol symbol() const {
            if (Large::m_is(m_pointer)) return m_as<Large>().symbol();  // faster
            return Value::Symbol(Small::m_decode(this), Small::m_bytes(m_pointer));
        }

        /**
         * @brief Gets the offset from a given index.
         * @param unit                  Unit index to resolve.
         */
        inline constexpr size_t offset(size_t unit) const {
            // resolve with large string if necessary
            if (Large::m_is(m_pointer)) return m_as<Large>().offset(unit);

            // otherwise we want to decipher the necessary offset
            auto data = Small::m_decode(this);
            auto bytes = Small::m_bytes(m_pointer);

            // if same, then same as ASCII
            if (bytes == Small::m_size(m_pointer)) return unit;
            return $::Encoding::UTF8::offset(data, bytes, unit);
        }

        /**
         * @brief Gets the rune at a given unit.
         * @param unit                  Unit to resolve codepoint.
         */
        inline constexpr uint32_t rune(size_t unit) const {
            // resolve with large string if necessary
            if (Large::m_is(m_pointer)) return m_as<Large>().rune(unit);

            // get the current sizes to be compared
            auto data = Small::m_decode(this);
            auto bytes = Small::m_bytes(m_pointer);

            // if same, then we have ASCII only
            if (bytes == Small::m_size(m_pointer)) return static_cast<uint32_t>(data[unit]);

            // otherwise attempt resolving the incoming rune now
            return $::Encoding::UTF8::rune(data, bytes, unit);
        }

        /**
         * @brief Handles comparing to another value.
         * @param right                         Right value to compare.
         */
        inline constexpr int32_t compare(const String::Dynamic& right) const noexcept {
            return view().compare(right.view());
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles validating string pointers.
         * @param traits                        Pointer traits.
         */
        static inline constexpr bool m_is(const Pointer::Traits& traits) {
            return Small::m_is(traits) || Large::m_is(traits);
        }

        /**
         * @brief Gets the truthiness of a value.
         * @param self                          String instance.
         */
        static inline constexpr bool m_truthiness(const Dynamic& self) { return self.size() != 0; }

        /**
         * @brief Handlers yielding strings safely.
         * @param self                          String instance.
         * @param yield                         Yield callback.
         */
        static inline constexpr void m_yield(const Dynamic& self, const Globals::Each& yield) {
            if (Large::m_is(self.traits())) Large::m_yield(self.m_as<Large>(), yield);
        }

        /**
         * @brief Handles dumping the runtime value.
         * @param os                    Output stream.
         * @param self                  Value instance.
         */
        static inline void m_print($::Stream::Output& os, const Dynamic& self) { os << self.view(); }
    };

}  // namespace Forge::String

#endif

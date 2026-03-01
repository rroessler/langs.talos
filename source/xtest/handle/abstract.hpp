#ifndef _XTEST_HANDLE_ABSTRACT_HPP
#define _XTEST_HANDLE_ABSTRACT_HPP

/// XT Modules
#include "xtest/forward/handle.hpp"
#include "xtest/session/location.hpp"

namespace XT {

    /// @brief Abstract test-handle.
    struct $_ABSTRACT Handle {
        //  TYPEDEFS  //

        /// @brief Initializer-list typing.
        using Initializer = std::initializer_list<const Handle*>;

        /// @brief Handle Callback.
        using Callback = $::Functor::Unique<void(Session::Runner*)>;

        /// @brief Internal metadata.
        struct Metadata {
            bool todo = false;  // Unimplemented flag.
            bool skip = false;  // Skip request flag.

            Location location;        // Source location.
            $::String::Buffer title;  // Title descriptor.
        };

        /// @brief Benchmark Abstraction.
        template <class T, std::derived_from<Handle> B = Handle>
        class $_ABSTRACT Abstract : public B {
            //  TYPEDEFS  //

            using Handle::Callback;
            using Handle::Initializer;
            using Handle::Metadata;

           public:
            //  CONSTRUCTORS  //

            /**
             * @brief Handles constructing tests.
             * @param title                 Title of test.
             * @param location              Location to bind.
             */
            explicit Abstract(const $::String::Buffer& title, const Location& location = $::Location()) :
                B($::Ptr::Unique<Metadata>(new Metadata{ .location = location, .title = title })) {}

            //  PUBLIC METHODS  //

            inline T* todo(bool state = true) noexcept { return m_meta->todo = state, static_cast<T*>(this); }
            inline T* skip(bool state = true) noexcept { return m_meta->skip = state, static_cast<T*>(this); }
        };

       protected:
        //  PROPERTIES  //

        /// @brief Internal metadata.
        $::Ptr::Unique<Metadata> m_meta;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a test-handle.
         * @param meta                  Metadata to bind.
         */
        explicit Handle($::Ptr::Unique<Metadata>&& meta) : m_meta(std::move(meta)) {}

        /// @brief Virtual abstract destructor.
        virtual ~Handle() = default;

        //  PUBLIC METHODS  //

        /// @brief Denotes how large a test could be (eg: groups can be any-number)
        virtual inline size_t count() const { return 1; }

        /// @brief Gets the underlying meta-data.
        inline constexpr const Metadata* meta() const noexcept { return m_meta.get(); }

        /**
         * @brief Handles executing a test instance.
         * @param runner                Session runner.
         */
        virtual void execute(Session::Runner* runner) const = 0;
    };

}  // namespace XT

#endif

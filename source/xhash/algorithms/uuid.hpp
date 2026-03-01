#ifndef _XHASH_UUID_HPP
#define _XHASH_UUID_HPP

/// Vendor Modules
#include <modern-uuid/uuid.h>

namespace XH::UUID {

    //  TYPEDEFS  //

    /// @brief The hashed value of a UUID.
    using Hash = muuid::uuid;

    //  PUBLIC METHODS  //

    static inline constexpr Hash DNS() { return muuid::uuid::namespaces::dns; }
    static inline constexpr Hash URL() { return muuid::uuid::namespaces::url; }
    static inline constexpr Hash OID() { return muuid::uuid::namespaces::oid; }
    static inline constexpr Hash X500() { return muuid::uuid::namespaces::x500; }
    static inline constexpr Hash NIL() { return { "00000000-0000-0000-0000-000000000000" }; }

    static inline constexpr Hash V1() { return muuid::uuid::generate_time_based(); }
    static inline constexpr Hash V4() { return muuid::uuid::generate_random(); }
    static inline constexpr Hash V6() { return muuid::uuid::generate_reordered_time_based(); }
    static inline constexpr Hash V7() { return muuid::uuid::generate_unix_time_based(); }

    static inline constexpr Hash V3(const Hash& ns, const std::string_view& name) {
        return muuid::uuid::generate_md5(ns, name);
    }

    static inline constexpr Hash V5(const Hash& ns, const std::string_view& name) {
        return muuid::uuid::generate_sha1(ns, name);
    }

}  // namespace XH::UUID

#endif

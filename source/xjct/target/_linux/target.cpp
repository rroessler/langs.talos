/// Platform Modules
#include "xjct/target/linux.hpp"

#if $_PLATFORM_LINUX

/// Linux Modules
#include <elf.h>
#include <link.h>
#include <sys/param.h>

/// Forward Declarations
$_FWD(using Info = dl_phdr_info, XJCT::Utils::DL)
$_FWD(int32_t callback(Info*, size_t, void*), XJCT::Utils::DL)

//  PUBLIC METHODS  //

int32_t XJCT::Utils::DL::callback(Info* info, size_t, void* data) { return (*((Info*)data) = *info, 1); }

//  PRIVATE METHODS  //

XJCT::Archive::Blob XJCT::Target::Linux::m_resource(const $::String::View& name) const noexcept {
    // prepare the information structure
    Utils::DL::Info info = {};

    // attempt finding the information details
    dl_iterate_phdr(Utils::DL::callback, &info);

    // prepare the base program information
    size_t bn = info.dlpi_phnum;
    uintptr_t ba = info.dlpi_addr;
    uintptr_t bp = (uintptr_t)info.dlpi_phdr;

    // prepare some constants to be used now
    static constexpr auto s_nhdr = sizeof(ElfW(Nhdr));
    static constexpr auto s_phdr = sizeof(ElfW(Phdr));

    // iterate over the program header
    for (; bn > 0; bn--, bp += s_phdr) {
        ElfW(Phdr)* phdr = reinterpret_cast<ElfW(Phdr)*>(bp);

        // skip everything but the incoming notes
        if (phdr->p_type != PT_NOTE) continue;

        // segment starts at base address + segment
        uintptr_t pos = ba + phdr->p_vaddr;
        uintptr_t end = pos + phdr->p_memsz;

        // iterate through segment until we reach the end
        for (; pos < end;) {
            // received an invalid not here
            if ((pos + s_nhdr) > end) break;

            // destructure the incoming note to be handled
            ElfW(Nhdr)* note = reinterpret_cast<ElfW(Nhdr)*>(pos);

            auto exists = note->n_namesz != 0 && note->n_descsz != 0;  // check for existence
            exists = exists && std::strncmp((char*)(pos + s_nhdr), name.data(), name.size()) == 0;

            // found the required note so lets show it
            if (exists) {
                // cast the incoming data to something usable now
                auto offset = reinterpret_cast<uintptr_t>(note) + s_nhdr;
                auto* data = reinterpret_cast<char*>(offset + roundup(note->n_namesz, 4));

                // and cast into the appropriate output now
                return Archive::Blob(data, note->n_descsz);
            }

            // increment our current note position now
            pos += s_nhdr + roundup(note->n_namesz, 4) + roundup(note->n_descsz, 4);
        }
    }

    // could not find any valid note
    return {};
}

#endif

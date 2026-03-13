/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PRIVATE METHODS  //

TALOS_MM_FORMAT_DECL(Overload, reader) {
    // attempt parsing an incoming signature now
    auto* signature = m_signature(reader, true);
    if (signature == nullptr) return nullptr;

    // prepare the storage instance now
    auto* storage = reader->storage();

    // construct the resulting value
    return storage->append(storage->space().hard(), signature);
}

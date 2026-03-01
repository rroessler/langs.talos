/// XJCT Modules
#include "xjct/target/darwin.hpp"
#include "xjct/forward/lief.hpp"

//  PRIVATE METHODS  //

bool XJCT::Target::Darwin::m_imbue(Archive::Binary& binary, const Imbue::Options& options) const noexcept {
    // prepare the parser to be used for modification
    auto parser = LIEF::MachO::Parser::parse(binary.buffer());
    if (parser == nullptr) return false;  // failed to create

    // pre-build the necessary content now
    Archive::Buffer content = { options.blob.begin(), options.blob.end() };

    // iterate over the available Mach-O binaries
    for (auto& fat : *parser) {
        // attempt adding our section (ensuring it doesn't exist)
        if (fat.has_section(options.name)) return false;

        // add the content as a section now
        fat.add_section({ options.name, content });

        // remove code-signature as well if necessary (required to rebuild)
        if (fat.has_code_signature()) fat.remove_signature();
    }

    // update our executable and return now
    return binary.buffer() = parser->raw(), true;
}

/// XJCT Modules
#include "xjct/target/linux.hpp"
#include "xjct/forward/lief.hpp"

//  PRIVATE METHODS  //

bool XJCT::Target::Linux::m_imbue(Archive::Binary& binary, const Imbue::Options& options) const noexcept {
    auto parser = LIEF::ELF::Parser::parse(binary.buffer());
    if (parser == nullptr) return false;  // failed building

    // fail if any of the notes have the same name
    auto predicate = [options](const auto& note) { return note.name() == options.name; };
    if (std::any_of(parser->notes().begin(), parser->notes().end(), predicate)) return false;

    auto type = LIEF::ELF::Note::TYPE::UNKNOWN;  // prepare note options
    Archive::Buffer content = { options.blob.begin(), options.blob.end() };

    // prepare the note (need to have a temporary value since its a unique_ptr)
    auto note = LIEF::ELF::Note::create(options.name, type, content, ".note.custom");

    // finally rebuild the output as necessary now (this currently fails due to LIEF being bad)
    return parser->add(*note), binary.buffer() = parser->raw(), true;
}

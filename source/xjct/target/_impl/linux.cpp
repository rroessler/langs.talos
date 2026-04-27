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

    // prepare some constants to be used
    static constexpr auto s_section = ".note.custom";
    static constexpr auto s_type = LIEF::ELF::Note::TYPE::UNKNOWN;

    // prepare the archive content to be used
    Archive::Buffer content = { options.blob.begin(), options.blob.end() };

    // prepare the note (need to have a temporary value since its a unique_ptr)
    auto note = $::New().unique<LIEF::ELF::Note>(options.name, s_type, 0, content, s_section);

    // bind the note we require to our parser
    parser->add(*note);

    // manually build our instance (as we require note building)
    LIEF::ELF::Builder builder = { *parser, { .notes = true } };

    // finally rebuild the output as necessary now (this currently fails due to LIEF being bad)
    return builder.build(), binary.buffer() = builder.get_build(), true;
}

/// Talos Modules
#include "talos/bytecode/assembler.hpp"
#include "talos/number/tagged.hpp"
#include "talos/runtime/container.hpp"

//  CONSTRUCTORS  //

Talos::Bytecode::Assembler::Assembler() : Assembler($::Global::get<Runtime::Container>()) {}
Talos::Bytecode::Assembler::Assembler(XI::Container*) {}

//  PUBLIC METHODS  //

Talos::Linker::View Talos::Bytecode::Assembler::process(Routine* routine, Linker::Arena* arena) {
    // prepare the details to be used
    auto& buffer = arena->bytecode;
    auto& sources = buffer.sources();

    // prepare the starting offsets
    auto start = buffer.size();
    Label::Encoded offset = start;

    // clear all the compilation details to be used now
    m_head = routine->head, m_placed = {}, m_unresolved = {};

    // prepare the output for our instructions now
    auto merged = Cache();

    // attempt building the necessary offset labels and handle elisions
    for (const auto& block : routine->blocks) {
        for (const auto& label : block->labels()) m_placed.emplace(label, offset);  // place labels now
        for (const auto& instruction : block->instructions()) offset += m_elide(merged, instruction.get());
    }

    // attempt encoding all the merged instructions now
    for (const auto& instruction : merged) {
        auto pointer = buffer.size();  // prepare
        buffer.write(m_encode(instruction, pointer));
        auto* position = m_positions.get(instruction);
        if (position) sources.append(pointer, *position);
    }

    // and return the resulting slice
    return m_patch(buffer, arena), m_positions.clear(), buffer.view(start);
}

//  PRIVATE METHODS  //

void Talos::Bytecode::Assembler::m_patch(Linker::Buffer& buffer, Linker::Arena* arena) const {
    // prepare the slot to be used
    auto slot = Index();

    // prepare the constants that are available
    auto& constants = arena->constants;

    // iterate over the available unresolved labels now
    for (const auto& [offset, entry] : m_unresolved) {
        // get the incoming details to be used
        auto [index, label] = entry;

        // validate the labels that we need to refer from
        $_ASSERT(m_placed.contains(index), "Unexpected patch-base '{0}'", index);
        $_ASSERT(m_placed.contains(label), "Unexpected patch-label '{0}'", label);

        // determine the relative offset now
        int64_t boff = m_placed.at(index);
        int64_t loff = m_placed.at(label);

        auto jump = Number::Tagged(boff - loff - static_cast<int64_t>(sizeof(Instruction)));
        $_ASSERT(jump.value() >= INT32_MIN && jump.value() <= INT32_MAX, "Jump offset exceeds range");

        // emplace the patch-constant now to be used
        auto iter = std::ranges::find(constants, Value::Any(jump));

        if (iter != constants.end()) slot = std::distance(constants.begin(), iter);
        else constants.push_back(jump), slot = constants.size() - 1;  // resolve now

        // get the incoming patch-offset now
        auto peeked = buffer.data()[offset];
        auto opcode = static_cast<Syllable>(peeked);

        // attempt patching the incoming opcode now
        switch (opcode) {
#define TALOS_XX_SYLLABLE_JUMP(N, ...) \
    case Syllable::N: buffer.patch(offset + 1, slot.encode()); break;
#include "talos/bytecode/_defines/syllables.def"
            default: $_ABORT("Unexpected opcode patch: {0}", peeked);
        }
    }
}

uint64_t Talos::Bytecode::Assembler::m_encode(const Instruction* instruction, Label::Encoded offset) {
    // prepare an instruction label here
    auto label = m_head++;

    // and emplace the current label now
    m_placed.emplace(label, offset);

    // reserve some unresolved labels if necessary
    switch (instruction->syllable()) {
#define TALOS_XX_SYLLABLE_JUMP(N, ...)                  \
    case Syllable::N: {                                 \
        auto* jump = instruction->cast<Syllable::N>();  \
        Label::Patch entry = { jump->get<0>(), label }; \
        m_unresolved.emplace(offset, entry);            \
    } break;
#include "talos/bytecode/_defines/syllables.def"

        // regular values so we can ignore
        default: break;
    }

    // encode the incoming instruction now
    return instruction->encode();
}

int32_t Talos::Bytecode::Assembler::m_elide(Cache& instructions, const Instruction* current) const {
    return instructions.emplace_back(current), sizeof(Instruction);
}

/// Inline Modules
#include "talos/machine/_inline/macros.ipp"
#include "talos/value/_inline/value.ipp"

/// Forward Definitions
$_FWD(Talos::Machine, using Kind = Operator::Kind)

//  PRIVATE METHODS  //

TALOS_MM_MACHINE_EMIT(UNOP_INC, builder, instruction) { __tm__ unary(builder, Kind::INC, instruction); }
TALOS_MM_MACHINE_EMIT(UNOP_DEC, builder, instruction) { __tm__ unary(builder, Kind::DEC, instruction); }
TALOS_MM_MACHINE_EMIT(UNOP_NOT, builder, instruction) { __tm__ unary(builder, Kind::NOT, instruction); }
TALOS_MM_MACHINE_EMIT(UNOP_NEG, builder, instruction) { __tm__ unary(builder, Kind::NEG, instruction); }
TALOS_MM_MACHINE_EMIT(UNOP_INV, builder, instruction) { __tm__ unary(builder, Kind::INV, instruction); }

TALOS_MM_MACHINE_EMIT(BINOP_ADD, builder, instruction) { __tm__ binary(builder, Kind::ADD, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_SUB, builder, instruction) { __tm__ binary(builder, Kind::SUB, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_MUL, builder, instruction) { __tm__ binary(builder, Kind::MUL, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_DIV, builder, instruction) { __tm__ binary(builder, Kind::DIV, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_MOD, builder, instruction) { __tm__ binary(builder, Kind::MOD, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_POW, builder, instruction) { __tm__ binary(builder, Kind::POW, instruction); }

TALOS_MM_MACHINE_EMIT(BINOP_SHL, builder, instruction) { __tm__ binary(builder, Kind::SHL, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_SHR, builder, instruction) { __tm__ binary(builder, Kind::SHR, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_XOR, builder, instruction) { __tm__ binary(builder, Kind::XOR, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_BOR, builder, instruction) { __tm__ binary(builder, Kind::BOR, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_BAND, builder, instruction) { __tm__ binary(builder, Kind::BAND, instruction); }

TALOS_MM_MACHINE_EMIT(BINOP_ADDI, builder, instruction) { __tm__ binary_i(builder, Kind::ADD, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_SUBI, builder, instruction) { __tm__ binary_i(builder, Kind::SUB, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_MULI, builder, instruction) { __tm__ binary_i(builder, Kind::MUL, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_DIVI, builder, instruction) { __tm__ binary_i(builder, Kind::DIV, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_MODI, builder, instruction) { __tm__ binary_i(builder, Kind::MOD, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_POWI, builder, instruction) { __tm__ binary_i(builder, Kind::POW, instruction); }

TALOS_MM_MACHINE_EMIT(BINOP_SHLI, builder, instruction) { __tm__ binary_i(builder, Kind::SHL, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_SHRI, builder, instruction) { __tm__ binary_i(builder, Kind::SHR, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_XORI, builder, instruction) { __tm__ binary_i(builder, Kind::XOR, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_BORI, builder, instruction) { __tm__ binary_i(builder, Kind::BOR, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_BANDI, builder, instruction) { __tm__ binary_i(builder, Kind::BAND, instruction); }

TALOS_MM_MACHINE_EMIT(BINOP_COAL, builder, instruction) { __tm__ coalesce(builder, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_LOR, builder, instruction) { __tm__ logical(builder, Kind::LOR, instruction); }
TALOS_MM_MACHINE_EMIT(BINOP_LAND, builder, instruction) { __tm__ logical(builder, Kind::LAND, instruction); }

TALOS_MM_MACHINE_EMIT(TEST_EQ, builder, instruction) { __tm__ equality(builder, Kind::EQ, instruction); }
TALOS_MM_MACHINE_EMIT(TEST_NE, builder, instruction) { __tm__ equality(builder, Kind::NE, instruction); }

TALOS_MM_MACHINE_EMIT(TEST_GT, builder, instruction) { __tm__ compare(builder, Kind::LT, instruction); }
TALOS_MM_MACHINE_EMIT(TEST_LT, builder, instruction) { __tm__ compare(builder, Kind::LT, instruction); }
TALOS_MM_MACHINE_EMIT(TEST_GE, builder, instruction) { __tm__ compare(builder, Kind::GE, instruction); }
TALOS_MM_MACHINE_EMIT(TEST_LE, builder, instruction) { __tm__ compare(builder, Kind::LE, instruction); }

TALOS_MM_MACHINE_EMIT(TEST_GTI, builder, instruction) { __tm__ compare_i(builder, Kind::GT, instruction); }
TALOS_MM_MACHINE_EMIT(TEST_LTI, builder, instruction) { __tm__ compare_i(builder, Kind::LT, instruction); }
TALOS_MM_MACHINE_EMIT(TEST_GEI, builder, instruction) { __tm__ compare_i(builder, Kind::GE, instruction); }
TALOS_MM_MACHINE_EMIT(TEST_LEI, builder, instruction) { __tm__ compare_i(builder, Kind::LE, instruction); }

TALOS_MM_MACHINE_EMIT(UNOP_TPL, , ) { $::System::unreachable(); }
TALOS_MM_MACHINE_EMIT(BINOP_TPL, , ) { $::System::unreachable(); }
TALOS_MM_MACHINE_EMIT(BINOP_TPLI, , ) { $::System::unreachable(); }

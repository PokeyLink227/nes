#ifndef __NES_CPU__
#define __NES_CPU__

enum cpu_status_flags {
    CARRY       = 0x01,
    ZERO        = 0x02,
    IRQDISABLE  = 0x04,
    DECIMALMODE = 0x08,
    BRKCOMMAND  = 0x10,
    UNUSED      = 0x20,
    OVERFLOW    = 0x40,
    NEGATIVE    = 0x80
};

enum addr_mode {
    ADR_XXX,
    ADR_ACC,
    ADR_IMM,
    ADR_ZPG,
    ADR_ZPX,
    ADR_ZPY,
    ADR_ABS,
    ADR_ABX,
    ADR_ABY,
    ADR_IMP,
    ADR_REL,
    ADR_INX,
    ADR_INY,
    ADR_IND
};

enum opcode {
    OP_XXX,
    OP_ADC,
    OP_AND,
    OP_ASL,
    OP_BCC,
    OP_BCS,
    OP_BEQ,
    OP_BIT,
    OP_BMI,
    OP_BNE,
    OP_BPL,
    OP_BRK,
    OP_BVC,
    OP_BVS,
    OP_CLC,
    OP_CLD,
    OP_CLI,
    OP_CLV,
    OP_CMP,
    OP_CPX,
    OP_CPY,
    OP_DEC,
    OP_DEX,
    OP_DEY,
    OP_EOR,
    OP_INC,
    OP_INX,
    OP_INY,
    OP_JMP,
    OP_JSR,
    OP_LDA,
    OP_LDX,
    OP_LDY,
    OP_LSR,
    OP_NOP,
    OP_ORA,
    OP_PHA,
    OP_PHP,
    OP_PLA,
    OP_PLP,
    OP_ROL,
    OP_ROR,
    OP_RTI,
    OP_RTS,
    OP_SBC,
    OP_SEC,
    OP_SED,
    OP_SEI,
    OP_STA,
    OP_STX,
    OP_STY,
    OP_TAX,
    OP_TAY,
    OP_TSX,
    OP_TXA,
    OP_TXS,
    OP_TYA
};

typedef struct instruction {
    byte opcode, addr_mode, cycles;
} Instr;

struct INES_HEADER {
    byte ID[4];
    byte PRG_ROM_SZ, CHR_ROM_SZ;
    byte FLAGS[5];
    byte PADDING[5];
};

void set_flag(byte, word);
byte get_flag(byte);

byte read(word);
byte write(word, byte);

byte set_address_mode(byte);
byte execute_instr(byte);

void reset_cpu();

#endif /* __NES_CPU__ */

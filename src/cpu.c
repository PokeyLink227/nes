#include <stdio.h>
#include "cpu.h"

Instr opcode_lookup[0x100] = {
    {OP_BRK, ADDR_IMP, 7}, {OP_ORA, ADDR_INX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_ORA, ADDR_ZPG, 3}, {OP_ASL, ADDR_ZPG, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_PHP, ADDR_IMP, 3}, {OP_ORA, ADDR_IMM, 2}, {OP_ASL, ADDR_ACC, 2}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_ORA, ADDR_ABS, 4}, {OP_ASL, ADDR_ABS, 6}, {OP_XXX, ADDR_XXX, 1},
    {OP_BPL, ADDR_REL, 2}, {OP_ORA, ADDR_INY, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_ORA, ADDR_ZPX, 4}, {OP_ASL, ADDR_ZPX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_CLC, ADDR_IMP, 2}, {OP_ORA, ADDR_ABY, 4}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_ORA, ADDR_ABX, 4}, {OP_ASL, ADDR_ABX, 7}, {OP_XXX, ADDR_XXX, 1},
    {OP_JSR, ADDR_ABS, 6}, {OP_AND, ADDR_INX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_BIT, ADDR_ZPG, 3}, {OP_AND, ADDR_ZPG, 3}, {OP_ROL, ADDR_ZPG, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_PLP, ADDR_IMP, 4}, {OP_AND, ADDR_IMM, 2}, {OP_ROL, ADDR_ACC, 2}, {OP_XXX, ADDR_XXX, 1}, {OP_BIT, ADDR_ABS, 4}, {OP_AND, ADDR_ABS, 4}, {OP_ROL, ADDR_ABS, 6}, {OP_XXX, ADDR_XXX, 1},
    {OP_BMI, ADDR_REL, 2}, {OP_AND, ADDR_INY, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_AND, ADDR_ZPX, 4}, {OP_ROL, ADDR_ZPX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_SEC, ADDR_IMP, 2}, {OP_AND, ADDR_ABY, 4}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_AND, ADDR_ABX, 4}, {OP_ROL, ADDR_ABX, 7}, {OP_XXX, ADDR_XXX, 1},
    {OP_RTI, ADDR_IMP, 6}, {OP_EOR, ADDR_INX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_EOR, ADDR_ZPG, 3}, {OP_LSR, ADDR_ZPG, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_PHA, ADDR_IMP, 3}, {OP_EOR, ADDR_IMM, 2}, {OP_LSR, ADDR_ACC, 2}, {OP_XXX, ADDR_XXX, 1}, {OP_JMP, ADDR_ABS, 3}, {OP_EOR, ADDR_ABS, 4}, {OP_LSR, ADDR_ABS, 6}, {OP_XXX, ADDR_XXX, 1},
    {OP_BVC, ADDR_REL, 2}, {OP_EOR, ADDR_INY, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_EOR, ADDR_ZPX, 4}, {OP_LSR, ADDR_ZPX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_CLI, ADDR_IMP, 2}, {OP_EOR, ADDR_ABY, 4}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_EOR, ADDR_ABX, 4}, {OP_LSR, ADDR_ABX, 7}, {OP_XXX, ADDR_XXX, 1},
    {OP_RTS, ADDR_IMP, 6}, {OP_ADC, ADDR_INX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_ADC, ADDR_ZPG, 3}, {OP_ROR, ADDR_ZPG, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_PLA, ADDR_IMP, 4}, {OP_ADC, ADDR_IMM, 2}, {OP_ROR, ADDR_ACC, 2}, {OP_XXX, ADDR_XXX, 1}, {OP_JMP, ADDR_IND, 5}, {OP_ADC, ADDR_ABS, 4}, {OP_ROR, ADDR_ABS, 6}, {OP_XXX, ADDR_XXX, 1},
    {OP_BVS, ADDR_REL, 2}, {OP_ADC, ADDR_INY, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_ADC, ADDR_ZPX, 4}, {OP_ROR, ADDR_ZPX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_SEI, ADDR_IMP, 2}, {OP_ADC, ADDR_ABY, 4}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_ADC, ADDR_ABX, 4}, {OP_ROR, ADDR_ABX, 7}, {OP_XXX, ADDR_XXX, 1},
    {OP_XXX, ADDR_XXX, 1}, {OP_STA, ADDR_INX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_STY, ADDR_ZPG, 3}, {OP_STA, ADDR_ZPG, 3}, {OP_STX, ADDR_ZPG, 3}, {OP_XXX, ADDR_XXX, 1}, {OP_DEY, ADDR_IMP, 2}, {OP_XXX, ADDR_XXX, 1}, {OP_TXA, ADDR_IMP, 2}, {OP_XXX, ADDR_XXX, 1}, {OP_STY, ADDR_ABS, 4}, {OP_STA, ADDR_ABS, 4}, {OP_STX, ADDR_ABS, 4}, {OP_XXX, ADDR_XXX, 1},
    {OP_BCC, ADDR_REL, 2}, {OP_STA, ADDR_INY, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_STY, ADDR_ZPX, 4}, {OP_STA, ADDR_ZPX, 4}, {OP_STX, ADDR_ZPY, 4}, {OP_XXX, ADDR_XXX, 1}, {OP_TYA, ADDR_IMP, 2}, {OP_STA, ADDR_ABY, 5}, {OP_TXS, ADDR_IMP, 2}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_STA, ADDR_ABX, 4}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1},
    {OP_LDY, ADDR_IMM, 2}, {OP_LDA, ADDR_INX, 6}, {OP_LDX, ADDR_IMM, 2}, {OP_XXX, ADDR_XXX, 1}, {OP_LDY, ADDR_ZPG, 3}, {OP_LDA, ADDR_ZPG, 3}, {OP_LDX, ADDR_ZPG, 3}, {OP_XXX, ADDR_XXX, 1}, {OP_TAY, ADDR_IMP, 2}, {OP_LDA, ADDR_IMM, 2}, {OP_TAX, ADDR_IMP, 2}, {OP_XXX, ADDR_XXX, 1}, {OP_LDY, ADDR_ABS, 4}, {OP_LDA, ADDR_ABS, 4}, {OP_LDX, ADDR_ABS, 4}, {OP_XXX, ADDR_XXX, 1},
    {OP_BCS, ADDR_REL, 2}, {OP_LDA, ADDR_INY, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_LDY, ADDR_ZPX, 3}, {OP_LDA, ADDR_ZPX, 4}, {OP_LDX, ADDR_ZPY, 4}, {OP_XXX, ADDR_XXX, 1}, {OP_CLV, ADDR_IMP, 2}, {OP_LDA, ADDR_ABY, 4}, {OP_TSX, ADDR_IMP, 2}, {OP_XXX, ADDR_XXX, 1}, {OP_LDY, ADDR_ABX, 4}, {OP_LDA, ADDR_ABX, 4}, {OP_ADC, ADDR_ABY, 4}, {OP_XXX, ADDR_XXX, 1},
    {OP_CPY, ADDR_IMM, 2}, {OP_CMP, ADDR_INX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_CPY, ADDR_ZPG, 3}, {OP_CMP, ADDR_ZPG, 3}, {OP_DEC, ADDR_ZPG, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_INY, ADDR_IMP, 2}, {OP_CMP, ADDR_IMM, 2}, {OP_DEX, ADDR_IMP, 2}, {OP_XXX, ADDR_XXX, 1}, {OP_CPY, ADDR_ABS, 4}, {OP_CMP, ADDR_ABS, 4}, {OP_DEC, ADDR_ABS, 6}, {OP_XXX, ADDR_XXX, 1},
    {OP_BNE, ADDR_REL, 2}, {OP_CMP, ADDR_INY, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_CMP, ADDR_ZPX, 4}, {OP_DEC, ADDR_ZPX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_CLD, ADDR_IMP, 2}, {OP_CMP, ADDR_ABY, 4}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_CMP, ADDR_ABX, 4}, {OP_DEC, ADDR_ABX, 7}, {OP_XXX, ADDR_XXX, 1},
    {OP_CPX, ADDR_IMM, 2}, {OP_SBC, ADDR_INX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_CPX, ADDR_ZPG, 3}, {OP_SBC, ADDR_ZPG, 3}, {OP_INC, ADDR_ZPG, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_INX, ADDR_IMP, 2}, {OP_SBC, ADDR_IMM, 2}, {OP_NOP, ADDR_IMP, 2}, {OP_XXX, ADDR_XXX, 1}, {OP_CPX, ADDR_ABS, 4}, {OP_SBC, ADDR_ABS, 4}, {OP_INC, ADDR_ABS, 6}, {OP_XXX, ADDR_XXX, 1},
    {OP_BEQ, ADDR_REL, 2}, {OP_SBC, ADDR_INY, 5}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_SBC, ADDR_ZPX, 4}, {OP_INC, ADDR_ZPX, 6}, {OP_XXX, ADDR_XXX, 1}, {OP_SED, ADDR_IMP, 2}, {OP_SBC, ADDR_ABY, 4}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_XXX, ADDR_XXX, 1}, {OP_SBC, ADDR_ABX, 4}, {OP_INC, ADDR_ABX, 7}, {OP_XXX, ADDR_XXX, 1}
};

const char mnemonics[57][4] = {
    "XXX", "ADC", "AND", "ASL", "BCC",
    "BCS", "BEQ", "BIT", "BMI", "BNE",
    "BPL", "BRK", "BVC", "BVS", "CLC",
    "CLD", "CLI", "CLV", "CMP", "CPX",
    "CPY", "DEC", "DEX", "DEY", "EOR",
    "INC", "INX", "INY", "JMP", "JSR",
    "LDA", "LDX", "LDY", "LSR", "NOP",
    "ORA", "PHA", "PHP", "PLA", "PLP",
    "ROL", "ROR", "RTI", "RTS", "SBC",
    "SEC", "SED", "SEI", "STA", "STX",
    "STY", "TAX", "TAY", "TSX", "TXA",
    "TXS", "TYA"
};


word pc;
byte acc, x, y, stkptr, status;
byte ram[0x800];

Instr cur_instr;
word data_addr;
byte cycles;

void set_flag(byte flag, word b) {
    if (b) {
        status |= flag;
    } else {
        status &= ~flag;
    }
    return;
}

byte get_flag(byte flag) {
    return (status & flag) != 0;
}

byte read(word addr) {
    if (addr < 0x2000) return ram[addr & 0x07FF];
    else return bus_read(addr);
}

byte write(word addr, byte data) {
    if (addr < 0x2000) {
        ram[addr & 0x07FF] = data;
        return 0x00;
    }
    return bus_write(addr, data);
}

byte set_address_mode(byte mode) {
    word low, high;
    switch (mode) {
    case ADDR_XXX: {
        return 0;
    }

    case ADDR_ACC: {
        return 0;
    }

    case ADDR_IMM: {
        data_addr = pc++;
        return 0;
    }

    case ADDR_ZPG: {
        data_addr = read(pc++);
        return 0;
    }

    case ADDR_ZPX: {
        data_addr = (x + read(pc++)) & 0x00FF;
        return 0;
    }

    case ADDR_ZPY: {
        data_addr = (y + read(pc++)) & 0x00FF;
        return 0;
    }

    case ADDR_ABS: {
        low = read(pc++);
        high = read(pc++);
        data_addr = (high << 8) | low;
        return 0;
    }

    case ADDR_ABX: {
        low = read(pc++);
        high = read(pc++);
        data_addr = (high << 8) | low;
        data_addr += x;
        /* checks if page boundry was crossed */
        return ((data_addr & 0xFF00) != (high << 8));
    }

    case ADDR_ABY: {
        low = read(pc++);
        high = read(pc++);
        data_addr = (high << 8) | low;
        data_addr += y;
        return ((data_addr & 0xFF00) != (high << 8));
    }

    case ADDR_IMP: {
        return 0;
    }

    case ADDR_REL: { /* additional cycles need to be calculated per instruction */
        data_addr = read(pc++);
        if (data_addr & 0x80) data_addr |= 0xFF00;
        return 0;
    }

    case ADDR_INX: {
        low = read(pc++);
        low = (low + x) & 0x00FF;
        data_addr = low;

        low = read(data_addr++);
        high = read(data_addr);
        data_addr = (high << 8) | low;
        return 0;
    }

    case ADDR_INY: {
        low = read(pc++);
        high = read(pc++);
        data_addr = (high << 8) | low;
        data_addr += y;
        return ((data_addr & 0xFF00) != (high << 8));
    }

    case ADDR_IND: {
        low = read(pc++);
        high = read(pc++);
        data_addr = (high << 8) | low;

        /*
            needed in order to emulate a bug that caused invalid memory addresses to be read
            when reading across page boundries wrap rather than cross
        */
        if (low == 0x00FF) {
            low = read(data_addr);
            high = read(data_addr & 0xFF00);
            data_addr = (high << 8) | low;
        } else {
            low = read(data_addr++);
            high = read(data_addr);
            data_addr = (high << 8) | low;
        }
        return 0;
    }

    }

    return 0; // num extra cycles
}

byte execute_instr(byte instr) {
    switch (instr) {
    case OP_ADC: {
        if (get_flag(DECIMALMODE)) printf("AHHHHHHHH I CANT DO THIS\n");
        word sum = acc + read(data_addr) + get_flag(CARRY);

        set_flag(OVERFLOW, (~(acc ^ read(data_addr)) & (acc ^ (byte)sum)) & 0x0080);
        set_flag(CARRY, sum > 0xFF);
        set_flag(ZERO, sum == 0x00);
        set_flag(NEGATIVE, sum & 0x80);

        acc = sum & 0x00FF;
        return 1;
    }

    case OP_AND: {
        acc &= read(data_addr);
        set_flag(ZERO, acc == 0x00);
        set_flag(NEGATIVE, acc & 0x80);
        return 1;
    }

    case OP_ASL: {
        if (cur_instr.addr_mode == ADDR_ACC) {
            set_flag(CARRY, acc & 0x80);
            acc <<= 1;
            set_flag(ZERO, acc == 0x00);
            set_flag(NEGATIVE, acc & 0x80);
        } else {
            byte temp = read(data_addr);
            set_flag(CARRY, temp & 0x80);
            temp <<= 1;
            set_flag(ZERO, temp == 0x00);
            set_flag(NEGATIVE, temp & 0x80);
        }
        return 0;
    }

    case OP_BCC: {
        if (!get_flag(CARRY)) {
            cycles++;
            if ((pc & 0xFF00) != ((pc + data_addr) & 0xFF00)) cycles++;
            pc += data_addr;
        }
        return 0;
    }

    case OP_BCS: {
        if (get_flag(CARRY)) {
            cycles++;
            if ((pc & 0xFF00) != ((pc + data_addr) & 0xFF00)) cycles++;
            pc += data_addr;
        }
        return 0;
    }

    case OP_BEQ: {
        if (get_flag(ZERO)) {
            cycles++;
            if ((pc & 0xFF00) != ((pc + data_addr) & 0xFF00)) cycles++;
            pc += data_addr;
        }
        return 0;
    }

    case OP_BIT: {
        byte temp = read(data_addr);
        set_flag(ZERO, (temp & acc) == 0);
        set_flag(OVERFLOW, temp & 0x40);
        set_flag(NEGATIVE, temp & 0x80);
        return 0;
    }

    case OP_BMI: {
        if (get_flag(NEGATIVE)) {
            cycles++;
            if ((pc & 0xFF00) != ((pc + data_addr) & 0xFF00)) cycles++;
            pc += data_addr;
        }
        return 0;
    }

    case OP_BNE: {
        if (!get_flag(ZERO)) {
            cycles++;
            if ((pc & 0xFF00) != ((pc + data_addr) & 0xFF00)) cycles++;
            pc += data_addr;
        }
        return 0;
    }

    case OP_BPL: {
        if (!get_flag(NEGATIVE)) {
            cycles++;
            if ((pc & 0xFF00) != ((pc + data_addr) & 0xFF00)) cycles++;
            pc += data_addr;
        }
        return 0;
    }

    case OP_BRK: {
        write(0x0100 + stkptr--, (pc >> 8) & 0x00FF);
        write(0x0100 + stkptr--, pc & 0x00FF);
        write(0x0100 + stkptr--, status);

        pc = read(0xFFFE);
        pc |= (read(0xFFFF) << 8) & 0xFF00;

        set_flag(BRKCOMMAND, 1);
        return 0;
    }

    case OP_BVC: {
        if (!get_flag(OVERFLOW)) {
            cycles++;
            if ((pc & 0xFF00) != ((pc + data_addr) & 0xFF00)) cycles++;
            pc += data_addr;
        }
        return 0;
    }

    case OP_BVS: {
        if (get_flag(OVERFLOW)) {
            cycles++;
            if ((pc & 0xFF00) != ((pc + data_addr) & 0xFF00)) cycles++;
            pc += data_addr;
        }
        return 0;
    }

    case OP_CLC: {
        status &= ~CARRY;
        return 0;
    }

    case OP_CLD: {
        status &= ~DECIMALMODE;
        return 0;
    }

    case OP_CLI: {
        status &= ~IRQDISABLE;
        return 0;
    }

    case OP_CLV: {
        status &= ~OVERFLOW;
        return 0;
    }

    case OP_CMP: {
        word temp = acc - read(data_addr);
        set_flag(CARRY, acc >= read(data_addr));
        set_flag(NEGATIVE, temp & 0x80);
        set_flag(ZERO, temp == 0);
        return 0;
    }

    case OP_CPX: {
        word temp = x - read(data_addr);
        set_flag(CARRY, x >= read(data_addr));
        set_flag(NEGATIVE, temp & 0x80);
        set_flag(ZERO, temp == 0);
        return 0;
    }

    case OP_CPY: {
        word temp = y - read(data_addr);
        set_flag(CARRY, y >= read(data_addr));
        set_flag(NEGATIVE, temp & 0x80);
        set_flag(ZERO, temp == 0);
        return 0;
    }

    case OP_DEC: {
        byte temp = read(data_addr);
        temp -= 1;
        write(data_addr, temp);
        set_flag(ZERO, temp == 0x00);
        set_flag(NEGATIVE, temp & 0x80);
        return 0;
    }

    case OP_DEX: {
        x -= 1;
        set_flag(ZERO, x == 0x00);
        set_flag(NEGATIVE, x & 0x80);
        return 0;
    }

    case OP_DEY: {
        y -= 1;
        set_flag(ZERO, y == 0x00);
        set_flag(NEGATIVE, y & 0x80);
        return 0;
    }

    case OP_EOR: {
        acc ^= read(data_addr);
        set_flag(ZERO, acc == 0x00);
        set_flag(NEGATIVE, acc & 0x80);
        return 1;
    }

    case OP_INC: {
        byte temp = read(data_addr);
        temp += 1;
        write(data_addr, temp);
        set_flag(ZERO, temp == 0x00);
        set_flag(NEGATIVE, temp & 0x80);
        return 0;
    }

    case OP_INX: {
        x += 1;
        set_flag(ZERO, x == 0x00);
        set_flag(NEGATIVE, x & 0x80);
        return 0;
    }

    case OP_INY: {
        y -= 1;
        set_flag(ZERO, y == 0x00);
        set_flag(NEGATIVE, y & 0x80);
        return 0;
    }

    case OP_JMP: {
        pc = data_addr;
        return 0;
    }

    case OP_JSR: {
        pc--;
        write(0x0100 + stkptr--, (pc >> 8) & 0x00FF);
        write(0x0100 + stkptr--, pc & 0x00FF);
        pc = data_addr;
        return 0;
    }

    case OP_LDA: {
        acc = read(data_addr);
        set_flag(ZERO, acc == 0x00);
        set_flag(NEGATIVE, acc & 0x80);
        return 0;
    }

    case OP_LDX: {
        x = read(data_addr);
        set_flag(ZERO, x == 0x00);
        set_flag(NEGATIVE, x & 0x80);
        return 0;
    }

    case OP_LDY: {
        y = read(data_addr);
        set_flag(ZERO, y == 0x00);
        set_flag(NEGATIVE, y & 0x80);
        return 0;
    }

    case OP_LSR: {
        if (cur_instr.addr_mode == ADDR_ACC) {
            set_flag(CARRY, acc & 0x80);
            acc >>= 1;
            set_flag(ZERO, acc == 0x00);
            set_flag(NEGATIVE, acc & 0x80);
        } else {
            byte temp = read(data_addr);
            set_flag(CARRY, temp & 0x01);
            temp >>= 1;
            set_flag(ZERO, temp == 0x00);
            set_flag(NEGATIVE, 0);
        }
        return 0;
    }

    case OP_NOP: {
        /*implement unofficial NOP's in lookup table*/
        return 0;
    }

    case OP_ORA: {
        acc |= read(data_addr);
        set_flag(ZERO, acc == 0x00);
        set_flag(NEGATIVE, acc & 0x80);
        return 0;
    }

    case OP_PHA: {
        write(0x0100 | stkptr, acc);
        stkptr--;
        return 0;
    }

    case OP_PHP: {
        write(0x0100 | stkptr, status);
        stkptr--;
        return 0;
    }

    case OP_PLA: {
        stkptr++;
        acc = read(0x0100 | stkptr);
        return 0;
    }

    case OP_PLP: {
        stkptr++;
        status = read(0x0100 | stkptr);
        return 0;
    }

    case OP_ROL: {
        byte temp;
        if (cur_instr.addr_mode == ADDR_ACC) {
            temp = acc << 1;
            if (get_flag(CARRY)) temp |= 0x01;
            set_flag(CARRY, acc & 0x80);
            acc = temp;
        }
        else {
            temp = read(data_addr) << 1;
            if (get_flag(CARRY)) temp |= 0x01;
            set_flag(CARRY, read(data_addr) & 0x80);
            write(data_addr, temp);
        }
        set_flag(ZERO, temp == 0x00);
        set_flag(NEGATIVE, temp & 0x80);
        return 0;
    }

    case OP_ROR: {
        byte temp;
        if (cur_instr.addr_mode == ADDR_ACC) {
            temp = acc >> 1;
            if (get_flag(CARRY)) temp |= 0x80;
            set_flag(CARRY, acc & 0x01);
            acc = temp;
        }
        else {
            temp = read(data_addr) >> 1;
            if (get_flag(CARRY)) temp |= 0x80;
            set_flag(CARRY, read(data_addr) & 0x01);
            write(data_addr, temp);
        }
        set_flag(ZERO, temp == 0x00);
        set_flag(NEGATIVE, temp & 0x80);
        return 0;
    }

    case OP_RTI: {
        status = read(++stkptr);
        pc = read(++stkptr);
        pc |= (read(++stkptr) << 8) & 0xFF00;
        return 0;
    }

    case OP_RTS: {
        pc = read(++stkptr);
        pc |= (read(++stkptr) << 8) & 0xFF00;

        pc++;
        return 0;
    }

    case OP_SBC: {
        /*
        word temp = acc - read(data_addr) - (1 - get_flag(CARRY));
        word temp = acc + (~read(data_addr) + 1) - 1 + get_flag(CARRY);
        */
        word temp = acc + ~read(data_addr) + get_flag(CARRY);

        set_flag(CARRY, !(temp & 0xFF00));
        set_flag(ZERO, (temp & 0x00FF) == 0x00);
        set_flag(OVERFLOW, ((acc ^ read(data_addr)) & (acc ^ temp)) & 0x0080);
        set_flag(NEGATIVE, temp & 0x80);
        acc = temp & 0x00FF;
        return 0;
    }

    case OP_SEC: {
        set_flag(CARRY, 1);
        return 0;
    }

    case OP_SED: {
        printf("dont do this\n");
        set_flag(DECIMALMODE, 1);
        return 0;
    }

    case OP_SEI: {
        set_flag(IRQDISABLE, 1);
        return 0;
    }

    case OP_STA: {
        write(data_addr, acc);
        return 0;
    }

    case OP_STX: {
        write(data_addr, x);
        return 0;
    }

    case OP_STY: {
        write(data_addr, y);
        return 0;
    }

    case OP_TAX: {
        x = acc;
        set_flag(ZERO, x == 0x00);
        set_flag(NEGATIVE, x & 0x80);
        return 0;
    }

    case OP_TAY: {
        y = acc;
        set_flag(ZERO, y == 0x00);
        set_flag(NEGATIVE, y & 0x80);
        return 0;
    }

    case OP_TSX: {
        x = stkptr;
        set_flag(ZERO, x == 0x00);
        set_flag(NEGATIVE, x & 0x80);
        return 0;
    }

    case OP_TXA: {
        acc = x;
        set_flag(ZERO, acc == 0x00);
        set_flag(NEGATIVE, acc & 0x80);
        return 0;
    }

    case OP_TXS: {
        stkptr = x;
        return 0;
    }

    case OP_TYA: {
        acc = y;
        set_flag(ZERO, acc == 0x00);
        set_flag(NEGATIVE, acc & 0x80);
        return 0;
    }
    }
    return 0;
}

void reset_cpu() {
    acc = 0x00;
    x = 0x00;
    y = 0x00;
    stkptr = 0xFF;
    //pc = 0x200;
    status = UNUSED;
}



byte load_prog(const char *file_name, word addr) {
    int read_size, f_size;
    FILE *fp = fopen(file_name, "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    fread(ram + addr, 1, f_size, fp);
    fclose(fp);

    return 1;
}

int clock_cpu() {
    byte extra_cycle;

    cur_instr = opcode_lookup[read(pc++)];
    cycles = cur_instr.cycles;
    printf("%s", mnemonics[cur_instr.opcode]);
    extra_cycle = set_address_mode(cur_instr.addr_mode);
    extra_cycle &= execute_instr(cur_instr.opcode);
    if (extra_cycle) cycles++;
}

int run_cpu() {
    byte extra_cycle, c;
    printf("loading\n");

    if (load_prog("prog.nes", 0x0200)) printf("loaded rom\n");
    else {
        printf("failed to load rom\n");
        return 0;
    }



    pc = 0x0200;

    reset_cpu();
    //printf("\033[2J\033[H");
    //disp_cpu();


    while (1) {

        c = getc(stdin);
        if (c == 'q') break;
        clock_cpu();

    }

    //printf("\033[2J\033[H");


    return 0;
}

/*
int main(int argc, char **argv) {
    byte extra_cycle, c;
    printf("loading\n");

    if (load_prog("prog.nes", 0x0200)) printf("loaded rom\n");
    else {
        printf("failed to load rom\n");
        //return 0;
    }



    pc = 0x0200;

    reset_cpu();
    printf("\033[2J\033[H");
    disp_cpu();


    while (1) {

        c = getc(stdin);
        if (c == 'q') break;

        disp_cpu();
        cur_instr = opcode_lookup[read(pc++)];
        cycles = cur_instr.cycles;
        printf("%s", mnemonics[cur_instr.opcode]);
        extra_cycle = set_address_mode(cur_instr.addr_mode);
        extra_cycle &= execute_instr(cur_instr.opcode);
        if (extra_cycle) cycles++;
    }

    printf("\033[2J\033[H");


    return 0;
}
*/

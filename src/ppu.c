#include "ppu.h"

byte ppu_read(word addr) {
    if      (addr < 0x1000) return ppu_pattern_table[0][addr];
    else if (addr < 0x2000) return ppu_pattern_table[1][addr - 0x1000];
    else if (addr < 0x3000) return ppu_nametable[addr - 0x2000];
    else if (addr < 0x3F00) return ppu_nametable[addr - 0x3000];
    else                    return ppu_palette[addr & 0x001F];
}

byte ppu_write(word addr, byte data) {
    if      (addr < 0x1000) ppu_pattern_table[0][addr] = data;
    else if (addr < 0x2000) ppu_pattern_table[1][addr - 0x1000] = data;
    else if (addr < 0x3000) ppu_nametable[addr - 0x2000] = data;
    else if (addr < 0x3F00) ppu_nametable[addr - 0x3000] = data;
    else                    ppu_palette[addr & 0x001F] = data;
    return 0x0;
}

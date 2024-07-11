#include "ppu.h"

enum ppu_state {
    PPU_IDLE,
    PPU_NAME,
    PPU_ATTRIBUTE,
    PPU_PATTERN_LOW,
    PPU_PATTERN_HIGH,
    PPU_RENDER,
};

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

byte clock_ppu() {
    static int scanline = 0;
    static int cycle = 0;
    //static int state = PPU_IDLE;

    static byte nametable, attribute, pattern_low, pattern_high;

    switch ((cycle - 1) % 8) {
        case -1: break;
        case 0: break; /* name table */
        case 1: {
            
        }
        case 2: break; /* attribute table */
        case 3: {

        }
        case 4: break; /* pattern table low */
        case 5: {

        }
        case 6: break; /* pattern table high */
        case 7: {

        }
        default:
            break;
    }

}

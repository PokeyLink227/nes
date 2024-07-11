#ifndef __POKEY_NES_PPU__
#define __POKEY_NES_PPU__

#include "bus.h"

enum ppu_control_fields {
    CONTROL_NMI            = 0x80, /* 1000 0000 */
    CONTROL_MSMODE         = 0x40, /* 0100 0000 */
    CONTROL_SPRITEHEIGHT   = 0x20, /* 0010 0000 */
    CONTROL_BACKGROUNDTILE = 0x10, /* 0001 0000 */
    CONTROL_SPRITETILE     = 0x08, /* 0000 1000 */
    CONTROL_INCMODE        = 0x04, /* 0000 0100 */
    CONTROL_NAMETABLE      = 0x03  /* 0000 0011 */
};

enum ppu_mask_fields {
    MASK_COLOR        = 0xC0, /* 1110 0000 */
    MASK_SPRITE       = 0x10, /* 0001 0000 */
    MASK_BACKGROUND   = 0x08, /* 0000 1000 */
    MASK_SPRITELC     = 0x04, /* 0000 0100 */
    MASK_BACKGROUNDLC = 0x02, /* 0000 0010 */
    MASK_GRAYSCALE    = 0x01  /* 0000 0001 */
};

enum ppu_status_fields {
    STATUS_VBLANK     = 0x80, /* 1000 0000 */
    STATUS_SPRITEZERO = 0x40, /* 0100 0000 */
    STATUS_OVERFLOW   = 0x20  /* 0010 0000 */
};

byte ppu_registers[0x8];
byte ppu_pattern_table[2][0x1000];
byte ppu_nametable[0x1000];
byte ppu_palette[0x0020];

byte ppu_read(word);
byte ppu_write(word, byte);

byte clock_ppu();

#endif /* __POKEY_NES_PPU__ */

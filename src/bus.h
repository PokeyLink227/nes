#ifndef __POKEY_NES_BUS__
#define __POKEY_NES_BUS__

typedef unsigned char   byte;
typedef unsigned short  word;
typedef unsigned int    dword;

struct INES_HEADER {
    byte ID[4];
    byte PRG_ROM_SIZE, CHR_ROM_SIZE;
    byte FLAGS[5];
    byte PADDING[5];
} rom_header;

byte *prg_rom, *prg_ram, *chr_rom;

byte bus_read(word);
byte bus_write(word, byte);

#endif /* __POKEY_NES_BUS__ */

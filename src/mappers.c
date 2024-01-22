#include "bus.h"
#include "mappers.h"

/* MAPPER_00 */
byte mapper_read__00(word addr) {
    if      (addr < 0x6000)  return 0x0;
    else if (addr < 0x8000)  return prg_ram[addr];
    else if (addr < 0xC000)  return prg_rom[addr];
    else                     return prg_rom[addr];
}

byte mapper_write_00(word addr, byte data) {
    if      (addr < 0x6000)  return 0x1;
    else if (addr < 0x8000)  prg_ram[addr] = data;
    else if (addr < 0xC000)  return 0x1;
    else                     return 0x1;
    return 0x0;
}

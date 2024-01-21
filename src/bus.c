#include <stdio.h>
#include "bus.h"
#include "cpu.h"
#include "ppu.h"

byte bus_read(word addr) {
    if      (addr < 0x2000)  return 0x0;
    else if (addr < 0x4000)  return ppu_registers[addr & 0x01];
    else                     return 0x0;
}

/*
    returns 0x0 on successful write and 0x1 on failure
*/
byte bus_write(word addr, byte data) {
    if      (addr < 0x2000)  return 0x1;
    else if (addr < 0x4000)  ppu_registers[addr & 0x01] = data;
    else                     return 0x1;
    return 0x0;
}

byte load_rom(const char *file_name, word addr) {
    int read_size, f_size;
    struct INES_HEADER header;
    FILE *fp = fopen(file_name, "rb");
    if (!fp) return 0;

    read_size = fread(&header, 1, 16, fp);
    if (read_size != 16) return 0;

    if (header.ID[0] != 'N' || header.ID[1] != 'E' || header.ID[2] != 'S' || header.ID[3] != 0x1A) return 0;


    // read trainer
    // read PRG ROM
    // read CHR rom
    // read INST-rom
    // read PROM
    byte mapper = header.FLAGS[1] & 0x0F;
    mapper |= (header.FLAGS[0] & 0xF0) >> 4;
    printf("mapper id: %d\n", mapper);
    return 0;


    /*
    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    ret_size = fread(ram + addr, 1, f_size, fp);
    if (ret_size != f_size) return 0;
    */

    fclose(fp);
    return 1;
}

int main(int argc, char **argv) {


    run_cpu();

    printf("CPU RETURNED\n");


    return 0;
}

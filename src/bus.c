#include <stdio.h>
#include "bus.h"
#include "cpu.h"
#include "ppu.h"
#include "mappers.h"

byte (* mapper_read)(word);
byte (* mapper_write)(word, byte);

byte bus_read(word addr) {
    if      (addr < 0x2000)  return 0x0;
    else if (addr < 0x4000)  return ppu_registers[addr & 0x01];
    else if (addr < 0x4018)  return 0x0;
    else if (addr < 0x4020)  return 0x0;
    else                     return mapper_read(addr);
}

/*
    returns 0x0 on successful write and 0x1 on failure
*/
byte bus_write(word addr, byte data) {
    if      (addr < 0x2000)  return 0x1;
    else if (addr < 0x4000)  ppu_registers[addr & 0x01] = data;
    else if (addr < 0x4018)  return 0x1;
    else if (addr < 0x4020)  return 0x1;
    else                     return mapper_write(addr, data);
    return 0x0;
}

byte load_rom(const char *file_name) {
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
    byte mapper_id = header.FLAGS[1] & 0x0F;
    mapper_id |= (header.FLAGS[0] & 0xF0) >> 4;
    printf("mapper id: %d\n", mapper_id);
    return 0;
    switch (mapper_id) {
        case 0: mapper_read = mapper_read__00; mapper_write = mapper_write_00; break;
    }


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

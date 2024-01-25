#include <stdio.h>
#include <stdlib.h>

#include "bus.h"
#include "cpu.h"
#include "ppu.h"
#include "mappers.h"
#include "raylib.h"

byte (* mapper_read)(word);
byte (* mapper_write)(word, byte);

byte bus_read(word addr) {
    if      (addr < 0x2000) return 0x0;
    else if (addr < 0x4000) return ppu_registers[addr & 0x07];
    else if (addr < 0x4018) return 0x0;
    else if (addr < 0x4020) return 0x0;
    else                    return mapper_read(addr);
}

/*
    returns 0x0 on successful write and 0x1 on failure
*/
byte bus_write(word addr, byte data) {
    if      (addr < 0x2000) return 0x1;
    else if (addr < 0x4000) ppu_registers[addr & 0x07] = data;
    else if (addr < 0x4018) return 0x1;
    else if (addr < 0x4020) return 0x1;
    else                    return mapper_write(addr, data);
    return 0x0;
}

byte load_rom(const char *file_name) {
    int read_size, f_size;
    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        printf("Error: Unable to find rom\n");
        return 0;
    }

    read_size = fread(&rom_header, 1, 16, fp);
    if (read_size != 16) return 0;

    if (rom_header.ID[0] != 'N' || rom_header.ID[1] != 'E' || rom_header.ID[2] != 'S' || rom_header.ID[3] != 0x1A) return 0;

    /* determine header format */
    if ((rom_header.FLAGS[0] & 0x0C) == 0x08) printf("NES 2.0\n");
    else if ((rom_header.FLAGS[0] & 0x0C) == 0x04) printf("archaic iNES\n");
    else if ((rom_header.FLAGS[0] & 0x0C) == 0x00 &&
        rom_header.PADDING[0] == 0x0 && rom_header.PADDING[1] == 0x0 && rom_header.PADDING[2] == 0x0 && rom_header.PADDING[3] == 0x0
    ) printf("iNES\n");
    else printf("iNES 0.7 or archaic iNES\n");

    /* construct mapper number */
    byte mapper_id = rom_header.FLAGS[1] & 0xF0;
    mapper_id |= (rom_header.FLAGS[0] & 0xF0) >> 4;
    printf("mapper id: %d\n", mapper_id);

    switch (mapper_id) {
        case 0: mapper_read = mapper_read__00; mapper_write = mapper_write_00; mapper_data = 1; break;
        case 9:
        default: {
            printf("Error: Unsupported mapper\n");
            fclose(fp);
            return 1;
        }
    }

    printf("prg_rom size: %i, chr_rom size: %i\n", rom_header.PRG_ROM_SIZE,  rom_header.CHR_ROM_SIZE);
    prg_rom = (byte *)malloc(16384 * rom_header.PRG_ROM_SIZE);
    chr_rom = (byte *)malloc(8192 * rom_header.CHR_ROM_SIZE);

    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp);
    fseek(fp, 16, SEEK_SET); /* only works for ines with no trainer */

    read_size = fread(prg_rom, 1, 16384 * rom_header.PRG_ROM_SIZE, fp);
    if (read_size != 16384 * rom_header.PRG_ROM_SIZE) {
        printf("Error: bad read\n");
        return 1;
    }
    read_size = fread(chr_rom, 1, 8192 * rom_header.CHR_ROM_SIZE, fp);
    if (read_size != 8192 * rom_header.CHR_ROM_SIZE) {
        printf("Error: bad read\n");
        return 1;
    }

    fclose(fp);
    return 1;
}

int main() {
    int screen_width = 256, screen_height = 240, scale = 2;
    InitWindow(screen_width * scale, screen_height * scale, "Pokey Nes Emu");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("TEST", 0, 0, 15, WHITE);
        EndDrawing();
    }

    return 0;

    load_rom("nestest.nes");
    reset_cpu();


    while (clock_cpu() == 0) {}

    for (int i = 0; i < 0x100; i++) printf("%02X ", cpu_read(i));

    return 0;
}

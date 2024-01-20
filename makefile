CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors

nes: obj\bus.o obj\cpu.o obj\ppu.o
	$(CC) $(CFLAGS) obj\bus.o obj\cpu.o obj\ppu.o -o nes

obj\bus.o: src\bus.c src\bus.h
	$(CC) $(CFLAGS) src\bus.c -c -o obj\bus.o

obj\cpu.o: src\cpu.c src\cpu.h
	$(CC) $(CFLAGS) src\cpu.c -c -o obj\cpu.o

obj\ppu.o: src\ppu.c src\ppu.h
	$(CC) $(CFLAGS) src\ppu.c -c -o obj\ppu.o

clean:
	del obj\* nes.exe /Q

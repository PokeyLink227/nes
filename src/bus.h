#ifndef __NES_BUS__
#define __NES_BUS__

typedef unsigned char   byte;
typedef unsigned short  word;
typedef unsigned int    dword;

byte bus_read(word);
byte bus_write(word, byte);

#endif /* __NES_BUS__ */

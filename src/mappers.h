#ifndef __NES_MAPPERS__
#define __NES_MAPPERS__

#include "bus.h"

dword mapper_data;

byte mapper_read__00(word);
byte mapper_write_00(word, byte);

byte mapper_read__01(word);
byte mapper_write_01(word, byte);

byte mapper_read__02(word);
byte mapper_write_02(word, byte);

#endif /* __NES_MAPPERS__ */

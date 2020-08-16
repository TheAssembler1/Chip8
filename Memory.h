#ifndef MEMORY_H
#define MEMORY_H
#include <stdio.h>
#include <stdlib.h>
#include "LiquidClearDisplay.h"

#define MEMORY_SIZE 4096
#define PROGRAM_ROM 0x200

unsigned char memory[MEMORY_SIZE];

void LoadGame(char* file_name);
void SetupMemory();
void DumpMemory();

#endif //MEMORY_H

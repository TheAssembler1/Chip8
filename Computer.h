#ifndef COMPUTER_H
#define COMPUTER_H
#include <stdlib.h>
#include "Memory.h"
#include "LiquidClearDisplay.h"
#include "Input.h"
#include "Sound.h"

#define REGISTER_SIZE 16
#define STACK_SIZE 16

#define CPU_RATE 500

unsigned char registers[16];
unsigned short index_register;
unsigned short program_counter_register;

unsigned short stack[16];
unsigned short stack_pointer;

unsigned char delay_timer;
unsigned char sound_timer; 

unsigned short opcode;

void SetupComputer();
void FetchInstruction();
void ExecuteInsruction(char* draw_flag);
void UpdateTimers();
void PrintRegisters();

#endif //COMPUTER_H
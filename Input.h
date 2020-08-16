#ifndef INPUT_H
#define INPUT_H
#include <SDL.h>

#define KEY_SIZE 16

unsigned char keys[KEY_SIZE];

void ClearInput();
void UpdateInput(char* running);
void PrintKeys();

#endif
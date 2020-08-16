#ifndef LCD_H
#define LCD_H
#include "Setup.h"

#define FONT_DATA_SIZE 80
#define FONT_CHARACTER_SIZE 5
#define FONT_DATA_LOCATION 0x50

unsigned char screen[WINDOW_WIDTH_RES * WINDOW_HEIGHT_RES];

extern unsigned char font_data[FONT_DATA_SIZE];

void UpdateScreen(SDL_Renderer* renderer);
void SetupScreen();

#endif //LCD_H
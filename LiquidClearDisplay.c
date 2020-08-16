#include "LiquidClearDisplay.h"

unsigned char font_data[FONT_DATA_SIZE] = {
   0xF0,0x90,0x90,0x90,0xF0, //0
   0x20,0x60,0x20,0x20,0x70, //1
   0xF0,0x10,0xF0,0x80,0xF0, //2
   0xF0,0x10,0xF0,0x10,0xF0, //3
   0x90,0x90,0xF0,0x10,0x10, //4
   0xF0,0x80,0xF0,0x10,0xF0, //5
   0xF0,0x80,0xF0,0x90,0xF0, //6
   0xF0,0x10,0x20,0x40,0x40, //7
   0xF0,0x90,0xF0,0x90,0xF0, //8
   0xF0,0x90,0xF0,0x10,0xF0, //9
   0xF0,0x90,0xF0,0x90,0x90, //A
   0xE0,0x90,0xE0,0x90,0xE0, //B
   0xF0,0x80,0x80,0x80,0xF0, //C
   0xE0,0x90,0x90,0x90,0xE0, //D
   0xF0,0x80,0xF0,0x80,0xF0, //E
   0xF0,0x80,0xF0,0x80,0x80, //F
};

void SetupScreen() {
	for (int i = 0; i < sizeof(screen); i++)
		screen[i] = 0;
}

void UpdateScreen(SDL_Renderer* renderer) {
	SDL_Rect pixel;
	pixel.w = WINDOW_SCALE;
	pixel.h = WINDOW_SCALE;

	for (int y = 0; y < WINDOW_HEIGHT_RES; y++) {
		for (int x = 0; x < WINDOW_WIDTH_RES; x++) {
			if (screen[(y * WINDOW_WIDTH_RES) + x] == 0) {
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				pixel.x = x * WINDOW_SCALE;
				pixel.y = y * WINDOW_SCALE;

				SDL_RenderFillRect(renderer, &pixel);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				pixel.x = x * WINDOW_SCALE;
				pixel.y = y * WINDOW_SCALE;

				SDL_RenderFillRect(renderer, &pixel);
			}
		}
	}
}
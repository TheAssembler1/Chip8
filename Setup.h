#ifndef SETUP_H
#define SETUP_H
#include <stdio.h>
#include <SDL.h>

#define WINDOW_WIDTH_RES 64
#define WINDOW_HEIGHT_RES 32

#define WINDOW_SCALE 18

#define WINDOW_WIDTH (WINDOW_WIDTH_RES * WINDOW_SCALE)
#define WINDOW_HEIGHT (WINDOW_HEIGHT_RES * WINDOW_SCALE)

#define SCREEN_FPS 60
#define GAMETITLE "../Chip8/Games/MISSILE"

void Setup();
SDL_Window* CreateWindow();
SDL_Renderer* CreateRenderer(SDL_Window* window);

#endif //SETUP_H
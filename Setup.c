#include "Setup.h"

void Setup() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		printf("Unable to init SDL!");
}

SDL_Window* CreateWindow() {
	SDL_Window* window;

	window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_SetWindowSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	if (window == NULL)
		printf("Unable to create window!");

	return window;
}

SDL_Renderer* CreateRenderer(SDL_Window* window) {
	SDL_Renderer* renderer;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
		printf("Unable to create renderer!");

	return renderer;
}
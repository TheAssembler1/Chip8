#include <stdio.h>
#include <SDl.h>
#include "Setup.h"
#include "Memory.h"
#include "Computer.h"
#include "Timer.h"
#include "LiquidClearDisplay.h"
#include "Input.h"
#include "Sound.h"

int main(int arc, char* argv[]) {
	SDL_Window* window;
	SDL_Renderer* renderer;
	char running;
	char draw_flag;

	uint64_t frame_ticks;
	struct Timer fps_timer;
	struct Timer cap_timer;
	float avg_fps;
	int counted_frames;
	const float SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	Setup();
	SetupSound();

	window = CreateWindow();
	renderer = CreateRenderer(window);
	running = 1;

	SetupMemory();
	LoadGame("../Chip8/Games/INVADERS");
	DumpMemory();

	SetupComputer();

	Timer_Init(&fps_timer);
	Timer_Init(&cap_timer);
	avg_fps = 0;
	counted_frames = 0;

	ClearInput();
	SetupScreen();

	draw_flag = 0;

	while (running) {
		Timer_Start(&cap_timer);
		Timer_Part_One(&avg_fps, counted_frames, fps_timer);


		if (draw_flag == 1) {
			SDL_RenderClear(renderer);
			UpdateScreen(renderer);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderPresent(renderer);
		}

		FetchInstruction();
		draw_flag = 0;
		ExecuteInsruction(&draw_flag);

		UpdateTimers();
		UpdateInput(&running);

		Timer_Part_Two(&frame_ticks, &counted_frames, SCREEN_TICKS_PER_FRAME, cap_timer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	CleanupSound();

	return 0;
}
#include <stdio.h>
#include <SDl.h>
#include "Setup.h"
#include "Memory.h"
#include "Computer.h"
#include "LiquidClearDisplay.h"
#include "Input.h"
#include "Sound.h"

int main(int arc, char* argv[]) {
	SDL_Window* window;
	SDL_Renderer* renderer;
	char running;
	char draw_flag;

	Setup();
	SetupSound();

	window = CreateWindow();
	renderer = CreateRenderer(window);
	running = 1;

	SetupMemory();
	LoadGame(GAMETITLE);
	DumpMemory();

	SetupComputer();

	ClearInput();
	SetupScreen();

	draw_flag = 0;

	int current_time = SDL_GetPerformanceCounter();
	int last_time = 0;
	double delta_time = 0;
	double time_elapsed = 0;
	double cpu_time_elapsed = 0;

	while (running) {

		last_time = current_time;
		current_time = SDL_GetPerformanceCounter();
		delta_time = (((double)current_time - last_time) * 1000 / (double)SDL_GetPerformanceFrequency());
		time_elapsed += delta_time;
		cpu_time_elapsed = time_elapsed;

		if (time_elapsed > 1000/SCREEN_FPS) {
			time_elapsed = 0;
			UpdateTimers();
		}

		if (cpu_time_elapsed > 1000/CPU_RATE) {
			cpu_time_elapsed = 0;

			if (draw_flag == 1) {
				SDL_RenderClear(renderer);
				UpdateScreen(renderer);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderPresent(renderer);

				//wait for draw instruction to finish
				SDL_Delay(16);
			}

			FetchInstruction();
			draw_flag = 0;
			ExecuteInsruction(&draw_flag);

			UpdateInput(&running);
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	CleanupSound();

	return 0;
}
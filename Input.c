#include "Input.h"

void ClearInput() {
	for (int i = 0; i < KEY_SIZE; i++)
		keys[i] = 0;
}

void PrintKeys(){
	for (int i = 0; i < KEY_SIZE; i++) {
		printf("KEY NUMBER %d is set to %d \n", i, keys[i]);
	}
}

void UpdateInput(char* running) {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) 
			*running = 0;

		if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_1:
				keys[0] = 0;
				break;
			case SDLK_2:
				keys[1] = 0;
				break;
			case SDLK_3:
				keys[2] = 0;
				break;
			case SDLK_4:
				keys[3] = 0;
				break;
			case SDLK_q:
				keys[4] = 0;
				break;
			case SDLK_w:
				keys[5] = 0;
				break;
			case SDLK_e:
				keys[6] = 0;
				break;
			case SDLK_r:
				keys[7] = 0;
				break;
			case SDLK_a:
				keys[8] = 0;
				break;
			case SDLK_s:
				keys[9] = 0;
				break;
			case SDLK_d:
				keys[10] = 0;
				break;
			case SDLK_f:
				keys[11] = 0;
				break;
			case SDLK_z:
				keys[12] = 0;
				break;
			case SDLK_x:
				keys[13] = 0;
				break;
			case SDLK_c:
				keys[14] = 0;
				break;
			case SDLK_v:
				keys[15] = 0;
				break;
			}
		}

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_1:
					keys[0] = 1;
					break;
				case SDLK_2:
					keys[1] = 1;
					break;
				case SDLK_3:
					keys[2] = 1;
					break;
				case SDLK_4:
					keys[3] = 1;
					break;
				case SDLK_q:
					keys[4] = 1;
					break;
				case SDLK_w:
					keys[5] = 1;
					break;
				case SDLK_e:
					keys[6] = 1;
					break;
				case SDLK_r:
					keys[7] = 1;
					break;
				case SDLK_a:
					keys[8] = 1;
					break;
				case SDLK_s:
					keys[9] = 1;
					break;
				case SDLK_d:
					keys[10] = 1;
					break;
				case SDLK_f:
					keys[11] = 1;
					break;
				case SDLK_z:
					keys[12] = 1;
					break;
				case SDLK_x:
					keys[13] = 1;
					break;
				case SDLK_c:
					keys[14] = 1;
					break;
				case SDLK_v:
					keys[15] = 1;
					break;
			}
		}
	}
}
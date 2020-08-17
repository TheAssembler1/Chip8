#include "Sound.h"

void SetupSound() {
	if (SDL_LoadWAV("../Chip8/Sounds/beep.wav", &wav_spec, &wav_buffer, &wav_length) == NULL) {
		printf("ERROR:Could not load audio file\n");
		printf(SDL_GetError());
		exit(-1);
	}
	device_id = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
}

void PlayBeep() {
	int success = SDL_QueueAudio(device_id, wav_buffer, wav_length);
	SDL_PauseAudioDevice(device_id, 0);
}

void StopBeep() {
	SDL_PauseAudioDevice(device_id, 1);
}

void CleanupSound() {
	SDL_CloseAudioDevice(device_id);
	SDL_FreeWAV(wav_buffer);
}
#ifndef SOUND_H
#define SOUND_H
#include <SDL.h>

SDL_AudioSpec wav_spec;
SDL_AudioDeviceID device_id;
int wav_length;
int* wav_buffer;

void SetupSound();
void PlayBeep();
void StopBeep();
void CleanupSound();

#endif
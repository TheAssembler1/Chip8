#include "Timer.h"

void Timer_Init(struct Timer* timer) {
	timer->timer_started = false;
	timer->timer_paused = false;
	timer->timer_start_ticks = 0;
	timer->timer_paused_ticks = 0;
}

void Timer_Start(struct Timer* timer) {
	timer->timer_started = true;
	timer->timer_paused = false;
	timer->timer_start_ticks = SDL_GetTicks();
	timer->timer_paused_ticks = 0;
}

uint32_t Timer_Get_Ticks(struct Timer* timer) {
	uint32_t time = 0;
	if (timer->timer_started) {
		if (timer->timer_paused) {
			time = timer->timer_paused_ticks;
		}
		else {
			time = SDL_GetTicks() - timer->timer_start_ticks;
		}
	}
	return time;
}

void Timer_Part_One(float* avg_fps, uint64_t counted_frames, struct Timer fps_timer) {
	*avg_fps = counted_frames / (Timer_Get_Ticks(&fps_timer) / 1000.f);
	if (avg_fps > 2000000) {
		*avg_fps = 0;
	}
}

void Timer_Part_Two(uint64_t* frame_ticks, uint64_t* counted_frames, const float SCREEN_TICKS_PER_FRAME, struct Timer cap_timer) {
	(*counted_frames) += 1;
	*frame_ticks = Timer_Get_Ticks(&cap_timer);
	if (*frame_ticks < SCREEN_TICKS_PER_FRAME) {
		SDL_Delay(SCREEN_TICKS_PER_FRAME - *frame_ticks);
	}
}
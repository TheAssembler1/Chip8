#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>
#include <stdbool.h>

struct Timer {
	bool timer_started;
	bool timer_paused;

	uint32_t timer_start_ticks;
	uint32_t timer_paused_ticks;
};
void Timer_Init(struct Timer* timer);
void Timer_Start(struct Timer* timer);
uint32_t Timer_Get_Ticks(struct Timer* timer);
void Timer_Part_One(float* avg_fps, uint64_t counted_frames, struct Timer fps_timer);
void Timer_Part_Two(uint64_t* frame_ticks, uint64_t* counted_frames, const float SCREEN_TICKS_PER_FRAME, struct Timer cap_timer);

#endif //TIMER_H
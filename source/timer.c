#include "timer.h"

void tick(Timer* timer) {
    timer->currentTicks = SDL_GetPerformanceCounter();
    Uint64 delta = timer->currentTicks - timer->previousTicks;
    timer->previousTicks = timer->currentTicks;
    timer->ticksPerSecond = SDL_GetPerformanceFrequency();
    timer->deltaTime = (double) delta / (double) timer->ticksPerSecond;
    if (timer->deltaTime > 5) {
        timer->deltaTime = 5;       // Limit the max amount of delta time in the event of really poor performance
    }
}
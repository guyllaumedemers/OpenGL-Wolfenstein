//
// Created by gdemers on 12/9/2020.
//

#include "Timer.h"

Timer::Timer() {
    startTime = 0;
}

Timer::~Timer() {

}

void Timer::restart() {
    startTime = SDL_GetTicks();
}

Uint32 Timer::getStart() {
    return startTime;
}

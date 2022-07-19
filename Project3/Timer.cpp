#include "Timer.h"

Timer::Timer() {
    resetted = true;
    running = false;
    beg = 0;
    end = 0;
}
void Timer::Start() {
    if (!running) {
        if (resetted)
            beg = (unsigned long)clock();
        else
            beg -= end - (unsigned long)clock();
        running = true;
        resetted = false;
    }
}
void Timer::Stop() {
    if (running) {
        end = (unsigned long)clock();
        running = false;
    }
}
void Timer::Reset() {
    bool wereRunning = running;
    if (wereRunning)
        Stop();
    resetted = true;
    beg = 0;
    end = 0;
    if (wereRunning)
        Start();
}
bool Timer::IsRunning() {
    return running;
}
unsigned long Timer::GetTime() {
    if (running)
        return ((unsigned long)clock() - beg) / CLOCKS_PER_SEC;
    else
        return end - beg;
}
bool Timer::IsOver(unsigned long seconds) {
    return seconds >= GetTime();
}

#pragma once
#include <time.h>
#include <conio.h>

class Timer {

    bool resetted;
    bool running;
    unsigned long beg;
    unsigned long end;

public:
    Timer();
    void Start();
    void Stop();
    void Reset();
    bool IsRunning();
    unsigned long GetTime();
    bool IsOver(unsigned long seconds);
};


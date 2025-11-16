#pragma once
#include <chrono>

class Timer
{
private:
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer()
    {
        start();
    }
    void start()
    {
        start_time = chrono::high_resolution_clock::now();
    }
    double elapsed_ms()
    {
        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end_time - start_time;
        return duration.count();
    }
};
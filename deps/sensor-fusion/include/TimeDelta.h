// This file is a part of embed-sensor-fusion project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <chrono>


struct TimeDelta
{
    using Float = double;

    TimeDelta()
            : previousTimePoint(std::chrono::system_clock::now())
    {
    }

    void reset()
    {
        previousTimePoint = std::chrono::system_clock::now();
    }

    Float get()
    {
        std::chrono::time_point<std::chrono::system_clock> timePoint = std::chrono::system_clock::now();
        Float seconds = static_cast<Float>(std::chrono::duration_cast<std::chrono::microseconds>(timePoint - previousTimePoint).count()) / static_cast<Float>(1'000'000);
        previousTimePoint = timePoint;
        return seconds;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> previousTimePoint;
};

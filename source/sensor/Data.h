// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <math/MathTypes.h>


namespace sensor {
struct Data
{
    V3 accelerometer;
    V3 gyroscope;
    V3 magnetometer;
};
}
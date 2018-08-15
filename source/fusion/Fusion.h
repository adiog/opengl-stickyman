// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <fusion/Data.h>
#include <sensor/Data.h>


namespace fusion {
struct Fusion
{
    virtual fusion::Data apply(const sensor::Data &data) = 0;
};
}
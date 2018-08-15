// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.


#include "Data.h"
#include "Fusion.h"
#include <sensor/Data.h>


namespace fusion {
struct Kalman : public Fusion
{
    fusion::Data apply(const sensor::Data &data) override
    {
        return fusion::Data{};
    }
};
}

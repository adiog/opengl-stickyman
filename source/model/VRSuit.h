// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <unordered_map>
#include <bio/Medium.h>
#include <bio/Model.h>
#include <sensor/Sensor.h>

namespace model {

class VRSuit
{
public:
    VRSuit(const bio::Medium& medium)
            : model(medium.getModel())
    {
    }

    void update(bio::Segment segment, sensor::Data data)
    {
        sensorCollection[segment].update(data);
    }

private:
    bio::Model model;
    std::unordered_map<bio::Segment, sensor::Sensor> sensorCollection;
};
}
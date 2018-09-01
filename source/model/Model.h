// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <unordered_map>
#include <model/Layout.h>
#include <sensor/Sensor.h>


namespace model {
struct Model : public std::unordered_map<bio::Segment, sensor::Sensor>
{
    Layout getLayout()
    {
        Layout layout;
        for(auto &sensorEntry : *this)
        {
            layout.segmentLayout.emplace(std::make_pair(sensorEntry.first, sensorEntry.second.get().arrow));
        }
        return layout;
    }
};
}
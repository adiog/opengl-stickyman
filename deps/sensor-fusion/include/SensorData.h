// This file is a part of embed-sensor-fusion project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <glm/glm.hpp>


namespace sensorFusion {
struct SensorData
{
    glm::vec3 accelerometer;
    glm::vec3 gyroscope;
    glm::vec3 magnetometer;
};
}

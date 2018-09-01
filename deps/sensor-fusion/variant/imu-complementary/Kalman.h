// This file is a part of embed-sensor-fusion project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include "KalmanImpl.h"
#include <KalmanImpl.h>
#include <SensorFusion.h>
#include <TimeDelta.h>

namespace sensorFusion {
struct Complementary : public SensorFusion
{
    void initialize(const SensorData &sensorData) override
    {
        Float roll = getRoll(sensorData.accelerometer);
        Float pitch = getPitch(sensorData.accelerometer);

        compAngleX = roll;
        compAngleY = pitch;
    }

    FusionData apply(const SensorData &sensorData) override
    {
        Float dt = timeDelta.get();

        Float roll = getRoll(sensorData.accelerometer);
        Float pitch = getPitch(sensorData.accelerometer);

        Float gyroXrate = sensorData.gyroscope[0] / 131.0;  // Convert to deg/s
        Float gyroYrate = sensorData.gyroscope[1] / 131.0;  // Convert to deg/s

        // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
        if ((roll < -90 && compAngleX > 90) || (roll > 90 && compAngleX < -90))
        {
            compAngleX = roll;
        }

        if (abs(compAngleX) > 90)
        {
            gyroYrate = -gyroYrate;  // Invert rate, so it fits the restriced accelerometer reading
        }

        compAngleX = 0.93 * (compAngleX + gyroXrate * dt) + 0.07 * roll;  // Calculate the angle using a Complimentary filter
        compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch;

        return FusionData{{compAngleX, compAngleY, 0}};
    }

private:
    Float compAngleX;
    Float compAngleY;

    TimeDelta timeDelta;
};
}

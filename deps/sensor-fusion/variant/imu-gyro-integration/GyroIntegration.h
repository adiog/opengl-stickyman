// This file is a part of embed-sensor-fusion project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <SensorFusion.h>
#include <TimeDelta.h>

namespace sensorFusion {
struct GyroIntegration : public SensorFusion
{
    void initialize(const SensorData &sensorData) override
    {
        Float roll = getRoll(sensorData.accelerometer);
        Float pitch = getPitch(sensorData.accelerometer);

        gyroXAngle = roll;
        gyroYAngle = pitch;
    }

    FusionData apply(const SensorData &sensorData) override
    {
        Float dt = timeDelta.get();

        Float roll = getRoll(sensorData.accelerometer);
        Float pitch = getPitch(sensorData.accelerometer);

        Float gyroXrate = sensorData.gyroscope[0] / 131.0;  // Convert to deg/s
        Float gyroYrate = sensorData.gyroscope[1] / 131.0;  // Convert to deg/s

        // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
        if ((roll < -90 && gyroXAngle > 90) || (roll > 90 && gyroXAngle < -90))
        {
            gyroXAngle = roll;
        }

        if (abs(gyroXAngle) > 90)
        {
            gyroYrate = -gyroYrate;  // Invert rate, so it fits the restriced accelerometer reading
        }

        gyroXAngle += gyroXrate * dt;  // Calculate gyro angle without any filter
        gyroYAngle += gyroYrate * dt;

        // Reset the gyro angle when it has drifted too much
        if (gyroXAngle < -180 || gyroXAngle > 180)
            gyroXAngle = getRoll(sensorData.accelerometer);
        if (gyroYAngle < -180 || gyroYAngle > 180)
            gyroYAngle = getPitch(sensorData.accelerometer);

        return FusionData{{gyroXAngle, gyroYAngle, 0}};
    }

private:
    Float gyroXAngle;
    Float gyroYAngle;

    TimeDelta timeDelta;
};
}

// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <memory>
#include <mutex>
#include <bio/Segment.h>
#include <fusion/Data.h>
#include <fusion/Fusion.h>
#include <fusion/Kalman.h>
#include <sensor/Calibrator.h>
#include <sensor/Data.h>


namespace sensor {
class Sensor
{
public:
    Sensor(bio::Segment segment = bio::Segment::Head)
            : segment(segment)
            , aFusion(std::make_unique<fusion::Kalman>())
    {
    }

    void calibrate(CalibrationStep calibrationStep)
    {
        std::unique_lock<std::mutex> sensorLock{sensorMutex};
        calibrator.calibrate(rawData.accelerometer, calibrationStep);
    }

    void update(Data rawData)
    {
        std::unique_lock<std::mutex> sensorLock{sensorMutex};
        this->rawData = rawData;
        this->data = calibrator.transform(rawData);
        fusionData = aFusion->apply(this->data);
    }

    fusion::Data get()
    {
        std::unique_lock<std::mutex> sensorLock{sensorMutex};
        return fusionData;
    }

private:
    std::mutex sensorMutex;
    bio::Segment segment;
    sensor::Data rawData;
    sensor::Data data;
    fusion::Data fusionData;
    Calibrator calibrator;
    std::unique_ptr<fusion::Fusion> aFusion;
};
}

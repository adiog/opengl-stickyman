// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <memory>
#include <bio/Segment.h>
#include <fusion/Data.h>
#include <fusion/Fusion.h>
#include <sensor/Calibrator.h>
#include <sensor/Data.h>


namespace sensor {
class Sensor
{
public:
    void calibrate(CalibrationStep calibrationStep)
    {
        calibrator.calibrate(rawData.accelerometer, calibrationStep);
    }

    void update(Data rawData)
    {
        this->rawData = rawData;
        this->data = calibrator.transform(rawData);
        fusionData = aFusion->apply(this->data);
    }

private:
    bio::Segment segment;
    sensor::Data rawData;
    sensor::Data data;
    fusion::Data fusionData;
    Calibrator calibrator;
    std::unique_ptr<fusion::Fusion> aFusion;
};
}

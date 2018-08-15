// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <math/LinearAlgebra.h>
#include <math/MathTypes.h>

#include <optional>
#include <sensor/Data.h>


namespace sensor {

enum class CalibrationStep
{
    NPose,
    SPose
};

class Calibrator
{
public:
    Calibrator()
            : calibrationMatrix(ID33)
    {
    }

    void calibrate(V3 referenceV3, CalibrationStep calibrationStep)
    {
        switch (calibrationStep)
        {
            case CalibrationStep::NPose:
                referenceZCalibrationVector = referenceV3;
                break;
            case CalibrationStep::SPose:
                referenceXZCalibrationVector = referenceV3;
                break;
        }
        if (referenceZCalibrationVector && referenceXZCalibrationVector)
        {
            calibrationMatrix = math::getCalibrationMatrix(*referenceZCalibrationVector, *referenceXZCalibrationVector);
        }
    }

    Data transform(const Data &rawData)
    {
        Data transformedData;
        transformedData.accelerometer = rawData.accelerometer * calibrationMatrix;
        transformedData.gyroscope = rawData.gyroscope * calibrationMatrix;
        transformedData.magnetometer = rawData.magnetometer * calibrationMatrix;
        return transformedData;
    }

private:
    std::optional<V3> referenceZCalibrationVector;
    std::optional<V3> referenceXZCalibrationVector;
    M33 calibrationMatrix;
};
}

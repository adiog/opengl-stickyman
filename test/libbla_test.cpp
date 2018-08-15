// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include "googletest"
#include "../source/math/LinearAlgebra.h"


TEST(libmath, reduce111)
{
    // given
    V3 v = {1, 1, 1};

    // when
    M33 mNPoseRotation = math::getRotationMatrixReducingYAndX(v);
    V3 r = v * mNPoseRotation;

    // then
    EXPECT_DOUBLE_EQ(r[X], 0.0);
    //EXPECT_DOUBLE_EQ(r[Y], 0.0);
    EXPECT_NEAR(r[Y], 0.0, 0.000000000000001);
    EXPECT_DOUBLE_EQ(r[Z], math::getNorm(v));
}

TEST(libmath, getCalibrationMatrixHuman)
{
    // given
    V3 vNPose = {1, 0, -1};
    V3 vSPose = {1, 0, 1};

    // when
    M33 mSensorToSegment = math::getCalibrationMatrix(vNPose, vSPose);

    // then
    V3 vRandomInNPosePosePlane = {1.41, 0, 0};
    V3 vRandomSegment = vRandomInNPosePosePlane * mSensorToSegment;
    Real angleSquat = atan2(vRandomSegment[0], vRandomSegment[2]);

    EXPECT_DOUBLE_EQ(angleSquat, M_PI_4);
}

TEST(libmath, getCalibrationMatrixRobot)
{
    // given
    V3 vNPose = {1/sqrt(2), 1/sqrt(2), -1};
    V3 vSPose = {1/sqrt(2), 1/sqrt(2), 1};

    // when
    M33 mSensorToSegment = math::getCalibrationMatrix(vNPose, vSPose);

    // then
    V3 vRandomInNPosePosePlane = {1.41, 0, 0};
    V3 vRandomSegment = vRandomInNPosePosePlane * mSensorToSegment;
    Real angleSquat = atan2(vRandomSegment[0], vRandomSegment[2]);

    EXPECT_DOUBLE_EQ(angleSquat, M_PI_4);
}

GTEST_MAIN()

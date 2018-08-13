// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include "googletest"
#include "libmath.h"


TEST(libmath, reduce111)
{
    // given
    V3 v = {1, 1, 1};

    // when
    M33 mNPoseRotation = getRotationMatrixReducingYAndX(v);
    V3 r = v * mNPoseRotation;

    // then
    EXPECT_EQ(getNorm(v), getNorm(r));
}

TEST(libmath, calibration)
{
    // given
    V3 vNPose = {3, 4, 1};
    V3 vSPose = {3, 4, -1};

    M33 mNPoseRotation = getRotationMatrixReducingYAndX(vNPose);
    V3 vSPosePostNPoseRotation = vSPose * mNPoseRotation;
    M33 mCalibration = getRotationMatrix(vSPosePostNPoseRotation, Z, Y);

    M33 mSensorToSegment = preventNan(mNPoseRotation * mCalibration);

    V3 vRandomInNPosePosePlane = {3, 4, 0};

    V3 vRandomSegment = preventNan(vRandomInNPosePosePlane * mSensorToSegment);
    Real angleSquat = atan2(vRandomSegment[0], vRandomSegment[2]);
}


GTEST_MAIN()

// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <algorithm>
#include <numeric>

#include <math/MathTypes.h>

M33 operator*(Real s, M33 m);
V3 operator*(Real s, V3 v);
V3 operator*(V3 v, M33 m);
M33 operator*(M33 lhs, M33 rhs);

namespace math {
M33 getRotationMatrix(Real angle, axis index);

Real getNormInf(V3 v);

Real getNormLp(V3 v, Real p);

Real getNorm(V3 v);

M33 getRotationMatrix(V3 v, axis keepIndex, axis reduceIndex);

M33 getRotationMatrixReducingYAndX(V3 v);

/** Returns calibration matrix
 *
 * @param vZ - first calibration vector V3
 * @param vXZ - second calibration vector V3
 * @return calibration matrix M33
 *
 * The calibration matrix is rotation matrix that:
 * - for vZ - supersedes X and Y axis, assuming that result vZ * M has form [0,0,Z]
 * - for vXZ - supersedes Y axis, assuming that result vXZ * M has form [X,0,Z]
 */
M33 getCalibrationMatrix(V3 vZ, V3 vXZ);
}
#ifdef DO_NOT_KNOW_HOW_TO_FLOAT
extern double epsilon;
Real preventZero(Real x);
V3 preventNan(V3 v);
M33 preventNan(M33 m);
#endif

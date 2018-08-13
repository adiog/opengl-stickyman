// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include "libbla.h"

constexpr const V3 ZERO3 = {0.0, 0.0, 0.0};
constexpr const M33 ZERO33 = {ZERO3, ZERO3, ZERO3};


#ifdef DONT_UNDERSTAND_FLOAT_ARITHMETICS

double epsilon = 0.000000001;


Real preventZero(Real x)
{
    return (fabs(x) < epsilon) ? 0.0 : x;
}

V3 preventNan(V3 v)
{
    V3 result;
    std::transform(v.cbegin(), v.cend(), result.begin(), preventZero);
    return result;
}

M33 preventNan(M33 m)
{
    M33 result;
    for (auto xIndex : I3)
    {
        for (auto yIndex : I3)
        {
            result[xIndex][yIndex] = preventZero(m[xIndex][yIndex]);
        }
    }
    return result;
}
#endif

V3 operator*(V3 v, M33 m)
{
    V3 result = ZERO3;
    for (auto resultIndex : I3)
    {
        for (auto matrixIndex : I3)
        {
            result[resultIndex] += v[matrixIndex] * m[resultIndex][matrixIndex];
        }
    }
#ifdef DONT_UNDERSTAND_FLOAT_ARITHMETICS
    return preventNan(result);
#else
    return result;
#endif
}

M33 operator*(M33 lhs, M33 rhs)
{
    M33 result = ZERO33;
    for (auto xIndex : I3)
    {
        for (auto yIndex : I3)
        {
            for (auto cellIndex : I3)
            {
                result[xIndex][yIndex] += rhs[xIndex][cellIndex] * lhs[cellIndex][yIndex];
            }
        }
    }
#ifdef DONT_UNDERSTAND_FLOAT_ARITHMETICS
    return preventNan(result);
#else
    return result;
#endif
}

M33 getRotationMatrix(Real angle, axis index)
{
    M33 result;
    switch (index) {
        case 0:
            result = M33{
                    V3{1.0, 0.0, 0.0},
                    V3{0.0, cos(angle), -sin(angle)},
                    V3{0.0, sin(angle), cos(angle)}};
            break;
        case 1:
            result = M33{
                    V3{cos(angle), 0.0, -sin(angle)},
                    V3{0.0, 1.0, 0.0},
                    V3{sin(angle), 0.0, cos(angle)}};
            break;
        case 2:
            result = M33{
                    V3{cos(angle), -sin(angle), 0.0},
                    V3{sin(angle), cos(angle), 0.0},
                    V3{0.0, 0.0, 1.0}};
            break;
    }
#ifdef DONT_UNDERSTAND_FLOAT_ARITHMETICS
    return preventNan(result);
#else
    return result;
#endif
}

Real getNormInf(V3 v)
{
    return std::accumulate(v.cbegin(), v.cend(), 0.0);
}

Real getNormLp(V3 v, Real p)
{
    V3 vp;
    std::transform(v.cbegin(), v.cend(), vp.begin(), [p](Real x) { return pow(x, p); });
    return pow(std::accumulate(vp.cbegin(), vp.cend(), 0.0), 1.0 / p);
}

Real getNorm(V3 v)
{
    return getNormLp(v, 2.0);
}

M33 getRotationMatrix(V3 v, axis keepIndex, axis reduceIndex)
{
    Real dir = (reduceIndex == Y) ? -1.0 : ((reduceIndex == Z) ? -1.0 : 1.0);
    Real x = v[reduceIndex];
    Real y = getNormInf(v) - v[reduceIndex] - v[keepIndex];
    Real angle = dir * atan2(x, y);
    return getRotationMatrix(angle, keepIndex);
}

M33 getRotationMatrixReducingYAndX(V3 v)
{
#ifdef DONT_UNDERSTAND_FLOAT_ARITHMETICS
    M33 supersedeYKeepZRotation = preventNan(getRotationMatrix(v, Z, Y));
    V3 supersedeYKeepZVector = preventNan(v * supersedeYKeepZRotation);
    M33 supersedeXRotation = preventNan(getRotationMatrix(supersedeYKeepZVector, Y, X));
    V3 test = preventNan(supersedeYKeepZVector * supersedeXRotation);
    return preventNan(supersedeYKeepZRotation * supersedeXRotation);
#else
    M33 supersedeYKeepZRotation = getRotationMatrix(v, Z, Y);
    V3 supersedeYKeepZVector = v * supersedeYKeepZRotation;
    M33 supersedeXRotation = getRotationMatrix(supersedeYKeepZVector, Y, X);
    V3 test = supersedeYKeepZVector * supersedeXRotation;
    return supersedeYKeepZRotation * supersedeXRotation;
#endif
}

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
M33 getCalibrationMatrix(V3 vZ, V3 vXZ)
{
    M33 vZCalibrationMatrix = getRotationMatrixReducingYAndX(vZ);
    V3 vXZSubCalibrated = vXZ * vZCalibrationMatrix;
    M33 vXZCalibrationMatrix = getRotationMatrix(vXZSubCalibrated, Z, Y);

    return vZCalibrationMatrix * vXZCalibrationMatrix;
}

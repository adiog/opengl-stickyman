// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include "libmath.h"


double epsilon = 0.0000001;

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

V3 operator*(V3 v, M33 m)
{
    V3 result;
    for (auto resultIndex : I3)
    {
        for (auto matrixIndex : I3)
        {
            result[resultIndex] += v[matrixIndex] * m[resultIndex][matrixIndex];
        }
    }
    return result;
    //preventNan(result);
}

M33 operator*(M33 lhs, M33 rhs)
{
    M33 result;
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
    return result;
    //preventNan(result);
}

M33 getRotationMatrix(Real angle, axis index)
{
    M33 result;
    switch (index)
    {
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
    return result;
    //    return preventNan(result);
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
    M33 supersedeYKeepZRotation = preventNan(getRotationMatrix(v, Z, Y));
    V3 supersedeYKeepZVector = preventNan(v * supersedeYKeepZRotation);
    M33 supersedeXRotation = preventNan(getRotationMatrix(supersedeYKeepZVector, Y, X));
    V3 test = supersedeYKeepZVector * supersedeXRotation;
    return preventNan(supersedeYKeepZRotation * supersedeXRotation);
}

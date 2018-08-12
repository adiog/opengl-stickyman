// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <cmath>
#include <numeric>


#define X 0
#define Y 1
#define Z 2

#define I3      \
    {           \
        0, 1, 2 \
    }


using axis = uint8_t;

using Real = double;

template <typename T>
using V2T = std::array<T, 2>;

using V2 = V2T<Real>;

template <typename T>
using M22T = V2T<V2T<T>>;

using M22 = M22T<Real>;

template <typename T>
using V3T = std::array<T, 3>;

using V3 = V3T<Real>;

template <typename T>
using M33T = V3T<V3T<T>>;

using M33 = M33T<Real>;

double epsilon = 0.0000001;

Real preventZeroNan(Real x)
{
    return abs(x) < epsilon ? 0.0 : x;
}


V3 preventNan(V3 v)
{
    V3 result;
    std::transform(v.cbegin(), v.cend(), result.begin(), preventZeroNan);
    return result;
}

M33 preventNan(M33 m)
{
    M33 result;
    for (auto xIndex : I3)
    {
        for (auto yIndex : I3)
        {
            result[xIndex][yIndex] = preventZeroNan(m[xIndex][yIndex]);
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
}

M33 getRotationMatrix(Real angle, axis index)
{
    switch (index)
    {
        case 0:
            return M33{
                V3{1.0, 0.0, 0.0},
                V3{0.0, cos(angle), -sin(angle)},
                V3{0.0, sin(angle), cos(angle)}};
        case 1:
            return M33{
                V3{cos(angle), 0.0, -sin(angle)},
                V3{0.0, 1.0, 0.0},
                V3{sin(angle), 0.0, cos(angle)}};
        case 2:
            return M33{
                V3{cos(angle), -sin(angle), 0.0},
                V3{sin(angle), cos(angle), 0.0},
                V3{0.0, 0.0, 1.0}};
    }
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

M33 getRotationMatrix(V3 v, int dir, axis keepIndex, axis reduceIndex)
{
    Real x = v[reduceIndex];
    Real y = getNormInf(v) - v[reduceIndex] - v[keepIndex];
    Real angle = dir * atan2(x, y);
    return getRotationMatrix(angle, keepIndex);
}

M33 getRotationMatrixReducingYAndX(V3 v)
{
    M33 supersedeYKeepZRotation = preventNan(getRotationMatrix(v, -1.0, Z, Y));
    V3 supersedeYKeepZVector = preventNan(v * supersedeYKeepZRotation);
    M33 supersedeXRotation = preventNan(getRotationMatrix(supersedeYKeepZVector, 1.0, Y, X));
    V3 test = supersedeYKeepZVector * supersedeXRotation;
    return preventNan(supersedeYKeepZRotation * supersedeXRotation);
}
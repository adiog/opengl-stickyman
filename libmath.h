// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <cmath>
#include <numeric>
#include <cstdint>
#include <array>
#include <algorithm>


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

extern double epsilon;

Real preventZero(Real x);
V3 preventNan(V3 v);
M33 preventNan(M33 m);
V3 operator*(V3 v, M33 m);
M33 operator*(M33 lhs, M33 rhs);
M33 getRotationMatrix(Real angle, axis index);
Real getNormInf(V3 v);
Real getNormLp(V3 v, Real p);
Real getNorm(V3 v);
M33 getRotationMatrix(V3 v, axis keepIndex, axis reduceIndex);
M33 getRotationMatrixReducingYAndX(V3 v);


// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <array>
#include <cmath>
#include <cstdint>


extern const int X;
extern const int Y;
extern const int Z;

extern const std::array<int, 3> I3;

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

extern const V3 ZERO3;
extern const V3 I3X;
extern const V3 I3Y;
extern const V3 I3Z;
extern const M33 ZERO33;
extern const M33 ID33;



// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.


#include "MathTypes.h"

const int X = 0;
const int Y = 1;
const int Z = 2;

constexpr const std::array<int, 3> I3 = {X, Y, Z};

constexpr const V3 ZERO3 = {0.0, 0.0, 0.0};
constexpr const V3 I3X = {1.0, 0.0, 0.0};
constexpr const V3 I3Y = {0.0, 1.0, 0.0};
constexpr const V3 I3Z = {0.0, 0.0, 1.0};
constexpr const M33 ZERO33 = {ZERO3, ZERO3, ZERO3};
constexpr const M33 ID33 = {I3X, I3Y, I3Z};


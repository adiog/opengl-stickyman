// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <string>
#include <vector>

namespace network {
struct Datagram
{
    std::string sender;
    std::vector<uint8_t> payload;
};
}
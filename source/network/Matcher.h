// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include "Datagram.h"
#include <bio/Segment.h>


namespace network {
struct Matcher
{
    static bio::Segment match(Datagram& datagram)
    {
        return bio::Segment{};
    }
};
}

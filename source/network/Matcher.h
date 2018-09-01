// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <udpbox.h>
#include <model/Model.h>


namespace network {
struct Matcher
{
    static bio::Segment match(const udpbox::Datagram& datagram)
    {
        static std::unordered_map<std::string, bio::Segment> mapping = {
                std::make_pair(std::string("192.168.0.102"), bio::Segment::Head)
        };
        return mapping[datagram.sender];
    }
};
}

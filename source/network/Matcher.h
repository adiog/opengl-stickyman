// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <udpbox.h>
#include <model/Model.h>


namespace network {
struct Matcher
{
    static model::Element match(const udpbox::Datagram& datagram)
    {
        static std::unordered_map<std::string, model::Element> mapping = {
            std::make_pair(std::string("192.168.0.102"), model::Element::Sensor0),
            std::make_pair(std::string("192.168.0.103"), model::Element::Sensor1),
            std::make_pair(std::string("192.168.0.104"), model::Element::Sensor2)};
        return mapping[datagram.sender];
    }
};
}

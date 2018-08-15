// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.


#pragma once

#include <sensor/Data.h>
#include "Datagram.h"

namespace network {
struct Dispatcher
{
    static sensor::Data dispatch(network::Datagram &datagram)
    {
        return sensor::Data{};
    }
};
}

// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <functional>
#include <network/Datagram.h>


using OnDatagramCallback = std::function<void(network::Datagram&&)>;

namespace network {
struct Server
{
    void start() {}

    void onDatagram(OnDatagramCallback onDatagramCallback) {}
};
}
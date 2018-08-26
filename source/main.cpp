// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <bio/Bio4.h>
#include <model/VRSuit.h>
#include <network/Dispatcher.h>
#include <network/Matcher.h>
#include <network/Server.h>
#include <opengl/RigidRenderer.h>
#include <opengl/opengl-stickyman.h>


int main(int argc, char**argv)
{
    main_(argc, argv);

    model::VRSuit vrsuit(bio::Bio4{});
    opengl::RigidRenderer rigidRenderer;
    network::Server server;
    server.onDatagram([&](network::Datagram&& datagram) {
        bio::Segment segment = network::Matcher::match(datagram);
        sensor::Data data = network::Dispatcher::dispatch(datagram);
        vrsuit.update(segment, data);
        rigidRenderer.render(vrsuit);
    });
    server.start();
    return 0;
}
// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include "Tracker.h"
#include <component/Axis.h>
#include <component/Floor.h>
#include <opengl/ContextPreserver.h>
#include <model/Layout.h>


namespace component {
struct Scene
{
    Scene() : tracker(model::Element::Sensor0, 1.0, 0.3) {}

    Floor floor;
    Tracker tracker;
    model::Layout layout;

    void apply(model::Layout&& newLayout)
    {
        layout = std::forward<model::Layout>(newLayout);
    }

    void render()
    {
        Axis::render();
        floor.render();
        tracker.render(layout);
    }
};
}
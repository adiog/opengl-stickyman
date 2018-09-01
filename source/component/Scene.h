// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <component/Axis.h>
#include <component/Floor.h>
#include <component/Skeleton.h>
#include <model/Layout.h>
#include <opengl/ContextPreserver.h>


namespace component {
struct Scene
{
    Floor floor;
    Skeleton skeleton;

    model::Layout layout;

    void apply(model::Layout&& newLayout)
    {
        layout = newLayout;
    }

    void render()
    {
        Axis::render();
        floor.render();
        skeleton.render(layout);
    }
};
}
// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include "Bone.h"
#include "opengl/ContextPreserver.h"
#include <functional>
#include <vector>
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>
#include <math/MathTypes.h>
#include <model/Layout.h>


namespace component {
struct BoneSequence
{
    std::vector<std::reference_wrapper<Bone>> description;

    void setStartingPoint(glm::vec3 v3)
    {
        position = v3;
    }

    void setDirection(Real angle, glm::vec3 v3)
    {
        this->angle = angle;
        direction = v3;
    }

    Real angle;
    glm::vec3 position;
    glm::vec3 direction;

    void follow()
    {
        glTranslatef(position[X], position[Y], position[Z]);
        glRotatef(angle, direction[0], direction[1], direction[2]);
    }

    void render(const model::Layout & layout)
    {
        ContextPreserver contextPreserver;
        follow();
        for (Bone &bone : description)
        {
            bone.render(layout);
            bone.follow();
        }
    }
};
}

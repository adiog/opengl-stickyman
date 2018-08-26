// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once


#include <math/MathTypes.h>
#include <vector>
#include "Bone.h"
#include <functional>

struct BoneSequence
{
    virtual void draw() = 0;

    V3 startingPoint;
    std::vector<std::reference_wrapper<Bone>> description;
};

struct Spine : public BoneSequence
{
    void follow(V3 point)
    {}

    void draw()
    {
        follow(startingPoint);
        glRotated(90, 0.0, 1.0, 0.0);
        for(Bone& bone : description)
        {
            bone.draw();
            bone.follow();
        }
    }
};

struct Limb : public BoneSequence
{
    void follow(V3 point)
    {}

    void draw()
    {
        follow(startingPoint);
        glRotated(90, 0.0, 1.0, 0.0);
        for(Bone& bone : description)
        {
            bone.draw();
            bone.follow();
        }
    }
};

// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <GL/glu.h>
#include <math/MathTypes.h>
#include <model/Layout.h>

namespace component {
class Bone
{
public:
    static constexpr const Real thicknessRatio = 0.15;
    Real thickness;
    Real lengthPart;
    Real lengthRemain;

    Bone(bio::Segment segment, Real length, Real weight)
            : segment(segment)
            , length(length)
            , weight(weight)
    {
        thickness = length * thicknessRatio;
        lengthPart = length * weight;
        lengthRemain = length * (1.0F - weight);
    }

    Real getThickness()
    {
        return thickness;
    }

    Real getThicknessOffset()
    {
        return lengthPart;
    }

    void render(const model::Layout & layout)
    {
        ContextPreserver contextPreserver;
        auto it = layout.segmentLayout.find(segment);
        if(it != layout.segmentLayout.end())
        {
            glRotatef(it->second[0], 1, 0, 0);
        }
        gluCylinder(quads[0].get(), 0.0, thickness, lengthPart, 10, 10);
        glTranslatef(0.0, 0.0, lengthPart);
        gluCylinder(quads[1].get(), thickness, 0.0, lengthRemain, 10, 10);
    }

    void follow()
    {
        glTranslatef(0.0, 0.0, length);
    }

private:
    bio::Segment segment;
    Real length;
    Real weight;

    opengl::Quad quads[2];
};
}
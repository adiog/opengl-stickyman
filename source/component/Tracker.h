// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <glm/vec3.hpp>
#include <math/MathTypes.h>
#include <model/Element.h>
#include <opengl/Quad.h>
#include <model/Layout.h>

namespace component {
class Tracker
{
public:
    static constexpr const Real thicknessRatio = 0.10;
    Real thickness;
    Real lengthPart;
    Real lengthRemain;

    Tracker(model::Element element, Real length, Real weight)
            : element(element)
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
        glPushMatrix();
        auto it = layout.find(element);
        if (it != layout.end())
        {
            glRotatef(it->second[0], 1, 0, 0);
        }
        gluCylinder(quads[0].get(), 0.0, thickness, lengthPart, 4, 4);
        glTranslatef(0.0, 0.0, lengthPart);
        gluCylinder(quads[1].get(), thickness, 0.0, lengthRemain, 10, 10);
        glPopMatrix();
    }

    void follow()
    {
        glTranslatef(0.0, 0.0, length);
    }

private:
    model::Element element;
    Real length;
    Real weight;

    opengl::Quad quads[2];
};
}

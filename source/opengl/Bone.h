// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <GL/glu.h>
#include <math/MathTypes.h>


class Bone
{
public:
    Bone(Real length, Real weight)
            : length(length)
            , weight(weight)
    {
        for (auto partIndex : {0, 1})
        {
            gluObject[partIndex] = gluNewQuadric();
            gluQuadricTexture(gluObject[partIndex], GL_TRUE);
            gluQuadricDrawStyle(gluObject[partIndex], GLU_FILL);
        }
    }

    void draw()
    {
        glPushMatrix();
        glTranslatef(0.0, 0.0, 20.0);
        Real diameter = length * 0.15;
        Real lengthPart = length * weight;
        Real lengthRemain = length * (1.0 - weight);
        gluCylinder(gluObject[0], 0.0, diameter, lengthPart, 10, 10);
        glTranslatef(0.0, 0.0, lengthPart);
        gluCylinder(gluObject[1], diameter, 0.0, lengthRemain, 10, 10);
        glPopMatrix();
    }

    void follow()
    {

        glTranslatef(0.0, 0.0, length);
    }

private:
    Real length;
    Real weight;

    GLUquadricObj *gluObject[2];

};



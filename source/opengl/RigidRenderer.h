// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <model/VRSuit.h>
#include <GL/glu.h>

void rotateX(Real angle)
{
    glRotated(angle, 1.0, 0.0, 0.0);
}

void rotateY(Real angle)
{
    glRotated(angle, 0.0, 1.0, 0.0);
}

void rotateZ(Real angle)
{
    glRotated(angle, 0.0, 0.0, 1.0);
}

void drawFloor(GLUquadricObj * floor)
{
    rotateX(180);
    gluCylinder(floor, 2.0, 2.0, 0.1, 1, 1);
}

namespace opengl {
class RigidRenderer
{
public:
    void render(const model::VRSuit& suit)
    {
    }
    GLUquadricObj *floor;
};
}

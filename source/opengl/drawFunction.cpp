// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include "drawFunction.h"

#include <GL/glut.h>
#include <math/MathTypes.h>
#include "globals.h"
#include "opengl-stickyman.h"


void drawArrow(int axis)
{
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    gluCylinder(sensorArrow[axis], 1.0, 1.0, 10.0, 10, 10);
    glTranslatef(0.0, 0.0, 10.0);
    gluCylinder(sensorArrow[axis], 1.5, 0.0, 3.0, 10, 10);
    glPopMatrix();
}


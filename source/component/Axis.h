// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <opengl/ContextPreserver.h>


struct Axis
{
    static void render()
    {
        ContextPreserver contextPreserver;
        glLoadIdentity();
        glPointSize(10.0);
        glBegin(GL_POINTS);
        glColor3f(1, 1, 1);
        glVertex3f(0.0F, 0.0F, 0.0F);
        glColor3f(1, 0, 0);
        glVertex3f(1.0F, 0.0F, 0.0F);
        glVertex3f(2.0F, 0.0F, 0.0F);
        glVertex3f(3.0F, 0.0F, 0.0F);
        glColor3f(0, 1, 0);
        glVertex3f(0.0F, 1.0F, 0.0F);
        glVertex3f(0.0F, 2.0F, 0.0F);
        glVertex3f(0.0F, 3.0F, 0.0F);
        glVertex3f(0.0F, 4.0F, 0.0F);
        glColor3f(0, 0, 1);
        glVertex3f(0.0F, 0.0F, 1.0F);
        glVertex3f(0.0F, 0.0F, 2.0F);
        glVertex3f(0.0F, 0.0F, 3.0F);
        glVertex3f(0.0F, 0.0F, 4.0F);
        glVertex3f(0.0F, 0.0F, 5.0F);
        glEnd();
    }
};
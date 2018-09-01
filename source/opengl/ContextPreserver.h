// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <GL/gl.h>


struct ContextPreserver {
    ContextPreserver()
    {
        glPushMatrix();
    }

    ~ContextPreserver()
    {
        glPopMatrix();
    }
};

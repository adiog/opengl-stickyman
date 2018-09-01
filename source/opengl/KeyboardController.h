// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once


struct KeyboardController
{
    static void keyboardCallback(unsigned char key, int x, int y)
    {
        if (key == 'q')
        {
            exit(0);
        }
        else
        {
            openGLContext.lastKey = key;
        }
        Display::redisplay();
    }
};

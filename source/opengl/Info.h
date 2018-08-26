// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

///////////////////////////////////////////////////////////////////////////////
// write 2d text using GLUT
// The projection matrix must be set to orthogonal before call this function.
///////////////////////////////////////////////////////////////////////////////

#include <GL/gl.h>
#include <GL/glut.h>

struct Info
{
    static void drawString(const char *str, int x, int y, float color[4], void *font)
    {
        glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);  // lighting and color mask
        glDisable(GL_LIGHTING);                          // need to disable lighting for proper text color
        glDisable(GL_TEXTURE_2D);
        glDepthFunc(GL_ALWAYS);

        glColor4fv(color);    // set text color
        glRasterPos2i(x, y);  // place text position

        // loop all characters in the string
        while (*str)
        {
            glutBitmapCharacter(font, *str);
            ++str;
        }

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glDepthFunc(GL_LEQUAL);
        glPopAttrib();
    }
};
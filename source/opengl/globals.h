// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <GL/glut.h>

extern GLint mouseChoice;


extern GLUquadricObj *sensorArrow[3];

typedef struct _area
{
    int id;
    int x, y;
    float min, max;
    float value;
    float step;
} area;

extern area translation[5];

extern GLfloat eye[3];
extern GLfloat at[3];
extern GLfloat up[3];

extern GLuint sampleTexture;

extern GLint selection;


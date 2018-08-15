// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include "globals.h"


GLint mouseChoice;
GLUquadricObj *sensorArrow[3];

area translation[5] = {
    {
        0,
        120,
        40,
        -30.0,
        30.0,
        0.0,
        0.05,
    },
    {
        1,
        180,
        40,
        -30.0,
        30.0,
        0.0,
        0.05,
    },
    {
        2,
        180,
        40,
        -200.0,
        200.0,
        0.0,
        0.1,
    },
    {3, 180, 120, -100, 100, 0.0, 0.5},
    {4, 240, 120, -100, 100, 0.0, 0.5}};

GLfloat eye[3] = {0.0, 0.0, 60.0};
GLfloat at[3] = {0.0, 0.0, 0.0};
GLfloat up[3] = {0.0, 1.0, 0.0};

GLuint sampleTexture = 0;

GLint selection = 0;

// This file is a part of Treadmill project.
// Copyright 2018 Disco WTMH S.A.


#include "globals.h"

bool flag1 = true;
bool flag2 = false;
bool flag3 = true;
bool flag4 = false;
bool flag5 = true;
bool flag6 = false;
bool hflag = true;

GLfloat theta[17] = {0.0, 0.0, 0.0, 90.0, -20.0, 90.0, -20.0, 180.0, 0.0, 180.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
GLint choice = 2;
GLint m_choise = 0;

GLUquadricObj *torso, *head, *neck, *jointPoint,
    *leftHand, *leftFoot, *leftUpperArm, *leftLowerArm,
    *rightUpperArm, *righLowerArm, *leftLowerLeg, *rightLowerLeg,
    *rightUpperLeg, *leftUpperLeg, *rightHand, *rightFoot;

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

GLuint texture1 = 0;
GLuint texture2 = 0;
GLuint texture3 = 0;
GLuint texture4 = 0;

GLint selection = 0;

#pragma once

#include <GL/glut.h>


extern bool flag1;
extern bool flag2;
extern bool flag3;
extern bool flag4;
extern bool flag5;
extern bool flag6;
extern bool hflag;

extern GLfloat theta[17];
extern GLint choice;
extern GLint m_choise;

extern GLUquadricObj *torso, *head, *neck, *jointPoint,
        *leftHand, *leftFoot, *leftUpperArm, *leftLowerArm,
        *rightUpperArm, *righLowerArm, *leftLowerLeg, *rightLowerLeg,
        *rightUpperLeg, *leftUpperLeg, *rightHand, *rightFoot;

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

extern GLuint texture1;
extern GLuint texture2;
extern GLuint texture3;
extern GLuint texture4;

extern GLint selection;


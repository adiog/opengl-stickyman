// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include "drawFunction.h"

#include <GL/glut.h>
#include "globals.h"
#include "opengl-stickyman.h"


void drawHead()
{
    glPushMatrix();
    glColor3f(1.0, 0.0, 5.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glRotatef(15.0, 0.0, 0.0, 1.0);
    glScalef(HEAD_HEIGHT, HEAD_HEIGHT, HEAD_RADIUS);
    gluSphere(head, 1.0, 10, 10);
    glPopMatrix();
}

void drawNeck()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(neck, NECK_RADIUS, NECK_RADIUS, NECK_HEIGHT, 10, 10);
    glPopMatrix();
}

void drawTorso()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(torso, TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT, 10, 10);
    glPopMatrix();
}

void joint_point()
{
    glPushMatrix();
    glScalef(JOINT_POINT_RADIUS, JOINT_POINT_HEIGHT, JOINT_POINT_RADIUS);
    gluSphere(jointPoint, 1.0, 10, 10);
    glPopMatrix();
}

void left_upper_arm()
{
    glPushMatrix();
    gluCylinder(leftUpperArm, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_lower_arm()
{
    glPushMatrix();
    glRotatef(0.0, 1.0, 0.0, 0.0);
    gluCylinder(leftLowerArm, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_hand()
{
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(HAND_RADIUS, HAND_HEIGHT, HAND_RADIUS);
    gluSphere(leftHand, 1.0, 10, 10);
    glPopMatrix();
}

void right_upper_arm()
{
    glPushMatrix();
    gluCylinder(rightUpperArm, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_lower_arm()
{
    glPushMatrix();
    gluCylinder(righLowerArm, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_hand()
{
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(HAND_RADIUS, HAND_HEIGHT, HAND_RADIUS);
    gluSphere(rightHand, 1.0, 10, 10);
    glPopMatrix();
}

void left_upper_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(leftUpperLeg, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_lower_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(leftLowerLeg, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_foot()
{
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(FOOT_RADIUS, FOOT_HEIGHT, FOOT_RADIUS);
    gluSphere(leftFoot, 1.0, 10, 10);
    glPopMatrix();
}

void right_upper_leg()
{
    glPushMatrix();
    glRotatef(-90.0F, 1.0, 0.0, 0.0);
    gluCylinder(rightUpperLeg, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_lower_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rightLowerLeg, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_foot()
{
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(FOOT_RADIUS, FOOT_HEIGHT, FOOT_RADIUS);
    gluSphere(rightFoot, 1.0, 10, 10);
    glPopMatrix();
}
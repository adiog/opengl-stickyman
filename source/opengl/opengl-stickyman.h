#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

int main_(int argc, char** argv);


/*
Define of humanoid body properties 
*/
#define WIN_WIDTH 800
#define WIN_HEIGHT 800
#define TORSO_HEIGHT 5.0
#define TORSO_RADIUS 1.3
#define UPPER_ARM_HEIGHT 2.5
#define LOWER_ARM_HEIGHT 2.3
#define UPPER_ARM_RADIUS 0.5
#define LOWER_ARM_RADIUS 0.5
#define UPPER_LEG_RADIUS 0.5
#define LOWER_LEG_RADIUS 0.5
#define LOWER_LEG_HEIGHT 3.1
#define UPPER_LEG_HEIGHT 3.3
#define HEAD_HEIGHT 1.2
#define HEAD_RADIUS 1.4
#define HAND_RADIUS 0.6
#define HAND_HEIGHT 0.9
#define FOOT_RADIUS 0.7
#define FOOT_HEIGHT 1.1
#define NECK_RADIUS 0.5
#define NECK_HEIGHT 1.0
#define JOINT_POINT_RADIUS 0.5
#define JOINT_POINT_HEIGHT 0.5

#define THETA_THORSO 0
#define THETA_NECK_X 1
#define THETA_NECX_Y 2
#define THETA_LEFT_UPPER_ARM_X 3
#define THETA_LEFT_UPPER_ARM_Z 11
#define THETA_LEFT_LOWER_ARM_X 4
#define THETA_RIGHT_UPPER_ARM_X 5
#define THETA_RIGHT_UPPER_ARM_Z 12
#define THETA_RIGHT_FOOT 16
#define THETA_RIGHT_LOWER_LEG 10
#define THETA_RIGHT_UPPER_LEG_X 9
#define THETA_RIGHT_UPPER_LEG_Z 14
#define THETA_LEFT_FOOT 15
#define THETA_LEFT_LOWER_LEG 8
#define THETA_LEFT_UPPER_LEG_Z 13
#define THETA_LEFT_UPPER_LEG_X 7
#define THETA_RIGHT_LOWER_ARM 6

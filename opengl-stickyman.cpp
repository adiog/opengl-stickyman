// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include "drawFunction.h"
#include "globals.h"
#include "opengl-stickyman.h"

void timer_walk(int);
void timer_kick(int);

void myReshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width <= height)
    {
        glOrtho(-30.0,
                30.0,
                -30.0 * (GLfloat)height / (GLfloat)width,
                30.0 * (GLfloat)height / (GLfloat)width,
                -200,
                200);
    }
    else
    {
        glOrtho(-30.0 * (GLfloat)width / (GLfloat)height,
                30.0 * (GLfloat)width / (GLfloat)height,
                -30.0,
                30.0,
                -200,
                200);
    }

    gluPerspective(1.0, (float)width / height, 2.0, 1.0);
    gluLookAt(translation[3].value, translation[4].value, eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
    glTranslatef(translation[0].value, translation[1].value, translation[2].value);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void redisplay_all(void)
{
    myReshape(WIN_WIDTH, WIN_HEIGHT);
    glutPostRedisplay();
}


//--------------------------------Display function--------------------------------
void myDisplay()
{
    glClearColor(1, 1, 0.5, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    glColor3ub(0, 0, 0);

    glBindTexture(GL_TEXTURE_2D, texture2);
    glRotatef(theta[THETA_THORSO], 0.0, 1.0, 0.0);
    drawTorso();

    {
        glPushMatrix();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0, TORSO_HEIGHT, 0.0);
        drawNeck();

        glBindTexture(GL_TEXTURE_2D, texture1);
        glTranslatef(0.0, NECK_HEIGHT + 0.5 * HEAD_HEIGHT, 0.0);
        glRotatef(theta[THETA_NECK_X], 1.0, 0.0, 0.0);
        glRotatef(theta[THETA_NECX_Y], 0.0, 1.0, 0.0);
        drawHead();

        glPopMatrix();
    }

    {
        glPushMatrix();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(-0.85 * (TORSO_RADIUS + JOINT_POINT_RADIUS),
                     0.9 * TORSO_HEIGHT,
                     0.0);
        joint_point();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, 0.0, 0.0);
        glRotatef(theta[THETA_LEFT_UPPER_ARM_X], 1.0, 0.0, 0.0);
        glRotatef(theta[THETA_LEFT_UPPER_ARM_Z], 0.0, 0.0, 1.0);
        left_upper_arm();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, 0.0, UPPER_ARM_HEIGHT);
        joint_point();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, 0.1 * JOINT_POINT_HEIGHT, 0.0);
        glRotatef(theta[THETA_LEFT_LOWER_ARM_X], 1.0, 0.0, 0.0);
        left_lower_arm();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, 0.0, LOWER_ARM_HEIGHT);
        left_hand();

        glPopMatrix();
    }

    {
        glPushMatrix();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.85 * (TORSO_RADIUS + JOINT_POINT_RADIUS),
                     0.9 * TORSO_HEIGHT,
                     0.0);
        joint_point();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, 0.0, 0.0);
        glRotatef(theta[THETA_RIGHT_UPPER_ARM_X], 1.0, 0.0, 0.0);
        glRotatef(theta[THETA_RIGHT_UPPER_ARM_Z], 0.0, 0.0, 1.0);
        right_upper_arm();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, 0.0, UPPER_ARM_HEIGHT);
        joint_point();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, 0.1 * JOINT_POINT_HEIGHT, 0.0);
        glRotatef(theta[THETA_RIGHT_LOWER_ARM], 1.0, 0.0, 0.0);
        right_lower_arm();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, 0.0, LOWER_ARM_HEIGHT);
        right_hand();

        glPopMatrix();
    }

    {
        glPushMatrix();

        glBindTexture(GL_TEXTURE_2D, texture3);
        glTranslatef(-(TORSO_RADIUS - JOINT_POINT_RADIUS),
                     -0.15 * JOINT_POINT_HEIGHT,
                     0.0);
        joint_point();

        glBindTexture(GL_TEXTURE_2D, texture3);
        glTranslatef(0, 0.1 * JOINT_POINT_HEIGHT, 0.0);
        glRotatef(theta[THETA_LEFT_UPPER_LEG_X], 1.0, 0.0, 0.0);
        glRotatef(theta[THETA_LEFT_UPPER_LEG_Z], 0.0, 0.0, 1.0);
        left_upper_leg();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
        joint_point();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, 0.1 * JOINT_POINT_HEIGHT, 0.0);
        glRotatef(theta[THETA_LEFT_LOWER_LEG], 1.0, 0.0, 0.0);
        left_lower_leg();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, LOWER_LEG_HEIGHT, -0.5 * FOOT_HEIGHT);
        glRotatef(theta[THETA_LEFT_FOOT], 1.0, 0.0, 0.0);
        left_foot();

        glPopMatrix();
    }
    {
        glPushMatrix();

        glBindTexture(GL_TEXTURE_2D, texture3);
        glTranslatef(TORSO_RADIUS - JOINT_POINT_RADIUS,
                     -0.15 * JOINT_POINT_HEIGHT,
                     0.0);
        joint_point();

        glBindTexture(GL_TEXTURE_2D, texture3);
        glTranslatef(0, 0.1 * JOINT_POINT_HEIGHT, 0.0);
        glRotatef(theta[THETA_RIGHT_UPPER_LEG_X], 1.0, 0.0, 0.0);
        glRotatef(theta[THETA_RIGHT_UPPER_LEG_Z], 0.0, 0.0, 1.0);
        right_upper_leg();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
        joint_point();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, 0.1 * JOINT_POINT_HEIGHT, 0.0);
        glRotatef(theta[THETA_RIGHT_LOWER_LEG], 1.0, 0.0, 0.0);
        right_lower_leg();

        glBindTexture(GL_TEXTURE_2D, texture4);
        glTranslatef(0.0, LOWER_LEG_HEIGHT, -0.5 * FOOT_HEIGHT);
        glRotatef(theta[THETA_RIGHT_FOOT], 1.0, 0.0, 0.0);
        right_foot();

        glPopMatrix();
    }

    glFlush();
    glutSwapBuffers();
}

//--------------------------------Keyboard control function-----------------------
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q')
    {
        choice = 2;
    }  // Head horiz
    if (key == 'a')
    {
        choice = 1;
    }  // Head vert

    if (key == 'w')
    {
        choice = 3;
    }  //left arm horiz
    if (key == 's')
    {
        choice = 11;
    }  //left arm vert

    if (key == 'e')
    {
        choice = 5;
    }  //right arm horiz
    if (key == 'd')
    {
        choice = 12;
    }  //right arm horiz

    if (key == 'r')
    {
        choice = 7;
    }  //left leg vert
    if (key == 'f')
    {
        choice = 13;
    }  //left leg horiz

    if (key == 't')
    {
        choice = 9;
    }  //right leg horiz
    if (key == 'g')
    {
        choice = 14;
    }  //right leg vert

    if (key == 'z')
    {
        choice = 0;
    }  //torso

    if (key == 'x')
    {
        choice = 4;
    }  //left_lower_arm

    if (key == 'c')
    {
        choice = 6;
    }  //right_lower_arm

    if (key == 'v')
    {
        choice = 8;
    }  //left_lower_leg

    if (key == 'b')
    {
        choice = 10;
    }  //right_lowerleg

    if (key == ',')
    {
        choice = 15;
    }  //left_foot

    if (key == '.')
    {
        choice = 16;
    }  //right_foot

    if (key == 'm')
    {
        glutTimerFunc(100, timer_walk, 0);
    }  //animation walk

    if (key == 'n')
    {
        theta[THETA_LEFT_UPPER_ARM_X] = 0;    // 0-30
        theta[THETA_LEFT_LOWER_ARM_X] = 0;    // 0
        theta[THETA_LEFT_UPPER_ARM_Z] = -15;  // 0
        theta[THETA_RIGHT_UPPER_ARM_X] = 60;  // 0
        theta[THETA_RIGHT_LOWER_ARM] = -120;  // 0
        theta[THETA_RIGHT_UPPER_ARM_Z] = 15;  // 0
        glutTimerFunc(200, timer_kick, 0);    /*glutTimerFunc(100,timer_kick,0);*/
    }                                         //animation kick

    if (key == '9')
    {
        theta[choice] += 5.0;
        if (theta[choice] > 360.0) theta[choice] -= 360.0;
        glutPostRedisplay();
    }
    if (key == '0')
    {
        theta[choice] -= 5.0;
        if (theta[choice] < 360.0) theta[choice] += 360.0;
        glutPostRedisplay();
    }
}

//--------------------------------Display area for mouse conrol-------------------
void area_update(area* area, int update)
{
    if (selection != area->id)
        return;

    area->value += update * area->step;

    if (area->value < area->min)
        area->value = area->min;
    else if (area->value > area->max)
        area->value = area->max;
}

int area_hit(area* area, int x, int y)
{
    if ((x > 0 && x < WIN_WIDTH) && (y > 0 && y < WIN_HEIGHT))
        return area->id;
    return 0;
}

int old_y, old_x;

void menu(int id)
{
    if (id < 3) m_choise = id;
    if (id == 3) exit(1);
}

void mouse(int button, int state, int x, int y)
{
    selection = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN
        && (m_choise == 0 || m_choise == 2))
    {
        selection += area_hit(&translation[0], x, y);
        if (m_choise == 0) selection += area_hit(&translation[0], x, y);
        if (m_choise == 2) selection += area_hit(&translation[3], x, y);
        old_x = x;
        redisplay_all();
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN
        && ((m_choise == 0 || m_choise == 1) || m_choise == 2))
    {
        if (m_choise == 0) selection += area_hit(&translation[1], x, y);
        if (m_choise == 1) selection += area_hit(&translation[2], x, y);
        if (m_choise == 2) selection += area_hit(&translation[4], x, y);
        old_y = y;
        redisplay_all();
    }
}

void pressed_mouse(int x, int y)
{
    area_update(&translation[0], x - old_x);
    area_update(&translation[1], old_y - y);
    area_update(&translation[2], old_y - y);
    area_update(&translation[3], x - old_x);
    area_update(&translation[4], old_y - y);
    old_y = y;
    old_x = x;

    redisplay_all();
}

//--------------------------------Reshape & redisplay functions--------------------
//--------------------------------Animation timer functions-------------------------
void timer_walk(int)
{
    if (switchLeftUpperArmDirectionFlag)
    {
        theta[THETA_LEFT_UPPER_ARM_X] += 5.0;
    }
    else
    {
        theta[THETA_LEFT_UPPER_ARM_X] -= 5.0;
    }
    if (theta[THETA_LEFT_UPPER_ARM_X] >= 110.0) switchLeftUpperArmDirectionFlag = false;
    if (theta[THETA_LEFT_UPPER_ARM_X] <= 70.0) switchLeftUpperArmDirectionFlag = true;

    if (switchLeftLowerArmDirectionFlag)
    {
        theta[THETA_RIGHT_UPPER_ARM_X] += 5.0;
    }
    else
    {
        theta[THETA_RIGHT_UPPER_ARM_X] -= 5.0;
    }
    if (theta[THETA_RIGHT_UPPER_ARM_X] >= 110.0) switchLeftLowerArmDirectionFlag = false;
    if (theta[THETA_RIGHT_UPPER_ARM_X] <= 70.0) switchLeftLowerArmDirectionFlag = true;

    if (switchRightUpperArmDirectionFlag)
    {
        theta[THETA_RIGHT_UPPER_LEG_X] += 5.0;
    }
    else
    {
        theta[THETA_RIGHT_UPPER_LEG_X] -= 5.0;
    }
    if (theta[THETA_RIGHT_UPPER_LEG_X] >= 200.0) switchRightUpperArmDirectionFlag = false;
    if (theta[THETA_RIGHT_UPPER_LEG_X] <= 160.0) switchRightUpperArmDirectionFlag = true;

    if (switchRightLowerArmDirectionFlag)
    {
        theta[THETA_LEFT_UPPER_LEG_X] += 5.0;
    }
    else
    {
        theta[THETA_LEFT_UPPER_LEG_X] -= 5.0;
    }
    if (theta[THETA_LEFT_UPPER_LEG_X] >= 200.0) switchRightLowerArmDirectionFlag = false;
    if (theta[THETA_LEFT_UPPER_LEG_X] <= 160.0) switchRightLowerArmDirectionFlag = true;

    if (switchHeadDirectionFlag)
    {
        theta[THETA_NECX_Y] += 5.0;
    }
    else
    {
        theta[THETA_NECX_Y] -= 5.0;
    }
    if (theta[THETA_NECX_Y] >= 30.0) switchHeadDirectionFlag = false;
    if (theta[THETA_NECX_Y] <= -30.0) switchHeadDirectionFlag = true;

    glutPostRedisplay();
    glutTimerFunc(100, timer_walk, 0);
}
void timer_kick(int)
{
    if (switchLeftUpperArmDirectionFlag)
    {
        theta[THETA_LEFT_UPPER_ARM_X] -= 15.0;
    }
    else
    {
        theta[THETA_LEFT_UPPER_ARM_X] += 15.0;
    }
    if (theta[THETA_LEFT_UPPER_ARM_X] >= 60) switchLeftUpperArmDirectionFlag = true;
    if (theta[THETA_LEFT_UPPER_ARM_X] <= 0) switchLeftUpperArmDirectionFlag = false;  // 0-45

    if (switchLeftLowerArmDirectionFlag)
    {
        theta[THETA_LEFT_LOWER_ARM_X] -= 30;
    }
    else
    {
        theta[THETA_LEFT_LOWER_ARM_X] += 30;
    }
    if (theta[THETA_LEFT_LOWER_ARM_X] >= 0) switchLeftLowerArmDirectionFlag = true;
    if (theta[THETA_LEFT_LOWER_ARM_X] <= -120) switchLeftLowerArmDirectionFlag = false;
    theta[THETA_LEFT_UPPER_ARM_Z] = -15;  // 0

    if (switchRightUpperArmDirectionFlag)
    {
        theta[THETA_RIGHT_UPPER_ARM_X] -= 15.0;
    }
    else
    {
        theta[THETA_RIGHT_UPPER_ARM_X] += 15.0;
    }
    if (theta[THETA_RIGHT_UPPER_ARM_X] >= 60) switchRightUpperArmDirectionFlag = true;
    if (theta[THETA_RIGHT_UPPER_ARM_X] <= 0) switchRightUpperArmDirectionFlag = false;  // 0-45

    if (switchRightLowerArmDirectionFlag)
    {
        theta[THETA_RIGHT_LOWER_ARM] -= 30;
    }
    else
    {
        theta[THETA_RIGHT_LOWER_ARM] += 30;
    }
    if (theta[THETA_RIGHT_LOWER_ARM] >= 0) switchRightLowerArmDirectionFlag = true;
    if (theta[THETA_RIGHT_LOWER_ARM] <= -120) switchRightLowerArmDirectionFlag = false;

    if (switchRightUpperLegDirectionFlag)
    {
        theta[THETA_RIGHT_UPPER_LEG_X] += 10.0;
    }
    else
    {
        theta[THETA_RIGHT_UPPER_LEG_X] -= 10.0;
    }
    if (theta[THETA_RIGHT_UPPER_LEG_X] >= 200.0) switchRightUpperLegDirectionFlag = false;
    if (theta[THETA_RIGHT_UPPER_LEG_X] <= 160.0) switchRightUpperLegDirectionFlag = true;

    if (switchLeftUpperLegDirectionFlag)
    {
        theta[THETA_LEFT_UPPER_LEG_X] += 10.0;
    }
    else
    {
        theta[THETA_LEFT_UPPER_LEG_X] -= 10.0;
    }
    if (theta[THETA_LEFT_UPPER_LEG_X] >= 200.0) switchLeftUpperLegDirectionFlag = false;
    if (theta[THETA_LEFT_UPPER_LEG_X] <= 160.0) switchLeftUpperLegDirectionFlag = true;

    glutPostRedisplay();
    glutTimerFunc(200, timer_kick, 0);
}

//--------------------------------Initialization function----------------------------
void myInit()
{
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess = {100.0};
    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {10.0, 10.0, 10.0, 0.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    /* allocate quadrics with filled drawing style */
    head = gluNewQuadric();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    gluQuadricTexture(head, GL_TRUE);
    gluQuadricDrawStyle(head, GLU_FILL);

    neck = gluNewQuadric();
    gluQuadricTexture(neck, GL_TRUE);
    gluQuadricDrawStyle(neck, GLU_FILL);

    torso = gluNewQuadric();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    gluQuadricTexture(torso, GL_TRUE);
    gluQuadricDrawStyle(torso, GLU_FILL);

    jointPoint = gluNewQuadric();
    gluQuadricTexture(jointPoint, GL_TRUE);
    gluQuadricDrawStyle(jointPoint, GLU_FILL);

    leftUpperArm = gluNewQuadric();
    gluQuadricTexture(leftUpperArm, GL_TRUE);
    gluQuadricDrawStyle(leftUpperArm, GLU_FILL);

    leftLowerArm = gluNewQuadric();
    gluQuadricTexture(leftLowerArm, GL_TRUE);
    gluQuadricDrawStyle(leftLowerArm, GLU_FILL);

    leftHand = gluNewQuadric();
    gluQuadricTexture(leftHand, GL_TRUE);
    gluQuadricDrawStyle(leftHand, GLU_FILL);

    rightHand = gluNewQuadric();
    gluQuadricTexture(rightHand, GL_TRUE);
    gluQuadricDrawStyle(rightHand, GLU_FILL);

    rightFoot = gluNewQuadric();
    gluQuadricTexture(rightFoot, GL_TRUE);
    gluQuadricDrawStyle(rightFoot, GLU_FILL);

    leftFoot = gluNewQuadric();
    gluQuadricTexture(leftFoot, GL_TRUE);
    gluQuadricDrawStyle(leftFoot, GLU_FILL);

    rightUpperArm = gluNewQuadric();
    gluQuadricTexture(rightUpperArm, GL_TRUE);
    gluQuadricDrawStyle(rightUpperArm, GLU_FILL);

    righLowerArm = gluNewQuadric();
    gluQuadricTexture(righLowerArm, GL_TRUE);
    gluQuadricDrawStyle(righLowerArm, GLU_FILL);

    leftUpperLeg = gluNewQuadric();
    gluQuadricTexture(leftUpperLeg, GL_TRUE);
    gluQuadricDrawStyle(leftUpperLeg, GLU_FILL);

    leftLowerLeg = gluNewQuadric();
    gluQuadricTexture(leftLowerLeg, GL_TRUE);
    gluQuadricDrawStyle(leftLowerLeg, GLU_FILL);

    rightUpperLeg = gluNewQuadric();
    gluQuadricTexture(rightUpperLeg, GL_TRUE);
    gluQuadricDrawStyle(rightUpperLeg, GLU_FILL);

    rightLowerLeg = gluNewQuadric();
    gluQuadricTexture(rightLowerLeg, GL_TRUE);
    gluQuadricDrawStyle(rightLowerLeg, GLU_FILL);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("opengl-stickman");
    myInit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);
    glutMotionFunc(pressed_mouse);
    glutMouseFunc(mouse);
    glutCreateMenu(menu);
    glutAddMenuEntry("view_hor/vert", 0);
    glutAddMenuEntry("view_zoom_in/out", 1);
    glutAddMenuEntry("view_lft-rgt/up-dow", 2);
    glutAddMenuEntry("quit", 3);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    glutKeyboardFunc(keyboard);
    redisplay_all();
    glutMainLoop();
    return 0;
}

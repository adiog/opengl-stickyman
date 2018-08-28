// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include "Bone.h"
#include "Skeleton.h"
#include "globals.h"
#include "opengl-stickyman.h"
#include "opengl/drawFunction.h"
#include "Info.h"
#include <initializer_list>
void timer_walk(int);
void timer_kick(int);

int gwidth;
int gheight;

void rashapeSensor(int width, int height)
{
    gwidth = width;
    gheight = height;

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
    /*
    float eye[3] = {0, 0, 1};
    float center[3] = {1, 0, 0};
    float top[3] = {0, 1, 0};
    gluLookAt(eye[X], eye[Y], eye[Z], center[X], center[Y], center[Z], top[X], top[Y], top[Z]);*/
    glTranslatef(translation[0].value, translation[1].value, translation[2].value);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void redisplay_all(void)
{
    rashapeSensor(WIN_WIDTH, WIN_HEIGHT);
    glutPostRedisplay();
}

Skeleton skeleton;

//--------------------------------Display function--------------------------------
void displaySensor()
{
    glClearColor(0.4, 0.8, 0.4, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    glColor3ub(0, 0, 0);

    {
        Info info;
        info << "Hello World";
        info << '\n';
        info << gwidth << " " << gheight << '\n';
        info.flush();
    }
    {
        glPushMatrix();
        skeleton.redraw();
        glPopMatrix();
    }
    /*
    {
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);

        glBindTexture(GL_TEXTURE_2D, sampleTexture);
        glTranslatef(0.0, 0.0, 0.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        drawArrow(0);

        glPopMatrix();
    }
    {
        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);

        glBindTexture(GL_TEXTURE_2D, sampleTexture);
        glTranslatef(0.0, 0.0, 0.0);
        glRotatef(90.0, 0.0, 1.0, 0.0);
        drawArrow(1);

        glPopMatrix();
    }
    {
        glPushMatrix();

        glBindTexture(GL_TEXTURE_2D, sampleTexture);
        glLoadIdentity();
        glColor3f(0.0, 0.0, 1.0);

        glTranslatef(0.0, 0.0, 0.0);
        glRotatef(90.0, 0.0, 0.0, 1.0);
        drawArrow(2);

        glPopMatrix();
    }*/
    glFlush();
    glutSwapBuffers();
}

//--------------------------------Keyboard control function-----------------------
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q')
    {
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
    if (id < 3) mouseChoice = id;
    if (id == 3) exit(1);
}

void mouse(int button, int state, int x, int y)
{
    selection = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN
        && (mouseChoice == 0 || mouseChoice == 2))
    {
        selection += area_hit(&translation[0], x, y);
        if (mouseChoice == 0) selection += area_hit(&translation[0], x, y);
        if (mouseChoice == 2) selection += area_hit(&translation[3], x, y);
        old_x = x;
        redisplay_all();
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN
        && ((mouseChoice == 0 || mouseChoice == 1) || mouseChoice == 2))
    {
        if (mouseChoice == 0) selection += area_hit(&translation[1], x, y);
        if (mouseChoice == 1) selection += area_hit(&translation[2], x, y);
        if (mouseChoice == 2) selection += area_hit(&translation[4], x, y);
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
    glutPostRedisplay();
    glutTimerFunc(100, timer_walk, 0);
}
void timer_kick(int)
{
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

    for (auto axis : {0, 1, 2})
    {
        sensorArrow[axis] = gluNewQuadric();
        gluQuadricTexture(sensorArrow[axis], GL_TRUE);
        gluQuadricDrawStyle(sensorArrow[axis], GLU_FILL);
    }
}

int main_(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("opengl-stickman");

    myInit();
    glutReshapeFunc(rashapeSensor);
    glutDisplayFunc(displaySensor);
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

// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include "OpenGLContext.h"
#include "OrbitCamera.h"
#include "glout.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


struct Display
{
    static void intialization()
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
    }

    static void rashape(int width, int height)
    {
        openGLContext.gwidth = width;
        openGLContext.gheight = height;

        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if (width <= height)
        {
            glOrtho(-8.0,
                    8.0,
                    -8.0 * (GLfloat)height / (GLfloat)width,
                    8.0 * (GLfloat)height / (GLfloat)width,
                    -200,
                    200);
        }
        else
        {
            glOrtho(-7.0 * (GLfloat)width / (GLfloat)height,
                    7.0 * (GLfloat)width / (GLfloat)height,
                    -7.0,
                    7.0,
                    -200,
                    200);
        }

        gluPerspective(1.0, (float)width / height, 0.0, 30.0);

        OrbitCamera::updateCamera(openGLContext.gyaw, openGLContext.gpitch, openGLContext.cameraDistance, openGLContext.cam, openGLContext.top);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    static void redisplay()
    {
        rashape(openGLContext.gwidth, openGLContext.gheight);
        glutPostRedisplay();
    }

    static void display()
    {
        glClearColor(0.4, 0.8, 0.4, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glColor3f(0.0, 0.0, 0.0);
        glColor3ub(0, 0, 0);

        {
            glPushMatrix();
            openGLContext.scene.render();
            glPopMatrix();
        }
        {
            glout out;
            out << "Window dimension: " << openGLContext.gwidth << " " << openGLContext.gheight << '\n';
            out << "mouseCallback: " << openGLContext.mouse_x << " " << openGLContext.mouse_y << '\n';
            out << "mousePressedCallback: " << openGLContext.old_x << " " << openGLContext.old_y << '\n';
            out << "passiveMouseCallback: " << openGLContext.pas_mouse_x << " " << openGLContext.pas_mouse_y << '\n';
            out << "camera position: " << openGLContext.cam[0] << " " << openGLContext.cam[1] << " " << openGLContext.cam[2] << '\n';
            out << "camera top: " << openGLContext.top[0] << " " << openGLContext.top[1] << " " << openGLContext.top[2] << '\n';
            out << "yaw pitch: " << (openGLContext.gyaw % 360) << "deg " << (openGLContext.gpitch % 360) << "deg\n";
            out << "cameraDistance: " << openGLContext.cameraDistance << '\n';
            out << "keyboard character: " << openGLContext.lastKey << " (" << (int)openGLContext.lastKey << ")\n";
            for(const auto &arrow : openGLContext.scene.layout.segmentLayout)
            {
                out << arrow.second[0] << '\n';
            }
            out.flush();
        }

        glFlush();
        glutSwapBuffers();
    }

};

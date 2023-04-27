#pragma once
#define _USE_MATH_DEFINES

#include <windows.h>
#include <gl/freeglut.h>
#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <cmath>
#include <fstream>
using namespace std;


class Hamburger : public Object
{
public:
    Point centru;
    double angle;

    Hamburger(double x, double y) : centru(x, y), angle(0) { ; }

    void draw()
    {
        glPushMatrix();

        glTranslated(centru.getX(), centru.getY(), 0);
        glScaled(0.3, 0.3, 1);
        glRotated(angle, 0, 0, 1);
        glTranslated(0, 15, 0);

        // top bun
        glColor3f(1.0, 0.8, 0.0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
        for (float theta = 0; theta <= M_PI; theta += 0.01)
        {
            float x = cos(theta) * 50;
            float y = sin(theta) * 30;
            glVertex2f(x, y);
        }
        glEnd();


        //bottom bun
        glColor3f(1.0, 0.8, 0.0);
        int offset = -35;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, offset);
        for (float theta = 0; theta <= M_PI; theta += 0.01)
        {
            float x = -cos(theta) * 50;
            float y = -sin(theta) * 30;
            glVertex2f(x, y + offset);
        }
        glEnd();

        // lettuce
        glColor3f(0.64, 0.78, 0.35);
        glBegin(GL_POLYGON);
        glVertex2f(-55, -28);
        glVertex2f(55, -28);
        glVertex2f(50, -40);
        glVertex2f(40, -28);
        glVertex2f(30, -40);
        glVertex2f(20, -28);
        glVertex2f(10, -48);
        glVertex2f(0, -28);
        glVertex2f(-10, -40);
        glVertex2f(-20, -28);
        glVertex2f(-30, -40);
        glVertex2f(-40, -28);

        glEnd();

        //tomato
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        int numSegments = 100;
        float radiusX = 55;
        float radiusY = 7;
        for (int i = 0; i < numSegments; i++)
        {
            float theta = 2.0 * M_PI * float(i) / float(numSegments);
            float x = radiusX * cos(theta);
            float y = radiusY * sin(theta);
            glVertex2f(x, y - 23);
        }
        glEnd();

        // meat
        glColor3f(0.46, 0.36, 0.30);
        glRecti(-50, -20, 50, 0);

        // cheese
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0.95, 0.18);
        glVertex2f(-50, 0);
        glVertex2f(50, 0);
        glVertex2f(30, -12.5);
        glEnd();

        glPopMatrix();

    }

    void update()
    {
        using namespace std::chrono;
        uint64_t current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        uint64_t delta_time = current_time - last_update;
        last_update = current_time;

        angle += 0.05 * delta_time;
        if (angle > 360)
        {
            angle = 0;
        }
        if (angle < 0)
        {
            angle = 360;
        }
        glutPostRedisplay();
    }
    void mouse(int button, int state, int x, int y) { ; }
};
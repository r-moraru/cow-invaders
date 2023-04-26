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
#include "Point.h"
using namespace std;

class Pahar : public Object
{
public:
    Point centru;
    Point base_point;
    double jump_speed;
    double max_jump_speed;
    double fall_acceleration;
    int fill;

    Pahar(double x, double y) : centru(x, y), base_point(x, y), fill(8), max_jump_speed(0.1),
        jump_speed(0.1), fall_acceleration(0.0002) { ; }

    void draw()
    {
        glPushMatrix();

        glTranslated(centru.getX(), centru.getY(), 0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(208 / 255.0, 250 / 255.0, 249 / 255.0, 0.7);
        glRecti(0, 0, -75, -150);

        // bottom part
        glColor4f(208 / 255.0, 250 / 255.0, 249 / 255.0, 1);
        glBegin(GL_POLYGON);
        int numSegments = 100;
        float radiusX = 75 / 2;
        float radiusY = 5;
        for (int i = 0; i < numSegments; i++)
        {
            float theta = 2.0 * M_PI * float(i) / float(numSegments);
            float x = radiusX * cos(theta);
            float y = radiusY * sin(theta);
            glVertex2f(x - 75 / 2, y);
        }
        glEnd();

        // top part
        glBegin(GL_POLYGON);
        numSegments = 100;
        radiusX = 75 / 2;
        radiusY = 10;
        for (int i = 0; i < numSegments; i++)
        {
            float theta = 2.0 * M_PI * float(i) / float(numSegments);
            float x = radiusX * cos(theta);
            float y = radiusY * sin(theta);
            glVertex2f(x - 75 / 2, y - 150);
        }
        glEnd();


        if (this->fill) {

            glColor4f(1.0, 1.0, 1.0, 0.93);

            glBegin(GL_POLYGON);
            numSegments = 100;
            radiusX = 75 / 2 - 5;
            radiusY = 5;
            for (int i = 0; i < numSegments; i++)
            {
                float theta = 2.0 * M_PI * float(i) / float(numSegments);
                float x = radiusX * cos(theta);
                float y = radiusY * sin(theta);
                glVertex2f(x - 75 / 2, y - 150);
            }
            glEnd();

              for (int i = 0; i < this->fill; i++)
            {
               glRecti(-5, 0 + (i * 15) - 150, -70, 15 + (i * 15) - 150);
            }
       
        }
        glPopMatrix();
    }

    void update()
    {
        if (base_point.getY() >= centru.getY()) {
            jump_speed = max_jump_speed;
            centru.setY(base_point.getY());
        }

        centru.setY(centru.getY() + jump_speed);
        jump_speed -= fall_acceleration;
    }
    void mouse(int button, int state, int x, int y) { ; }

    void keyPress(int key, int x, int y) { 
        switch (key) {
        case GLUT_KEY_LEFT:
            this->centru.setX(this->centru.getX() - 5);
            break;
        case GLUT_KEY_RIGHT:
            this->centru.setX(this->centru.getX() + 5);
            break;
        default:
            break;
        }
    };
    void keyUp(int key, int x, int y) { ; };
};
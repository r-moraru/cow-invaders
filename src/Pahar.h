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
#include "Screen.h"
using namespace std;

double arie_triunghi(Point& A, Point& B, Point& C) {
    return abs(A.getX() * B.getY() + B.getX() * C.getY() + C.getX() * A.getY()
        - C.getX() * B.getY() - B.getX() * A.getY() - A.getX() * C.getY()) / 2.0;
}
bool punct_in_triunghi(Point& A, Point& B, Point& C, Point& D) {
    return abs(arie_triunghi(A, B, D) + arie_triunghi(A, C, D) + arie_triunghi(B, C, D) - arie_triunghi(A, B, C)) < 1;
}

bool punct_in_dreptunghi(Point& A, Point& B, Point& C, Point& D, Point& P) {
    return punct_in_triunghi(A, B, C, P) || punct_in_triunghi(C, D, A, P);
}


class Pahar : public Object
{
public:
    Point centru;
    double jump_height;
    double jump_speed;
    double max_jump_speed;
    double x_speed;
    double fall_acceleration;
    int fill;

    Pahar(double x, double y) : centru(x, y), jump_height(0), fill(0), max_jump_speed(0.3),
        jump_speed(0.3), fall_acceleration(0.0015), x_speed(0) { ; }

    void draw()
    {
        glPushMatrix();

        glTranslated(centru.getX(), centru.getY() + jump_height, 0);

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
        if (jump_height <= 0) {
            jump_speed = max_jump_speed;
            jump_height = 0;
        }

        using namespace std::chrono;
        uint64_t current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        uint64_t delta_time = current_time - last_update;
        last_update = current_time;

        jump_height += jump_speed * delta_time;
        jump_speed -= fall_acceleration * delta_time;

        centru.setX(centru.getX() + x_speed * delta_time);

        if (centru.getX() < 50) {
            centru.setX(50);
        }

        if (centru.getX() > Screen::get_width()) {
            centru.setX(Screen::get_width());
        }
    }

    void mouse(int button, int state, int x, int y) { ; }

    void keyPress(int key, int x, int y) {
        switch (key) {
        case GLUT_KEY_LEFT:
            x_speed = -0.2 - 0.02 * Scene::lvl;
            break;
        case GLUT_KEY_RIGHT:
            x_speed = 0.2 + 0.02 * Scene::lvl;
            break;
        default:
            break;
        }
    };
    void keyUp(int key, int x, int y) { ; };

    bool contine_punct(Point punct) {
        Point A(0 + centru.getX(), 0 + centru.getY() + jump_height);
        Point B(0 + centru.getX(), -150 + centru.getY() + jump_height);
        Point C(-75 + centru.getX(), -150 + centru.getY() + jump_height);
        Point D(-75 + centru.getX(), 0 + centru.getY() + jump_height);
        return punct_in_dreptunghi(A, B, C, D, punct);
    }
};
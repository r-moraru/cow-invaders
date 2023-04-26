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
#include "Object.h"
using namespace std;

class Point : public Object
{
private:
    double x, y;

public:
    Point()
    {
        x = 0;
        y = 0;
    }

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    double getX() { return x; }
    double getY() { return y; }

    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }

    void draw()
    {
        glColor3f(0.0, 0.0, 0.0);
        glPointSize(10.0);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);

        glVertex2f(x, y);

        glEnd();
    }

    void update() { ; }
    void mouse(int button, int state, int x, int y) { ; }
};
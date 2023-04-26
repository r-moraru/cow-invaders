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


class Screen
{
private:
    static int w, h;

public:
    static int get_width()
    {
        return w;
    }

    static int get_height()
    {
        return h;
    }

    static void set_width(int new_w)
    {
        w = new_w;
    }

    static void set_height(int new_h)
    {
        h = new_h;
    }
};

int Screen::w, Screen::h;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0.0, 780.0, 0.0, 600.0, -1.0, 1.0);
    Screen::set_width(780);
    Screen::set_height(600);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

    Screen::set_width(w);
    Screen::set_height(h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
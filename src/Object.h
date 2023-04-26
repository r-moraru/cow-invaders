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



class Object
{
public:
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void mouse(int button, int state, int x, int y) = 0;
    virtual void keyPress(int key, int x, int y) { ; };
    virtual void keyUp(int key, int x, int y) { ; };
};



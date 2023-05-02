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
#include <vector>
#include "Hamburger.h"
#include "Point.h"
#include <string>
#include "Scene.h"
using namespace std;


class Healthbar : public Object
{
public:
    Point centru;
    vector<Hamburger> hp; 
    int scor;

    Healthbar(double x, double y) : centru(x, y), scor(0) {
        Hamburger hamburger1 = Hamburger(x, y);
        Hamburger hamburger2 = Hamburger(x + 50 , y);
        Hamburger hamburger3 = Hamburger(x + 100, y);

        hp.push_back(hamburger1);
        hp.push_back(hamburger2);
        hp.push_back(hamburger3);
    }

    void draw()
    {
        for (Hamburger &obj : hp) {
            obj.draw();
        }

    }

    void update()
    {
        for (Hamburger &obj: hp) {
            obj.update();
        }

    }
    void mouse(int button, int state, int x, int y) { ; }

};
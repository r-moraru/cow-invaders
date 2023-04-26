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


class Scene
{
private:
    static map<string, shared_ptr<Object>> objects;

public:
    static void add_object(const string name, shared_ptr<Object> obj)
    {
        objects[name] = obj;
    }

    static void update(void) {
        for (auto& object : objects) {
            object.second->update();
        }
        glutPostRedisplay();
    }

    static void mouse(int button, int state, int x, int y)
    {
        for (auto& object : objects)
        {
            object.second->mouse(button, state, x, y);
        }
    }

    static void draw(void)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        for (auto& object : objects)
        {
            object.second->draw();
        }
        glutSwapBuffers();
        glFlush();
    }

    static shared_ptr<Object> get_object(const string name)
    {
        if (objects.find(name) == objects.end())
        {
            return nullptr;
        }

        return objects[name];
    }

    static int get_objects_len(void)
    {
        return objects.size();
    }
};

map<string, shared_ptr<Object>> Scene::objects;
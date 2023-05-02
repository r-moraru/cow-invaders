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
#include "Healthbar.h"
#include "Screen.h"
using namespace std;


class Scene
{
private:
    static map<string, shared_ptr<Object>> objects;
public:
    static double movement_speed;
    static int lvl;
    static bool playing;
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
        if (playing) {
            for (auto& object : objects)
            {
                object.second->draw();
            }

            // super urat, imi cer scuze la domnul programator
            shared_ptr<Healthbar> healthbar = dynamic_pointer_cast<Healthbar>(Scene::get_object("zzz"));
            char str[20];
            snprintf(str, sizeof(str), "SCORE: %d", healthbar->scor);
            Scene::displayText(healthbar->centru.getX() - 15, healthbar->centru.getY() - 50, str);

            snprintf(str, sizeof(str), "LEVEL: %d", lvl);
            Scene::displayText(healthbar->centru.getX() - 15, healthbar->centru.getY() - 75, str);
        }
        else {
            glClearColor(0, 0, 0, 1);
            Scene::displayText(Screen::get_width() / 2 - 50, Screen::get_height() / 2, "YOU DIED");
            shared_ptr<Healthbar> healthbar = dynamic_pointer_cast<Healthbar>(Scene::get_object("zzz"));
            char str[20];
            snprintf(str, sizeof(str), "SCORE: %d", healthbar->scor);
            Scene::displayText(Screen::get_width() / 2 - 50, Screen::get_height() / 2 - 50, str);

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

    static void keyPress(int key, int x, int y) {
        for (auto& object : objects)
        {
            object.second->keyPress(key, x, y);
        }
        glutPostRedisplay();
    }

    static void keyUp(int key, int x, int y) {
        for (auto& object : objects)
        {
            object.second->keyUp( key, x, y);
        }
    }

    static int get_objects_len(void)
    {
        return objects.size();
    }

    static double get_movement_speed(void) {
        return movement_speed;
    }


    static void displayText(int x, int y, const char* string)
    {
        glColor4f(1.0f, 1.0f, 1.0f, 0.8);
        glRasterPos2f(x, y);
        for (int i = 0; i < strlen(string); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
        }
    }

};

map<string, shared_ptr<Object>> Scene::objects;
double Scene::movement_speed = 0.25;
bool Scene::playing = TRUE;
int Scene::lvl = 1;
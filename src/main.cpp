#define _USE_MATH_DEFINES

#include <windows.h>
#include <queue>
#include <gl/freeglut.h>
#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <cmath>
#include <fstream>
#include "Cow.h"
#include "Cows.h"
#include "Hamburger.h"
#include "Scene.h"
#include "Screen.h"
#include "Strada.h"
using namespace std;

bool game_loop() {
    Scene::get_object("cows");
    return true;
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cow Invaders 2000");
    Cow::init();
    init();

    shared_ptr<Strada> strada = make_shared<Strada>(Strada(0));

    shared_ptr<Cows> cows = make_shared<Cows>(Cows());

    Scene::add_object("strada", strada);
    Scene::add_object("tcows", cows);


    glutIdleFunc(Scene::update);
    glutDisplayFunc(Scene::draw);
    glutReshapeFunc(reshape);
    glutMouseFunc(Scene::mouse);
    glutMainLoop();
}
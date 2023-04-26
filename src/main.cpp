#define _USE_MATH_DEFINES

#include <windows.h>
#include <gl/freeglut.h>
#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <cmath>
#include <fstream>
#include "Cow.h"
#include "Hamburger.h"
#include "Scene.h"
#include "Screen.h"
#include "Pahar.h"
#include "Strada.h"
using namespace std;

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cow Invaders 2000");
    Cow::init();
    init();

    // shared_ptr<Square> square1 = make_shared<Square>(Square(0, 100, 20, 0.05, 0, 0, -0.06));
    shared_ptr<Strada> strada = make_shared<Strada>(Strada(0));
    // shared_ptr<Line> line1 = make_shared<Line>(Line(Screen::get_width() / 2, 0, Screen::get_width() / 2, Screen::get_height() / 2));
    shared_ptr<Hamburger> hamburger = make_shared<Hamburger>(Hamburger(300, 300));
    shared_ptr<Cow> cow = make_shared<Cow>(Cow(150, 150, 0));
    shared_ptr<Pahar> pahar = make_shared<Pahar>(Pahar(435, 200));

    // Scene::add_object("square1", square1);
    Scene::add_object("strada", strada);
    Scene::add_object("xamburger", hamburger);
    Scene::add_object("zow1", cow);
    Scene::add_object("zahar", pahar);

    glutIdleFunc(Scene::update);
    glutDisplayFunc(Scene::draw);
    glutReshapeFunc(reshape);
    glutMouseFunc(Scene::mouse);
    glutMainLoop();
}
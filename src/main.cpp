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
#include "Pahar.h"
#include "Strada.h"
#include "Healthbar.h"
using namespace std;

bool game_loop() {
    Scene::get_object("cows");
    return true;
}

bool game_loop() {
    Scene::get_object("cows");
    return true;
}

void main(int argc, char **argv)
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
    // shared_ptr<Line> line1 = make_shared<Line>(Line(Screen::get_width() / 2, 0, Screen::get_width() / 2, Screen::get_height() / 2));

    shared_ptr<Healthbar> hbar = make_shared<Healthbar>(Healthbar(30, 550));


    shared_ptr<Pahar> pahar = make_shared<Pahar>(Pahar(435, 200));
    shared_ptr<Cow> cow1 = make_shared<Cow>(Cow(150, 150, 0, 1, 1, 1, false, 5));
    shared_ptr<Cow> cow2 = make_shared<Cow>(Cow(450, 450, 0, 0, 0, 0, true, 10));

    Scene::add_object("strada", strada);
    Scene::add_object("tcows", cows);
    Scene::add_object("zahar", pahar);
    Scene::add_object("zow1", cow1);
    Scene::add_object("zow2", cow2);
    Scene::add_object("zzz", hbar);


    glutIdleFunc(Scene::update);
    glutDisplayFunc(Scene::draw);
    glutReshapeFunc(reshape);
    glutMouseFunc(Scene::mouse);
    glutSpecialFunc(Scene::keyPress);
    glutSpecialUpFunc(Scene::keyUp);
    glutMainLoop();
}
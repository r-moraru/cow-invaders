#pragma once
#define _USE_MATH_DEFINES

#include <windows.h>
#include <gl/freeglut.h>
#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <cmath>
#include <chrono>
#include <fstream>
#include "Object.h"
#include "Screen.h"
using namespace std;



class Strada : public Object {
private:
	// Punctul la care se imparte banda.
	// Banda e formata din doua linii care sunt translatate in jos.
	// Punctul de separare este initial la limita de sus a ecranului.
	// Cand punctul ajunge in limita de jos, liniile sunt resetate.
	// Poz banda este un procent din spatiul de pe ecran.
	double poz_banda;

public:
	Strada(double poz_banda) : poz_banda(poz_banda) { ; }

	void draw() {
		// asfalt
		glColor3f(0.2, 0.2, 0.2);
		glRectf(0., 0., Screen::get_width(), Screen::get_height());

		// iarba
		glColor3f(0, 0.4, 0);
		glRectf(0., 0., Screen::get_width() / 5, Screen::get_height());
		glRectf(4 * Screen::get_width() / 5, 0., Screen::get_width(), Screen::get_height());

		// banda de separare
		glPushMatrix();
		glTranslated(0, -poz_banda, 0);

		glColor3f(1, 1, 1);

		glEnable(GL_LINE_STIPPLE);
		glLineWidth(20);
		glLineStipple(7, 0xFFFC);

		glBegin(GL_LINES);

		glVertex2d(Screen::get_width() / 2.0, 0);
		glVertex2d(Screen::get_width() / 2.0, Screen::get_height() + 7 * 16);

		glEnd();

		glPopMatrix();
	}

	void update() {
		using namespace std::chrono;
		uint64_t current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		uint64_t delta_time = current_time - last_update;
		last_update = current_time;

		double delta_y = Scene::get_movement_speed() * delta_time;

		poz_banda += delta_y;
		if (poz_banda >= 7 * 16) {
			poz_banda = 0;
		}
	}

	void mouse(int button, int state, int x, int y) { ; }
};
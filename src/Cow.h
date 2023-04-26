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
#include "Point.h"
using namespace std;

class Cow : public Object {
private:
	Point centru;
	double unghi_rotatie;
	int marime = 5;
	static vector<Point> puncte_vaca;
public:
	Cow(double centru_x, double centru_y, double unghi_rotatie) {
		this->centru.setX(centru_x);
		this->centru.setY(centru_y);
		this->unghi_rotatie = unghi_rotatie;
	}

	static void init() {
		ifstream vaca_txt("vaca.txt");
		if (vaca_txt.is_open()) {
			int x, y;
			while (vaca_txt) {
				vaca_txt >> x >> y;
				puncte_vaca.push_back(Point(x, y));
			}
			vaca_txt.close();
			std::cout << puncte_vaca.size();
		}
	}

	void draw() override {
		glPushMatrix();
		glTranslated(centru.getX(), centru.getY(), 0.0);
		glRotated(unghi_rotatie, 0.0, 0.0, 1.0);
		glColor3f(0.0, 0.0, 0.0);

		glPointSize(1.0 * marime);
		glBegin(GL_POINTS);
		for (int i = 0; i < 140; i++) {
			glVertex2i(puncte_vaca[i].getX() * marime, puncte_vaca[i].getY() * marime);
		}
		glColor3f(1, 0.65, 0.75);
		for (int i = 140; i < puncte_vaca.size(); i++) {
			glVertex2i(puncte_vaca[i].getX() * marime, puncte_vaca[i].getY() * marime);
		}
		glEnd();
		glFlush();

		glPopMatrix();
	}

	void update() { ; }
	void mouse(int button, int state, int x, int y) { ; }
};

vector<Point> Cow::puncte_vaca = vector<Point>();
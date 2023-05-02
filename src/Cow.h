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
#include "Point.h"
#include "Scene.h"
using namespace std;

class Cow : public Object
{
public:

	Point centru;
	double unghi_rotatie;
	int marime;
	static vector<Point> puncte_vaca;
	double culoareR, culoareG, culoareB;
	bool ochi_rosu;

	Cow(double centru_x, double centru_y, double unghi_rotatie, double culoareR, double culoareG, double culoareB, bool ochi_rosu, int marime)
	{
		this->centru.setX(centru_x);
		this->centru.setY(centru_y);
		this->unghi_rotatie = unghi_rotatie;
		this->culoareR = culoareR;
		this->culoareG = culoareG;
		this->culoareB = culoareB;
		this->marime = marime;
		this->ochi_rosu = ochi_rosu;
	}

	static void init()
	{
		ifstream vaca_txt("vaca.txt");
		if (vaca_txt.is_open())
		{
			int x, y;
			while (vaca_txt)
			{
				vaca_txt >> x >> y;
				puncte_vaca.push_back(Point(x, y));
			}
			vaca_txt.close();
		}
	}

	void draw()
	{
		glPushMatrix();
		glTranslated(centru.getX(), centru.getY(), 0.0);
		glRotated(unghi_rotatie, 0.0, 0.0, 1.0);
		glColor3f(0.0, 0.0, 0.0);

		glPointSize(1.0 * marime);
		glBegin(GL_POINTS);
		for (int i = 0; i < 136; i++)
		{
			glVertex2i(puncte_vaca[i].getX() * marime, puncte_vaca[i].getY() * marime);
		}
		glColor3f(1, 0.65, 0.75);
		for (int i = 136; i < 167; i++)
		{
			glVertex2i(puncte_vaca[i].getX() * marime, puncte_vaca[i].getY() * marime);
		}
		glColor3f(culoareR, culoareG, culoareB);
		for (int i = 167; i < 264; i++)
		{
			glVertex2i(puncte_vaca[i].getX() * marime, puncte_vaca[i].getY() * marime);
		}
		if (ochi_rosu)
		{
			glColor3f(1, 0, 0);
		}
		else
		{
			glColor3f(0, 0, 0);
		}

		for (int i = 264; i < puncte_vaca.size(); i++)
		{
			glVertex2i(puncte_vaca[i].getX() * marime, puncte_vaca[i].getY() * marime);
		}

		glEnd();
		glFlush();

		glPopMatrix();
	}

	void update() {
		using namespace std::chrono;
		uint64_t current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		uint64_t delta_time = current_time - last_update;
		last_update = current_time;

		double delta_y = Scene::get_movement_speed() * delta_time;
		centru.setY(centru.getY() - delta_y);
	}

	Point get_pos() {
		return centru;
	}

	bool has_red_eyes() {
		return ochi_rosu;
	}

	vector<Point> get_puncte() {
		return puncte_vaca;
	}

	void mouse(int button, int state, int x, int y) { ; }
};

vector<Point> Cow::puncte_vaca = vector<Point>();

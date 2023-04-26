#pragma once

#include <ctime>
#include <vector>
#include <random>

#include "Object.h"
#include "Cow.h"
#include "Scene.h"
#include "Screen.h"

using namespace std;

class Cows : public Object {
private:
	vector<Cow> cows;
	time_t last_spawn, spawn_wait;
public:
	Cows() : last_spawn(time(NULL)), spawn_wait(2.0) { srand(time(NULL)); }

	void draw() {
		for (auto& cow : cows) {
			cow.draw();
		}
	}

	void update() {
		spawn_cow();
		for (auto& cow : cows) {
			cow.update();
		}
		
		for (int i = cows.size() - 1; i >= 0; i--) {
			if (cows[i].get_pos().getY() < -100) {
				cows.erase(cows.begin()+i);
			}
			// TODO: check if any cow is consumed by glass and update score accordingly
		}
	}

	void mouse(int button, int state, int x, int y) { ; }

	void spawn_cow() {
		if (time(NULL) < last_spawn + spawn_wait) {
			return;
		}

		int spawn_pos = rand() % (Screen::get_width() - 50) + 50;
		spawn_wait = (rand() % 4 + 1) / 2.0 + 1;
		last_spawn = time(NULL);

		cows.push_back(Cow(spawn_pos, Screen::get_height()+100.0, 0,
			(rand() % 100) / 99.0, (rand() % 100) / 99.0, (rand() % 100) / 99.0,
			rand() % 4 == 0 ? true : false, rand() % 4 + 3));
	}
};
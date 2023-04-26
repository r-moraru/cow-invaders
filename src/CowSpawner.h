#pragma once
#include <ctime>

#include <Cow.h>
#include <Object.h>
#include <Screen.h>
#include <Scene.h>

class Cows : public Object {
private:
	time_t last_call_time;
	time_t wait_time;
public:
	CowSpawner() : last_call_time(time(NULL)), wait_time(2.0) { ; }

	void spawnCow() {
		if (time(NULL) < last_call_time + wait_time) {
			continue;
		}
		int x_pos = 200;
	}
};
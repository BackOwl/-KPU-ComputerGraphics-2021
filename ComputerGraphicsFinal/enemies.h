#pragma once
#include <vector>
#include "enemy.h"

void update_enemy(std::vector<Enemy>* e, std::vector<Bullet>* e_b, std::vector<Bullet>* p_b, float pl_x, float pl_z, float time) {
	for (int i = 0; i < e->size(); ++i) {
		(*e)[i].Update(e_b, p_b, pl_x, pl_z, time);
	}
}

void draw_enemy(std::vector<Enemy>* e, unsigned int modelLocation, unsigned int colorLocation, int numTriangle) {
	for (int i = 0; i < e->size(); ++i) {
		(*e)[i].Draw(modelLocation, colorLocation, numTriangle);
	}
}
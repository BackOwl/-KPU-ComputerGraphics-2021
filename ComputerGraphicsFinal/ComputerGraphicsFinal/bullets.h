#pragma once
#include <vector>
#include "bullet.h"

void update_bullet(std::vector<Bullet>* v, float time) {
	for (int i = 0; i < v->size(); ++i) {
		(*v)[i].Update(time);

	}

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int i = 0;
	for (std::vector<Bullet>::iterator it = v->begin(); it != v->end(); it++)
	{
		if ((*v)[i].len_check()) {
			it = v->erase(it);
			break;
		}
		++i;
	}

}

void draw_bullet(std::vector<Bullet>* v, unsigned int modelLocation, unsigned int colorLocation, int numTriangle) {
	for (int i = 0; i < v->size(); ++i) {
		(*v)[i].Draw(modelLocation, colorLocation, numTriangle);
	}
}
#pragma once
#ifndef enemy_
#define enemy_
#include "character.h"

class Enemy : public Character {
private:
public:
	Enemy(float in_x, float in_y, float in_z) {
		x = in_x; y = in_y; z = in_z;
		x_width = height = z_width = 0.1; // 충돌처리시 사용
		speed = 5.0;
	};
	~Enemy() = default;

	void Enemy_Move(float pl_x, float pl_z, float time);

	void Update(float pl_x, float pl_z, float time);
	void Draw(unsigned int modelLocation, unsigned int colorLocation, int numTriangle);
};

#endif
#pragma once
#ifndef enemy_
#define enemy_
#include "character.h"
#include <vector>

class Enemy : public Character {
private:
	float len;
public:
	Enemy(float in_x, float in_y, float in_z) {
		x = in_x; y = in_y; z = in_z;
		x_width = height = z_width = 0.1; // 충돌처리시 사용
		speed = 6.0;
		len = 15.0;
		gun = Gun(x, y, z, x_angle, y_angle);
	};
	~Enemy() = default;

	void Enemy_Move(float pl_x, float pl_z, float time);

	void Update(std::vector<Bullet>* e_b, std::vector<Bullet>* p_b, float pl_x, float pl_z, float time);
	void Draw(unsigned int modelLocation, unsigned int colorLocation, int numTriangle);
};

#endif
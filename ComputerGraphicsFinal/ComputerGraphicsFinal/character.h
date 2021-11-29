#pragma once
#include "gun.h"
#ifndef character_
#define character_

class Character {
protected:
	float x, y, z;
	float x_width, height, z_width; // 충돌처리시 사용
	float speed;
	float x_angle, y_angle;	// 현재 보고 있는 곳이 어딘지 알기 위해 캐릭터 각도 표시, 총알 발사. 주인공이 보고 있는 곳등에 쓰일 예정

	Gun* gun;
public:
	Character() = default;
	~Character() = default;

	void GetPos(float* input_x, float* input_y, float* input_z);
	float GetXangle();
	float GetYangle();
};

#endif
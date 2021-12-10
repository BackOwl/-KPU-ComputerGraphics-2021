#pragma once
#include "gun.h"
#include "bullet.h"
#ifndef character_
#define character_

class Character {
protected:
	float x, y, z;
	float x_width, height, z_width; // 충돌처리시 사용
	float speed;
	float x_angle, y_angle;	// 현재 보고 있는 곳이 어딘지 알기 위해 캐릭터 각도 표시, 총알 발사. 주인공이 보고 있는 곳등에 쓰일 예정
public:
	Gun gun;

	Character() = default;
	~Character() = default;

	void Move_Right(float time);
	void Move_Left(float time);
	void Move_Front(float time);
	void Move_Back(float time);

	void GetPos(float* input_x, float* input_y, float* input_z);
	float GetXangle();
	float GetYangle();
	bool collide_bullet(std::vector<Bullet>* v);	// 충돌 처리
};

#endif
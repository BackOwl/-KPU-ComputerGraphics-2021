#pragma once
#include "character.h"
#ifndef player_
#define player_

class Player : public Character {
private:
	bool jump_bool;	// 현재 점프 중인지 판별
	float jump_power;

public:
	Player() {
		jump_bool = false;
		jump_power = 0.0;

		x = 0.0; y = 0.0; z = -10.0;	// 추후 스테이지 정보에서 플레이어 시작 좌표 받아오게  
		x_width = 0.4; height = 1.0, z_width = 0.2; // 충돌처리시 사용, 추후 적절한 값 찾아 수정 필요
		x_angle = 0.0; y_angle = 0.0;
		speed = 1.0;	// 적절한 값으로 수정 필요
		shot_bool = false;	// 총을 쏠 수 있는 상태인지
	};
	~Player() = default;

	void Move_Right();
	void Move_Left();
	void Move_Front();
	void Move_Back();

	void Rotate(int mouse_x, int mouse_y, float time);	// 마우스 좌표에 따라 회전.  현재 마우스 좌표 - 이전 마우스 좌표의 값을 받아온다 
};

#endif
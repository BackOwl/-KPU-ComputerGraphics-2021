#include "player.h"
#include <iostream>

void Player::Update(std::vector<Bullet>* v, int window_x, int window_y, int width, int height, float slow_time)
{
	float result = 0.0;
	if (x <= 50.0) {
		result = x;
	}
	else {
		result = -50.0;
	}
	if (result < -50.0) result = -50.0;

	x = result;
	result = 0.0;
	if (z <= 50.0) {
		result = z;
	}
	else {
		result = 50.0;
	}
	if (result < -50.0) result = -50.0;
	
	z = result;
	Rotate(window_x, window_y, width, height);
	gun.Set(x, y, z, x_angle, y_angle);
	gun.Update(slow_time);
	collide_bullet(v);
}

void Player::Rotate(int x, int y, int width, int height)	// 마우스 좌표에 따라 회전
{
	POINT current_mouse;
	GetCursorPos(&current_mouse);
	int x_dist = current_mouse.x - (x + width / 2);
	int y_dist = current_mouse.y - (y + height / 2);

	x_angle += (float)x_dist / 30;	// 감도 조정 필요
	y_angle += (float)y_dist / 30;

	if (y_angle < -90.0) {
		y_angle = -90.0;
	}
	if (y_angle > 90.0) {
		y_angle = 90.0;
	}
	
	SetCursorPos(x + width / 2, y + height / 2);	// 임시로 해놓은것 화면 중앙 좌표
}

#include "player.h"
#include <iostream>

void Player::Move_Right() 
{

}

void Player::Move_Left()
{

}
void Player::Move_Front()
{

}
void Player::Move_Back() 
{

}

void Player::Rotate(int mouse_x, int mouse_y, float time)	// 마우스 좌표에 따라 회전.  현재 마우스 좌표 - 이전 마우스 좌표의 값을 받아온다 
{
	if (mouse_x < 50 && mouse_x > -50 && mouse_y < 50 && mouse_y > -50) {
		x_angle += (float)mouse_x * time * 3.0;
		y_angle += (float)mouse_y * time * 3.0;
	}

	//std::cout << "time = " << time << ", x_angle = " << x_angle << ", y_angle = " << y_angle << std::endl;

	if (y_angle < -90.0) {
		y_angle = -90.0;
	}
	if (y_angle > 90.0) {
		y_angle = 90.0;
	}
}
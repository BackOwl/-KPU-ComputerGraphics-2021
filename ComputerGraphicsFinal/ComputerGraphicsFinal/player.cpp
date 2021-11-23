#include "player.h"


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

void Player::Rotate(int mouse_x, int mouse_y)	// 마우스 좌표에 따라 회전.  현재 마우스 좌표 - 이전 마우스 좌표의 값을 받아온다 
{
	x_angle += (float)mouse_x / 5.0;
	y_angle += (float)mouse_y / 10.0;
	if (y_angle < -90.0) {
		y_angle = -90.0;
	}
	if (y_angle > 90.0) {
		y_angle = 90.0;
	}
}
#include "character.h"

void Character::GetPos(float* input_x, float* input_y, float* input_z) 
{
	*input_x = x;
	*input_y = y;
	*input_z = z;
}

float Character::GetXangle() { return x_angle; }
float Character::GetYangle() { return y_angle; }


void Character::Move_Right(float time)
{
	x -= speed * time * cos(glm::radians(x_angle));
	z -= speed * time * sin(glm::radians(x_angle));
}

void Character::Move_Left(float time)
{
	x += speed * time * cos(glm::radians(x_angle));
	z += speed * time * sin(glm::radians(x_angle));
}
void Character::Move_Front(float time)
{
	x += speed * time * -sin(glm::radians(x_angle));
	z += speed * time * cos(glm::radians(x_angle));
}
void Character::Move_Back(float time)
{
	x -= speed * time * -sin(glm::radians(x_angle));
	z -= speed * time * cos(glm::radians(x_angle));
}

#include <iostream>

void Character::collide_bullet(std::vector<Bullet>* v)
{
	float b_x, b_y, b_z;
	float len;
	for (int i = 0; i < v->size(); ++i) {
		(*v)[i].GetPos(&b_x, &b_y, &b_z);

		len = sqrt(pow(b_x - x, 2) + pow(b_y - y, 2) + pow(b_z - z, 2));
		if (len < x_width) {
			printf("test");
		}
	}
}
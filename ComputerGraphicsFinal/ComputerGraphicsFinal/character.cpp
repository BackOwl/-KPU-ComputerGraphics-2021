#include "character.h"

void Character::GetPos(float* input_x, float* input_y, float* input_z) 
{
	*input_x = x;
	*input_y = y;
	*input_z = z;
}

float Character::GetXangle() { return x_angle; }
float Character::GetYangle() { return y_angle; }
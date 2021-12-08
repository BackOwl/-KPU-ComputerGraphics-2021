#include "enemy.h"
#include <iostream>

void Enemy::Enemy_Move(float pl_x, float pl_z, float time)
{
	if (pl_x > x) {
		Move_Left(time);
	}
	else if (pl_x < x) {
		Move_Right(time);
	}

	if (pl_z > z) {
		Move_Front(time);
	}
	else if (pl_z < z) {
		Move_Back(time);
	}
}


void Enemy::Update(float pl_x, float pl_z, float time)
{
	Enemy_Move(pl_x, pl_z, time);
}


void Enemy::Draw(unsigned int modelLocation, unsigned int colorLocation, int numTriangle)
{
	//printf("draw");
	glm::mat4 Si = glm::scale(glm::mat4(1.0f), glm::vec3(x_width, height, z_width));
	glm::mat4 Tr = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	glm::mat4 End = Tr * Si;
	glUniform3f(colorLocation, 0.5, 0.5, 0.5);	// 색 추후 지정
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(End));

	glDrawArrays(GL_TRIANGLES, 0, numTriangle);

}
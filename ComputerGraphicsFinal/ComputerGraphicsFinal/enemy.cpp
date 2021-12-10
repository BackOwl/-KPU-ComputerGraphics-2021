#include "enemy.h"
//#include <iostream>

void Enemy::Enemy_Move(float pl_x, float pl_z, float time)
{
	x_angle = atan2(x - pl_x, pl_z - z);
	x_angle = x_angle * 180.0 / 3.14159265358979;
	len = sqrt(pow(x - pl_x, 2) + pow(z - pl_z, 2));
	
	if (len > 7.0) {
		Move_Front(time);
	}
}


void Enemy::Update(std::vector<Bullet>* e_b, std::vector<Bullet>* p_b, float pl_x, float pl_z, float time)
{
	Enemy_Move(pl_x, pl_z, time);
	gun.Update(time);
	if (len < 10.0) {
		if (gun.Shot()) {
			e_b->push_back(Bullet(x, y, z, x_angle, y_angle, false));
		}
	}
	collide_bullet(p_b);
}


void Enemy::Draw(unsigned int modelLocation, unsigned int colorLocation, int numTriangle)
{
	glm::mat4 Si = glm::scale(glm::mat4(1.0f), glm::vec3(x_width, height, z_width));
	glm::mat4 Tr = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	glm::mat4 End = Tr * Si;
	glUniform3f(colorLocation, 0.5, 0.5, 0.5);	// 색 추후 지정
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(End));

	glDrawArrays(GL_TRIANGLES, 0, numTriangle);

}
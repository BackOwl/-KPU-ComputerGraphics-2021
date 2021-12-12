#include "gun.h"
//#include <iostream>

void Gun::Draw(unsigned int modelLocation, unsigned int colorLocation, int numTriangle) {

	glm::mat4 Si = glm::scale(glm::mat4(1.0f), glm::vec3(0.05, 0.05, 0.05));
	glm::mat4 Tr = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	glm::mat4 Rt =
		glm::rotate(glm::mat4(1.0f), glm::radians(float(-x_angle - 15.0)), glm::vec3(0.0, 1.0, 0.0))
		* glm::rotate(glm::mat4(1.0f), glm::radians(float(y_angle)), glm::vec3(1.0, 0.0, 0.0))
		* glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.5))
		* glm::rotate(glm::mat4(1.0f), glm::radians(float(-60.0)), glm::vec3(0.0, 1.0, 0.0))
		* glm::rotate(glm::mat4(1.0f), glm::radians(float(shot_angle)), glm::vec3(0.0, 0.0, 1.0));
	glm::mat4 End = Tr * Rt * Si;
	glUniform3f(colorLocation, 0.0, 0.0, 0.0);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(End));

	glDrawArrays(GL_TRIANGLES, 0, numTriangle);
}

void Gun::Update(float time)
{
	if (!shot_bool) {
		shot_power -= 800.0 * time;
		shot_angle += shot_power * time;
		if (shot_angle <= 0) {
			shot_angle = 0;
			shot_bool = true;
		}
	}
}


bool Gun::Shot()
{
	if (shot_bool) {
		shot_bool = false;
		shot_power = 300.0;
		
		return true;
	}
	else {
		return false;
	}
}

void Gun::Set(float in_x, float in_y, float in_z, float in_x_angle, float in_y_angle) {
	//shot_bool = true;
	//shot_power = 0.0;
	//shot_timer = 0.0;

	x = in_x; y = in_y; z = in_z;
	size = 1.0;	// 이후 변경
	x_angle = in_x_angle;
	y_angle = in_y_angle;
};
#include "bullet.h"

void Bullet::Update(float time) {
	x += speed * time * -sin(glm::radians(x_angle));
	z += speed * time * cos(glm::radians(x_angle));
	y += speed * time * sin(glm::radians(-y_angle));

	len = sqrt(pow(x - start_x, 2) + pow(y - start_y, 2) + pow(z - start_z, 2));
	if (len < 2.0) {
		z_width = len;
	}
	
}

void Bullet::Draw(unsigned int modelLocation, unsigned int colorLocation, int numTriangle) {
	glm::mat4 Si = glm::scale(glm::mat4(1.0f), glm::vec3(x_width, height, z_width));
	glm::mat4 Tr = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	glm::mat4 Rt =
		glm::rotate(glm::mat4(1.0f), glm::radians(float(-x_angle)), glm::vec3(0.0, 1.0, 0.0))
		* glm::rotate(glm::mat4(1.0f), glm::radians(float(y_angle)), glm::vec3(1.0, 0.0, 0.0))
		* glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -z_width  / 2));
	glm::mat4 End = Tr * Rt * Si;
	//glm::mat4 Light = Tr * Si;
	glUniform3f(colorLocation, 1.0, 0.0, 0.0);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(End));

	glDrawArrays(GL_TRIANGLES, 0, numTriangle);
}

bool Bullet::len_check() {
	if (len > 10.0) {
		return true;
	}
	return false;
}

void Bullet::GetPos(float* input_x, float* input_y, float* input_z)
{
	*input_x = x;
	*input_y = y;
	*input_z = z;
}
#include "gun.h"

void Gun::Draw(unsigned int modelLocation, unsigned int colorLocation, int numTriangle) {

	glm::mat4 Si = glm::scale(glm::mat4(1.0f), glm::vec3(0.05, 0.05, 0.05));
	glm::mat4 Tr = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	glm::mat4 Rt = glm::rotate(glm::mat4(1.0f), glm::radians(float(y_angle)), glm::vec3(1.0, 0.0, 0.0))
		//* glm::translate(glm::mat4(1.0f), glm::vec3(1.0, 0.0, 0.0))
		* glm::rotate(glm::mat4(1.0f), glm::radians(float(-x_angle - 15.0)), glm::vec3(0.0, 1.0, 0.0))
		* glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.5))
		* glm::rotate(glm::mat4(1.0f), glm::radians(float(-60.0)), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 End = Tr * Rt * Si;
	//glm::mat4 Light = Tr * Si;
	glUniform3f(colorLocation, 0.0, 0.0, 0.0);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(End));

	glDrawArrays(GL_TRIANGLES, 0, numTriangle);
}
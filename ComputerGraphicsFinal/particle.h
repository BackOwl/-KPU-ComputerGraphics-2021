#pragma once
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glew.h>
#include <gl/glm/ext.hpp>
#include <vector>
#include <iostream>
#ifndef particle_
#define particle_

class Particle {
private:
	float own_x, own_y;
	float speed;
	float angle;
	float r, g, b, a;
	float size;
public:
	Particle() {
		own_x = 0; own_y = 0;
		speed = (float)(rand() % 10000) / (float)(10000) * -0.8 + 1.0;
		angle = (float)(rand() % 10000) / (float)(10000) * 360.0;
		r = (float)(rand() % 10000) / (float)(10000);
		g = (float)(rand() % 10000) / (float)(10000);
		b = (float)(rand() % 10000) / (float)(10000);
		size = 0.05;
	}
	~Particle() = default;

	void Update(float deltaTime)
	{
		own_x += deltaTime * speed * cos(angle);
		own_y += deltaTime * speed * sin(angle);
	}

	void Draw(int x, int y, int z, float ch_angle, unsigned int modelLocation, unsigned int colorLocation, int numTriangle) {
		glm::mat4 Si = glm::scale(glm::mat4(1.0f), glm::vec3(size, size, size));
		glm::mat4 Tr = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
		glm::mat4 Rt = glm::rotate(glm::mat4(1.0f), glm::radians(float(-ch_angle)), glm::vec3(0.0, 1.0, 0.0))
			* glm::translate(glm::mat4(1.0f), glm::vec3(own_x, own_y, 0));
		glm::mat4 End = Tr * Rt * Si;
		//glm::mat4 Light = Tr * Si;
		glUniform3f(colorLocation, r, g, b);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(End));
		glDrawArrays(GL_POLYGON, 0, numTriangle);
	}
};

class ParticleSystem {
private:
	float x, y, z;
	float time;	// 일정 시간 지나면 사라짐
	std::vector<Particle> p;
public:

	ParticleSystem(float in_x, float in_y, float in_z) {
		x = in_x;
		y = in_y;
		z = in_z;
		time = 0.0;
		for (int i = 0; i < 100; ++i) {
			p.push_back(Particle());
		}
	}
	~ParticleSystem() = default;

	bool Update(float time_) {
		time += time_;
		if (time > 2.0) {
			p.clear();
			return true;
		}

		for (int i = 0; i < p.size(); ++i) {
			p[i].Update(time_);
		}
		
		return false;
	}

	void Draw(float ch_angle, unsigned int modelLocation, unsigned int colorLocation, int numTriangle) {
		for (int i = 0; i < p.size(); ++i) {
			p[i].Draw(x, y, z, ch_angle, modelLocation, colorLocation, numTriangle);
		}
	}
};


#endif
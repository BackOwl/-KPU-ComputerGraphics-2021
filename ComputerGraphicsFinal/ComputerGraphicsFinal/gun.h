#pragma once
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glew.h>
#include <gl/glm/ext.hpp>
#ifndef gun_
#define gun_

class Gun {
private:
	bool shot_bool;	
	float shot_power;
	//float shot_timer;
	float shot_angle;
	float x_angle, y_angle;
	float x, y, z;
	float size;

public:
	Gun() = default;
	Gun(float in_x, float in_y, float in_z, float in_x_angle, float in_y_angle) {
		shot_bool = true;
		shot_power = 0.0;
		//shot_timer = 0.0;
		shot_angle = 0.0;

		x = in_x; y = in_y; z = in_z;
		size = 1.0;	// 이후 변경
		x_angle = in_x_angle;
		y_angle = in_y_angle;
	};
	~Gun() = default;
	
	void Set(float in_x, float in_y, float in_z, float in_x_angle, float in_y_angle);	// 캐릭터 객체 위치 + 각도 업데이트

	void Update(float time);	// 총 반동 각도 update 시켜줌

	void Draw(unsigned int modelLocation, unsigned int colorLocation, int numTriangle);

	bool Shot();	// 총 발사 가능한지 체크 & 총 반동 시작.
	
	void Pos();


};

#endif
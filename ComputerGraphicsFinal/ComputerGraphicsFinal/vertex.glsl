#version 330 core

layout (location = 0) in vec3 vPos; //--- 위치 변수: attribute position 0
layout (location = 1) in vec3 vNormal;

out vec3 outColor; //--- 컬러를 fragment shader로 출력
out vec3 lightColor;
out vec3 lightPos;
out vec3 viewPos;
out float ambientlight;
out float Shininess;

out vec3 FragPos; //--- 객체의 위치값을 프래그먼트 세이더로 보낸다.
out vec3 Normal; //--- 노멀값을 프래그먼트 세이더로 보낸다.

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;


uniform vec3 objectColor;
uniform vec3 lightColo;
uniform vec3 lightPo;
uniform vec3 viewPo;
uniform float ambientLigh;
uniform float Shinines;

void main()
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vPos, 1.0);
	FragPos = vec3(modelTransform * vec4(vPos, 1.0)); //--- vertex data로부터 가져온 컬러 입력을 ourColor에 설정
	Normal = vec3(transpose(inverse(modelTransform)) * vec4(vNormal, 1.0));

	outColor = objectColor;
	lightColor = lightColo;
	lightPos = lightPo;
	viewPos = viewPo;
	ambientlight = ambientLigh;
	Shininess = Shinines;
} 
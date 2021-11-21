#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <random>
#include <malloc.h>
#include <stdio.h>
/////
#pragma comment(lib,"winmm")
#include < mmsystem.h> 
// SND_ASUNC = 재생중에도 프로그램이 계속 돌아감	
// SND_SYNC = 재생이 끝나야 프로그램이 돌아감
// SND_FILENAME  = 매개 변수가 파일이름일떄 
// SND_LOOP  = 반복재생
// SND_PURGE = 재생중지 
// PlaySound(TEXT(SOUND_FILE_NAME), NULL,SND_ASYNC|SND_ALIAS);
/////

#include "filetobuf.h"
#include "obj.h"
#define weight 600
#define height 600
#pragma warning(disable:4996)

int num_Triangle;
GLuint vao, vbo[2];

bool make_vertexShader();
bool make_fragmentShaders();
GLuint make_shaderProgram();

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Timer(int value);
GLuint shaderID;


GLuint vertexShader, fragmentShader;
GLchar* vertexsource, * fragmentsource;


bool make_fragmentShaders()
{
	fragmentsource = filetobuf((char*)"fragment.glsl"); // 프래그세이더 읽어오기
	//--- 프래그먼트 세이더 읽어 저장하고 컴파일하기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentsource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader error\n" << errorLog << std::endl;
		return false;
	}
	return true;
}
bool make_vertexShader()
{
	vertexsource = filetobuf("vertex.glsl");
	//--- 버텍스 세이더 객체 만들기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexsource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexShader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return false;
	}
	return true;
}
void InitShader()
{
	make_vertexShader(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);
	//checkCompileErrors(s_program, "PROGRAM");
	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program 사용하기
	glUseProgram(shaderID);

}
void InitBuffer()
{
	Obj obj = loadObj("Resource\\gun.obj");

	num_Triangle = obj.num;

	glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
	glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, obj.outvertex.size() * sizeof(glm::vec3), &obj.outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, obj.outnormal.size() * sizeof(glm::vec3), &obj.outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	//glBindVertexArray(VAO[]);
	////--- 위치 속성
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[32]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(이름), 이름, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[]); //가리키는 번호 불러오기 
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(이름), 이름, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);



	////--- vPos 속성 변수에 값을 저장
	//GLint pAttribute = glGetAttribLocation(shaderID, "vPos");
	//glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	//glVertexAttribPointer(pAttribute, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	//glEnableVertexAttribArray(pAttribute);
	////--- vColor 속성 변수에 값을 저장
	//GLint cAttribute = glGetAttribLocation(shaderID, "vColor");
	//glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	//glVertexAttribPointer(cAttribute, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	//glEnableVertexAttribArray(cAttribute);

}
GLuint make_shaderProgram()
{
	make_vertexShader(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	GLuint s_pro;

	s_pro = glCreateProgram();
	glAttachShader(s_pro, vertexShader);
	glAttachShader(s_pro, fragmentShader);
	glLinkProgram(s_pro);


	GLint result;
	GLchar errorLog[512];

	glGetProgramiv(s_pro, GL_LINK_STATUS, &result); // ---세이더가 잘 연결되었는지 체크하기
	if (!result) {
		glGetProgramInfoLog(s_pro, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
		return false;
	}
	//glUseProgram(shaderID); //--- 만들어진 세이더 프로그램 사용하기
	//--- 여러 개의 세이더프로그램 만들 수 있고, 그 중 한개의 프로그램을 사용하려면
	//--- glUseProgram 함수를 호출하여 사용 할 특정 프로그램을 지정한다.
	//--- 사용하기 직전에 호출할 수 있다.

	glDeleteShader(vertexShader); //--- 세이더 객체를 세이더 프로그램에 링크했음으로, 세이더 객체 자체는 삭제 가능
	glDeleteShader(fragmentShader);

	glUseProgram(s_pro);
	return s_pro;
}


void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(weight, height); // 윈도우의 크기 지정
	glutCreateWindow("super hot"); // 윈도우 생성(윈도우 이름 )

	glEnable(GL_DEPTH_TEST);    //--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";


	InitShader();
	InitBuffer();
	shaderID = make_shaderProgram(); //--- 세이더 프로그램 만들기
	//glutTimerFunc(TIMEMIN, Timer, 0);

	glutDisplayFunc(drawScene); // 출력 콜백함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 콜백함수 지정
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // 이벤트 처리 시작

}

GLvoid drawScene() {
	GLfloat rColor, gColor, bColor;
	rColor = gColor = bColor = 1.0;

	PlaySound(TEXT("test1.wav"), NULL, SND_ASYNC | SND_ALIAS|SND_LOOP);

	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec3 cameraPos = glm::vec3(5.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);	//glm::cross(cameraDirection, cameraRight);
	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	view = glm::rotate(view, (GLfloat)glm::radians(float(30.0)), glm::vec3(1.0f, 0.0f, 0.0f));
	unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- 버텍스 세이더에서 viewTransform 변수위치
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(45.0f), (float)weight / (float)height, 0.1f, 50.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.0)); //--- 공간을 약간 뒤로 미뤄줌


	unsigned int projectionLocation = glGetUniformLocation(shaderID, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glUseProgram(shaderID);
	unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	unsigned int colorLocation = glGetUniformLocation(shaderID, "objectColor");
	int lightPosLocation = glGetUniformLocation(shaderID, "lightPo"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
	int lightColorLocation = glGetUniformLocation(shaderID, "lightColo"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	int ambient = glGetUniformLocation(shaderID, "ambientLigh");
	int shine = glGetUniformLocation(shaderID, "Shinines");
	int viewPos = glGetUniformLocation(shaderID, "viewPo");

	glUniform1f(shine, 128.0);
	glUniform1f(ambient, 1.0);

	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	glUniform3f(lightPosLocation, 0.0, 0.0, 0.0);

	glm::vec4 Viewl = glm::vec4(0.0, 0.0, 5.0, 0.0);

	Viewl = Viewl * glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(float(30.0)), glm::vec3(1.0f, 0.0f, 0.0f));

	glUniform3f(viewPos, Viewl.x, Viewl.y, Viewl.z);

	glBindVertexArray(vao);

	glm::mat4 Si = glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.2));
	//glm::mat4 Light = Tr * Si;
	glUniform3f(colorLocation, 0.0, 0.0, 0.0);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Si));

	glDrawArrays(GL_TRIANGLES, 0, num_Triangle);

	glutSwapBuffers();
}

GLvoid Timer(int value) {
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	int i = 0;
	switch (key) {
	}
}

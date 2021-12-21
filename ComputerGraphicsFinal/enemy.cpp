#include "enemy.h"
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
//////노래함수 //////
#pragma comment(lib,"winmm")
#include <mmsystem.h> 
#include "Digitalv.h"

MCI_OPEN_PARMS m_mciOpenParms1;
MCI_PLAY_PARMS m_mciPlayParms1;
DWORD m_dwDeviceID1;
MCI_OPEN_PARMS mciOpen1;
MCI_PLAY_PARMS mciPlay1;
MCI_DGV_SETAUDIO_PARMS SetAudio1;
int gunID1,walkID1;
DWORD dwVolume1 = 250;
//float walk_time1 = 0.45;


void Enemy::Enemy_Move(float pl_x, float pl_z, float time)
{
	x_angle = atan2(x - pl_x, pl_z - z);
	x_angle = x_angle * 180.0 / 3.14159265358979;
	len = sqrt(pow(x - pl_x, 2) + pow(z - pl_z, 2));
	
	if (len > 7.0) {
		Move_Front(time);

			//walk_time1 += 0.05;
			//if (walk_time1 > 1.0) {
			//	walk_time1 = 0.0;
			//	mciOpen1.lpstrElementName = L"Resource/Sound/walk_4.wav"; // 파일 경로 입력
			//	mciOpen1.lpstrDeviceType = L"mpegvideo";
			//	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen1);
			//	walkID1 = mciOpen1.wDeviceID;
			//	mciSendCommand(walkID1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&m_mciPlayParms1);
			//	mciSendCommand(walkID1, MCI_PLAY, 0, (DWORD)(LPVOID)&m_mciPlayParms1);

			//}


	}
}


void Enemy::Update(std::vector<Bullet>* e_b, std::vector<Bullet>* p_b, float pl_x, float pl_z, float time)
{
	Enemy_Move(pl_x, pl_z, time);
	gun.Update(time);
	if (len < 10.0) {
		if (gun.Shot()) {
			e_b->push_back(Bullet(x, y, z, x_angle, y_angle, false));

			mciOpen1.lpstrElementName = L"Resource/Sound/gun_2.wav"; // 파일 경로 입력
			mciOpen1.lpstrDeviceType = L"mpegvideo";
			SetAudio1.dwCallback = SetAudio1.dwOver = 0;
			SetAudio1.dwItem = MCI_DGV_SETAUDIO_VOLUME;
			SetAudio1.dwValue = dwVolume1; //소리크기 조절
			SetAudio1.lpstrAlgorithm = SetAudio1.lpstrQuality = NULL;
			mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen1);
			gunID1 = mciOpen1.wDeviceID;
			mciSendCommandW(gunID1, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&SetAudio1);
			mciSendCommand(gunID1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&m_mciPlayParms1);
			mciSendCommand(gunID1, MCI_PLAY, 0, (DWORD)(LPVOID)&m_mciPlayParms1);

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
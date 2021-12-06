#include "timer_.h"

float Timer_::DeltaTime()	// 화면 회전 등에 사용
{
	return deltaTime;
}

float  Timer_::SlowDeltaTime()	// 캐릭터 이동, 총알 이동, 총 발사 시 반동 등에 사용
{
	return deltaSlowTime;
}

void  Timer_::Update()
{
	QueryPerformanceCounter(&curTime);
	deltaTime = (static_cast<double>(curTime.QuadPart) - static_cast<double>(prevTime.QuadPart)) / static_cast<double>(tSecond.QuadPart);
	if (slow) {
		deltaSlowTime = deltaTime / 10.0;
	}
	else {
		deltaSlowTime = deltaTime;
	}

	slow = true;
	QueryPerformanceCounter(&prevTime);
}

void  Timer_::SetTimerFast()
{
	slow = false;
}

void  Timer_::Reset()
{
	QueryPerformanceFrequency(&tSecond);    // 초당 클록수 가져오기
	QueryPerformanceCounter(&curTime);
	QueryPerformanceCounter(&prevTime);
}


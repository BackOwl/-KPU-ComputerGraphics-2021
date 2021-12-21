#pragma once
#ifndef timer_
#define timer_
#include <windows.h>

class Timer_ {
private:
	bool slow;	//  버튼이 안 눌렸을 때 (wasd, space) true

	LARGE_INTEGER tSecond;
	LARGE_INTEGER curTime;
	LARGE_INTEGER prevTime;
	float deltaTime;
	float deltaSlowTime;

public:
	Timer_() {
		QueryPerformanceFrequency(&tSecond);    // 초당 클록수 가져오기
		QueryPerformanceCounter(&curTime);
		QueryPerformanceCounter(&prevTime);
	};
	~Timer_() = default;
	
	float DeltaTime();	// 화면 회전 등에 사용

	float SlowDeltaTime();	// 캐릭터 이동, 총알 이동, 총 발사 시 반동 등에 사용

	void  SetTimerFast();

	void Update();

	void Reset();
};

#endif


#pragma once

#include <string>
#include "windows.h"
#include "time.h"


class CTimer
{
public:	
	~CTimer();
	
	static CTimer *getTimer();

	int GetInitFPS(){ return nInitFPS; }
	int GetCurFrame(){ return nCurFrame; }
	int GetRealFPS(){ return realFPS; }
	int GetAbsoluteFrame(){ return dwAbsoluteFrame; }
	LPCTSTR GetFPS();

	void Update();	// 타이머 업데이트

private:
	CTimer();

	UINT	nInitFPS;			// 설정하려고하는 초기 FPS
	UINT	realFPS;			// 실제 프레임레이트
	UINT	realFPSCount;		// 실제 프레임 카운트
	float	realFPSTime;		// 실제 프레임레이트 시간 변수
	UINT	nCurFrame;			// 현재 프레임 수
	DWORD	dwLastTime;			// 마지막에 기록되는 밀리초
	float	fAnimationTime;		// 애니메이션을 갱신하기위해 진행되는 밀리초
	DWORD	dwAbsoluteFrame;	// 전체 경과한프레임수
	float	fOneFrameTime;		// 한 프레임이 갱신되는데 걸리는 시간(초단위)
	
};



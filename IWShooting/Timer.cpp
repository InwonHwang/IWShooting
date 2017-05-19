#include "Timer.h"


CTimer::CTimer()
{
	nInitFPS = 80;
	fAnimationTime = 0;
	dwAbsoluteFrame = 0;
	realFPS = 0;
	realFPSCount = 0;
	realFPSTime = 0.0f;
	fOneFrameTime = 1 / (float)nInitFPS;
	srand(time(NULL));
}

CTimer::~CTimer(void)
{
}

CTimer *CTimer::getTimer()
{
	static CTimer inst;

	return &inst;
}

void CTimer::Update()
{

	int dwCurTimer = timeGetTime();								// 현재 시간을 기록
	float fDelta = (float)(dwCurTimer - dwLastTime) * 0.001;		// 0.001을 곱하는 이유는 밀리초(1/1000초)를
	// 초단위로 변경하기 위해서이다.

	// 실제 FPS 계산
	++realFPSCount;
	realFPSTime += fDelta;
	if (realFPSTime >= 1.0f){
		realFPS = realFPSCount / realFPSTime;
		realFPSCount = 0;
		realFPSTime = 0.0f;
	}

	dwLastTime = dwCurTimer;									// 현재시간을 마지막시간으로 기록한다.
	fAnimationTime += fDelta;									// 시간변화량을 애니메이션을 갱신하기위한 변수에 누적시킨다.

	if (fAnimationTime >= fOneFrameTime){						// 한프레임을 갱신하는데 필요한 시간이 경과되는 즉시 프레임을 증가시킨다.
		fAnimationTime = 0;
		++nCurFrame;
		++dwAbsoluteFrame;
		if (nCurFrame == nInitFPS){
			nCurFrame = 0;
		}
	}
}

LPCTSTR CTimer::GetFPS()
{
	TCHAR buf[256];
	wsprintf(buf, TEXT("FPS : %d"), realFPS);
	return buf;
}
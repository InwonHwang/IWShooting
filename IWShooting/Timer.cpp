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

	int dwCurTimer = timeGetTime();								// ���� �ð��� ���
	float fDelta = (float)(dwCurTimer - dwLastTime) * 0.001;		// 0.001�� ���ϴ� ������ �и���(1/1000��)��
	// �ʴ����� �����ϱ� ���ؼ��̴�.

	// ���� FPS ���
	++realFPSCount;
	realFPSTime += fDelta;
	if (realFPSTime >= 1.0f){
		realFPS = realFPSCount / realFPSTime;
		realFPSCount = 0;
		realFPSTime = 0.0f;
	}

	dwLastTime = dwCurTimer;									// ����ð��� �������ð����� ����Ѵ�.
	fAnimationTime += fDelta;									// �ð���ȭ���� �ִϸ��̼��� �����ϱ����� ������ ������Ų��.

	if (fAnimationTime >= fOneFrameTime){						// ���������� �����ϴµ� �ʿ��� �ð��� ����Ǵ� ��� �������� ������Ų��.
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
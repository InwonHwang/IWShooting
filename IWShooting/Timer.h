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

	void Update();	// Ÿ�̸� ������Ʈ

private:
	CTimer();

	UINT	nInitFPS;			// �����Ϸ����ϴ� �ʱ� FPS
	UINT	realFPS;			// ���� �����ӷ���Ʈ
	UINT	realFPSCount;		// ���� ������ ī��Ʈ
	float	realFPSTime;		// ���� �����ӷ���Ʈ �ð� ����
	UINT	nCurFrame;			// ���� ������ ��
	DWORD	dwLastTime;			// �������� ��ϵǴ� �и���
	float	fAnimationTime;		// �ִϸ��̼��� �����ϱ����� ����Ǵ� �и���
	DWORD	dwAbsoluteFrame;	// ��ü ����������Ӽ�
	float	fOneFrameTime;		// �� �������� ���ŵǴµ� �ɸ��� �ð�(�ʴ���)
	
};



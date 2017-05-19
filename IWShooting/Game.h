#pragma once

#include "Common.h"

class CGame
{
public:
	CGame();
	~CGame();

	LRESULT WINAPI WndProc(UINT msg, WPARAM wparam, LPARAM lparam);

	HWND hWnd_;

	double FPS;

	void run();		
private:
	void objectUpdate();
	void objectDraw();

	void collisionCheck();
	void aliveCheck();
	void initFont();
	void drawFont();
	void draw();

	void input();
	void SetStage();

	void EnemyPattern();

	DWORD BeforeFrame;	// 프레임속도를 위한 변수

	CTextureFactory *TFactory_;
	LPD3DXFONT Font;

};


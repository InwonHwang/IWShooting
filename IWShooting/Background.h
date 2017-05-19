#pragma once
#include "GameObject.h"

class CBackground :
	public CGameObject
{
public:
	CBackground(int textNum);
	~CBackground();

	void update(){};

private:
	void initUV();
	void move(){};
	void anim(){};
	void matrices();
};


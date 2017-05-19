#pragma once
#include "Entity.h"
class CBoss :
	public CEnemy
{
public:
	CBoss(
		int textNum,
		int hp,
		float positionX,
		float positionY,
		float sizeX,
		float sizeY,
		bool isLeft,
		int moveState);
	~CBoss();

	void update();
private:
	void initUV();
	void move();
	void anim();
};


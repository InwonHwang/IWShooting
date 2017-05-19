#pragma once

#include "Entity.h"

class CUFO :
	public CEnemy
{
public:
	CUFO(
		int textNum,
		int hp,
		float positionX,
		float positionY,
		float sizeX,
		float sizeY,
		bool isLeft,
		int moveState);
	~CUFO();

	void update();
private:
	void initUV();
	void isHit();
	void move();
	void anim();
	void matrices(){}
};
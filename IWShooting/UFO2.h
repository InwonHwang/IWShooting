#pragma once
#include "Entity.h"

class CUFO2 :
	public CEnemy
{
public:
	CUFO2(int textNum,
		int hp,
		float positionX,
		float positionY,
		float sizeX,
		float sizeY,
		bool isLeft,
		int moveState);
	~CUFO2();

	void update();
private:
	void initUV();
	void isHit();
	void move();
	void anim();
	void matrices(){}
};


#pragma once
#include "Entity.h"

class CGun :
	public CEntity
{
public:
	CGun(
		int textNum,
		int hp,
		float positionX,
		float positionY,
		float sizeX,
		float sizeY);
	~CGun();
	
	void update();

private:
	void initUV();
	void anim();
	void move();
	void matrices();

private:
	float valueOfRotation_;
	float gapX_;
	float gapY_;
};


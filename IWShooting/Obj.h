#pragma once
#include "Entity.h"

class CObj :
	public CEntity
{
public:
	CObj(
		int textNum,
		int hp,
		float positionX,
		float positionY,
		float sizeX,
		float sizeY);
	~CObj();

	void update();

private:
	void initUV();
	void setUV();
	void anim();
	void move();
	void matrices(){}
	
	float gapX_;
	float gapY_;
};


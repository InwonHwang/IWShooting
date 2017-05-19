#pragma once
#include "Entity.h"
class CEObj :
	public CEntity
{
public:
	CEObj(
		int textNum,
		int hp,
		float positionX,
		float positionY,
		float sizeX,
		float sizeY,
		int moveState);
	~CEObj();

	void update();

private:
	void initUV();
	void anim();
	void move();
	void matrices();

	int moveState_;
};


#pragma once
#include "Entity.h"
class CEBossObj :
	public CEntity
{
public:
	CEBossObj(
		int textNum,
		int hp,
		float positionX,
		float positionY,
		float sizeX,
		float sizeY,
		int moveState);
	~CEBossObj();

	void update();

private:
	void initUV();
	void setUV();
	void anim();
	void move();
	void matrices();

	float change_;
	int moveState_;

};


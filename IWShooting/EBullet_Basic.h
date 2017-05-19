#pragma once
#include "Entity.h"

class CEBullet_Basic :
	public CBullet
{
public:
	CEBullet_Basic(
		int textNum, int hp,
		float positionX,
		float positionY,
		float sizeX,
		float sizeY,
		bool isCharacterLeft,
		float angle,
		float angleRate,
		float speed,
		float speedRate);
	~CEBullet_Basic();


	void update();

private:
	void initUV();
	void setUV(){};
	void isHit();
	void move();
	void anim(){};
	void matrices(){}
};


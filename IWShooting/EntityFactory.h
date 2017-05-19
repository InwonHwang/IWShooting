#pragma once

#include "Camera.h"

class CEntityFactory
{
public:	
	~CEntityFactory();	

	static CEntityFactory *getFactory();	

	void createCharacter(int textNum, int hp, float posX, float posY, float sizeX, float sizeY);
	void createPlaneFire(int textNum, int hp, float posX, float posY, float sizeX, float sizeY);
	void createPlaneGun(int textNum, int hp, float posX, float posY, float sizeX, float sizeY);


	void createEnemy(int textNum, int hp, float posX, float posY, float sizeX, float sizeY, bool isLeft, int category, int moveState);
	void createEnemySub(int textNum, int hp, float posX, float posY, float sizeX, float sizeY,int moveState, int category);

	void createBullet(int textNum, int hp, float posX, float posY, float sizeX, float sizeY,
		bool isCharacterLeft, float angle, float angleRate, float speed, float speedRate, float valueOfRotation);
	void createEBullet(int textNum, int hp, float posX, float posY, float sizeX, float sizeY,
		bool isCharacterLeft, float angle, float angleRate, float speed, float speedRate);


	void createBackground(int textNum);

private:
	CEntityFactory();

};


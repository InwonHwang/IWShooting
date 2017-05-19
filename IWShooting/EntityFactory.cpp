#include "EntityFactory.h"
#include "Entity.h"
#include "Background.h"
#include "UFO.h"
#include "UFO2.h"
#include "EBullet_Basic.h"
#include "Boss.h"
#include "Obj.h"
#include "Gun.h"
#include "EObj.h"
#include "EBossObj.h"

extern list<CGameObject *>	listOfBullet;
extern list<CGameObject *>	listOfEnemy;
extern list<CGameObject *>	listOfEBullet;
extern list<CGameObject *>	listOfBackground;
extern list<CGameObject *>	listOfMyPlane;
extern list<CGameObject *>	listOfSub;

CEntityFactory::CEntityFactory()
{
}


CEntityFactory::~CEntityFactory()
{
}

CEntityFactory *CEntityFactory::getFactory()
{
	static CEntityFactory inst;

	return &inst;
}

void CEntityFactory::createCharacter(int textNum, int hp, float posX, float posY, float sizeX, float sizeY)
{
	CGameObject *ret = new CMyCharacter(textNum, hp, posX, posY, sizeX, sizeY);

	listOfMyPlane.push_back(ret);
}

void CEntityFactory::createPlaneFire(int textNum, int hp, float posX, float posY, float sizeX, float sizeY)
{
	CGameObject *ret = new CObj(textNum, hp, posX, posY, sizeX, sizeY);

	listOfMyPlane.push_front(ret);
}

void CEntityFactory::createPlaneGun(int textNum, int hp, float posX, float posY, float sizeX, float sizeY)
{
	CGameObject *ret = new CGun(textNum, hp, posX, posY, sizeX, sizeY);

	listOfSub.push_front(ret);
}

void CEntityFactory::createEnemy(int textNum, int hp, float posX, float posY, float sizeX, float sizeY, bool isLeft, int category,int moveState)
{
	CGameObject *ret = nullptr;

	switch (category) {
	case 0:
		ret = new CUFO(textNum, hp, posX, posY, sizeX, sizeY, isLeft, moveState);
		break;
	case 1:
		ret = new CUFO2(textNum, hp, posX, posY, sizeX, sizeY, isLeft, moveState);
		break;
	case 2:
		ret = new CBoss(textNum, hp, posX, posY, sizeX, sizeY, isLeft, moveState);
		break;

	}

	listOfEnemy.push_back(ret);
}

void CEntityFactory::createEnemySub(int textNum, int hp, float posX, float posY, float sizeX, float sizeY,int moveState, int category)
{
	CGameObject *ret = nullptr;

	switch (category) {
	case 0:
		ret = new CEObj(textNum, hp, posX, posY, sizeX, sizeY, moveState);
		break;
	case 1:
		ret = new CEBossObj(textNum, hp, posX, posY, sizeX, sizeY, moveState);
		break;
		
	}

	listOfEnemy.push_front(ret);
}



//林牢傍 醚舅 积己
void CEntityFactory::createBullet(
	int textNum,
	int hp,
	float posX,
	float posY,
	float sizeX,
	float sizeY,
	bool isCharacterLeft,
	float angle,
	float angleRate,
	float speed,
	float speedRate,
	float valueOfRotation)
{
	CGameObject *ret;

	if (isCharacterLeft)
		ret = new CBullet(textNum, hp, posX + 0.2f, posY, sizeX, sizeY,
		isCharacterLeft, angle, angleRate, speed, speedRate, valueOfRotation);
	else
		ret = new CBullet(textNum, hp, posX + 0.6f, posY, sizeX, sizeY,
		isCharacterLeft, angle, angleRate, speed, speedRate, valueOfRotation);
		
	listOfBullet.push_back(ret);
}

//利 醚舅 积己
void CEntityFactory::createEBullet(
	int textNum,
	int hp, 
	float posX,
	float posY,
	float sizeX, 
	float sizeY, 
	bool isCharacterLeft,
	float angle,
	float angleRate, 
	float speed, 
	float speedRate)
{
	CGameObject *ret;
	
	ret = new CEBullet_Basic(textNum, hp, posX, posY, sizeX, sizeY,
								isCharacterLeft, angle, angleRate, speed, speedRate);

	listOfEBullet.push_back(ret);
}

void CEntityFactory::createBackground(int textNum)
{

	CGameObject *ret = new CBackground(textNum);

	listOfBackground.push_back(ret);
}
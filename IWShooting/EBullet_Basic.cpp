#include "EBullet_Basic.h"

extern list<CGameObject *>	listOfMyPlane;
extern list<CGameObject *>	listOfSub;
extern list<CGameObject *>	listOfEBullet;

CEBullet_Basic::CEBullet_Basic(
	int textNum, int hp,
	float positionX,
	float positionY,
	float sizeX,
	float sizeY,
	bool isCharacterLeft,
	float angle,
	float angleRate,
	float speed,
	float speedRate)
	: CBullet(textNum, hp, positionX, positionY, sizeX, sizeY, isCharacterLeft, angle, angleRate, speed, speedRate, 0)
{
	initVertex(positionX, positionY, sizeX, sizeY);
}

CEBullet_Basic::~CEBullet_Basic()
{
}

void CEBullet_Basic::update()
{
	move();
	anim();
	isHit();
}

void CEBullet_Basic::move()
{
	float rad = angle_ * D3DX_PI * 2;

	if (isLeft_)
		CGameObject::move(-speed_ * cosf(rad), speed_ * sin(rad));
	else
		CGameObject::move(speed_ * cosf(rad), speed_ * sin(rad));

	angle_ += angleRate_;
	speed_ += speedRate_;
}

void CEBullet_Basic::initUV()
{
	pVertices[0].tu = 0.0f;
	pVertices[0].tv = 0.0f;
	pVertices[1].tu = 1.0f;
	pVertices[1].tv = 0.0f;
	pVertices[2].tu = 0.0f;
	pVertices[2].tv = 1.0f;
	pVertices[3].tu = 1.0f;
	pVertices[3].tv = 1.0f;
}

void CEBullet_Basic::isHit()
{
	for (list<CGameObject *>::iterator it = listOfMyPlane.begin(); it != listOfMyPlane.end(); it++) {
		if (CGameObject::isHit(*it)){
			CEntity *temp = nullptr;
			temp = dynamic_cast<CEntity *>(*it);
			temp->reduceHP();
			CEntity::reduceHP();
		}
	}

	for (list<CGameObject *>::iterator it = listOfSub.begin(); it != listOfSub.end(); it++) {
		if (CGameObject::isHit(*it)){
			CEntity *temp = nullptr;
			temp = dynamic_cast<CEntity *>(*it);
			temp->reduceHP();
			CEntity::reduceHP();
		}
	}

	

}
#include "EObj.h"

extern list<CGameObject *> listOfMyPlane;

CEObj::CEObj(
	int textNum,
	int hp,
	float positionX,
	float positionY,
	float sizeX,
	float sizeY,
	int moveState)
	: CEntity(textNum, hp, false), moveState_(moveState)
{
	initVertex(positionX, positionY, sizeX, sizeY);
}


CEObj::~CEObj()
{
}

void CEObj::update()
{
	move();
	anim();
}

void CEObj::initUV()
{
	pVertices[0].tu = 0.0f;
	pVertices[0].tv = 0.0f;
	pVertices[1].tu = (float)1 / 3;
	pVertices[1].tv = 0.0f;
	pVertices[2].tu = 0.0f;
	pVertices[2].tv = 1.0f;
	pVertices[3].tu = (float)1 / 3;
	pVertices[3].tv = 1.0f;
}

void CEObj::move()
{
	CGameObject::move(-0.003f, 0);

	//if (moveState_ == 0)
	//	CGameObject::move(-0.003f, -0.003f);
	//else if ( moveState_ == 1)
	//	CGameObject::move(0.003f, -0.003f);
	//else if (moveState_ == 2)
	//	CGameObject::move(-0.003f, 0);
	//else if (moveState_ == 3)
	//	CGameObject::move(-0.003f, 0.002f);
}

void CEObj::anim()
{
	if (aniTimer_ > 10) {
		if (aniNum_ < 3)
		{
			pVertices[0].tu += (float)1 / 3;
			pVertices[1].tu += (float)1 / 3;
			pVertices[2].tu += (float)1 / 3;
			pVertices[3].tu += (float)1 / 3;
			aniNum_++;
		}
		else if (aniNum_ >= 3 && aniNum_ < 6)
		{
			pVertices[0].tu -= (float)1 / 3;
			pVertices[1].tu -= (float)1 / 3;
			pVertices[2].tu -= (float)1 / 3;
			pVertices[3].tu -= (float)1 / 3;
			aniNum_++;
		}

		if (aniNum_ % 6 == 0) {
			list<CGameObject *>::iterator it = listOfMyPlane.begin();
			float planePosX = ((*it)->getVertex()[0].position.x + (*it)->getVertex()[1].position.x) / 2;
			float planePosY = ((*it)->getVertex()[0].position.y + (*it)->getVertex()[2].position.y) / 2;
			float posX = (pVertices[0].position.x + pVertices[1].position.x) / 2;
			float posY = (pVertices[0].position.y + pVertices[2].position.y) / 2;

			float radian = atan2f(posY - planePosY, posX - planePosX);
			float angle = (D3DXToDegree(radian) + 180) / 360;

			D3DXVECTOR3 pos = { (float)((pVertices[0].position.x + pVertices[1].position.x) / 2) - 0.05f, pVertices[3].position.y, 0 };
			CEntityFactory::getFactory()->createEBullet(8, 1, pos.x, pos.y, 0.1f, 0.1f, false,
				angle, 0, 0.05f, 0);
			
		}

		aniNum_ = aniNum_ % 6;
		aniTimer_ = 0;
	}
	aniTimer_++;
}

void CEObj::matrices()
{
	CGameObject::matrices();
}
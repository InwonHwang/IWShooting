#include "UFO2.h"


CUFO2::CUFO2(	int textNum,
				int hp,
				float positionX,
				float positionY,
				float sizeX,
				float sizeY,
				bool isLeft,
				int moveState)
				: CEnemy( textNum, hp, positionX, positionY, sizeX, sizeY , isLeft ,moveState)
{
	initVertex(positionX, positionY, sizeX, sizeY);

	if (!isLeft)
		reverseDirection();

	CEntityFactory::getFactory()->createEnemySub(7, hp, positionX + 0.18f, positionY - 0.18f, sizeX / 2, sizeY / 2, moveState, 0);
}


CUFO2::~CUFO2()
{
}

void CUFO2::update()
{
	move();
	anim();
}

void CUFO2::initUV()
{
	pVertices[0].tu = (float)1 / 16;
	pVertices[0].tv = 0.0f;
	pVertices[1].tu = 0.0f;
	pVertices[1].tv = 0.0f;
	pVertices[2].tu = (float)1 / 16;
	pVertices[2].tv = 1.0f;
	pVertices[3].tu = 0.0f;
	pVertices[3].tv = 1.0f;
}


void CUFO2::move()
{
	CGameObject::move(-0.003f, 0);

	/*if (isLeft_ && moveState_ == 0)
		CGameObject::move(-0.003f, -0.003f);
	else if (!isLeft_ && moveState_ == 1)
		CGameObject::move(+0.003f, -0.003f);
	else if (isLeft_ && moveState_ == 2)
		CGameObject::move(-0.003f, 0);
	else if (isLeft_ && moveState_ == 3)
		CGameObject::move(-0.003f, 0.002f);*/
		
}

void CUFO2::anim()
{
	switch (stateOfAnim_)
	{
	case 0:
		if (aniTimer_ > 4) {
			if (aniNum_ < 16)
			{
				for (int i = 0; i < 4; i++) {
					pVertices[i].tu += (float)1 / 16;
				}
				aniNum_++;
			}
			aniNum_ = aniNum_ % 16;
			aniTimer_ = 0;

		}
		aniTimer_++;
		break;
	}
}
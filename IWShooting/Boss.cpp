#include "Boss.h"

CBoss::CBoss(
	int textNum,
	int hp,
	float positionX,
	float positionY,
	float sizeX,
	float sizeY,
	bool isLeft,
	int moveState)
	: CEnemy(textNum, hp, positionX, positionY, sizeX, sizeY, isLeft, moveState)
{
	initVertex(positionX, positionY, sizeX, sizeY);
	if (!isLeft)
		reverseDirection();

	CEntityFactory::getFactory()->createEnemySub(7, hp, positionX + 1.6f, positionY - 1.0f, sizeX / 4, sizeY / 4,0, 1);
}


CBoss::~CBoss()
{
}


void CBoss::update()
{
	move();
	anim();
}

void CBoss::initUV()
{
	pVertices[0].tu = (float)1 / 4;
	pVertices[0].tv = 0.0f;
	pVertices[1].tu = 0.0f;
	pVertices[1].tv = 0.0f;
	pVertices[2].tu = (float)1 / 4;
	pVertices[2].tv = (float)1 / 6;
	pVertices[3].tu = 0.0f;
	pVertices[3].tv = (float)1 / 6;
}


void CBoss::move()
{
	if (pVertices[1].position.x < CCamera::getCamera()->getSizeOfScreen()[1].x - 1){
		CGameObject::move(0.001f, 0);
		return;
	}

	CGameObject::move(-0.003f, 0.0f);
}
void CBoss::anim()
{
	switch (stateOfAnim_)
	{
	case 0:
		if (aniTimer_ > 4) {
			if (aniNum_ < 24)
			{
				if (aniNum_ % 4 == 0) {
					for (int i = 0; i < 4; i++)
						pVertices[i].tu += (float)1 / 4;
				}

				for (int i = 0; i < 4; i++) {
					pVertices[i].tv += (float)1 / 6;
				}

				aniNum_++;
			}			
			
			aniNum_ = aniNum_ % 24;
			aniTimer_ = 0;

		}
		aniTimer_++;
		break;
	}
}



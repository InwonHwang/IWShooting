#include "EBossObj.h"


CEBossObj::CEBossObj(
	int textNum,
	int hp,
	float positionX,
	float positionY,
	float sizeX,
	float sizeY,
	int moveState) : CEntity(textNum, hp, false), change_(0), moveState_(moveState)
{
	initVertex(positionX, positionY, sizeX, sizeY);
}


CEBossObj::~CEBossObj()
{
}

void CEBossObj::update()
{
	
	move();
	anim();
}

void CEBossObj::initUV()
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

void CEBossObj::move()
{
	
	if (pVertices[1].position.x < CCamera::getCamera()->getSizeOfScreen()[1].x - 2.4f){
		CGameObject::move(0.001f, 0);
		return;
	}

	CGameObject::move(-0.003f, 0.0f);

}

void CEBossObj::anim()
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

		if (hp_ < 50){
			if (aniNum_ == 3 ) {
				D3DXVECTOR3 pos = { (float)((pVertices[0].position.x + pVertices[1].position.x) / 2) - 0.05f, pVertices[3].position.y, 0 };
				for (float i = 0; i < 1; i += 0.1)
					CEntityFactory::getFactory()->createEBullet(8, 1, pos.x, pos.y + 0.5f, 0.1f, 0.1f, false, i, 0, 0.05f, 0);
			}
			if (aniNum_ == 3) {
				D3DXVECTOR3 pos = { (float)((pVertices[0].position.x + pVertices[1].position.x) / 2) - 0.05f, pVertices[3].position.y, 0 };
				for (float i = 0.05; i < 1; i += 0.1)
					CEntityFactory::getFactory()->createEBullet(8, 1, pos.x, pos.y + 0.5f, 0.1f, 0.1f, false, i, 0, 0.05f, 0);
			}
			if (aniNum_ == 5 || aniNum_ == 1) {
				D3DXVECTOR3 pos = { (float)((pVertices[0].position.x + pVertices[1].position.x) / 2) - 0.05f, pVertices[3].position.y, 0 };
				for (float i = 0.075; i < 1; i += 0.1)
					CEntityFactory::getFactory()->createEBullet(8, 1, pos.x, pos.y + 0.5f, 0.1f, 0.1f, false, i, 0, 0.05f, 0);
			}
			if (aniNum_ == 5 || aniNum_ == 1) {
				D3DXVECTOR3 pos = { (float)((pVertices[0].position.x + pVertices[1].position.x) / 2) - 0.05f, pVertices[3].position.y, 0 };
				for (float i = 0.025; i < 1; i += 0.1)
					CEntityFactory::getFactory()->createEBullet(8, 1, pos.x, pos.y + 0.5f, 0.1f, 0.1f, false, i, 0, 0.05f, 0);
			}
		}
		else {
			if (aniNum_  == 3) {
				D3DXVECTOR3 pos = { (float)((pVertices[0].position.x + pVertices[1].position.x) / 2) - 0.05f, pVertices[3].position.y, 0 };
				for (float i = 0; i < 1; i += 0.1)
					CEntityFactory::getFactory()->createEBullet(8, 1, pos.x, pos.y + 0.5f, 0.1f, 0.1f, false, i, 0, 0.05f, 0);
			}
			if (aniNum_  == 5) {
				D3DXVECTOR3 pos = { (float)((pVertices[0].position.x + pVertices[1].position.x) / 2) - 0.05f, pVertices[3].position.y, 0 };
				for (float i = 0.05; i < 1; i += 0.1)
					CEntityFactory::getFactory()->createEBullet(8, 1, pos.x, pos.y + 0.5f, 0.1f, 0.1f, false, i, 0, 0.05f, 0);
			}
		}


		aniNum_ = aniNum_ % 6;
		aniTimer_ = 0;
	}
	aniTimer_++;
}

void CEBossObj::matrices()
{
	CGameObject::matrices();
}

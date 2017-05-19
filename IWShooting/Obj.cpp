#include "Obj.h"
#include "Common.h"

extern list<CGameObject *>	listOfMyPlane;

CObj::CObj(int textNum,
	int hp,
	float positionX,
	float positionY,
	float sizeX,
	float sizeY) : CEntity(textNum, hp, false), gapX_(positionX), gapY_(positionY)
{
	initVertex(positionX, positionY, sizeX, sizeY);
}


CObj::~CObj()
{
}

void CObj::update()
{
	setUV();
	move();
	anim();
}

void CObj::initUV()
{
	pVertices[0].tu = 0.0f;
	pVertices[0].tv = 0.0f;
	pVertices[1].tu = (float)1 / 5;
	pVertices[1].tv = 0.0f;
	pVertices[2].tu = 0.0f;
	pVertices[2].tv = 0.5f;
	pVertices[3].tu = (float)1 / 5;
	pVertices[3].tv = 0.5f;
}
void CObj::setUV()
{
	switch (stateOfAnim_) {
	case 0:
		pVertices[0].tu = (float)0 / 5;
		pVertices[1].tu = (float)1 / 5;
		pVertices[2].tu = (float)0 / 5;
		pVertices[3].tu = (float)1 / 5;		
		break;
	case 1:
		pVertices[0].tu = (float)1 / 5;
		pVertices[1].tu = (float)2 / 5;
		pVertices[2].tu = (float)1 / 5;
		pVertices[3].tu = (float)2 / 5;
		break;
	case 2:
		pVertices[0].tu = (float)2 / 5;
		pVertices[1].tu = (float)3 / 5;
		pVertices[2].tu = (float)2 / 5;
		pVertices[3].tu = (float)3 / 5;
		break;
	case 3:
		pVertices[0].tu = (float)3 / 5;
		pVertices[1].tu = (float)4 / 5;
		pVertices[2].tu = (float)3 / 5;
		pVertices[3].tu = (float)4 / 5;
		break;
	case 4:		
		pVertices[0].tu = (float)4 / 5;
		pVertices[1].tu = (float)5 / 5;
		pVertices[2].tu = (float)4 / 5;
		pVertices[3].tu = (float)5 / 5;
		if (isLeft_) 
			reverseDirection();
		break;
	default:
		pVertices[0].tu = (float)0 / 5;
		pVertices[1].tu = (float)1 / 5;
		pVertices[2].tu = (float)0 / 5;
		pVertices[3].tu = (float)1 / 5;
		break;
	}

	stateOfAnim_ = 0;
}

void CObj::move()
{
	
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		stateOfAnim_ = 3;
		CGameObject::move(0.0f, 0.03f);
		if (CGameObject::isOut(0, 0))
			CGameObject::move(-0.031f, 0.0f);
		
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000){
		stateOfAnim_ = 2;
		CGameObject::move(0.0f, -0.03f);
		if (CGameObject::isOut(0, 0))
			CGameObject::move(-0.031f, 0.0f);
		
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		stateOfAnim_ = 4;
		isLeft_ = true;
		CGameObject::move(-0.03f, 0.0f);
		if (CGameObject::isOut(0, 0))
			CGameObject::move(-0.031f, 0.0f);
		
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000){
		stateOfAnim_ = 4;
		isLeft_ = false;
		CGameObject::move(0.03f, 0.0f);
		if (CGameObject::isOut(0, 0))
			CGameObject::move(-0.031f, 0.0f);
		
	}	
	
}

void CObj::anim()
{
	if (aniTimer_ > 3) {
		if (aniNum_ < 2)
		{
			pVertices[0].tv += (float)1 / 2;
			pVertices[1].tv += (float)1 / 2;
			pVertices[2].tv += (float)1 / 2;
			pVertices[3].tv += (float)1 / 2;
			aniNum_++;
		}	
		aniNum_ = aniNum_ % 2;
		aniTimer_ = 0;
	}
	aniTimer_++;
}


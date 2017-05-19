#include "Gun.h"
#include "Timer.h"

extern list<CGameObject *>	listOfMyPlane;

CGun::CGun(
	int textNum,
	int hp,
	float positionX,
	float positionY,
	float sizeX,
	float sizeY) : CEntity(textNum, hp, false), valueOfRotation_(0), gapX_(positionX), gapY_(positionY)
{
	initVertex(positionX, positionY, sizeX, sizeY);
}


CGun::~CGun()
{
}

void CGun::update()
{
	move();
}

void CGun::initUV()
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

void CGun::move()	
{

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		valueOfRotation_ += 0.1f;
		CGameObject::move(0.0f, 0.03f);
		if (CGameObject::isOut(0, 0))
			CGameObject::move(0.0f, -0.03f);
	}
	
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)	{
		valueOfRotation_ -= 0.1f;
		CGameObject::move(0.0f, -0.03f);
		if (CGameObject::isOut(0, 0))
			CGameObject::move(0.0f, 0.03f);
	}
	
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)	{
		CGameObject::move(-0.03f, 0.0f);
		if (CGameObject::isOut(0, 0))
			CGameObject::move(0.031f, 0.0f);
	}


	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		CGameObject::move(0.03f, 0.0f);
		if (CGameObject::isOut(0, 0))
			CGameObject::move(-0.031f, 0.0f);
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		if (aniTimer_ > 3) {
			if (aniNum_ < 5)
				CEntityFactory::getFactory()->createBullet(1, 1, pVertices[0].position.x - 0.48f, pVertices[2].position.y + 0.07,
				0.1f, 0.03f, false, valueOfRotation_ / 6.25f, 0.0f, 0.1f, 0.0f, valueOfRotation_);
			
			aniNum_ = aniNum_ % 5;
			aniTimer_ = 0;
		}
		aniTimer_++;
	}	
}

void CGun::anim()
{
}

void CGun::matrices()
{
	D3DXVECTOR3 pos2 = pVertices[2].position;
	float gap = (pVertices[1].position.x - pVertices[0].position.x) / 2.0f;
	float gapY = (pVertices[0].position.y - pVertices[3].position.y) / 2.0f;

	D3DXMATRIX m_matWorld;
	D3DXMATRIX matRotateZ;
	D3DXMATRIX matTranslate;
	D3DXMATRIX matTranslate2;
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&matRotateZ);
	D3DXMatrixIdentity(&matTranslate);
	D3DXMatrixTranslation(&matTranslate, -pos2.x - gap, -pos2.y - gapY, 0);
	D3DXMatrixRotationZ(&matRotateZ, valueOfRotation_);
	D3DXMatrixTranslation(&matTranslate2, pos2.x + gap, pos2.y + gapY, 0);
	m_matWorld = matTranslate * matRotateZ * matTranslate2;

	CDevice::getDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);

	CCamera::getCamera()->move();

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	CDevice::getDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
}

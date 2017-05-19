#include "Entity.h"

extern list<CGameObject *>	listOfBullet;
extern list<CGameObject *>	listOfEnemy;
extern list<CGameObject *>	listOfEBullet;
extern list<CGameObject *>	listOfMyPlane;

CEntity::CEntity(int textNum, int hp, bool isLeft)
 : CGameObject(textNum),
 hp_(hp),
 isAlive_(true),
 isLeft_(isLeft), 
 aniTimer_(0),
 aniNum_(0),
 stateOfAnim_(0)
{
}


CEntity::~CEntity()
{
}

void CEntity::reduceHP()
{
	hp_--;

	if (hp_ == 0)
		isAlive_ = false;
}

bool CEntity::isDead()
{
	if (isAlive_)
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

CMyCharacter::CMyCharacter(
	int textNum, int hp,
	float positionX,
	float positionY,
	float sizeX,
	float sizeY)
	: CEntity(textNum, hp, true)
{	
	initVertex(positionX, positionY, sizeX, sizeY);
	CEntityFactory::getFactory()->createPlaneFire(2, 1, positionX + 0.010f, positionY + 0.0f, 0.3f, 0.25f);
	CEntityFactory::getFactory()->createPlaneFire(2, 1, positionX + 0.05f, positionY + 0.03f, 0.3f, 0.25f);
	CEntityFactory::getFactory()->createPlaneFire(2, 1, positionX + 0.25f, positionY + 0.0f, 0.3f, 0.25f);
	CEntityFactory::getFactory()->createPlaneFire(2, 1, positionX + 0.3f, positionY + 0.03f, 0.3f, 0.25f);
	CEntityFactory::getFactory()->createPlaneGun(3, 1, positionX + 0.3f, positionY + 0.19f, 0.35f, 0.2f);
}

CMyCharacter::~CMyCharacter()
{
}

void CMyCharacter::anim()
{
	if (aniTimer_ > 10) {
		if (aniNum_ < 5)
		{
			pVertices[0].tu += (float)1 / 5;
			pVertices[1].tu += (float)1 / 5;
			pVertices[2].tu += (float)1 / 5;
			pVertices[3].tu += (float)1 / 5;
			aniNum_++;
		}

		if (aniNum_ >= 5 && aniNum_ < 10)
		{
			pVertices[0].tu -= (float)1 / 5;
			pVertices[1].tu -= (float)1 / 5;
			pVertices[2].tu -= (float)1 / 5;
			pVertices[3].tu -= (float)1 / 5;
			aniNum_++;
		}
		aniNum_ = aniNum_ % 10;
		aniTimer_ = 0;
	}
	aniTimer_++;
}

void CMyCharacter::move()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		CGameObject::move(0.0f, 0.03f);
		if (CGameObject::isOut(0 , 0))
			CGameObject::move(0.0f, -0.031f);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000){
		CGameObject::move(0.0f, -0.03f);	
		if (CGameObject::isOut(0, 0))
			CGameObject::move(0.0f, 0.031f);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		CGameObject::move(-0.03f, 0.0f);
		if (CGameObject::isOut(0, 0))
			CGameObject::move(0.031f, 0.0f);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000){
		CGameObject::move(0.03f, 0.0f);
		if (CGameObject::isOut(0, 0))
			CGameObject::move(-0.031f, 0.0f);
	}	
}

void CMyCharacter::initUV()
{	
	pVertices[0].tu = 0.0f;
	pVertices[0].tv = 0.0f;
	pVertices[1].tu = (float)1 / 5;
	pVertices[1].tv = 0.0f;
	pVertices[2].tu = 0.0f;
	pVertices[2].tv = (float)1 / 6;
	pVertices[3].tu = (float)1 / 5;
	pVertices[3].tv = (float)1 / 6;	
}


void CMyCharacter::update()
{
	move();
	anim();
}

void CMyCharacter::matrices()
{
	CGameObject::matrices();
}



//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
CEnemy::CEnemy(
	int textNum, int hp,
	float positionX, 
	float positionY, 
	float sizeX, 
	float sizeY,
	bool isLeft,
	int moveState)
	: CEntity(textNum, hp, isLeft), moveState_(moveState)
{
}

CEnemy::~CEnemy()
{
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

CBullet::CBullet(
	int textNum, int hp,
	float positionX,
	float positionY,
	float sizeX,
	float sizeY,
	bool isCharacterLeft,
	float angle,
	float angleRate,
	float speed,
	float speedRate,
	float valueOfRotation)
: CEntity(textNum, hp, isCharacterLeft),
angle_(angle),
angleRate_(angleRate), 
speed_(speed), 
speedRate_(speedRate),
valueOfRotation_(valueOfRotation)
{
	if (isCharacterLeft)
		positionX -= 0.5;

	initVertex(positionX, positionY, sizeX, sizeY);
}

CBullet::~CBullet()
{
}

void CBullet::update()
{
	move();
	anim();
	isHit();
}

void CBullet::move()
{
	float rad = angle_ * D3DX_PI *2;
	
	CGameObject::move(speed_ * cosf(rad), speed_ * sin(rad));		

	angle_ += angleRate_;
	speed_ += speedRate_;	
}

void CBullet::initUV()
{
	pVertices[0].tu = 0.5f;
	pVertices[0].tv = 0.0f;
	pVertices[1].tu = 0.01f;
	pVertices[1].tv = 0.0f;
	pVertices[2].tu = 0.5f;
	pVertices[2].tv = 0.1f;
	pVertices[3].tu = 0.01f;
	pVertices[3].tv = 0.1f;
}

void CBullet::isHit()
{
	for (list<CGameObject *>::iterator it = listOfEnemy.begin(); it != listOfEnemy.end(); it++) {
		if (CGameObject::isHit(*it)){
			CEntity *temp = nullptr;
			temp = dynamic_cast<CEntity *>(*it);
			temp->reduceHP();
			CEntity::reduceHP();
		}
	}
}

void CBullet::matrices()
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
}
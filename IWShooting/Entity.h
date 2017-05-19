#pragma once

#include "GameObject.h"
#include "EntityFactory.h"

/////////////////////////////////////////////////////////////////// Entity Class
class CEntity : public CGameObject
{
public:
	CEntity(int textNum, int hp, bool isLeft);
	virtual ~CEntity();

	void reduceHP();
	bool isDead();

public:
	float	aniTimer_;
	int		aniNum_;
	int		hp_;

	bool	isAlive_;
	bool	isLeft_;
	int		stateOfAnim_;
};

/////////////////////////////////////////////////////////////////// Character Class

class CMyCharacter : public CEntity
{
public:
	CMyCharacter(
		int textNum, 
		int hp, 
		float positionX,
		float positionY,
		float sizeX,
		float sizeY);
	~CMyCharacter();

	void update();
	CUSTOMVERTEX *getPlaneVertex() const { return pVertices; }

protected:
	void initUV();
	void anim();
	void move();
	void matrices();
	
protected:	

};

/////////////////////////////////////////////////////////////////// Enemy Class
class CEnemy : public CEntity
{
public:
	CEnemy(
		int textNum,
		int hp,
		float positionX,
		float positionY,
		float sizeX,
		float sizeY,
		bool isLeft,
		int moveState);
	virtual ~CEnemy();

	virtual void update(){}
protected:
	virtual void initUV(){}
	virtual void move(){}
	virtual void anim(){}
	virtual void matrices(){}

	int moveState_;


protected:
	CGameObject* pSub_;
};

/////////////////////////////////////////////////////////////////// Bullet Class
class CBullet : public CEntity
{
public:
	CBullet(
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
		float valueOfRotation);
	virtual ~CBullet();

	virtual void update();		

protected:
	virtual void initUV();
	virtual void isHit();	
	virtual void move();
	virtual void anim() {}
	virtual void matrices();

protected:
	float angle_;		// 각도
	float angleRate_;	// 각속도
	float speed_;		// 속도
	float speedRate_;	// 가속도
	
	float valueOfRotation_;
	
};

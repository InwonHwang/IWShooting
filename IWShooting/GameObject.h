#pragma once

#include "Device.h"
#include "Texture.h"
#include "EntityFactory.h"
#include "Camera.h"

struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;
	D3DCOLOR color;
	FLOAT tu, tv;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class CGameObject
{
public:
	CGameObject(int textNum);
	virtual ~CGameObject();

	virtual void draw(CTexture *texture);					// draw함수
	virtual void update() = 0;
	
	CUSTOMVERTEX *getVertex() const { return pVertices; }
	int getTextNum() const { return textNum_; }

public:
	virtual void initUV() = 0;						// 텍스쳐 애니메이션 초기화
	virtual void move() = 0;						// move 함수
	virtual void matrices();						// 행렬 연산

	bool isHit(CGameObject * entity);				// 충돌 계산
	bool isOut(float gapX, float gapY);				// 화면 밖에 나가면 삭제하기 위해
	void move(float x, float y);					// move 계산
	void reverseDirection();						// 텍스쳐 뒤짚기
	HRESULT initVertex(float positionX, float positionY, float sizeX, float sizeY);	// 정점 초기화

protected:
	LPDIRECT3DVERTEXBUFFER9 pVB_;
	CUSTOMVERTEX* pVertices;

	int	textNum_;
};


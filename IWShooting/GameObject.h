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

	virtual void draw(CTexture *texture);					// draw�Լ�
	virtual void update() = 0;
	
	CUSTOMVERTEX *getVertex() const { return pVertices; }
	int getTextNum() const { return textNum_; }

public:
	virtual void initUV() = 0;						// �ؽ��� �ִϸ��̼� �ʱ�ȭ
	virtual void move() = 0;						// move �Լ�
	virtual void matrices();						// ��� ����

	bool isHit(CGameObject * entity);				// �浹 ���
	bool isOut(float gapX, float gapY);				// ȭ�� �ۿ� ������ �����ϱ� ����
	void move(float x, float y);					// move ���
	void reverseDirection();						// �ؽ��� ��¤��
	HRESULT initVertex(float positionX, float positionY, float sizeX, float sizeY);	// ���� �ʱ�ȭ

protected:
	LPDIRECT3DVERTEXBUFFER9 pVB_;
	CUSTOMVERTEX* pVertices;

	int	textNum_;
};


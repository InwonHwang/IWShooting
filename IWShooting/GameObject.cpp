#include "GameObject.h"
#include "Camera.h"


CGameObject::CGameObject(int textNum) : textNum_(textNum)
{
}


CGameObject::~CGameObject()
{
	if (pVB_) pVB_->Release();
}

HRESULT CGameObject::initVertex(float positionX, float positionY, float sizeX, float sizeY)
{
	if (FAILED(CDevice::getDevice()->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pVB_, NULL)))
	{
		return E_FAIL;
	}

	if (FAILED(pVB_->Lock(0, 0, (void**)&pVertices, 0)))
		return E_FAIL;

	pVertices[0].position = { positionX, positionY + sizeY, 0 };
	pVertices[1].position = { positionX + sizeX, positionY + sizeY, 0 };
	pVertices[2].position = { positionX, positionY, 0 };
	pVertices[3].position = { positionX + sizeX, positionY, 0};

	for (int i = 0; i < 4; i++) {
		pVertices[i].color = 0xffffffff;
	}

	initUV();

	pVB_->Unlock();

	return S_OK;
}

void CGameObject::matrices()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	CDevice::getDevice()->SetTransform(D3DTS_WORLD, &matWorld);

	
}

void CGameObject::draw(CTexture *texture)
{
	matrices();

	CDevice::getDevice()->SetTexture(0, texture->getTexture());
	CDevice::getDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	CDevice::getDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	CDevice::getDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	CDevice::getDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	CDevice::getDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	CDevice::getDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);


	CDevice::getDevice()->SetStreamSource(0, pVB_, 0, sizeof(CUSTOMVERTEX));
	CDevice::getDevice()->SetFVF(D3DFVF_CUSTOMVERTEX);
	CDevice::getDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void CGameObject::reverseDirection()
{
	for (int i = 0; i < 3; i = i + 2) {
		CUSTOMVERTEX temp;
		temp.tu = pVertices[i].tu;
		temp.tv = pVertices[i].tv;
		pVertices[i].tu = pVertices[i + 1].tu;
		pVertices[i].tv = pVertices[i + 1].tv;
		pVertices[i + 1].tu = temp.tu;
		pVertices[i + 1].tv = temp.tv;
	}
}

void CGameObject::move(float x, float y)
{
	for (int i = 0; i < 4; i++) {
		pVertices[i].position.x += x;
	}
	for (int i = 0; i < 4; i++) {
		pVertices[i].position.y += y;
	}
}

bool CGameObject::isHit(CGameObject* entity) {
	
	CUSTOMVERTEX *tmp = entity->getVertex();
	for (int i = 0; i < 4; i++) {
		if (pVertices[i].position.x >= tmp[0].position.x &&
			pVertices[i].position.x <= tmp[1].position.x &&
			pVertices[i].position.y >= tmp[2].position.y &&
			pVertices[i].position.y <= tmp[1].position.y)
			return true;		
	}

	return false;
}

bool CGameObject::isOut(float gapX, float gapY) {

	for (int i = 0; i < 4; i++) {
		if (pVertices[i].position.x <= CCamera::getCamera()->getSizeOfScreen()[0].x + gapX ||
			pVertices[i].position.x >= CCamera::getCamera()->getSizeOfScreen()[1].x - gapX ||
			pVertices[i].position.y <= CCamera::getCamera()->getSizeOfScreen()[2].y + gapY ||
			pVertices[i].position.y >= CCamera::getCamera()->getSizeOfScreen()[1].y - gapY)
			return true;
	}

	return false;
}



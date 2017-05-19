#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class CCamera
{
public:	
	~CCamera();
	static CCamera *getCamera();

	void move();
	D3DXVECTOR3 *getSizeOfScreen() { return sizeOfScreen; }

private:
	CCamera();

	void setView();
	
	D3DXVECTOR3 sizeOfScreen[4];
	
	D3DXVECTOR3	vEye_;
	D3DXVECTOR3 vLookat_;
	D3DXVECTOR3 vUp_;

	D3DXMATRIXA16 matView_;

	float moveLine_;
};


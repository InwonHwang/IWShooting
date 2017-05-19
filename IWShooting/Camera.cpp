#include "Camera.h"
#include "Device.h"


CCamera::CCamera()
{
	setView();
}

CCamera::~CCamera()
{
}

CCamera *CCamera::getCamera()
{
	static CCamera inst;

	return &inst;
}

void CCamera::setView()
{	
	vEye_ = { 4.0f, 3.0f, -10.0f };
	vLookat_ = { 4.0f, 3.0f, 0.0f };
	vUp_ = { 0.0f, 1.0f, 0.0f };
	sizeOfScreen[0] = { vLookat_.x - 6, vLookat_.y + 5, 0 };
	sizeOfScreen[1] = { vLookat_.x + 6, vLookat_.y + 5, 0 };
	sizeOfScreen[2] = { vLookat_.x - 6, vLookat_.y - 8, 0 };
	sizeOfScreen[3] = { vLookat_.x + 6, vLookat_.y - 8, 0 };
}

void CCamera::move()
{
	vEye_.x += 0.0025f/6.25f;
	vLookat_.x += 0.0025f/6.25f;
	sizeOfScreen[0] = { vLookat_.x - 6, vLookat_.y + 8, 0 };
	sizeOfScreen[1] = { vLookat_.x + 6, vLookat_.y + 8, 0 };
	sizeOfScreen[2] = { vLookat_.x - 6, vLookat_.y - 8, 0 };
	sizeOfScreen[3] = { vLookat_.x + 6, vLookat_.y - 8, 0 };

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEye_, &vLookat_, &vUp_);
	CDevice::getDevice()->SetTransform(D3DTS_VIEW, &matView);
	
}

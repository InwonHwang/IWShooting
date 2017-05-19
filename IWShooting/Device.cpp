#include "Device.h"

CDevice::CDevice()
: pD3D_(nullptr), pD3DDevice_(nullptr) {}

CDevice::~CDevice()
{
	if (pD3DDevice_) pD3DDevice_->Release();
	if (pD3D_) pD3D_->Release();
}

CDevice *CDevice::getInstance()
{
	static CDevice inst;

	return &inst;
}


int CDevice::init(HWND hWnd)
{
	if (NULL == (pD3D_ = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	
	if (FAILED(pD3D_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &pD3DDevice_)))
	{
		return E_FAIL;
	}

	pD3DDevice_->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDevice_->SetRenderState(D3DRS_ZENABLE, TRUE);
	pD3DDevice_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	pD3DDevice_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return S_OK;
}



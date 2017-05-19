#pragma once

#include <d3dx9.h>

class CDevice
{
public:
	~CDevice();
	static CDevice *getInstance();
	static LPDIRECT3DDEVICE9 getDevice() { return getInstance()->pD3DDevice_; };

	int init(HWND);

private:
	CDevice();	

	LPDIRECT3D9			pD3D_;
	LPDIRECT3DDEVICE9	pD3DDevice_;
};

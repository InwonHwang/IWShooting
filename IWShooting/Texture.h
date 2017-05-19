#pragma once

#include <d3dx9.h>
#include <list>
#include <string>
#include "Device.h"

using namespace std;

#define BUF_SIZE 1024

class CTexture
{
public:
	CTexture();
	~CTexture();

	void createTexture(LPCSTR fileName);

	LPDIRECT3DTEXTURE9 getTexture() const { return pD3DTexture_; }

private:
	LPDIRECT3DTEXTURE9 pD3DTexture_;
};

class CTextureFactory{

public:
	CTextureFactory(LPCSTR stage);
	~CTextureFactory();

	CTexture * getTexture(int index) const;
	int getNumOfTexture() const { return dwNumOfFile_; }
private:
	list<string> fileList;

private:
	CTexture *texture_;
	int dwNumOfFile_;

	void setTexture();
	void loadFileName(LPCSTR stage);
	void clear();
};

#include "Texture.h"

CTexture::CTexture() : pD3DTexture_(nullptr) {}

CTexture::~CTexture()
{
	pD3DTexture_->Release();
}

void CTexture::createTexture(LPCSTR fileName)
{
	D3DXCreateTextureFromFileEx(CDevice::getDevice(), fileName,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255),
		NULL, NULL, &pD3DTexture_);
}

//////////////////////////////////////////////////////////////////////////////////////////

CTextureFactory::CTextureFactory(LPCSTR stage)
: texture_(nullptr), dwNumOfFile_(0)
{
	loadFileName(stage);
	setTexture();
}

CTextureFactory::~CTextureFactory()
{
	clear();
}

void CTextureFactory::setTexture()
{
	texture_ = new CTexture[dwNumOfFile_];

	list<string>::iterator first;
	int i = 0;
	for (first = fileList.begin(); first != fileList.end(); first++)
	{
		texture_[i++].createTexture(first->c_str());
	}
}

CTexture * CTextureFactory::getTexture(int index) const
{
	if (index > dwNumOfFile_ || index < 0) return nullptr;

	return &texture_[index];
}

void CTextureFactory::loadFileName(LPCSTR stage)
{
	HANDLE hFile;
	DWORD bytesRead;
	char buf[BUF_SIZE];
	char numOfFile = 0;

	hFile = CreateFile(stage, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return;

	if (ReadFile(hFile, &numOfFile, sizeof(char), &bytesRead, NULL) == 0)
		return;

	dwNumOfFile_ = atoi(&numOfFile);

	if (ReadFile(hFile, buf, sizeof(char)* BUF_SIZE, &bytesRead, NULL) == 0)
		return;

	buf[bytesRead] = 0;

	char *ptr = strtok(buf, " \n\t\r");
	fileList.push_back(ptr);

	while (ptr = strtok(NULL, " \n\t\r"))
		fileList.push_back(ptr);

	CloseHandle(hFile);
}

void CTextureFactory::clear()
{
	delete texture_;
	fileList.clear();
}


#include "Background.h"


CBackground::CBackground(int textNum)
: CGameObject(textNum)
{	
	initVertex(-2.5, -1.5, 50, 9);	
}

CBackground::~CBackground()
{
}

void CBackground::initUV()
{
	pVertices[0].tu = 1.0f;
	pVertices[0].tv = 0.0f;
	pVertices[1].tu = 0.0f;
	pVertices[1].tv = 0.0f;
	pVertices[2].tu = 1.0f;
	pVertices[2].tv = 1.0f;
	pVertices[3].tu = 0.0f;
	pVertices[3].tv = 1.0f;
}

void CBackground::matrices()
{
	CGameObject::matrices();
}

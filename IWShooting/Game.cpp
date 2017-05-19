#include "Game.h"

extern list<CGameObject *>	listOfBullet;
extern list<CGameObject *>	listOfEnemy;
extern list<CGameObject *>	listOfEBullet;
extern list<CGameObject *>	listOfBackground;
extern list<CGameObject *>	listOfMyPlane;
extern list<CGameObject *>	listOfSub;

static LRESULT WINAPI DummyWndProc(
	HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam
	) {
	switch (msg)
	{


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

CGame::CGame() : TFactory_(nullptr)
{
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, DummyWndProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"D3D Tutorial", NULL
	};
	RegisterClassEx(&wc);

	
	hWnd_ = CreateWindow("D3D Tutorial", "D3D Tutorial 01: CreateDevice",
		WS_OVERLAPPEDWINDOW, 0, 0, 1024, 768,
		NULL, NULL, wc.hInstance, NULL);

	BeforeFrame = CTimer::getTimer()->GetAbsoluteFrame();
	CDevice::getInstance()->init(hWnd_);

	initFont();
}

LRESULT WINAPI CGame::WndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd_, msg, wparam, lparam);
}

CGame::~CGame()
{
	
	delete TFactory_;
	
	for (list<CGameObject *>::iterator it = listOfBullet.begin(); it != listOfBullet.end(); it++)
	{
		if ((*it))
		{
			delete (*it);
			it = listOfBullet.erase(it);
		}
		else
			++it;
	}
		

	for (list<CGameObject *>::iterator it = listOfEnemy.begin(); it != listOfEnemy.end(); it++)
	{
		if ((*it))
		{
			delete (*it);
			it = listOfEnemy.erase(it);
		}
		else
			++it;
	}

	for (list<CGameObject *>::iterator it = listOfEBullet.begin(); it != listOfEBullet.end(); it++)
	{
		if ((*it))
		{
			delete (*it);
			it = listOfBullet.erase(it);
		}
		else
			++it;
	}

	for (list<CGameObject *>::iterator it = listOfBackground.begin(); it != listOfBackground.end(); it++)
	{
		if ((*it))
		{
			delete (*it);
			it = listOfBackground.erase(it);
		}
		else
			++it;
	}

	for (list<CGameObject *>::iterator it = listOfMyPlane.begin(); it != listOfMyPlane.end(); it++)
	{
		if ((*it))
		{
			delete (*it);
			it = listOfMyPlane.erase(it);
		}
		else
			++it;
	}
}

void CGame::SetStage()
{
	TFactory_ = new CTextureFactory("stage.txt");
	
	CEntityFactory::getFactory()->createCharacter(Texture::MYPLANE, 1, CCamera::getCamera()->getSizeOfScreen()[2].x+3,
		CCamera::getCamera()->getSizeOfScreen()[2].y+5, 0.7f, 0.7f);
	

	list<CGameObject *>::iterator Cit = listOfMyPlane.begin();

	CEntityFactory::getFactory()->createBackground(Texture::BACKGROUND);

	//CEntityFactory::getFactory()->createEnemy(Texture::UFO2, 1,
	//	CCamera::getCamera()->getSizeOfScreen()[3].x + 5,
	//	CCamera::getCamera()->getSizeOfScreen()[3].y + 3, 0.7f, 0.5f, true, 1, 3);
	
	
}

void CGame::draw()
{
	if (!CDevice::getDevice()) return;	

	CDevice::getDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	if (SUCCEEDED(CDevice::getDevice()->BeginScene()))
	{		
		objectDraw();
		drawFont();

		
		CDevice::getDevice()->EndScene();
	}
	CDevice::getDevice()->Present(NULL, NULL, NULL, NULL);
}

void CGame::objectUpdate()
{
	for (list<CGameObject *>::iterator it = listOfMyPlane.begin(); it != listOfMyPlane.end(); it++)
		(*it)->update();

	for (list<CGameObject *>::iterator it = listOfBullet.begin(); it != listOfBullet.end(); it++)
		(*it)->update();

	for (list<CGameObject *>::iterator it = listOfEBullet.begin(); it != listOfEBullet.end(); it++)
		(*it)->update();

	for (list<CGameObject *>::iterator it = listOfEnemy.begin(); it != listOfEnemy.end(); it++)
		(*it)->update();	

	for (list<CGameObject *>::iterator it = listOfSub.begin(); it != listOfSub.end(); it++)
		(*it)->update();	

	
	collisionCheck();
	aliveCheck();
	
}


void CGame::objectDraw()
{
	CCamera::getCamera()->move();

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	CDevice::getDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
	
	for (list<CGameObject *>::iterator it = listOfBackground.begin(); it != listOfBackground.end(); it++)
		(*it)->draw(TFactory_->getTexture((*it)->getTextNum()));


	for (list<CGameObject *>::iterator it = listOfMyPlane.begin(); it != listOfMyPlane.end(); it++)
		(*it)->draw(TFactory_->getTexture((*it)->getTextNum()));
	
	
	for (list<CGameObject *>::iterator it = listOfEnemy.begin(); it != listOfEnemy.end(); it++)
		(*it)->draw(TFactory_->getTexture((*it)->getTextNum()));
	

	for (list<CGameObject *>::iterator it = listOfEBullet.begin(); it != listOfEBullet.end(); it++)
		(*it)->draw(TFactory_->getTexture((*it)->getTextNum()));
	
	for (list<CGameObject *>::iterator it = listOfBullet.begin(); it != listOfBullet.end(); it++)
		(*it)->draw(TFactory_->getTexture((*it)->getTextNum()));

	for (list<CGameObject *>::iterator it = listOfSub.begin(); it != listOfSub.end(); it++)
		(*it)->draw(TFactory_->getTexture((*it)->getTextNum()));

}

void CGame::collisionCheck()
{
	
	for (list<CGameObject *>::iterator it = listOfBullet.begin(); it != listOfBullet.end();){
		if ((*it)->isOut(0, 0)) {
			delete (*it);
			it = listOfBullet.erase(it);
		}
		else it++;
	}

	for (list<CGameObject *>::iterator it = listOfEBullet.begin(); it != listOfEBullet.end();){
		if ((*it)->isOut(0, 0)) {
			delete (*it);
			it = listOfEBullet.erase(it);
		}
		else it++;
	}

}

void CGame::aliveCheck()
{
	

	/*for (list<CGameObject *>::iterator it = listOfMyPlane.begin(); it != listOfMyPlane.end();){
		CEntity * temp = dynamic_cast<CEntity *>(*it);
		if (temp->isDead()) {
			delete *it;
			listOfMyPlane.clear();
			break;
		}
		else
			it++;
	}
	for (list<CGameObject *>::iterator it = listOfSub.begin(); it != listOfSub.end();){
		CEntity * temp = dynamic_cast<CEntity *>(*it);
		if (temp->isDead()) {
			delete *it;
			it = listOfSub.erase(it);
		}
		else
			it++;
	}*/
	for (list<CGameObject *>::iterator it = listOfEBullet.begin(); it != listOfEBullet.end();){
		CEntity * temp = dynamic_cast<CEntity *>(*it);
		if (temp->isDead()) {
			delete *it;
			it = listOfEBullet.erase(it);
		}
		else
			it++;
	}
	for (list<CGameObject *>::iterator it = listOfBullet.begin(); it != listOfBullet.end();){
		CEntity * temp = dynamic_cast<CEntity *>(*it);
		if (temp->isDead()) {
			delete *it;
			it = listOfBullet.erase(it);
		}
		else
			it++;
	}
	for (list<CGameObject *>::iterator it = listOfEnemy.begin(); it != listOfEnemy.end();){
		CEntity * temp = dynamic_cast<CEntity *>(*it);
		if (temp->isDead()) {
			delete *it;
			it = listOfEnemy.erase(it);
		}
		else
			it++;
	}	
}

void CGame::drawFont()
{
	RECT rect;
	char str[MAX_PATH];
	SetRect(&rect, 0, 0, 800, 600);
	ZeroMemory(str, sizeof(char)* MAX_PATH);

	Font->DrawTextA(NULL, CTimer::getTimer()->GetFPS(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

void CGame::initFont()
{
	Font = NULL;									 // LPD3DXFONT 인터페이스를 선언한다.
	
	D3DXFONT_DESC desc;					     			// 폰트를 설정한다.
	desc.CharSet = HANGUL_CHARSET;
	strcpy(desc.FaceName, "");                   // FaceName을 비워놓으면 Windows Default Font를 사용한다.
	desc.Height = static_cast<INT>(10 * 2.083f);    // 주의
	desc.Width = 10;
	desc.Weight = FW_NORMAL;
	desc.Quality = DEFAULT_QUALITY;
	desc.MipLevels = 1;
	desc.Italic = 0;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.PitchAndFamily = FF_DONTCARE;

	D3DXCreateFontIndirect(CDevice::getDevice(), &desc, &Font);        // Font 생성
}

void CGame::EnemyPattern()
{

	if (CTimer::getTimer()->GetAbsoluteFrame() % 200 == 0 && CTimer::getTimer()->GetAbsoluteFrame() < 1200){
		
		/*CEntityFactory::getFactory()->createEnemy(Texture::UFO, 1, 
			CCamera::getCamera()->getSizeOfScreen()[0].x - 5,
			CCamera::getCamera()->getSizeOfScreen()[0].y, 0.7f, 0.5f, false, 0, 1);*/

		for (int i = 0; i < 4; ++i)
		{
			srand((unsigned)time(0));
			int ySize = CCamera::getCamera()->getSizeOfScreen()[0].y - CCamera::getCamera()->getSizeOfScreen()[3].y;
			int num = (rand() % (ySize /2));
			CEntityFactory::getFactory()->createEnemy(Texture::UFO2, 1,
				CCamera::getCamera()->getSizeOfScreen()[3].x - 2,
				CCamera::getCamera()->getSizeOfScreen()[3].y + 4 + num, 0.7f, 0.5f, true, 1, 3);
		}
		
	}
	if (CTimer::getTimer()->GetAbsoluteFrame() == 1300){
		CEntityFactory::getFactory()->createEnemy(Texture::BOSS, 100,
			CCamera::getCamera()->getSizeOfScreen()[1].x,
			CCamera::getCamera()->getSizeOfScreen()[1].y - 8, 4, 4, true, 2, 1);
	}

}

void CGame::run()
{
	SetStage();

	ShowWindow(hWnd_, SW_SHOWDEFAULT);
	UpdateWindow(hWnd_);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));	

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			CTimer::getTimer()->Update();
			if (BeforeFrame - CTimer::getTimer()->GetAbsoluteFrame() >= 1){
				objectUpdate();				
				EnemyPattern();
				BeforeFrame = CTimer::getTimer()->GetAbsoluteFrame();
			}
			draw();
			
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;

	}

	UnregisterClass("D3D Tutorial", GetModuleHandle(NULL));
}


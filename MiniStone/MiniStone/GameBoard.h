#pragma once
#include "preCompile.h"
#include "ImageManager.h"

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;


class GameBoard
{
private:
	HDC	mDC;

	HBITMAP	hBitmap;
	BITMAP bit;
	POINT position;
	POINT positino2;
	ImageVec*	MapEffect[2];

public:
	void init(){



		// ������//
		hBitmap = (HBITMAP)LoadImage(NULL, "./BoardResource/worldmap.bmp", IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBitmap, sizeof(bit), &bit);

		HDC hdc = GetDC(g_hWnd);
		mDC = CreateCompatibleDC(hdc);

		SelectObject(mDC, hBitmap);
		// ������//
		ImageManager::getInstance()->init();
		position.x = 655;
		position.y = 0;
		positino2.x = 677;
		positino2.y = 468;
		ImageManager::getInstance()->EffectControl("./effect");
		ImageManager::getInstance()->SetAni("wan", position);
		ImageManager::getInstance()->SetAni("wan2", positino2);
	}

	void update(){
		ImageManager::getInstance()->update();
	}

	void render(const HDC& dc){
		BitBlt(dc, 0, 0, bit.bmWidth, bit.bmHeight, mDC, 0, 0, SRCCOPY);// ��Ʈ����ºκ�
		ImageManager::getInstance()->Maprender(dc);
	}

	void release(){

		DeleteObject(hBitmap);              ///////////////
		DeleteDC(mDC);                   ///////////////
	}
	GameBoard();
	~GameBoard();
};


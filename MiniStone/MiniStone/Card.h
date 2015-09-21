#pragma once
#include "preCompile.h"
#include "InputManager.h"
extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;

class CardResource
{
private:
	int CNum;
	char *CName[20];
	int CAttack;
	int CLife;
	RECT cardRect;
	POINT Position;
	POINT CapPos;
	//
	HDC	mDC;
	HBITMAP	hBitmap;
	BITMAP bit;
	//
	bool hang;

public:
	void init(){
		CNum = 00;
		*CName = "황금카드";
		CAttack = 5;
		CLife = 1;
		Position.x = 500;
		Position.y = 500;


		// 랜더링//
		HDC hdc = GetDC(g_hWnd);
		hBitmap = (HBITMAP)LoadImage(NULL, "./CardResouce/001.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(hBitmap, sizeof(bit), &bit);
		SelectObject(mDC, hBitmap);


		cardRect.left = Position.x;
		cardRect.top = Position.y;
		cardRect.bottom = Position.y + bit.bmHeight;
		cardRect.right = Position.x + bit.bmWidth;

		hang = false;
	}

	void render(HDC& dc){
		TransparentBlt(dc, Position.x, Position.y, (100 + bit.bmWidth) / 3, (100 + bit.bmHeight) / 3, mDC, 0, 0, bit.bmWidth, bit.bmHeight, RGB(255, 128, 128));
	}

	void move(){

		DWORD key = InputManager::getInstance()->getKeyState();
		//마우스 좌표 출력

		cardRect.left = Position.x;
		cardRect.top = Position.y;
		cardRect.bottom = Position.y + bit.bmHeight;
		cardRect.right = Position.x + bit.bmWidth;

		POINT pt = InputManager::getInstance()->getMousePos();

		if (PtInRect(&cardRect, pt)){
			//PtInRect = 점과 사각형의 충돌을 검출하는 함수

			if (key & MYKEY_FLAG::MK_LCLK){
				if (!hang) hang = true;
				else hang = false;
				CapPos = InputManager::getInstance()->getMousePos();
			}
		}


		if (hang)
		{
			POINT moveCard;

			moveCard.x = pt.x - CapPos.x;
			moveCard.y = pt.y - CapPos.y;

			Position.x += moveCard.x;
			Position.y += moveCard.y;
		}

		CapPos = pt;
	}


	void release(){
		DeleteObject(hBitmap);              ///////////////
		DeleteDC(mDC);                   ///////////////

	}

	CardResource();
	~CardResource();
};


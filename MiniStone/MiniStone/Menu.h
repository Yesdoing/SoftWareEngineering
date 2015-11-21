#pragma once
#include "preCompile.h"
#include "InputManager.h"
#include "ImageDB.h"

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;

class Menu
{
private:
	SImageDB	Opening;
	SImageDB	MenuInterface;
	SImageDB	Menu1;
	SImageDB	Menu2;
	SImageDB	Menu3;
	SImageDB	Menu4;
	RECT	M1, M2, M3, M4;

	/*
	1 430 218 / 595 245
	2 397 278 / 627 301
	3 400 334 / 622 357
	4 427 390 / 592 412
	*/

public:
	void init(){
		Opening.hBit = (HBITMAP)LoadImage(NULL, "./Menu/Opening.bmp", IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(Opening.hBit, sizeof(Opening.Bit), &Opening.Bit);
		HDC hdc = GetDC(g_hWnd);
		Opening.mDC = CreateCompatibleDC(hdc);
		SelectObject(Opening.mDC, Opening.hBit);

		MenuInterface.hBit = (HBITMAP)LoadImage(NULL, "./Menu/menu.bmp", IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(MenuInterface.hBit, sizeof(MenuInterface.Bit), &MenuInterface.Bit);
		MenuInterface.mDC = CreateCompatibleDC(hdc);
		SelectObject(MenuInterface.mDC, MenuInterface.hBit);

		Menu1.hBit = (HBITMAP)LoadImage(NULL, "./Menu/menu1-1.bmp", IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(Menu1.hBit, sizeof(Menu1.Bit), &Menu1.Bit);
		Menu1.mDC = CreateCompatibleDC(hdc);
		SelectObject(Menu1.mDC, Menu1.hBit);

		Menu2.hBit = (HBITMAP)LoadImage(NULL, "./Menu/menu1-2.bmp", IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(Menu2.hBit, sizeof(Menu2.Bit), &Menu2.Bit);
		Menu2.mDC = CreateCompatibleDC(hdc);
		SelectObject(Menu2.mDC, Menu2.hBit);

		Menu3.hBit = (HBITMAP)LoadImage(NULL, "./Menu/menu1-3.bmp", IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(Menu3.hBit, sizeof(Menu3.Bit), &Menu3.Bit);
		Menu3.mDC = CreateCompatibleDC(hdc);
		SelectObject(Menu3.mDC, Menu3.hBit);

		Menu4.hBit = (HBITMAP)LoadImage(NULL, "./Menu/menu1-4.bmp", IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(Menu4.hBit, sizeof(Menu4.Bit), &Menu4.Bit);
		Menu4.mDC = CreateCompatibleDC(hdc);
		SelectObject(Menu4.mDC, Menu4.hBit);


			M1.left = 430;
			M1.top = 218;
			M1.right = 595;
			M1.bottom = 245;

		M2.left = 397;
		M2.top = 278;
		M2.right = 627;
		M2.bottom = 301;

		M3.left = 400;
		M3.top = 334;
		M3.right = 622;
		M3.bottom = 357;

		M4.left = 427;
		M4.top = 390;
		M4.right = 592;
		M4.bottom = 412;
	}

	void Openingrender(const HDC& dc){
		BitBlt(dc, 0, 0, Opening.Bit.bmWidth, Opening.Bit.bmHeight, Opening.mDC, 0, 0, SRCCOPY);// 비트맵출력부분
	}

	void render(const HDC& dc){
		switch (GetState())
		{
		case 0:
			BitBlt(dc, 0, 0, MenuInterface.Bit.bmWidth, MenuInterface.Bit.bmHeight, MenuInterface.mDC, 0, 0, SRCCOPY);
			break;
		case 1:
			BitBlt(dc, 0, 0, Menu1.Bit.bmWidth, Menu1.Bit.bmHeight, Menu1.mDC, 0, 0, SRCCOPY);
			break;
		case 2:
			BitBlt(dc, 0, 0, Menu2.Bit.bmWidth, Menu2.Bit.bmHeight, Menu2.mDC, 0, 0, SRCCOPY);
			break;
		case 3:
			BitBlt(dc, 0, 0, Menu3.Bit.bmWidth, Menu3.Bit.bmHeight, Menu3.mDC, 0, 0, SRCCOPY);
			break;
		case 4:
			BitBlt(dc, 0, 0, Menu4.Bit.bmWidth, Menu4.Bit.bmHeight, Menu4.mDC, 0, 0, SRCCOPY);
			break;
		case 5:
			BitBlt(dc, 0, 0, Opening.Bit.bmWidth, Opening.Bit.bmHeight, Opening.mDC, 0, 0, SRCCOPY);
			break;
		}
	}

	//void Menurender(const HDC& dc){
	//	BitBlt(dc, 0, 0, MenuInterface.Bit.bmWidth, MenuInterface.Bit.bmHeight, MenuInterface.mDC, 0, 0, SRCCOPY);// 비트맵출력부분
	//}

	//void Menu1_render(const HDC& dc){
	//	BitBlt(dc, 0, 0, Menu1.Bit.bmWidth, Menu1.Bit.bmHeight, Menu1.mDC, 0, 0, SRCCOPY);// 비트맵출력부분
	//}

	//void Menu2_render(const HDC& dc){
	//	BitBlt(dc, 0, 0, Menu2.Bit.bmWidth, Menu2.Bit.bmHeight, Menu2.mDC, 0, 0, SRCCOPY);// 비트맵출력부분
	//}

	//void Menu3_render(const HDC& dc){
	//	BitBlt(dc, 0, 0, Menu3.Bit.bmWidth, Menu3.Bit.bmHeight, Menu3.mDC, 0, 0, SRCCOPY);// 비트맵출력부분
	//}

	//void Menu4_render(const HDC& dc){
	//	BitBlt(dc, 0, 0, Menu4.Bit.bmWidth, Menu4.Bit.bmHeight, Menu4.mDC, 0, 0, SRCCOPY);// 비트맵출력부분
	//}
	bool offOpening = true;
	int GetState(){
		POINT _pos = InputManager::getInstance()->getMousePos();
		DWORD _key = InputManager::getInstance()->getKeyState();

		if (_key & MYKEY_FLAG::MK_LCLK)
			offOpening = false;
		if (offOpening) return 5;
		else{
			if (PtInRect(&M1, _pos)) return 1;
			else if (PtInRect(&M2, _pos)) return 2;
			else if (PtInRect(&M3, _pos)) return 3;
			else if (PtInRect(&M4, _pos)) return 4;
			else return 0;
		}
	}

	int update(POINT pos){
		DWORD _key = InputManager::getInstance()->getKeyState();
		if (_key & MYKEY_FLAG::MK_LCLK)
		{
			if (PtInRect(&M1, pos)) return 1;
			else if (PtInRect(&M2, pos)) return 2;
			else if (PtInRect(&M3, pos)) return 3;
			else if (PtInRect(&M4, pos)) return 4;
		}

	}


	Menu();
	~Menu();
};


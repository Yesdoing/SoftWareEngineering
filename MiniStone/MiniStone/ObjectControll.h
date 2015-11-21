#pragma once
#include "preCompile.h"
#include "ImageDB.h"
#include "Card.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;

class ObjectControll
{
private:
	SImageDB	board;
	SImageDB	Menu1;
	SImageDB	Menu2;
public:
	void init(){
		HDC	hdc = GetDC(g_hWnd);
		board.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/blackworld.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		board.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(board.hBit, sizeof(board.Bit), &board.Bit);
		SelectObject(board.mDC, board.hBit);

		Menu1.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/01.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Menu1.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(Menu1.hBit, sizeof(Menu1.Bit), &Menu1.Bit);
		SelectObject(Menu1.mDC, Menu1.hBit);

		Menu2.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/02.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Menu2.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(Menu2.hBit, sizeof(Menu2.Bit), &Menu2.Bit);
		SelectObject(Menu2.mDC, Menu2.hBit);

	}

	void FirstCardSelect(Card* _deck){
		
	}

	void render(const HDC& dc){
		BitBlt(dc, 0, 0, board.Bit.bmWidth, board.Bit.bmHeight, board.mDC, 0, 0, SRCCOPY);
		BitBlt(dc, 200, 200, Menu1.Bit.bmWidth, Menu1.Bit.bmHeight, Menu1.mDC, 0, 0, SRCCOPY);
		BitBlt(dc, 200, 500, Menu2.Bit.bmWidth, Menu2.Bit.bmHeight, Menu2.mDC, 0, 0, SRCCOPY);
	}

	ObjectControll();
	~ObjectControll();
};


#pragma once
#include "preCompile.h"

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;


class GameBoard
{
private:
	HDC	mDC;

	HBITMAP	hBitmap;
	BITMAP bit;

public:
	void init(){



		// 랜더링//
		hBitmap = (HBITMAP)LoadImage(NULL, "./BoardResource/worldmap.bmp", IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBitmap, sizeof(bit), &bit);

		HDC hdc = GetDC(g_hWnd);
		mDC = CreateCompatibleDC(hdc);// MemDC 하는..솔직히 뭐하는건지 모름..-_-; 그냥사용한다는

		SelectObject(mDC, hBitmap);////hBitmap 에서 warning 뜸...스펠링맞나..-_-; ******//
		// 랜더링//


	}

	void render(const HDC& dc){



		BitBlt(dc, 0, 0, bit.bmWidth, bit.bmHeight, mDC, 0, 0, SRCCOPY);// 비트맵출력부분



	}

	void release(){

		DeleteObject(hBitmap);              ///////////////
		DeleteDC(mDC);                   ///////////////
	}
	GameBoard();
	~GameBoard();
};


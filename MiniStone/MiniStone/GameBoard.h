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



		// ������//
		hBitmap = (HBITMAP)LoadImage(NULL, "./BoardResource/worldmap.bmp", IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBitmap, sizeof(bit), &bit);

		HDC hdc = GetDC(g_hWnd);
		mDC = CreateCompatibleDC(hdc);// MemDC �ϴ�..������ ���ϴ°��� ��..-_-; �׳ɻ���Ѵٴ�

		SelectObject(mDC, hBitmap);////hBitmap ���� warning ��...���縵�³�..-_-; ******//
		// ������//


	}

	void render(const HDC& dc){



		BitBlt(dc, 0, 0, bit.bmWidth, bit.bmHeight, mDC, 0, 0, SRCCOPY);// ��Ʈ����ºκ�



	}

	void release(){

		DeleteObject(hBitmap);              ///////////////
		DeleteDC(mDC);                   ///////////////
	}
	GameBoard();
	~GameBoard();
};


#pragma once
#include "preCompile.h"
#include "ImageDB.h"

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;


class CObjectManager
{
private:
	SCard CardObject;
	FILE *f;

public:
	void init(){
		
		SCard temp;
		f = fopen("card.dat", "rb");
		if (f != NULL){
			fscanf(f, "%s %s %d %d %d", &temp.Cnum, &temp.Cname, &temp.CAttack, &temp.CLife, &temp.CMana);
		}
	
		CardObject = temp;

		CardObject.Position.x = 100;
		CardObject.Position.y = 100;

		char pathBuf[_MAX_DIR] = { 0, };

		strcat_s(pathBuf, _MAX_DIR, "./CardResouce");
		strcat_s(pathBuf, _MAX_DIR, "/");
		strcat_s(pathBuf, _MAX_DIR, CardObject.Cnum);
		strcat_s(pathBuf, _MAX_DIR, ".bmp");
		
		HDC hdc = GetDC(g_hWnd);
		CardObject.imgDB.hBit = (HBITMAP)LoadImage(NULL, pathBuf, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		CardObject.imgDB.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(CardObject.imgDB.hBit, sizeof(CardObject.imgDB.Bit), &CardObject.imgDB.Bit);
		SelectObject(CardObject.imgDB.mDC, CardObject.imgDB.hBit);

		int a = 10;

		CardObject.imgDB.Source.left = CardObject.Position.x;
		CardObject.imgDB.Source.top = CardObject.Position.y;
		CardObject.imgDB.Source.right = CardObject.Position.y + CardObject.imgDB.Bit.bmWidth;
		CardObject.imgDB.Source.bottom = CardObject.Position.x + CardObject.imgDB.Bit.bmHeight;

		fclose(f);
	}

	void render(HDC& dc){
		TransparentBlt(dc, CardObject.Position.x, CardObject.Position.y, 
			(100 + CardObject.imgDB.Bit.bmWidth) / 3, 
			(100 + CardObject.imgDB.Bit.bmHeight) / 3, 
			CardObject.imgDB.mDC, 
			0, 
			0, 
			CardObject.imgDB.Bit.bmWidth, 
			CardObject.imgDB.Bit.bmHeight, 
			RGB(255, 128, 128));
	}

	CObjectManager();
	~CObjectManager();
};


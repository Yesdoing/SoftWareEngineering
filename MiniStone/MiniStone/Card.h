#pragma once
#include "preCompile.h"
#include "InputManager.h"
#include "ImageDB.h"

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;

class Card{
protected:
	SImageDB	Fieldimg;
	SImageDB	handimg;
	CType		type;
	char		Cnum[4];
	char		Cname[10];
	int			CAttack;
	int			CLife;
	int			CMana;
	POINT		Position;
	int			CardSize;


public:
	void SetCardPosition(int _x, int _y)
	{
		Position.x = _x;
		Position.y = _y;
	}

	char* getCardnum()
	{
		return Cnum;
	}

	void init(char* _Cnum, char* _Cname, int _CAtk, int _CLife, int _CMana){
		char pathBuf[_MAX_DIR] = { 0, };

		type = Minion;


		CardSize = 5;

		strcpy(this->Cnum, _Cnum);
		strcpy(this->Cname, _Cname);
		this->CAttack = _CAtk;
		this->CLife = _CLife;
		this->CMana = _CMana;

		this->Position.x = 800;
		this->Position.y = 300;

		strcat_s(pathBuf, _MAX_DIR, "./CardResouce");
		strcat_s(pathBuf, _MAX_DIR, "/");
		strcat_s(pathBuf, _MAX_DIR, this->Cnum);
		strcat_s(pathBuf, _MAX_DIR, ".bmp");

		HDC hdc = GetDC(g_hWnd);
		handimg.hBit = (HBITMAP)LoadImage(NULL, pathBuf, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		handimg.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(handimg.hBit, sizeof(handimg.Bit), &handimg.Bit);
		SelectObject(handimg.mDC, handimg.hBit);


		ZeroMemory(pathBuf, sizeof(pathBuf));

		strcat_s(pathBuf, _MAX_DIR, "./CardFieldResource");
		strcat_s(pathBuf, _MAX_DIR, "/");
		strcat_s(pathBuf, _MAX_DIR, this->Cnum);
		strcat_s(pathBuf, _MAX_DIR, ".bmp");

		Fieldimg.hBit = (HBITMAP)LoadImage(NULL, pathBuf, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Fieldimg.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(Fieldimg.hBit, sizeof(Fieldimg.Bit), &Fieldimg.Bit);
		SelectObject(Fieldimg.mDC, Fieldimg.hBit);


		this->handimg.Source.left = 0;
		this->handimg.Source.top = 0;
		this->handimg.Source.right = this->handimg.Bit.bmWidth / 5;
		this->handimg.Source.bottom = this->handimg.Bit.bmWidth / 5;
	}
	

	void Handrender(HDC& dc){
		TransparentBlt(dc, Position.x, Position.y, (100 + handimg.Bit.bmWidth) / CardSize,
			(100 + handimg.Bit.bmHeight) / CardSize,
			handimg.mDC,
			0,
			0,
			handimg.Bit.bmWidth,
			handimg.Bit.bmHeight,
			RGB(255, 128, 128));
	}

	void Fieldrender(HDC& dc){
		TransparentBlt(dc, Position.x, Position.y, (100 + Fieldimg.Bit.bmWidth) / CardSize,
			(100 + Fieldimg.Bit.bmHeight) / CardSize,
			Fieldimg.mDC,
			0,
			0,
			Fieldimg.Bit.bmWidth,
			Fieldimg.Bit.bmHeight,
			RGB(255, 128, 128));
	}



	Card();
	~Card();
};
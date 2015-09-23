#pragma once
#include "preCompile.h"
#include "ImageDB.h"
#include "InputManager.h"
#include "ObjectManager.h"

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;

class CInventory
{
private:
	SImageDB	imgInven;
	POINT		PosInven;
	POINT		CapPos;


	bool InvenMove;
	bool CardMove;


	//아이템창 크기설정
	const int			stackInvenCol = 8;
	const int			stackInvenRow = 4;
	int					stackInvenElementSize = 32;

	int					curInven = 0;

	RECT				_stackWindow;
public:
	void Init(){
		PosInven.x = 600;
		PosInven.y = 600;

		InvenMove = false;
		CardMove = false;
	
		CapPos.x = .0f;
		CapPos.y = .0f;

		HDC hdc = GetDC(g_hWnd);

		imgInven.hBit = (HBITMAP)LoadImage(NULL, "./Inventory.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		imgInven.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(imgInven.hBit, sizeof(imgInven.Bit), &imgInven.Bit);
		SelectObject(imgInven.mDC, imgInven.hBit);

	
	}

	void render(HDC& dc){
		TransparentBlt(dc, PosInven.x, PosInven.y,
			(100 + imgInven.Bit.bmWidth),
			(100 + imgInven.Bit.bmHeight),
			imgInven.mDC,
			0,
			0,
			imgInven.Bit.bmWidth,
			imgInven.Bit.bmHeight,
			RGB(255, 255, 255));

	}

	void MoveInventory(){
		DWORD _key = InputManager::getInstance()->getKeyState();
		POINT _pos = InputManager::getInstance()->getMousePos();

		imgInven.Source.left = PosInven.x;
		imgInven.Source.top = PosInven.y;
		imgInven.Source.right = PosInven.y + imgInven.Bit.bmHeight;
		imgInven.Source.bottom = PosInven.x + imgInven.Bit.bmWidth;

		if (PtInRect(&imgInven.Source, _pos)){
			if (_key & MYKEY_FLAG::MK_LCLK){
				if (!InvenMove) InvenMove = true;
				else InvenMove = false;
				CapPos = InputManager::getInstance()->getMousePos();
			}

		}
		
		if (InvenMove){
			POINT mvpoint;

			mvpoint.x = _pos.x - CapPos.x;
			mvpoint.y = _pos.y - CapPos.y;

			PosInven.x += mvpoint.x;
			PosInven.y += mvpoint.y;
		}

		CapPos = _pos;
	}

	CInventory();
	~CInventory();
};


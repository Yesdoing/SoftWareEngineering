//#pragma once
//#include "preCompile.h"
//#include "ImageDB.h"
//#include "InputManager.h"
//#include "ObjectManager.h"
//
//extern HWND g_hWnd;
//extern HINSTANCE		g_hInstance;
//
//class CInventory
//{
//private:
//	SImageDB	imgInven;
//	POINT		PosInven;
//	POINT		CapPos;
//
//
//	bool InvenMove;
//	bool CardMove;
//
//
//	CObjVector PlayerInventory;
//
//
//	//아이템창 크기설정
//	const int			stackInvenCol = 8;
//	const int			stackInvenRow = 4;
//	int					stackInvenElementSize = 32;
//	POINT				ItemPos;
//
//	int					curInven = 0;
//
//	RECT				_stackWindow;
//
//public:
//	void Init(){
//		PosInven.x = 100;
//		PosInven.y = 100;
//
//		InvenMove = false;
//		CardMove = false;
//	
//		CapPos.x = .0f;
//		CapPos.y = .0f;
//
//		ItemPos.x = .0f;
//		ItemPos.y = .0f;
//
//		HDC hdc = GetDC(g_hWnd);
//
//		imgInven.hBit = (HBITMAP)LoadImage(NULL, "./Inventory.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
//		imgInven.mDC = CreateCompatibleDC(GetDC(GetFocus()));
//		GetObject(imgInven.hBit, sizeof(imgInven.Bit), &imgInven.Bit);
//		SelectObject(imgInven.mDC, imgInven.hBit);
//
//	
//	}
//
//	void render(HDC& dc){
//		TransparentBlt(dc, PosInven.x, PosInven.y,
//			(100 + imgInven.Bit.bmWidth)/5,
//			(100 + imgInven.Bit.bmHeight)/5,
//			imgInven.mDC,
//			0,
//			0,
//			imgInven.Bit.bmWidth,
//			imgInven.Bit.bmHeight,
//			RGB(255, 255, 255));
//
//	}
//
//	void addCard(int _posNum, CObjectManager *card){
//		PlayerInventory[_posNum] = card;
//	}
//
//	void MoveInventory(){
//		DWORD _key = InputManager::getInstance()->getKeyState();
//		POINT _pos = InputManager::getInstance()->getMousePos();
//
//		imgInven.Source.left = PosInven.x;
//		imgInven.Source.top = PosInven.y;
//		imgInven.Source.right = PosInven.y + imgInven.Bit.bmHeight;
//		imgInven.Source.bottom = PosInven.x + imgInven.Bit.bmWidth;
//
//
//
//		if (PtInRect(&imgInven.Source, _pos)){
//			int index = 0;
//			int xx = (_pos.x - PosInven.x) / (imgInven.Bit.bmWidth / 3);
//			int yy = (_pos.y - PosInven.y) / (imgInven.Bit.bmHeight / 3);
//
//			index = xx + yy * stackInvenCol;
//
//				if (_key & MYKEY_FLAG::MK_LCLK){
//					if (!CardMove) CardMove = true;
//					else CardMove = false;
//					CapPos = InputManager::getInstance()->getMousePos();
//				}
//
//
//			if (CardMove){
//				POINT moveItem;
//
//				moveItem.x = _pos.x - CapPos.x;
//				moveItem.y = _pos.y - CapPos.y;
//
//				PlayerInventory[index]->move();
//
//			}
//		}
//
//
//		//if (InvenMove){
//		//	POINT mvpoint;
//
//		//	mvpoint.x = _pos.x - CapPos.x;
//		//	mvpoint.y = _pos.y - CapPos.y;
//
//		//	PosInven.x += mvpoint.x;
//		//	PosInven.y += mvpoint.y;
//		//}
//
//		CapPos = _pos;
//	}
//
//	CInventory();
//	~CInventory();
//};
//

#pragma once
#include "preCompile.h"
#include "GameBoard.h"
#include "Card.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "Inventory.h"

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;

class MainFrameWork{
private:
	CardResource C1;
	CObjectManager O1;
	GameBoard board;
	CInventory Inven1;
	//
	HDC dc, backDC;
	HBITMAP backBuf;
	//

	bool Inven;


public:
	void Initialize(){
		// 랜더링//
		dc = GetDC(g_hWnd);
		backDC = CreateCompatibleDC(dc);
		backBuf = CreateCompatibleBitmap(dc, WINDOW_WIDTH, WINDOW_HEIGHT);
		(HBITMAP)SelectObject(backDC, backBuf);

		/*
		// 랜더링//
		dc = GetDC(g_hWnd);
		backDC = CreateCompatibleDC(dc);
		backBuf = CreateCompatibleBitmap(dc, 1920, 1000);
		(HBITMAP)SelectObject(backDC, backBuf);
		*/

		board.init();
		C1.init();
		O1.init();
		Inven1.Init();
		//초기화

	}

	void update(){
		DWORD _key = InputManager::getInstance()->getKeyState();;

		//업데이트? Progress??
		if (_key & MYKEY_FLAG::MK_I)
		{
			if (!Inven) Inven = true;
			else Inven = false;
		}
		Inven1.MoveInventory();

	}

	void Progress(){
		InputManager::getInstance()->updateMousePos();
		InputManager::getInstance()->updateKeyState();

		C1.move();
		update();
		render();
	}

	void render(){





		board.render(backDC);
		C1.render(backDC);
		O1.render(backDC);
		if (Inven)	Inven1.render(backDC);
		BitBlt(dc, 0, 0, 1920, 1000, backDC, 0, 0, SRCCOPY);

		//	SelectObject(backDC, o );

	}

	void relesae(){
		board.release();
	}
};
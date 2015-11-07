#pragma once
#include "preCompile.h"
#include "GameBoard.h"
#include "Card.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "Inventory.h"
#include "Deck.h"
#include "Player.h"
#include "Menu.h"

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;

class MainFrameWork{
private:
	HDC dc, backDC;
	HBITMAP backBuf;

	Menu MenuIF;
	int GameState;
	Player P1;
//	CardResource C1;
//	CObjectManager O1;
	GameBoard board;
//	CInventory Inven1;
//	Deck	D1;




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
		GameState = 0;
		MenuIF.init();
//		D1.init();
		board.init();
//		C1.init();
//		O1.init();
		P1.init();
	//	Inven1.Init();
		//초기화

	}

	void update(){
		DWORD _key = InputManager::getInstance()->getKeyState();
		POINT pos = InputManager::getInstance()->getMousePos();
		P1.Update(pos);
//		GameState = MenuIF.GetState();
		//업데이트? Progress??
	}

	void Progress(){
		InputManager::getInstance()->updateMousePos();
		InputManager::getInstance()->updateKeyState();
		
////메뉴창 구현완료
		//switch (GameState){
		//case 0:
		//	MenuIF.Menurender(dc);
		//	break;
		//case 1:
		//	MenuIF.Menu1_render(dc);
		//	break;
		//case 2:
		//	MenuIF.Menu2_render(dc);
		//	break;
		//case 3:
		//	MenuIF.Menu3_render(dc);
		//	break;
		//case 4:
		//	MenuIF.Menu4_render(dc);
		//	break;
		//}

		render();
		update();
	
	}

	void render(){
		board.render(backDC);
		P1.draw(backDC);
		BitBlt(dc, 0, 0, 1920, 1000, backDC, 0, 0, SRCCOPY);

		//	SelectObject(backDC, o );

	}

	void relesae(){
		board.release();
	}
};
#pragma once
#include "preCompile.h"
#include "GameBoard.h"
#include "Card.h"
#include "InputManager.h"
#include "Player.h"
#include "Menu.h"
#include "ImageManager.h"
#include "Battle.h"

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
	Battle	battle1;



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
		battle1.Initialize();
//		D1.init();
//		board.init();
//		C1.init();
//		O1.init();
//		P1.init();
	//	Inven1.Init();
		//초기화
		
	}

	void update(){
		DWORD _key = InputManager::getInstance()->getKeyState();
		POINT pos = InputManager::getInstance()->getMousePos();

//		board.update();
	//	GameState = MenuIF.GetState();
		//업데이트? Progress??
//		P1.update(pos);
		if (GameState == 0){
			GameState = MenuIF.update(pos);

			battle1.setMode(GameState);

		}
		else if (GameState == 1)
			battle1.update();
		else if (GameState == 2)
			;
	}

	void Progress(){
		InputManager::getInstance()->updateMousePos();
		InputManager::getInstance()->updateKeyState();
		
		update();
		render();
	
	
	
	}

	void render(){
//		board.render(backDC);
//		P1.draw(backDC);
//		P1.ExImage(backDC);
		if(GameState == 0)
			MenuIF.render(backDC);
		else if(GameState == 1)
			battle1.render(backDC);
		else if (GameState == 2)
			battle1.render(backDC);
		BitBlt(dc, 0, 0, 1920, 1000, backDC, 0, 0, SRCCOPY);


		//	SelectObject(backDC, o );

	}

	void relesae(){
		board.release();
	}
};
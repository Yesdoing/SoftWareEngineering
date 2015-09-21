#pragma once
#include "preCompile.h"
#include "GameBoard.h"
#include "Card.h"
#include "InputManager.h"

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;

class MainFrameWork{
private:
	CardResource C1;
	GameBoard board;

	//
	HDC dc, backDC;
	HBITMAP backBuf;
	//

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
		//초기화

	}

	void update(){
		//업데이트? Progress??
	}

	void Progress(){
		InputManager::getInstance()->updateMousePos();
		InputManager::getInstance()->updateKeyState();

		C1.move();

		render();
	}

	void render(){






		board.render(backDC);
		C1.render(backDC);

		BitBlt(dc, 0, 0, 1920, 1000, backDC, 0, 0, SRCCOPY);

		//	SelectObject(backDC, o );

	}

	void relesae(){
		board.release();
	}
};
#pragma once
#include "preCompile.h"
#include "GameBoard.h"
#include "Card.h"
#include "InputManager.h"
#include "Menu.h"
#include "ImageManager.h"
#include "Battle.h"
#include "VSUser.h"

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;
extern pass E_recv;

class MainFrameWork{
private:
	HDC dc, backDC;
	HBITMAP backBuf;

	Menu MenuIF;
	int GameState;
	GameBoard board;
	Battle	battle1;
	VSUser	v1;


	bool Inven;

	bool GameInit;
	bool GameInit2;
	BOOL sound;
	MCI_OPEN_PARMS mciOpen;
	int dwID;
	MCI_PLAY_PARMS mciPlay;

public:
	void Initialize(){
		///////////배경음 초기화////////////
		mciOpen.lpstrDeviceType = "mpegvideo";  // mpegvideo : mp3, waveaudio : wav, avivideo : avi
		mciOpen.lpstrElementName = "d:\\bgm.wav"; // 파일이름
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
		/////////////////////////


		// 재생/////////////
		dwID = mciOpen.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
		//////////////////

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
		GameInit = true;
		GameInit2 = true;
		//초기화
		CNum::getInstance()->set();
	}

	void update(){
		DWORD _key = InputManager::getInstance()->getKeyState();
		POINT pos = InputManager::getInstance()->getMousePos();

		if (GameState == 0){
			GameState = MenuIF.update(pos);
		}
		else if (GameState == 1){
			battle1.update();

			if (battle1.relesae() == -1){
				GameState = 0;
				GameInit = true;
			}
		}

		else if (GameState == 2){
			v1.update();
		}

	}

	void Progress(){
		InputManager::getInstance()->updateMousePos();
		InputManager::getInstance()->updateKeyState();
		


		update();
		if (GameState == 1){
			if (GameInit)
			{
				GameInit = false;
				battle1.Initialize();
			}
		}
		else if (GameState == 2){
			if (GameInit2)
			{
				GameInit2 = false;
				v1.Initialize();
			}
		}

		render();


	
	
	}

	void render(){
		if(GameState == 0)
			MenuIF.render(backDC);
		else if (GameState == 1){
			////////////플레이 사운드//////////////
			if (sound == TRUE){
				mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);

				mciOpen.lpstrElementName = "d:\\bgm2.wav"; // 파일이름
				mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

				// 재생
				//	dwID = mciOpen.wDeviceID;
				mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);

				//PlaySound(TEXT("D:\\bgm2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
				sound = FALSE;

			}
			////////////////////////////

			battle1.render(backDC);
		}

		else if (GameState == 2){
			v1.render(backDC);
		}

		BitBlt(dc, 0, 0, 1920, 1000, backDC, 0, 0, SRCCOPY);


		//	SelectObject(backDC, o );

	}

	void relesae(){
		board.release();
	}
};
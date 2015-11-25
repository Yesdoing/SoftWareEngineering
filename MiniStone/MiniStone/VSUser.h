#pragma once
#include "preCompile.h"
#include "Player.h"
#include "GameBoard.h"
#include "Num.h"
#include "Network.h"

class VSUser
{
private:
	int		GameState;
	Player P1;
	Player E1;
	GameBoard board;
	bool Turn;
	bool Inven;


public:
	void Initialize(){
		board.init();
		P1.init();
		E1.init();
		Turn = true;
		P1.setTheOther(&E1);
		E1.setTheOther(&P1);
		Network::getInstance()->init();
		setMode();

	}

	void update(){
		DWORD _key = InputManager::getInstance()->getKeyState();
		POINT pos = InputManager::getInstance()->getMousePos();

		board.update();
		///		GameState = MenuIF.GetState();
		//업데이트? Progress??
		P1.Net_update(pos);
		E1.N_update();

	}

	void Progress(){
		InputManager::getInstance()->updateMousePos();
		InputManager::getInstance()->updateKeyState();
		update();


	}

	void render(HDC& dc){
		board.render(dc);
		P1.ManaRender(dc);
		E1.E_ManaRender(dc);
		P1.ExImage(dc);
		P1.draw(dc);
		E1.N_draw(dc);

	}

	int relesae(){
		return P1.checkVictory();
	}

	void setMode(){
			//네트워크
			GameState = 2;
			P1.startDeck(3);
	}

public:
	VSUser();
	~VSUser();
};
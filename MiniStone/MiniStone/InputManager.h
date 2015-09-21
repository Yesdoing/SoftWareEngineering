#pragma once
#include "preCompile.h"
#include "MouseCtrl.h"

class InputManager
	:private MouseCtrl
{
private:
	int Movesize;
	static InputManager *myInstance;
public:
	static InputManager *getInstance(){
		if (!myInstance)
			myInstance = new InputManager;

		return myInstance;
	}

	static void Release(){
		if (myInstance)
			delete myInstance;
		myInstance = NULL;
	}

public:
	//���콺 �������̽�
	void const updateMousePos(){
		MouseCtrl::UpdateMouseWinAPI();
	}

	const POINT& const getMousePos(){
		return MouseCtrl::getMousePos();
	}

	//Ű���� �������̽�
	void const updateKeyState(){
		MouseCtrl::UpdateKeyStateWinAPI();
	}

	const DWORD& const getKeyState(){
		return MouseCtrl::GetKeyState();
	}

private:
	InputManager(){}
	~InputManager(){}
};


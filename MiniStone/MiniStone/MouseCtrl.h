#pragma once
#include "preCompile.h"



class MouseCtrl
{
private:
	POINT m_MousePos;
	DWORD m_KeyState;

public:
	void UpdateMouseWinAPI(){
		GetCursorPos(&m_MousePos);
		ScreenToClient(GetActiveWindow(), &m_MousePos);
	}

	const POINT& getMousePos() const {
		return m_MousePos;
	}

	const DWORD& GetKeyState() {
		return m_KeyState;
	}

	void UpdateKeyStateWinAPI(){
		m_KeyState = 0;

		// <- A ,  D ->
		m_KeyState |= (GetAsyncKeyState(VK_LEFT) & 0x8001) ? MK_LEFT : 0;
		//		m_KeyState |= (GetAsyncKeyState('A') & 0x8001) ? MK_LEFT : 0;
		m_KeyState |= (GetAsyncKeyState(VK_RIGHT) & 0x8001) ? MK_RIGHT : 0;
		//		m_KeyState |= (GetAsyncKeyState('D') & 0x8001) ? MK_RIGHT : 0;
		m_KeyState |= (GetAsyncKeyState(VK_UP) & 0x8001) ? MK_UP : 0;
		m_KeyState |= (GetAsyncKeyState(VK_DOWN) & 0x8001) ? MK_DOWN : 0;
		m_KeyState |= (GetAsyncKeyState(VK_RETURN) & 0x8001) ? MK_ENTER : 0;
		m_KeyState |= (GetAsyncKeyState(VK_SPACE) & 0x8001) ? MK_SPACE : 0;
		m_KeyState |= (GetAsyncKeyState(VK_SHIFT) & 0x8001) ? MK_SHIF : 0;
		m_KeyState |= (GetAsyncKeyState('A') & 0x8001) ? MK_A : 0;
		m_KeyState |= (GetAsyncKeyState('S') & 0x8001) ? MK_S : 0;
		m_KeyState |= (GetAsyncKeyState('D') & 0x8001) ? MK_D : 0;
		m_KeyState |= (GetAsyncKeyState('F') & 0x8001) ? MK_F : 0;
		m_KeyState |= (GetAsyncKeyState('Q') & 0x8001) ? MK_Q : 0;
		m_KeyState |= (GetAsyncKeyState('W') & 0x8001) ? MK_W : 0;
		m_KeyState |= (GetAsyncKeyState('E') & 0x8001) ? MK_E : 0;
		m_KeyState |= (GetAsyncKeyState('R') & 0x8001) ? MK_R : 0;
		m_KeyState |= (GetAsyncKeyState('1') & 0x8001) ? MK_1 : 0;
		m_KeyState |= (GetAsyncKeyState('2') & 0x8001) ? MK_2 : 0;
		m_KeyState |= (GetAsyncKeyState('3') & 0x8001) ? MK_3 : 0;
		m_KeyState |= (GetAsyncKeyState('4') & 0x8001) ? MK_4 : 0;
		m_KeyState |= (GetAsyncKeyState('5') & 0x8001) ? MK_5 : 0;
		m_KeyState |= (GetAsyncKeyState('6') & 0x8001) ? MK_6 : 0;
		m_KeyState |= (GetAsyncKeyState('7') & 0x8001) ? MK_7 : 0;
		m_KeyState |= (GetAsyncKeyState(VK_LBUTTON) & 8001) ? MK_LCLK : 0;
		m_KeyState |= (GetAsyncKeyState(VK_RBUTTON) & 8001) ? MK_RCLK : 0;
		m_KeyState |= (GetAsyncKeyState('I') & 0x8001) ? MK_I : 0;
		m_KeyState |= (GetAsyncKeyState('T') & 0x8001) ? MK_T : 0;
		m_KeyState |= (GetAsyncKeyState('Y') & 0x8001) ? MK_Y : 0;

	}
};
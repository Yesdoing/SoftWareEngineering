#pragma once;
#include "preCompile.h"
#include "MainFraimWork.h"
#include "GameBoard.h"

HWND				g_hWnd;
HINSTANCE		g_hInstance;

//
void Initialize();
MainFrameWork mainframe;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT){

	Initialize();

	ShowWindow(g_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(g_hWnd);


	//CreateWindow(WINDOW_CLASSNAME, "ee",
	//	WS_POPUPWINDOW | WS_VISIBLE , 0, 0,
	//	800, 600, g_hWnd, NULL, g_hInstance, NULL);

	//SetFocus(g_hWnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		mainframe.Progress();
	}

	mainframe.relesae();

	UnregisterClass(WINDOW_CLASSNAME, g_hInstance);

	return 0;
}

void InitWindow();

void Initialize(){

	InitWindow();
	mainframe.Initialize();

}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hWnd);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void InitWindow(){
	WNDCLASSEX g_wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, WINDOW_CLASSNAME, NULL };
	RegisterClassEx(&g_wc);

	RECT _rect;
	SetRect(&_rect, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	AdjustWindowRect(&_rect, WS_OVERLAPPEDWINDOW, NULL);

	g_hWnd = CreateWindow(WINDOW_CLASSNAME, "MiniStone",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_WIDTH+15, WINDOW_HEIGHT+40, NULL, NULL, g_hInstance, NULL);


}
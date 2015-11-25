#pragma once
#include "preCompile.h"
class CNum
{
private:
	// 이미지 시트
	HDC	mDC;
	HBITMAP	hBitmap;
	BITMAP bit;
	//
	HDC	mDC2;
	HBITMAP	hBitmap2;
	BITMAP bit2;

	int width, height;

	int num[10][2];
	enum {
		posX = 0,
		posY = 1
	};

public:
	void set(){

		// 이미지 시트 세팅
		hBitmap = (HBITMAP)LoadImage(NULL, "./GameUI/Whitenum.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(hBitmap, sizeof(bit), &bit);
		SelectObject(mDC, hBitmap);

		hBitmap2 = (HBITMAP)LoadImage(NULL, "./GameUI/Rednum.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		mDC2 = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(hBitmap2, sizeof(bit2), &bit2);
		SelectObject(mDC2, hBitmap2);

		// 위치 메핑
		width = 40;
		height = 57;


		num[0][posX] = width * 4;
		num[0][posY] = height;


		for (int i = 0; i < 5; i++)
		{
			num[i + 1][posX] = width * i;
			num[i + 1][posY] = 0;
		}

		for (int i = 0; i < 4; i++)
		{
			num[i + 6][posX] = width * i;
			num[i + 6][posY] = height;
		}



	}

	void Whiteprint(const HDC& dc, int x, int y, int inputnum = 1){

		int nX = x, nY = y;

		int arr[2] = { inputnum / 10, inputnum % 10 };


		if (arr[0]) {
			TransparentBlt(dc, nX, nY, width / 3, height / 3, mDC, num[arr[0]][posX], num[arr[0]][posY], width, height, RGB(255, 0, 255));

			nX += width / 4;
		}


		TransparentBlt(dc, nX, nY-1, width / 3, height / 3, mDC, num[arr[1]][posX], num[arr[1]][posY], width, height, RGB(255, 0, 255));



	}

	void Redprint(const HDC& dc, int x, int y, int inputnum = 1){

		int nX = x, nY = y;

		int arr[2] = { inputnum / 10, inputnum % 10 };


		if (arr[0]) {
			TransparentBlt(dc, nX, nY, width, height, mDC2, num[arr[0]][posX], num[arr[0]][posY], width, height, RGB(255, 0, 255));

			nX += width;
		}


		TransparentBlt(dc, nX, nY, width, height, mDC2, num[arr[1]][posX], num[arr[1]][posY], width, height, RGB(255, 0, 255));

		//nX += width;

	}



private:
	static CNum *myInstance;
	CNum();
	~CNum();
public:
	static CNum *getInstance(){
		if (!myInstance)
			myInstance = new CNum;

		return myInstance;
	}

	static void Release(){
		if (myInstance)
			delete myInstance;
		myInstance = NULL;
	}
};


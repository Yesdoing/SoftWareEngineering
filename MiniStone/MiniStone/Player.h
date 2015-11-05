#pragma once
#include "preCompile.h"
#include "InputManager.h"
//#include "ObjectManager.h"
#include "Card.h"
#include "Inventory.h"
#include "ImageDB.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;

class Player
{
private:
		int MaxMana; //최대 마나
		int PMana; //현재 마나
		int MaxLife; // 최대 체력
		int PLife; //현재 체력 
		RECT	Inven[30];


		SImageDB PlayerImg; //플레이어 이미지
		SImageDB FirstDrawImg;
private:
	Card		Cdeck[30];
	char		Cnum[4];
	char		Cname[10];
	int			CAttack;
	int			CLife;
	int			CMana;
	FILE		*f;


public:

	void init(){
		int i = 0;
		f = fopen("card.dat", "rb");
		while (f != NULL){
			fscanf(f, "%s %s %d %d %d", &Cnum, &Cname, CAttack, CLife, CMana);
			Cdeck[i].init(Cnum, Cname, CAttack, CLife, CMana);
			i++;
		}
	}

	void suffle(){
		Card temp;
		int nDust, nSour;
		srand(unsigned int(time(NULL)));

		for (int i = 0; i < 100; i++)
		{
			nDust = rand() % 30 + 1;
			nSour = rand() % 30 + 1;

			temp = Cdeck[nDust];
			Cdeck[nDust] = Cdeck[nSour];
			Cdeck[nSour] = temp;
		}
	}

	void draw(){

	}

//private:
//	int MaxMana; //최대 마나
//	int PMana; //현재 마나
//	int MaxLife; // 최대 체력
//	int PLife; //현재 체력 
//
//	SImageDB PlayerImg; //플레이어 이미지
//	SImageDB FirstDrawImg;
//
//
//	bool flag; //운영체제 플래그 기법? 턴제에 적용할생각
//	CObjectManager	Deck;
//	CObjectManager *Inventory[50];
//
//	int NowCardSelect;
//
//public:
//
//	void init(){
//		NowCardSelect = 0;
//		MaxMana = 10;
//		PMana = 0;
//		MaxLife = 30;
//		PLife = 30;
//		ZeroMemory(Inventory, sizeof(Inventory));
//		flag = false;
//
//		HDC hdc = GetDC(g_hWnd);
//		PlayerImg.hBit = (HBITMAP)LoadImage(NULL, "./Player.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
//		PlayerImg.mDC = CreateCompatibleDC(GetDC(GetFocus()));
//		GetObject(PlayerImg.hBit, sizeof(PlayerImg.Bit), &PlayerImg.Bit);
//		SelectObject(PlayerImg.mDC, PlayerImg.hBit);
//
//		Deck.init();
//	}
//
//	void firstDraw(){
//		HDC hdc = GetDC(g_hWnd);
//		FirstDrawImg.hBit = (HBITMAP)LoadImage(NULL, "./Boardresource/FirstDraw", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
//		FirstDrawImg.mDC = CreateCompatibleDC(GetDC(GetFocus()));
//		GetObject(FirstDrawImg.hBit, sizeof(FirstDrawImg.Bit), &FirstDrawImg.Bit);
//		SelectObject(FirstDrawImg.mDC, FirstDrawImg.hBit);
//
//		
//	}
//
//	int tick = 0;
//	int value = 10;
//	bool flag1 = true;
//	bool flagOnce = true;
//	int max = 1;
//	int min = 50;
//
//	void Draw(HDC& dc){
//		
//		if (++tick > 5) {
//			tick = 0;
//
//			if (flagOnce){
//				if (flag1){
//					if (--value <= max)
//						flag1 = false;
//
//				}
//				else{
//
//
//					if (++value > min){
//						flagOnce = false;
//						flag1 = true;
//					}
//				}
//			}
//		}
//
//
//	}

	Player();
	~Player();
};


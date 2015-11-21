#pragma once
#include "preCompile.h"
#include "InputManager.h"
#include "ImageDB.h"
#include "Num.h"

extern HWND g_hWnd;
extern HINSTANCE		g_hInstance;

enum CState{
	STA_DECK,
	STA_HAND,
	STA_FIELD,
	STA_SLEEP,
	STA_READY,
	STA_ATTACK,
	STA_DEAD,
};

class Card{

protected:
	CState		CardState;
	SImageDB	Fieldimg;
	SImageDB	handimg;
	SImageDB	ExImage;
	SImageDB	Lifeimg;
	SImageDB	Atkimg;
	CType		type;
	char		Cnum[4];
	int			Cindex;
	char		Cname[10];
	int			CAttack;
	int			CLife;
	int			CMana;
	POINT		Position;
	int			CardSize;
	///마우스이동을 위한 변수
	POINT		Prevpos;	//이전 마우스 포인터
	bool		hang;		//마우스에 걸렷는지 검출
	POINT		temp;
	SImageDB	Back_img;


public:
	CState getCardState(){
		return CardState;
	}
	
	bool GetCardHang(){
		return hang;
	}

	int	getCindex(){
		return Cindex-1;
	}

	void SetCardLife(int Damage){
		CLife -= Damage;
	}

	int getCardAttack(){
		return CAttack;
	}

	void SetCardSize(int num)
	{
		CardSize = num;
	}
	void SetCardPosition(int _x, int _y)
	{
		Position.x = _x;
		Position.y = _y;
	}

	RECT getCardRect(){
		return handimg.Source;
	}

	POINT getCardPosition(){
		return Position;
	}
	char* getCardnum()
	{
		return Cnum;
	}

	SImageDB getHandImg()
	{
		return handimg;
	}
	void init(){
		handimg.mDC = 0;
	}

	void init(char* _Cnum, char* _Cname, int _CAtk, int _CLife, int _CMana){
		char pathBuf[_MAX_DIR] = { 0, };

		type = Minion;
		hang = false;
		CardSize = 5;



		strcpy(this->Cnum, _Cnum);
		strcpy(this->Cname, _Cname);
		this->CAttack = _CAtk;
		this->CLife = _CLife;
		this->CMana = _CMana;

		this->Position.x = 800;
		this->Position.y = 300;

		strcat_s(pathBuf, _MAX_DIR, "./CardResouce");
		strcat_s(pathBuf, _MAX_DIR, "/");
		strcat_s(pathBuf, _MAX_DIR, this->Cnum);
		strcat_s(pathBuf, _MAX_DIR, ".bmp");

		HDC hdc = GetDC(g_hWnd);
		handimg.hBit = (HBITMAP)LoadImage(NULL, pathBuf, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		handimg.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(handimg.hBit, sizeof(handimg.Bit), &handimg.Bit);
		SelectObject(handimg.mDC, handimg.hBit);

		ZeroMemory(pathBuf, sizeof(pathBuf));

		strcat_s(pathBuf, _MAX_DIR, "./CardFieldResource");
		strcat_s(pathBuf, _MAX_DIR, "/");
		strcat_s(pathBuf, _MAX_DIR, this->Cnum);
		strcat_s(pathBuf, _MAX_DIR, ".bmp");

		Fieldimg.hBit = (HBITMAP)LoadImage(NULL, pathBuf, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Fieldimg.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(Fieldimg.hBit, sizeof(Fieldimg.Bit), &Fieldimg.Bit);
		SelectObject(Fieldimg.mDC, Fieldimg.hBit);

		this->handimg.Source.left = 0;
		this->handimg.Source.top = 0;
		this->handimg.Source.right = this->handimg.Bit.bmWidth / 5;
		this->handimg.Source.bottom = this->handimg.Bit.bmWidth / 5;

		Lifeimg.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/life.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Lifeimg.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(Lifeimg.hBit, sizeof(Lifeimg.Bit), &Lifeimg.Bit);
		SelectObject(Lifeimg.mDC, Lifeimg.hBit);

		Atkimg.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/atk.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Atkimg.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(Atkimg.hBit, sizeof(Atkimg.Bit), &Atkimg.Bit);
		SelectObject(Atkimg.mDC, Atkimg.hBit);

		Back_img.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/000.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Back_img.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(Back_img.hBit, sizeof(Back_img.Bit), &Back_img.Bit);
		SelectObject(Back_img.mDC, Back_img.hBit);

		Prevpos.x = 0;
		Prevpos.y = 0;

		Cindex = atoi(Cnum);

		ExImage = handimg;
	}

	void Handrender(HDC& dc){
		TransparentBlt(dc, Position.x, Position.y, (100 + handimg.Bit.bmWidth) / CardSize,
			(100 + handimg.Bit.bmHeight) / CardSize,
			handimg.mDC,
			0,
			0,
			handimg.Bit.bmWidth,
			handimg.Bit.bmHeight,
			RGB(255, 0, 255));

//		CardState = STA_HAND;
	}

	void Back_Handrender(HDC& dc){
		TransparentBlt(dc, Position.x, Position.y, (Back_img.Bit.bmWidth) / 2,
			(Back_img.Bit.bmHeight) / 2,
			Back_img.mDC,
			0,
			0,
			Back_img.Bit.bmWidth,
			Back_img.Bit.bmHeight,
			RGB(255, 0, 255));

		//		CardState = STA_HAND;
	}

	void Ex_Handrender(HDC& dc){
		TransparentBlt(dc, Position.x - 30, Position.y - 180, (100 + ExImage.Bit.bmWidth) / CardSize - 2,
			(100 + ExImage.Bit.bmHeight) / CardSize - 2,
			ExImage.mDC,
			0,
			0,
			ExImage.Bit.bmWidth,
			ExImage.Bit.bmHeight,
			RGB(255, 0, 255));
	}

	void Fieldrender(HDC& dc, int x, int y){
		TransparentBlt(dc, x, y, (100 + Fieldimg.Bit.bmWidth) / (CardSize-1),
			(100 + Fieldimg.Bit.bmHeight) / (CardSize-1),
			Fieldimg.mDC,
			0,
			0,
			Fieldimg.Bit.bmWidth,
			Fieldimg.Bit.bmHeight,
			RGB(255, 0, 255));

		TransparentBlt(dc, x-10, y + 67, ( 5 + Atkimg.Bit.bmWidth),
			(5 + Atkimg.Bit.bmHeight),
			Atkimg.mDC,
			0,
			0,
			Atkimg.Bit.bmWidth,
			Atkimg.Bit.bmHeight,
			RGB(255, 0, 255));
	
		CNum::getInstance()->Whiteprint(dc, x+5, y + 80, CAttack);

		TransparentBlt(dc, x + 55, y + 70, (Lifeimg.Bit.bmWidth),
			( Lifeimg.Bit.bmHeight) ,
			Lifeimg.mDC,
			0,
			0,
			Lifeimg.Bit.bmWidth,
			Lifeimg.Bit.bmHeight,
			RGB(255, 0, 255));
		CNum::getInstance()->Whiteprint(dc, x + 60, y + 80, CLife);

		CardState = STA_FIELD;
	}

	void backCard(RECT inven){
		Position.x = inven.left;
		Position.y = inven.top;
	}

	void cardSelectDraw(HDC &dc, POINT pos){
		TransparentBlt(dc, pos.x, pos.y, (100 + handimg.Bit.bmWidth) / CardSize-1,
			(100 + handimg.Bit.bmHeight) / CardSize-1,
			handimg.mDC,
			0,
			0,
			handimg.Bit.bmWidth,
			handimg.Bit.bmHeight,
			RGB(255, 0, 255));
	}
	void cardSelect(POINT pos){

//		RECT temp;
//		temp = inven;
		

		
		Position.x = pos.x;
		Position.y = pos.y;

		handimg.Source.left = Position.x;
		handimg.Source.top = Position.y;
		handimg.Source.right = Position.x + (handimg.Bit.bmWidth / CardSize);
		handimg.Source.bottom = Position.y + (handimg.Bit.bmWidth / CardSize);

//		if (PtInRect(&inven, pos)){
		//	if (_key & MYKEY_FLAG::MK_LCLK){
				//if (!hang) hang = true;
				//else hang = false;

				Prevpos = InputManager::getInstance()->getMousePos();
	//		}
//		}

		
	//	if (hang){
			POINT	moveCard;
			moveCard.x = pos.x - Prevpos.x;
			moveCard.y = pos.y - Prevpos.y;

			Position.x += moveCard.x;
			Position.y += moveCard.y;
	//	}
		
		//if (_key & MYKEY_FLAG::MK_RCLK){
		//	Position.x = temp.left;
		//	Position.y = temp.top;
		//	handimg.Source = temp;
		//	hang = false;
		//}


		Prevpos = pos;
	}

	void CheckDeathCard(){
		if (CLife < 1){
			CardState = STA_DEAD;
			Fieldrelease();
		}
	}

	void Fieldrelease(){
				DeleteObject(Fieldimg.hBit);      
				DeleteDC(Fieldimg.mDC);    	
			}

	void HandRelease(){
		DeleteObject(handimg.hBit);
		DeleteDC(handimg.mDC);
		DeleteObject(Back_img.hBit);
		DeleteDC(Back_img.mDC);
		handimg.mDC = 0;
	}

	Card();
	~Card();
};
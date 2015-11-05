//#pragma once
//#include "preCompile.h"
//#include "InputManager.h"
//
//extern HWND g_hWnd;
//extern HINSTANCE		g_hInstance;
//
//class Card
//{
//protected:
//	enum CType{
//		Minion,
//		Spell,
//		Weapon,
//	};
//
//	struct SImageDB{
//		HDC	mDC;
//		HBITMAP hBit; //앞면 이미지
//		HBITMAP BackBit; // 뒷면이미지
//		BITMAP Bit; //이미지 정보
//		RECT Source;
//		const char *str;
//	};
//
//
//	struct SCard{
//
//		CType cardtype;
//		SImageDB imgDB;
//		char Cnum[4];
//		char Cname[20];
//		int CAttack;
//		int CLife;
//		int CMana;
//
//		RECT cardRect;
//		POINT Position;
//	};
//
//	SCard CardObject[30];
//	FILE *f;
//	bool hang;
//	POINT CapPos;
//
//public :
//	void SetCardPosition(int _x, int _y, int k){
//		CardObject[k].Position.x = _x;
//		CardObject[k].Position.y = _y;
//	}
//};
//
//class CObjectManager : private Card
//{
//private:
//
//public:
//	void init(){
//		SCard temp[30];
//		int i = 0;
//		int j = 0;
//		char pathBuf[_MAX_DIR] = { 0, };
//
//		f = fopen("card.dat", "rb");
//		while(f != NULL){
//			fscanf(f, "%s %s %d %d %d", &temp[i].Cnum, &temp[i].Cname, &temp[i].CAttack, &temp[i].CLife, &temp[i].CMana);
//			i++;
//		}
//		
//		for (int i = 0; i < 30; i++){
//			CardObject[i] = temp[i];
//
//			CardObject[i].Position.x = 800;
//			CardObject[i].Position.y = 300;
//
//			strcat_s(pathBuf, _MAX_DIR, "./CardResouce");
//			strcat_s(pathBuf, _MAX_DIR, "/");
//			strcat_s(pathBuf, _MAX_DIR, CardObject[i].Cnum);
//			strcat_s(pathBuf, _MAX_DIR, ".bmp");
//
//			HDC hdc = GetDC(g_hWnd);
//			CardObject[i].imgDB.hBit = (HBITMAP)LoadImage(NULL, pathBuf, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
//			CardObject[i].imgDB.mDC = CreateCompatibleDC(GetDC(GetFocus()));
//			GetObject(CardObject[i].imgDB.hBit, sizeof(CardObject[i].imgDB.Bit), &CardObject[i].imgDB.Bit);
//			SelectObject(CardObject[i].imgDB.mDC, CardObject[i].imgDB.hBit);
//
//
//			CardObject[i].cardRect.left = CardObject[i].Position.x;
//			CardObject[i].cardRect.top = CardObject[i].Position.y;
//			CardObject[i].cardRect.right = CardObject[i].Position.y + (CardObject[i].imgDB.Bit.bmWidth / 5);
//			CardObject[i].cardRect.bottom = CardObject[i].Position.x + (CardObject[i].imgDB.Bit.bmWidth / 5);
//		}
//
//
//
//		hang = false;
//
//		fclose(f);
//	}
//
//	void render(HDC& dc, int Cardnum, int Size){
//		TransparentBlt(dc, CardObject[Cardnum].Position.x, CardObject[Cardnum].Position.y,
//			(100 + CardObject[Cardnum].imgDB.Bit.bmWidth) / Size,
//			(100 + CardObject[Cardnum].imgDB.Bit.bmHeight) / Size,
//			CardObject[Cardnum].imgDB.mDC,
//			0, 
//			0, 
//			CardObject[Cardnum].imgDB.Bit.bmWidth,
//			CardObject[Cardnum].imgDB.Bit.bmHeight,
//			RGB(255, 128, 128));
//	}
//
//	void move(){
//
//		DWORD key = InputManager::getInstance()->getKeyState();
//		//마우스 좌표 출력
//
//		CardObject.cardRect.left = CardObject.Position.x;
//		CardObject.cardRect.top = CardObject.Position.y;
//		CardObject.cardRect.right = CardObject.Position.x + (CardObject.imgDB.Bit.bmWidth / 5);
//		CardObject.cardRect.bottom = CardObject.Position.y + (CardObject.imgDB.Bit.bmHeight / 5);
//
//		POINT pt = InputManager::getInstance()->getMousePos();
//
//		if (PtInRect(&CardObject.cardRect, pt)){
//			//PtInRect = 점과 사각형의 충돌을 검출하는 함수
//
//			if (key & MYKEY_FLAG::MK_LCLK){
//				if (!hang) hang = true;
//				else hang = false;
//				CapPos = InputManager::getInstance()->getMousePos();
//			}
//		}
//
//
//		if (hang)
//		{
//			POINT moveCard;
//
//			moveCard.x = pt.x - CapPos.x;
//			moveCard.y = pt.y - CapPos.y;
//
//			CardObject.Position.x += moveCard.x;
//			CardObject.Position.y += moveCard.y;
//		}
//
//		CapPos = pt;
//	}
//
//	void Death(){
//		if (CardObject.CLife = 0)
//			release();
//	}
//	
//	void release(){
//		DeleteObject(CardObject.imgDB.hBit);              ///////////////
//		DeleteDC(CardObject.imgDB.mDC);                   ///////////////
//
//	}
//
//	CObjectManager();
//	~CObjectManager();
//};
//
//typedef std::vector <CObjectManager*> CObjVector;
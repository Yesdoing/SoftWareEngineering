#pragma once
#include "preCompile.h"
#include "InputManager.h"
//#include "ObjectManager.h"
#include "Card.h"
#include "ImageDB.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;

#define DECKMAX 30
#define CARDMAX 30

class Player
{
private:
		int MaxMana; //�ִ� ����
		int PMana; //���� ����
		int MaxLife; // �ִ� ü��
		int PLife; //���� ü�� 
		int Handnum; //���ڵ� ��
		int Drawnum; //��ο� ��
		RECT	Inven[30];
		SImageDB PlayerImg; //�÷��̾� �̹���
		SImageDB FirstDrawImg;
		Card ExDrawImg;
		

		int		Cfield[8];
		RECT	Field[8];

		//////////////////////// �� �÷��̾ ���� ����
		
	//	RECT	EnemyCfield[8];
	//	int		EnemyCard[8];
		int		EnemyHandCount;

		/////////////////////////

		bool hang;
		DWORD tick;
		DWORD now;
		DWORD value;
		bool flag1;
		bool flagOnce;
		int max;
		int min;

		SImageDB	TurnButtonON;
		SImageDB	TurnButtonOFF;
		SImageDB	myTurnimg;
		POINT		ButtonPos;

private:
	Card		CHand[30];
	Card		Cdeck[30];
	char		Cnum[4];
	char		Cname[10];
	int			CAttack;
	int			CLife;
	int			CMana;
	FILE		*f;
	int			hangnum;
	int			FSelect;
	static bool		Myturn;
	static bool		E_turn;


public:
	Player();
	~Player();

	void init(){
		int i = 0;
		f = fopen("card.dat", "rb");
		while (fscanf(f, "%s %s %d %d %d", &Cnum, &Cname, &CAttack, &CLife, &CMana) != EOF){
			Cdeck[i].init(Cnum, Cname, CAttack, CLife, CMana);
			i++;
		}

		for (int z = 0; z < 8; z++){
			Cfield[z] = -1;
		//	EnemyCfield[z] = -1;
		}

		FSelect = 0;
		MaxMana = 10;
		PMana = 0;
		MaxLife = 30;
		PLife = MaxMana;

		for (int i = 0; i < 30; i++){
			CHand[i].init();

			Inven[i].left = 70 + (20*i);
			Inven[i].top = 690;
			Inven[i].right = 90 + (20*i);
			Inven[i].bottom = 765;
		}

		for (int i = 0; i < 8; i++){
			Field[i].left = 130 + (91 * i);
			Field[i].top = 370;
			Field[i].right = 221 + (91 * i);
			Field[i].bottom = 480;
		}

		Handnum = 0;
		Drawnum = 0;

		tick = GetTickCount();
		value = 2 * 1000;
		flag1 = true;
		flagOnce = true;
		max = 1;
		min = 50;
		hang = false;
		hangnum = -1;

		Myturn = true;

		HDC hdc = GetDC(g_hWnd);
		TurnButtonON.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/myturn2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		TurnButtonON.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(TurnButtonON.hBit, sizeof(TurnButtonON.Bit), &TurnButtonON.Bit);
		SelectObject(TurnButtonON.mDC, TurnButtonON.hBit);

		ButtonPos.x = 857;
		ButtonPos.y = 297;

		TurnButtonON.Source.left = ButtonPos.x;
		TurnButtonON.Source.top = ButtonPos.y;
		TurnButtonON.Source.bottom = ButtonPos.y + 100;
		TurnButtonON.Source.right = ButtonPos.x + 156;

		TurnButtonOFF.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/yourturn.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		TurnButtonOFF.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(TurnButtonOFF.hBit, sizeof(TurnButtonOFF.Bit), &TurnButtonOFF.Bit);
		SelectObject(TurnButtonOFF.mDC, TurnButtonOFF.hBit);

		TurnButtonOFF.Source.left = ButtonPos.x;
		TurnButtonOFF.Source.top = ButtonPos.y;
		TurnButtonOFF.Source.bottom = ButtonPos.y + 100;
		TurnButtonOFF.Source.right = ButtonPos.x + 156;

		myTurnimg.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/turn.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		myTurnimg.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(myTurnimg.hBit, sizeof(myTurnimg.Bit), &myTurnimg.Bit);
		SelectObject(myTurnimg.mDC, myTurnimg.hBit);



		// ī�� �ޱ� 
	

		
	

	}

	void startDeck(int firstcarddeck){
	
		Drawnum = -1;
		int tarr[CARDMAX] = { 0 };
		int temp = rand() % CARDMAX;
		for (int i = 0; i < firstcarddeck; ++i){

			while (tarr[temp])
				temp = rand() % CARDMAX;

			tarr[temp] = 1;

			Drawnum++;
			CHand[Drawnum] = Cdeck[temp];
			
		}

		return;
	}

	void getOneCard(){

		int temp = rand() % CARDMAX;

		for (int i = 0; i <= Drawnum; ++i){

			if (CHand[i].getCindex() == temp){
			
				i = 0;
				temp = rand() % CARDMAX;
				continue;
			}
	
			
		}
	
		CHand[++Drawnum] = Cdeck[temp];
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




	bool firstDraw = true;
	DWORD _tick1, _now1;


	void draw(HDC& dc){

		if (firstDraw){
			firstDraw = false;
			for (int i = 0; i <= Drawnum; ++i)
				CHand[i].SetCardPosition(Inven[i].left, Inven[i].top);
		}

		if (Myturn && turnStart){
			turnStart = false;
			getOneCard();

			CHand[Drawnum].SetCardPosition(Inven[Drawnum].left, Inven[Drawnum].top);

			ExDrawImg = Cdeck[Drawnum];
			ExDrawImg.SetCardPosition(850, 413);
			ExDrawImg.SetCardSize(3);


			_tick1 = GetTickCount();
		}


		//CHand[Drawnum] = Cdeck[Drawnum];
	//	CHand[Drawnum].SetCardPosition(Inven[Drawnum].left, Inven[Drawnum].top);
	
		////////////////// ī�� �̸����� 
		_now1 = GetTickCount();
		if (_now1 - _tick1 < value)
		{
			ExDrawImg.Handrender(dc);
		}

	
		for(int k=0; k<= Drawnum; k++) 
			CHand[k].Handrender(dc);
		
	
		if (hangnum > -1){
			POINT pos = InputManager::getInstance()->getMousePos();
			if (CHand[hangnum].getHandImg().mDC != NULL)
			CHand[hangnum].cardSelectDraw(dc, pos);
		}

		turnButton(dc);

		renderfield(dc);
	}




	void ExImage(HDC& dc){
		POINT pos = InputManager::getInstance()->getMousePos();
		DWORD key = InputManager::getInstance()->getKeyState();
		for (int i = 0; i < Drawnum; i++){
			if (PtInRect(&Inven[i], pos)){
				CHand[i].Ex_Handrender(dc);
			}
		}
	}

	void DamagePlayer(int damage){
		PLife -= damage;
	}

	void update(POINT pos){
		DWORD key = InputManager::getInstance()->getKeyState();
		if (Myturn){
			if (key & MYKEY_FLAG::MK_LCLK){
				RECT rc;
				SetRect(&rc, Inven[0].left, Inven[0].top, Inven[29].right, Inven[0].bottom);

				if (PtInRect(&rc, pos))
				{
					hangnum = (pos.x - 70) / 20;
				}
				else if(hangnum != -1){
					addMyfield(CHand[hangnum].getCindex());
					hangnum = -1;
				}
			}
			else if (key & MYKEY_FLAG::MK_RCLK)
			{
				hangnum = -1;
			}
			TurnFlag(pos);
		}
	}

	void addMyfield(int _index){
		for (int i = 0; i < 8; i++){
			if (-1 == Cfield[i] ) {
				Cfield[i] = _index;
				break;
			}
		}
	}

	void turnButton(HDC& dc){
		if (Myturn)
		{

			now = GetTickCount();
			if ((now - tick) > value)
			{
				flag1 = false;
				tick = now;
			}

			if (flag1)
			{
				TransparentBlt(dc, 200, 200, (myTurnimg.Bit.bmWidth),
					(myTurnimg.Bit.bmHeight),
					myTurnimg.mDC,
					0,
					0,
					myTurnimg.Bit.bmWidth,
					myTurnimg.Bit.bmHeight,
					RGB(255, 0, 255));
			}

			TransparentBlt(dc, ButtonPos.x, ButtonPos.y, (TurnButtonON.Bit.bmWidth),
				(TurnButtonON.Bit.bmHeight),
				TurnButtonON.mDC,
				0,
				0,
				TurnButtonON.Bit.bmWidth,
				TurnButtonON.Bit.bmHeight,
				RGB(255, 0, 255));
		}

		else
		{
			TransparentBlt(dc, 875, 318, (TurnButtonOFF.Bit.bmWidth),
				(TurnButtonOFF.Bit.bmHeight),
				TurnButtonOFF.mDC,
				0,
				0,
				TurnButtonOFF.Bit.bmWidth,
				TurnButtonOFF.Bit.bmHeight,
				RGB(255, 0, 255));
		}

	}


	void changeTurn(){
		for (int i = 0; i < 29; i++){
			if (CHand[i].getHandImg().mDC == NULL)
			{
				for (int j = i + 1; j < 30; j++)
				{
					if (CHand[j].getHandImg().mDC != NULL)
					{
						CHand[i] = CHand[j];
						break;
					}
				}
			}
		}




		Myturn = !Myturn;
		turnStart = true;
	}

	void TurnFlag(POINT pos){
		DWORD key = InputManager::getInstance()->getKeyState();
		if (Myturn){
			if (key & MYKEY_FLAG::MK_LCLK)
			{
				if (PtInRect(&TurnButtonON.Source, pos))
					changeTurn();
			}
		}
		else {
			
		}
	}

	//////////////////////////////////////////////////////////
	//Enemy��


	bool efirstDraw = true;
	bool turnStart = true;

	void E_draw(HDC& dc){
		/*
		ī�尡 ������ �ڵ�� ������ ����. �÷��̾��� ���ݴ� ��ġ�� ī���̹����� �޸��� ��µǾ��Ѵ�.
		�ϴ� 3������ø��� for������ ������
		�ö� ���°��� Ȯ���� �Ŀ� ����üũ ����
		*/

		if (E_turn){
			changeTurn();
			E_turn = false;
		}

		if (efirstDraw){
			efirstDraw = false;

			
			CMana = 0;
			for (int i = 0; i <= Drawnum; ++i)
				CHand[i].SetCardPosition(Inven[i].left, 20);

		}

		if (turnStart){
			turnStart = false;
			getOneCard();
			
			if( ++CMana > 10 )
				CMana = 10;

			CHand[Drawnum].SetCardPosition(Inven[Drawnum].left, 20);

		}
			
		for (int k = 0; k <= Drawnum; k++)
			CHand[k].Back_Handrender(dc);

		for (int i = 0; i < 8 && Cfield[i] > -1; i++)
			Cdeck[Cfield[i]].Fieldrender(dc, Field[i].left, Field[i].top-150);
	}



	
	DWORD E_Tick = 0;
	bool  E_trunStart = false;
	void E_update(){
		if (Myturn)
			return ;

		if (!E_trunStart && E_turn == false){
			E_trunStart = true;

			E_Tick = GetTickCount();
		}


		if (GetTickCount() - E_Tick > 2000){

			E_Tick = GetTickCount();

			int mana = E_SelectCard();
			E_trunStart = false;
		
			CMana -= mana;


			if (0==CMana){ // ���� üũ 
				// ���� �� ������

				E_turn = true; // �� ����
			}


		}
		
	}

	int E_SelectCard(){
		int temp = rand() % Drawnum;
		for (int i = 0; i < 8; i++){
			if (CHand[temp].getCindex() == Cfield[i]){
				temp = rand() % Drawnum;
				i = -1;
				continue;
			}
		}

		addMyfield(CHand[temp].getCindex());
		Drawnum--;
		CHand[temp].HandRelease();
		return 1; // getMAna\ �߰� �ʿ�
	}

	void E_SetTarget(){
	}

	void renderfield(HDC& dc){
		for (int i = 0; i < 8 && Cfield[i] > -1 ; i++)
			Cdeck[Cfield[i]].Fieldrender(dc, Field[i].left, Field[i].top);
	
	}


	void FieldAttack(){

	}
};



/*
���� ó���� �ϰ�
�Ȱ����� �ȳ����� ����ó��
��������

*/
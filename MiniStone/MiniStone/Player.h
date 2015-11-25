#pragma once
#include "preCompile.h"
#include "InputManager.h"
#include "Card.h"
#include "ImageDB.h"
#include "Network.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern pass	E_recv;
extern bool		Myturn;
extern bool		E_turn;

#define DECKMAX 30
#define CARDMAX 30

class Player
{
private:
		int MaxMana; //최대 마나
		int PMana; //현재 마나
		int MaxLife; // 최대 체력
		int PLife; //현재 체력 
		int Handnum; //내핸드 수
		int Drawnum; //드로우 수

		static int		atk_index;
		static int		dmg_index;
		static int		atk_num;


		RECT	Inven[30];
		SImageDB FirstDrawImg;
		Card ExDrawImg;
		

		int		Cfield[8];
		RECT	Field[8];
		RECT	E_Field[8];

		Player* other;

		//////////////////////// 적 플레이어에 대한 정보
		
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
		int temp;

		SImageDB	AtkPointer1;
		SImageDB	AtkPointer2;
		SImageDB	TurnButtonON;
		SImageDB	TurnButtonOFF;
		SImageDB	myTurnimg;
		POINT		ButtonPos;
		SImageDB	Lifeimg;
		SImageDB	Manaimg;
		SImageDB	AttackEffet;

		Card		CHand[30];
		Card		Cdeck[30];
		struct pass	P_pass;

private:
	char		Cnum[4];
	char		Cname[10];
	int			CAttack;
	int			CLife;
	int			CMana;
	FILE		*f;
	int			hangnum;
	int			FSelect;


	RECT		PlayerRect;
	RECT		EnemyRect;
	bool firstDraw;
	bool efirstDraw;
	DWORD _tick1, _now1;

	bool turnStart;
	bool arrowflag;
	int atkparamater1, atkparamater2;
	int plusnum;
	int k;
	DWORD E_Tick;
	DWORD shortTick;
	bool  E_trunStart;

public:
	Player();
	~Player();




	void setTheOther(Player* _other){

		 
		other = _other;
	

	}

	void init(){
		int i = 0;
		temp = -1;
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
		MaxMana = 1;
		PMana = 0;
		MaxLife = 30;
		PLife = MaxLife;

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

			E_Field[i].left = 130 + (91 * i);
			E_Field[i].top = 220;
			E_Field[i].right = 221 + (91 * i);
			E_Field[i].bottom = 330;
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

		Myturn = false;

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

		AtkPointer1.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/arrow1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		AtkPointer1.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(AtkPointer1.hBit, sizeof(AtkPointer1.Bit), &AtkPointer1.Bit);
		SelectObject(AtkPointer1.mDC, AtkPointer1.hBit);


		AtkPointer2.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/arrow2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		AtkPointer2.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(AtkPointer2.hBit, sizeof(AtkPointer2.Bit), &AtkPointer2.Bit);
		SelectObject(AtkPointer2.mDC, AtkPointer2.hBit);

		Lifeimg.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/life.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Lifeimg.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(Lifeimg.hBit, sizeof(Lifeimg.Bit), &Lifeimg.Bit);
		SelectObject(Lifeimg.mDC, Lifeimg.hBit);

		Manaimg.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/kristal.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Manaimg.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(Manaimg.hBit, sizeof(Manaimg.Bit), &Manaimg.Bit);
		SelectObject(Manaimg.mDC, Manaimg.hBit);

		AttackEffet.hBit = (HBITMAP)LoadImage(NULL, "./GameUI/damage.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		AttackEffet.mDC = CreateCompatibleDC(GetDC(GetFocus()));
		GetObject(AttackEffet.hBit, sizeof(AttackEffet.Bit), &AttackEffet.Bit);
		SelectObject(AttackEffet.mDC, AttackEffet.hBit);


		EnemyRect.left = 475;
		EnemyRect.top = 119;
		EnemyRect.right = 549;
		EnemyRect.bottom = 183;

		PlayerRect.left = 478;
		PlayerRect.top = 552;
		PlayerRect.right = 554;
		PlayerRect.bottom = 629;

		for (int i = 0; i < 8; i++){
			P_pass.Cfield[i] = -1;
			E_recv.Cfield[i] = -1;
			
			for (int j = 0; j < 2; j++){
				P_pass.Attackflag[i][j] = -1;
				E_recv.Attackflag[i][j] = -1;
			}
		}

		P_pass.E_Hand = -1;
		E_recv.E_Hand = -1;
		P_pass.cTurn = false;
		E_recv.cTurn = false;

		firstDraw = true;
		efirstDraw = true;
		_tick1, _now1;

		turnStart = true;
		arrowflag = false;
		atkparamater1 = -1, atkparamater2 = -1;
		plusnum = 0;
		k = 0;
		E_Tick = 0;
		shortTick = 0;
		E_trunStart = false;
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
		srand((unsigned)time(NULL));
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







	void draw(HDC& dc){

		if (firstDraw){
			firstDraw = false;
			for (int i = 0; i <= Drawnum; ++i)
				CHand[i].SetCardPosition(Inven[i].left, Inven[i].top);
		}

		if (Myturn && turnStart){
			PMana = MaxMana;
			turnStart = false;
			getOneCard();

			CHand[Drawnum].SetCardPosition(Inven[Drawnum].left, Inven[Drawnum].top);

			ExDrawImg = CHand[Drawnum];
			ExDrawImg.SetCardPosition(850, 413);
			ExDrawImg.SetCardSize(3);


			_tick1 = GetTickCount();
		}
	
		////////////////// 카드 미리보기 
		_now1 = GetTickCount();
		if (_now1 - _tick1 < value)
		{
			TransparentBlt(dc, 260, 260, (myTurnimg.Bit.bmWidth),
				(myTurnimg.Bit.bmHeight),
				myTurnimg.mDC,
				0,
				0,
				myTurnimg.Bit.bmWidth,
				myTurnimg.Bit.bmHeight,
				RGB(255, 0, 255));
			ExDrawImg.Handrender(dc);
		}

	
		for(int k=0; k<= Drawnum; k++) 
			CHand[k].Handrender(dc);
		
	
		if (hangnum > -1){
			POINT pos = InputManager::getInstance()->getMousePos();
			if (CHand[hangnum].getHandImg().mDC != NULL)
			CHand[hangnum].cardSelectDraw(dc, pos);
		}



		renderfield(dc);
		turnButton(dc);

		arrowRender(dc);

		if (atkparamater1 != -1 && atkparamater2 != -1){
			attackreder(dc, atkparamater1, atkparamater2);

			if (Cdeck[atkparamater1].atkMoveFlag == 0)
			{
				atkparamater1 = -1;
				atkparamater2 = -1;
			}
		}

	}




	void ExImage(HDC& dc){
		POINT pos = InputManager::getInstance()->getMousePos();
		DWORD key = InputManager::getInstance()->getKeyState();
		for (int i = 0; i <= Drawnum; i++){
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
		FieldAttack();
		if (Myturn){
			if (key & MYKEY_FLAG::MK_LCLK){
				RECT rc;
				SetRect(&rc, Inven[0].left, Inven[0].top, Inven[29].right, Inven[0].bottom);

				if (PtInRect(&rc, pos))
				{
					hangnum = (pos.x - 70) / 20;
				}
				else if ((hangnum != -1) && (CHand[hangnum].CMana <= PMana)){
					if (CHand[hangnum].getHandImg().mDC != 0)
						addMyfield(CHand[hangnum].getCindex());
					CHand[hangnum].HandRelease();
					PMana -= CHand[hangnum].CMana;
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

		for (int i = 0; i < 8; i++){
			if (Cfield[i] > -1)
				Cdeck[Cfield[i]].atkflag = true;

			P_pass.Cfield[i] = Cfield[i];
		}

		if (++MaxMana > 10)
			MaxMana = 10;

		P_pass.E_Hand = Drawnum;
		P_pass.cTurn = false;

		Myturn = !Myturn;
		turnStart = true;
		flag1 = true;
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
	//Enemy용




	void E_draw(HDC& dc){
		if (efirstDraw){
			efirstDraw = false;
			for (int i = 0; i <= Drawnum; ++i)
				CHand[i].SetCardPosition(Inven[i].left, 0);
		}

		if (E_turn){
			changeTurn();
			E_turn = false;
		}



		if (turnStart){
			PMana = MaxMana;
			turnStart = false;
			getOneCard();
			

			CHand[Drawnum].SetCardPosition(Inven[Drawnum].left, 0);

	//		attackreder(dc);


		}
			
		for (int k = 0; k <= Drawnum; k++)
			CHand[k].Back_Handrender(dc);

	


		for (int i = 0; i < 8; i++)
		{
			if (Cfield[i] > -1)
				Cdeck[Cfield[i]].Fieldrender(dc, E_Field[i].left, E_Field[i].top);
		}

		if (atkparamater1 != -1 && atkparamater2 != -1){
			attackreder(dc, atkparamater1, atkparamater2);

			if (Cdeck[atkparamater1].atkMoveFlag == 0)
			{
				atkparamater1 = -1;
				atkparamater2 = -1;
			}
		}


		
	}



	void E_update(){
		if (Myturn)
			return ;

		if ((!E_trunStart) && (E_turn == false)){
			E_trunStart = true;

			E_Tick = GetTickCount();
			shortTick = GetTickCount();
		}


		if (GetTickCount() - E_Tick > 5000){
			E_Tick = GetTickCount();

			int mana = E_SelectCard();
			E_trunStart = false;
			PMana -= mana;

			E_turn = true; // 턴 종료
			k = 0;

		}
		else {
			if (GetTickCount() - shortTick > 500){
				if (Cfield[k] > -1){
					shortTick = GetTickCount();
					Cdeck[Cfield[k]].SetMoveFlag(1, PlayerRect.left, PlayerRect.top, 5, NULL);
					other->PLife -= Cdeck[Cfield[k]].getCardAttack();

					atkparamater1 = Cfield[k];
					atkparamater2 = 8;

					if (k++ > 7) k = 7;
					shortTick = GetTickCount();
				}
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
		if (CHand[temp].CMana <= PMana){
			addMyfield(CHand[temp].getCindex());
			Drawnum--;
			CHand[temp].HandRelease();
			return CHand[temp].CMana; // getMAna\ 추가 필요
		}
		else return 0;
	}


	void renderfield(HDC& dc){
		for (int i = 0; i < 8; i++)
		{
			if (Cfield[i] > -1)
				Cdeck[Cfield[i]].Fieldrender(dc, Field[i].left, Field[i].top);
		}
	}


	void FieldAttack(){
		if (!Myturn || hangnum != -1)
			return;

		
			DWORD key = InputManager::getInstance()->getKeyState();
			POINT pos = InputManager::getInstance()->getMousePos();

			RECT remp;
			if (key & MYKEY_FLAG::MK_LCLK)
			{
				int index = (pos.x - 130) / 91;

				if (PtInRect(&Field[index], pos))
				{
					if (Cfield[index] > -1){
						if (Cdeck[Cfield[index]].atkflag)
							arrowflag = !arrowflag;

						temp = index;
					}
					
				}


				if (arrowflag)
				{
					AtkPointer1.Source.left = pos.x;
					AtkPointer1.Source.top = pos.y;
					AtkPointer1.Source.right = pos.x + 108;
					AtkPointer1.Source.bottom = pos.y + 107;
					if (other->Cfield[index] > -1)
					{
						if (IntersectRect(&remp, &AtkPointer1.Source, &E_Field[index]))
						{
							// 1이면 공격
							Cdeck[Cfield[temp]].SetMoveFlag(1, E_Field[index].left, E_Field[index].top, 5, NULL);

							atk_index = temp;
							dmg_index = index;
							atk_num = Cdeck[Cfield[temp]].getCardAttack();
							arrowflag = false;


							other->Cdeck[other->Cfield[index]].CLife -= Cdeck[Cfield[temp]].getCardAttack();
							other->Cfield[index] = other->Cdeck[other->Cfield[index]].CheckDeathCard(other->Cfield[index]);

							Cdeck[Cfield[temp]].CLife -= other->Cdeck[other->Cfield[index]].getCardAttack();
							Cfield[temp] = Cdeck[Cfield[temp]].CheckDeathCard(Cfield[temp]);

							atkparamater1 = Cfield[temp];
							atkparamater2 = other->Cfield[index];

							P_pass.Attackflag[plusnum][0] = temp;
							P_pass.Attackflag[plusnum][1] = index;
							if (plusnum++ > 8) plusnum = 7;
						}
					}
						if (IntersectRect(&remp, &AtkPointer1.Source, &EnemyRect))
						{
							Cdeck[Cfield[temp]].SetMoveFlag(1, EnemyRect.left, EnemyRect.top, 5, NULL);
							other->PLife -= Cdeck[Cfield[temp]].getCardAttack();

							atkparamater1 = Cfield[temp];
							atkparamater2 = 9;

							P_pass.Attackflag[plusnum][0] = temp;
							P_pass.Attackflag[plusnum][1] = 8;
							if (plusnum++ > 8) plusnum = 7;

							arrowflag = false;
						}
				}
			}
			else if (key & MYKEY_FLAG::MK_RCLK){
				arrowflag = false;
			}
		
	}

	void arrowRender(HDC& dc){
		POINT pos = InputManager::getInstance()->getMousePos();
		if (arrowflag)
		{
			AtkPointer1.Source.left = pos.x;
			AtkPointer1.Source.top = pos.y;
			AtkPointer1.Source.right = pos.x + 108;
			AtkPointer1.Source.bottom = pos.y + 107;

			TransparentBlt(dc, pos.x-50, pos.y-50, (AtkPointer1.Bit.bmWidth),
			(AtkPointer1.Bit.bmHeight),
			AtkPointer1.mDC,
			0,
			0,
			AtkPointer1.Bit.bmWidth,
			AtkPointer1.Bit.bmHeight,
			RGB(255, 0, 255));
		}
	}

	void ManaRender(HDC& dc){
		CNum::getInstance()->Whiteprint(dc, 700, 704, PMana);
		CNum::getInstance()->Whiteprint(dc, 735, 704, MaxMana);
		for (int i = 0; i < PMana; i++)
		{
			TransparentBlt(dc, 763 + (i * 23), 699, (Manaimg.Bit.bmWidth),
				(Manaimg.Bit.bmHeight),
				Manaimg.mDC,
				0,
				0,
				Manaimg.Bit.bmWidth,
				Manaimg.Bit.bmHeight,
				RGB(255, 0, 255));
		}

		TransparentBlt(dc, PlayerRect.right, PlayerRect.bottom, (Lifeimg.Bit.bmWidth),
			(Lifeimg.Bit.bmHeight),
			Lifeimg.mDC,
			0,
			0,
			Lifeimg.Bit.bmWidth,
			Lifeimg.Bit.bmHeight,
			RGB(255, 0, 255));
		CNum::getInstance()->Whiteprint(dc, PlayerRect.right, PlayerRect.bottom+10, PLife);
	}

	void E_ManaRender(HDC& dc){
		CNum::getInstance()->Whiteprint(dc, 678, 40, PMana);
		CNum::getInstance()->Whiteprint(dc, 705, 40, MaxMana);

		TransparentBlt(dc, EnemyRect.right, EnemyRect.bottom, (Lifeimg.Bit.bmWidth),
			(Lifeimg.Bit.bmHeight),
			Lifeimg.mDC,
			0,
			0,
			Lifeimg.Bit.bmWidth,
			Lifeimg.Bit.bmHeight,
			RGB(255, 0, 255));
		CNum::getInstance()->Whiteprint(dc, EnemyRect.right, EnemyRect.bottom+10, PLife);
	}

	void attackreder(HDC& dc, int _index, int E_index){
		if (_index == 8 || E_index == 8){
			TransparentBlt(dc, PlayerRect.left + 10, PlayerRect.top + 10, (AttackEffet.Bit.bmWidth),
				(AttackEffet.Bit.bmHeight),
				AttackEffet.mDC,
				0,
				0,
				AttackEffet.Bit.bmWidth,
				AttackEffet.Bit.bmHeight,
				RGB(255, 0, 255));

			CNum::getInstance()->Redprint(dc, PlayerRect.left+60, PlayerRect.top + 50, Cdeck[_index].getCardAttack());
		}
		else if (E_index == 9){
			TransparentBlt(dc, EnemyRect.left + 10, EnemyRect.top + 10, (AttackEffet.Bit.bmWidth),
				(AttackEffet.Bit.bmHeight),
				AttackEffet.mDC,
				0,
				0,
				AttackEffet.Bit.bmWidth,
				AttackEffet.Bit.bmHeight,
				RGB(255, 0, 255));

			CNum::getInstance()->Redprint(dc, EnemyRect.left + 60, EnemyRect.top + 50, Cdeck[_index].getCardAttack());
		}
		else
		{
			TransparentBlt(dc, Cdeck[_index].getCardPosition().x + 10, Cdeck[_index].getCardPosition().y + 10, (AttackEffet.Bit.bmWidth),
				(AttackEffet.Bit.bmHeight),
				AttackEffet.mDC,
				0,
				0,
				AttackEffet.Bit.bmWidth,
				AttackEffet.Bit.bmHeight,
				RGB(255, 0, 255));

			CNum::getInstance()->Redprint(dc, Cdeck[_index].getCardPosition().x+60, Cdeck[_index].getCardPosition().y + 50, other->Cdeck[E_index].getCardAttack());


			TransparentBlt(dc, other->Cdeck[E_index].getCardPosition().x + 10, other->Cdeck[E_index].getCardPosition().y + 10, (AttackEffet.Bit.bmWidth),
				(AttackEffet.Bit.bmHeight),
				AttackEffet.mDC,
				0,
				0,
				AttackEffet.Bit.bmWidth,
				AttackEffet.Bit.bmHeight,
				RGB(255, 0, 255));

			CNum::getInstance()->Redprint(dc, other->Cdeck[E_index].getCardPosition().x+60, other->Cdeck[E_index].getCardPosition().y + 50, Cdeck[_index].getCardAttack());
		}
	}
	
	

	/*
	void attackEffectRender(){
		어택플래그 2일때 뜨도록 하고 적에 대한 처리는 other가져와서하는걸로...
	}
	*/

	int checkVictory(){
		if (PLife <= 0){
			other->efirstDraw = true;
			firstDraw = true;
			return -1;
		}
		else if (other->PLife <= 0){
			other->efirstDraw = true;
			firstDraw = true;
			return -1;
		}
		else return 1;
	}

	void N_draw(HDC& dc){
		if (efirstDraw){
			efirstDraw = false;
			for (int i = 0; i <= Drawnum; ++i)
				CHand[i].SetCardPosition(Inven[i].left, 0);
		}

		if (E_turn){
			changeTurn();
			E_turn = false;
		}



		if (turnStart){
			PMana = MaxMana;
			turnStart = false;
		}

		for (int k = 0; k <= Drawnum; k++)
			CHand[k].Back_Handrender(dc);




		for (int i = 0; i < 8; i++)
		{
			if (Cfield[i] > -1)
				Cdeck[Cfield[i]].Fieldrender(dc, E_Field[i].left, E_Field[i].top);
		}

		if (atkparamater1 != -1 && atkparamater2 != -1){
			attackreder(dc, atkparamater1, atkparamater2);

			if (Cdeck[atkparamater1].atkMoveFlag == 0)
			{
				atkparamater1 = -1;
				atkparamater2 = -1;
			}
		}



	}
	

	int k1 = 0;
	void N_update(){
		if (Myturn)
			return;

		if (!E_trunStart && E_turn == false){
			E_trunStart = true;

			shortTick = GetTickCount();
		}


		if (GetTickCount() - E_Tick < 500){
			E_Tick = GetTickCount();

	//		int mana = E_SelectCard();
//			E_trunStart = false;
	//		PMana -= mana;

			E_turn = true; // 턴 종료
			k1 = 0;

		}

		else {
			if (GetTickCount() - shortTick < 500){
				if (Cfield[k1] > -1){
					shortTick = GetTickCount();

					if (E_recv.Attackflag[k1][0] > -1 && E_recv.Attackflag[k1][1] > -1) //k는 인트값 정수 초기값은 0 -> -1이면 공격신호가 없다. 
					{
						if (E_recv.Attackflag[k1][1] < 8) // 조건에 들어가야하는거는 카드를 공격
						{
							// 1이면 공격
							Cdeck[Cfield[E_recv.Attackflag[k1][0]]].SetMoveFlag(1, Field[E_recv.Attackflag[k1][1]].left, Field[E_recv.Attackflag[k1][1]].top, 5, NULL);

							other->Cdeck[other->Cfield[E_recv.Attackflag[k1][1]]].CLife -= Cdeck[Cfield[E_recv.Attackflag[k1][0]]].getCardAttack();
							other->Cfield[Cfield[E_recv.Attackflag[k1][1]]] = other->Cdeck[other->Cfield[Cfield[E_recv.Attackflag[k1][1]]]].CheckDeathCard(other->Cfield[Cfield[E_recv.Attackflag[k][1]]]);

							Cdeck[Cfield[Cfield[E_recv.Attackflag[k1][0]]]].CLife -= other->Cdeck[other->Cfield[Cfield[E_recv.Attackflag[k1][0]]]].getCardAttack();
							Cfield[Cfield[E_recv.Attackflag[k1][1]]] = Cdeck[Cfield[Cfield[E_recv.Attackflag[k1][1]]]].CheckDeathCard(Cfield[Cfield[E_recv.Attackflag[k1][1]]]);

							atkparamater1 = Cfield[Cfield[E_recv.Attackflag[k1][1]]];
							atkparamater2 = other->Cfield[Cfield[E_recv.Attackflag[k1][0]]];
						}

						if (E_recv.Attackflag[k1][1] == 8) //조건에 들어가야하는거는 나를 공격
						{
							Cdeck[Cfield[Cfield[E_recv.Attackflag[k1][0]]]].SetMoveFlag(1, PlayerRect.left, PlayerRect.top, 5, NULL);
							other->PLife -= Cdeck[Cfield[Cfield[E_recv.Attackflag[k1][0]]]].getCardAttack();

							atkparamater1 = Cfield[Cfield[E_recv.Attackflag[k1][0]]];
							atkparamater2 = 8;
						}

						if (k++ > 7){
							k = 7;
							E_Tick = GetTickCount();
						}
						shortTick = GetTickCount();


					}
				}

			}
			else if ((E_recv.cTurn == true)){
				E_Tick = GetTickCount();
			}
		}

	}

	void Net_changeTurn(){
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

		for (int i = 0; i < 8; i++){
			if (Cfield[i] > -1)
				Cdeck[Cfield[i]].atkflag = true;

			P_pass.Cfield[i] = Cfield[i];
		}

		if (++MaxMana > 10)
			MaxMana = 10;

		P_pass.E_Hand = Drawnum;
		P_pass.cTurn = true;

		Myturn = !Myturn;
		turnStart = true;
		flag1 = true;

		Network::getInstance()->send_message(P_pass);

		for (int i = 0; i < 8; i++){
			P_pass.Cfield[i] = -1;
			for (int j = 0; j < 2; j++)
			{
				P_pass.Attackflag[i][j] = -1;
			}
		}

		P_pass.E_Hand = -1;
		P_pass.cTurn = false;
	}

	void Net_update(POINT pos){
		DWORD key = InputManager::getInstance()->getKeyState();
		FieldAttack();
		if (Myturn){
			if (key & MYKEY_FLAG::MK_LCLK){
				RECT rc;
				SetRect(&rc, Inven[0].left, Inven[0].top, Inven[29].right, Inven[0].bottom);

				if (PtInRect(&rc, pos))
				{
					hangnum = (pos.x - 70) / 20;
				}
				else if ((hangnum != -1) && (CHand[hangnum].CMana <= PMana)){
					if (CHand[hangnum].getHandImg().mDC != 0)
						addMyfield(CHand[hangnum].getCindex());
					CHand[hangnum].HandRelease();
					PMana -= CHand[hangnum].CMana;
					hangnum = -1;
				}
			}
			else if (key & MYKEY_FLAG::MK_RCLK)
			{
				hangnum = -1;
			}

			if (Myturn){
				if (key & MYKEY_FLAG::MK_LCLK)
				{
					if (PtInRect(&TurnButtonON.Source, pos))
						Net_changeTurn();

					E_recv.cTurn = false;
				}
			}
			//			TurnFlag(pos);
		}
	}
};
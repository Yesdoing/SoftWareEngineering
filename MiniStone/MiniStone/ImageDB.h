#pragma once
#include "preCompile.h"

enum CType{
	Minion,
	Spell,
	Weapon,
};

struct SImageDB{
	HDC	mDC;
	HBITMAP hBit; //�ո� �̹���
//	HBITMAP BackBit; // �޸��̹���
	BITMAP Bit; //�̹��� ����
	RECT Source;
	const char *str;
};


struct SCard{
	CType cardtype;
	SImageDB imgDB;
	char Cnum[4];
	char Cname[20];
	int CAttack;
	int CLife;
	int CMana;
	
	RECT cardRect;
	POINT Position;
};

struct pass{
	int Cfield[8]; /// ���ʵ忡 ���� index��ȣ
	int Attackflag[8][2]; //�ʵ忡�� 8������ �ö�� �� �ְ� 0���� ������ 1���� �ǰ����ڿ� ���� �ʵ��ȣ ����
	int E_Hand; //�� �ڵ� ��
	bool cTurn;
};

typedef std::vector <SImageDB*> ImageVec;
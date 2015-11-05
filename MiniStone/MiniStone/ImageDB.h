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


typedef std::vector <SImageDB*> ImageVec;
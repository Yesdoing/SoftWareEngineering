#pragma once
#include "preCompile.h"

struct SImageDB{
	HBITMAP hBit; //�ո� �̹���
	HBITMAP BackBit; // �޸��̹���
	BITMAP Bit; //�̹��� ����
};

struct SCard{
	enum CType{
		Minion,
		Spell,
		Weapon,
	};

	SImageDB imgDB;
	int Cnum;
	int CAttack;
	int CLife;
	int CMana;
	char *Cname[20];
};


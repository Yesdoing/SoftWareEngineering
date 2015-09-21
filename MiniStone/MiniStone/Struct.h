#pragma once
#include "preCompile.h"

struct SImageDB{
	HBITMAP hBit; //앞면 이미지
	HBITMAP BackBit; // 뒷면이미지
	BITMAP Bit; //이미지 정보
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


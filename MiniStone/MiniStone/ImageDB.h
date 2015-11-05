#pragma once
#include "preCompile.h"

enum CType{
	Minion,
	Spell,
	Weapon,
};

struct SImageDB{
	HDC	mDC;
	HBITMAP hBit; //앞면 이미지
//	HBITMAP BackBit; // 뒷면이미지
	BITMAP Bit; //이미지 정보
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
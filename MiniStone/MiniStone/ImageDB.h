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

struct pass{
	int Cfield[8]; /// 적필드에 대한 index번호
	int Attackflag[8][2]; //필드에는 8마리가 올라올 수 있고 0번은 공격자 1번은 피공격자에 대한 필드번호 저장
	int E_Hand; //적 핸드 수
	bool cTurn;
};

typedef std::vector <SImageDB*> ImageVec;
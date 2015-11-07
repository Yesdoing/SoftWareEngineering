#pragma once
#include "preCompile.h"
#include "Card.h"

class Deck
{
private:
	Card	Cdeck[30];
	char		Cnum[4];
	char		Cname[10];
	int			CAttack;
	int			CLife;
	int			CMana;
	FILE		*f;

public:

	void init(){
		int i = 0;
		f = fopen("card.dat", "rb");
		while (fscanf(f, "%s %s %d %d %d", &Cnum, &Cname, &CAttack, &CLife, &CMana) != EOF){
			Cdeck[i].init(Cnum, Cname, CAttack, CLife, CMana);
			i++;
		}
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


	Deck();
	~Deck();
};


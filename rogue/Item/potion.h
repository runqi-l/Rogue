#ifndef __POTION_H__
#define __POTION_H__
#include "item.h"
class Player;
class Potion: public Item{
  public:
	Potion(Cell* locate);
};

class RH: public Potion{
  public:
	RH(Cell* locate);
	~RH()override;
	void usedBy(Player*& pl)override;
	void sawBy(Player* pl)override;
};
class BA: public Potion{
  public:
	BA(Cell* locate);
	~BA()override;
	void usedBy(Player*& pl)override;
	void sawBy(Player* pl)override;
};
class BD: public Potion{
  public:
	BD(Cell* locate);
	~BD()override;
	void usedBy(Player*& pl)override;
	void sawBy(Player* pl)override;
};
class PH: public Potion{
  public:
	PH(Cell* locate);
	~PH()override;
	void usedBy(Player*& pl)override;
	void sawBy(Player* pl)override;
};
class WA: public Potion{
  public:
	WA(Cell* locate);
	~WA()override;
	void usedBy(Player*& pl)override;
	void sawBy(Player* pl)override;
};
class WD: public Potion{
  public:
	WD(Cell* locate);
	~WD()override;
	void usedBy(Player*& pl)override;
	void sawBy(Player* pl)override;
};
#endif

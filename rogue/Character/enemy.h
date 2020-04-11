//merchant, dragon, //special abilities //concrete enemies
#ifndef __ENEMY_H__
#define __ENEMY_H__
#include <string>
#include "character.h"
class Cell;
class Player;
class Potion;
class Enemy: public Character{
  public: 
	Enemy(char sym, int HP, int Atk, int Def, int gold=1);
	virtual ~Enemy()=0;
	
	bool attackedBy(Player* attacker) override;
	virtual bool attack(Player* defender);
	void notifyAttackObservers(int damage);
	void notifyMissObservers();
	
	virtual bool isClosedTo(Player* p)const;
};

class Vampire: public Enemy {
  public:
	Vampire();
};

class Werewolf: public Enemy {
  public:
	Werewolf();
};

class Troll: public Enemy {
  public:
	Troll();
};

class Goblin: public Enemy {
  public:
	Goblin();
};

class Phoenix: public Enemy {
  public:
	Phoenix();
};

class Merchant: public Enemy {
	Potion* goods=nullptr;
  public:
	Merchant();
	~Merchant() override;
	bool attack(Player* defender) override;
	bool attackedBy(Player* attacker) override;
	void sawBy(Player* p) override;
	void attach(Observer* ob)override;
	void sellTo(Player*& buyer)override;
};

class Dragon: public Enemy {
	Cell* guarding;
  public:
	Dragon(Cell* guarding);
	bool isClosedTo(Player* p)const override;
	bool attackedBy(Player* attacker) override;
	void moveTo(Cell* newstand) override;
};

#endif

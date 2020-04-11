//to be implemented: use potion, pick up gold
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include "character.h"
class Cell;
class Enemy;
class RH;
class BA;
class BD;
class PH;
class WA;
class WD;
class Player: public Character{
	int potionLayer=0;
	bool RHKnowledge = false;
	bool BAKnowledge = false;
	bool BDKnowledge = false;
	bool PHKnowledge = false;
	bool WAKnowledge = false;
	bool WDKnowledge = false;
	bool merchantSlain = false;
  public: 
	Player();
	Player(char sym, int HP, int Atk, int Def, int gold=0);
	virtual ~Player()=0;
	
	virtual Player *getBasePlayer();
	virtual int getPotionLayer() const;
	virtual void setDestroyable();
	
	virtual void learnPotion(RH*);
	virtual void learnPotion(BA*);
	virtual void learnPotion(BD*);
	virtual void learnPotion(PH*);
	virtual void learnPotion(WA*);
	virtual void learnPotion(WD*);
	virtual bool getPotionKnowledge(RH*)const;
	virtual bool getPotionKnowledge(BA*)const;
	virtual bool getPotionKnowledge(BD*)const;
	virtual bool getPotionKnowledge(PH*)const;
	virtual bool getPotionKnowledge(WA*)const;
	virtual bool getPotionKnowledge(WD*)const;
	
	bool attackedBy(Enemy* attacker) override;
	bool attack(Enemy* defender);
	void notifyAttackObservers(Character *e, const int damage);
	void notifyStatusObservers();
	
	//virtual void usePotion(Potion* pt, Player* pl);
	void usePotion(RH* pt, Player*& pl);
	void usePotion(BA* pt, Player*& pl);
	void usePotion(BD* pt, Player*& pl);
	virtual void usePotion(PH* pt, Player*& pl);
	virtual void usePotion(WA* pt, Player*& pl);
	virtual void usePotion(WD* pt, Player*& pl);
	
	virtual bool merchantHostile();
	virtual void slainMerchant();
	virtual int score();
	virtual bool spend(const int gld);
};


class Human: public Player {
  public:
	Human();
	int score() override;
};

class Dwarf: public Player {
  public:
	Dwarf();
	std::string getGoldValue() const override;
	bool spend(const int gld)override;
};

class Elf: public Player {
  public:
	Elf();
	//void usePotion(Potion* pt, Player* pl) override;
	void usePotion(PH* pt, Player*& pl)override;
	void usePotion(WA* pt, Player*& pl)override;
	void usePotion(WD* pt, Player*& pl)override;
};

class Orc: public Player {
  public:
	Orc();
	std::string getGoldValue() const override;
	bool spend(const int gld)override;
};

#endif


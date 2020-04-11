#ifndef __DECORATOR_H__
#define __DECORATOR_H__
#include <string>
#include <vector>
#include "player.h"
class Observer;
class Cell;
class Decorator: public Player{
  protected:
	Player* component;
  public:
	Decorator(Player *p);
	virtual ~Decorator()=0;
	
	Player* getBasePlayer()  override;
	int getPotionLayer() const override;
	void setDestroyable() override;
	char getSym() const override;
	int getColumn() const override;
	int getRow() const override;
	int getHP() const override;
	int getAtk() const override;
	int getDef() const override;
	Cell* getStand() const override;
	int getMaxHP() const override;
	void setHP(const int hp)override;
	void setStand(Cell* newstand)override;
	int getGold() const override;
	std::string getGoldValue() const override;
	void setGold(const int newgold)override;
	void learnPotion(RH* p)override;
	void learnPotion(BA* p)override;
	void learnPotion(BD* p)override;
	void learnPotion(PH* p)override;
	void learnPotion(WA* p)override;
	void learnPotion(WD* p)override;
	bool getPotionKnowledge(RH* p)const override;
	bool getPotionKnowledge(BA* p)const override;
	bool getPotionKnowledge(BD* p)const override;
	bool getPotionKnowledge(PH* p)const override;
	bool getPotionKnowledge(WA* p)const override;
	bool getPotionKnowledge(WD* p)const override;
	std::vector<Observer*>& getObservers() override;
	bool merchantHostile()override;
	void slainMerchant()override;
	int score() override;
	bool spend(const int gold)override;
};

class BoostAtk: public Decorator{
  public:
	BoostAtk(Player *p);
	int getAtk()const override;
};

class BoostDef: public Decorator{
  public:
	BoostDef(Player *p);
	int getDef()const override;
};

class WoundAtk: public Decorator{
  public:
	WoundAtk(Player *p);
	int getAtk()const override;
};

class WoundDef: public Decorator{
  public:
	WoundDef(Player *p);
	int getDef()const override;
};
#endif

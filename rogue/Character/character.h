#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <vector>
#include <string>
class Cell;
class Observer;
class Enemy;
class Player;
class Character {
	char sym;
	int HP;
	int maxHP;
	int Atk;
	int Def;
	Cell* stand = nullptr;
	int gold;
  protected:
	std::vector<Observer*> observers;
  public:
	//ctor & dtor;
	Character();
	Character(char sym, int HP, int Atk, int Def, int gold);
	virtual ~Character()=0;
	//getters
	virtual char getSym() const;
	virtual int getColumn() const;
	virtual int getRow() const;
	virtual int getHP() const;
	virtual int getAtk() const;
	virtual int getDef() const;
	virtual Cell* getStand() const;
	virtual int getMaxHP() const;
	//setters
	virtual void setHP(const int hp);
	virtual void setStand(Cell* newstand);
	
	virtual std::vector<Observer*>& getObservers();
	virtual void attach(Observer* ob);
	virtual void moveTo(Cell* newstand);
	
	virtual int getGold() const;
	virtual std::string getGoldValue() const;
	virtual void setGold(const int newgold);
	
	virtual bool attackedBy(Enemy* attacker);
	virtual bool attackedBy(Player* attacker);
	virtual void sawBy(Player* p);
	virtual void sellTo(Player*& buyer);
};
#endif

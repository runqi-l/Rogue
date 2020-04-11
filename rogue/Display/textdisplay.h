//notify, ostream &operator<<
#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <string>
#include <vector>
#include "observer.h"
#include <iostream>
class Cell;
class Enemy;
class Player;
class Character;
class Gold;
class TextDisplay: public Observer {
	std::vector<std::string> theDisplay;
	std::string race;
	std::string gold;
	int floor;
	int HP;
	int Atk;
	int Def;
	std::string Action="";
	
  public:
	TextDisplay(std::string race="Human", std::string gold="0", int floor=0, int HP=140, int Atk=20, int Def=20);
	void setFloor(int newfloor);
	void setRace(std::string r);
	void notify(Cell *c) override;
	void notify(Enemy *e, int damage) override;
	void notify(Player *p, Character *e, int damage) override;
	void notify(Player *p) override;
	void notify(Enemy *e) override;
	void notify(Gold *e, std::string name)override;
	void notify(Potion *p, std::string name)override;
	void saw(Potion *p, std::string name)override;
	void action(std::string msg);
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
	friend void print(const TextDisplay &td, Player* PC);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
void print(const TextDisplay &td, Player* PC);
#endif

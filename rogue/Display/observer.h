//notify
#ifndef __OBSERVER_H__
#define __OBSERVER_H__
#include <string>
class Cell;
class Enemy;
class Character;
class Player;
class Gold;
class Potion;
class Observer {
 public:
  virtual void notify(Cell *c) = 0;  // c is the Cell that called the notify method
  virtual void notify(Enemy *e, int damage) = 0;//notify that enemy is damaging PC
  virtual void notify(Player *p, Character *e, int damage) = 0;//notify that PC is damaging an Enemy
  virtual void notify(Player *p) = 0;//notify PC status change, when taken damage, drinking potion, getting gold.
  virtual void notify(Enemy *e) = 0;//notify that Enemy attacked but missed.
  virtual void notify(Gold *e, std::string name) = 0;// notify that Gold is picked up
  virtual void notify(Potion *p, std::string name) = 0;//notify that Potion is used
  virtual void saw(Potion *p, std::string name) = 0;//notify that Potion is saw by PC
  //virtual void notify(Gold *e, std::string name) = 0;// notify that 
  virtual ~Observer() = default;
};
#endif

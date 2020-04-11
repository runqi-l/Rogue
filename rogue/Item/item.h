//stair, gold, potion
#ifndef __ITEM_H__
#define __ITEM_H__
#include <string>
#include <vector>
class Player;
class Cell;
class Observer;
class Item {
	char sym;
	Cell* locate = nullptr;
	bool isCollectable;//meaning whether PC can step on it;
  protected:
	std::vector<Observer*> observers;
  public:
	//ctor & dtor;
	Item(char sym, Cell* locate, bool isCollectable=true);
	virtual ~Item()=0;
	//getters
	char getSym() const;
	bool Collectable() const;
	int getColumn() const;
	int getRow() const;
	Cell* getLocate() const;
	
	void setLocate(Cell* newlocate);
	void free();
	
	virtual void usedBy(Player*& pl);
	virtual void pickedUpBy(Player* pl);
	virtual void sawBy(Player* pl);
	void attachObserver(Observer* observer);
};

#endif



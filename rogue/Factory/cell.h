#ifndef __CELL_H__
#define __CELL_H__
#include <string>
#include <vector>
class Character;
class Item;
class Observer;
class Cell {
	char sym;
	int row;
	int column;
	Character* standing=nullptr;
	Item* locating=nullptr;
	std::vector<Observer*> observers;
  public:
	Cell(char sym, int row, int column);
	virtual ~Cell()=0;
	
	void attach(Character* c);
	void attach(Item* i);
	
	void detach();
	char getSym() const;
	int getRow() const;
	int getColumn() const;
	Character* getStanding()const;
	Item* getLocating()const;
	virtual bool isFloorTile()const;
	virtual bool isDoorWay()const;
	virtual bool isPassage()const;
	
	void attachObserver(Observer* o);
	void notifyObservers();
};

class VirticalWall: public Cell{
  public:
	VirticalWall(int row, int column);
};

class HorizontalWall: public Cell{
  public:
	HorizontalWall(int row, int column);
};

class FloorTile: public Cell{
  public:
	FloorTile(int row, int column);
	bool isFloorTile()const override;
};

class DoorWay: public Cell{
  public:
	DoorWay(int row, int column);
	bool isDoorWay()const override;
};

class Passage: public Cell{
  public:
	Passage(int row, int column);
	bool isPassage()const override;
};

class Space: public Cell{
  public:
	Space(int row, int column);
};
#endif

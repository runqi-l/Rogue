#include "cell.h"
#include "../Character/character.h"
#include "../Item/item.h"
#include "../Display/observer.h"
using namespace std;

Cell::Cell(char sym, int row, int column): sym{sym}, row{row}, column{column}{}
Cell::~Cell(){delete locating;}

void Cell::attach(Character* c){
	detach();
	locating=nullptr;
	standing=c;
	c->setStand(this);
	notifyObservers();
}
void Cell::attach(Item* i){
	locating=i;
	i->setLocate(this);
	notifyObservers();
}

void Cell::detach(){
	standing = nullptr;
	delete locating;
	locating = nullptr;
	notifyObservers();
}

char Cell::getSym() const{
	return sym;
}
int Cell::getRow() const{
	return row;
}
int Cell::getColumn() const{
	return column;
}
Character* Cell::getStanding()const{
	return standing;
}
Item* Cell::getLocating()const{
	return locating;
}
bool Cell::isFloorTile()const{return false;}
bool Cell::isDoorWay()const{return false;}
bool Cell::isPassage()const{return false;}

void Cell::attachObserver(Observer* o){
	observers.emplace_back(o);
}
void Cell::notifyObservers(){
	for (unsigned int i=0; i<observers.size(); ++i){
		observers[i]->notify(this);
	}
}


VirticalWall::VirticalWall(int row, int column): Cell{'|', row, column}{}


HorizontalWall::HorizontalWall(int row, int column): Cell{'-', row, column}{}


FloorTile::FloorTile(int row, int column): Cell{'.', row, column}{}
bool FloorTile::isFloorTile()const{return true;}


DoorWay::DoorWay(int row, int column): Cell{'+', row, column}{notifyObservers();}
bool DoorWay::isDoorWay()const{return true;}


Passage::Passage(int row, int column): Cell{'#', row, column}{}
bool Passage::isPassage()const{return true;}


Space::Space(int row, int column): Cell{' ', row, column}{}

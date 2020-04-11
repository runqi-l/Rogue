#include "item.h"
#include "../Factory/cell.h"
#include "../Display/observer.h"
using namespace std;

Item::Item(char sym, Cell* locate, bool isCollectable): sym{sym}, locate{locate}, isCollectable{isCollectable}{
	if(locate != nullptr) locate->attach(this);
}
Item::~Item(){}
//getters
char Item::getSym() const{
	return sym;
}
bool Item::Collectable() const{
	return isCollectable;
}
int Item::getColumn() const{
	return locate->getColumn();
}
int Item::getRow() const{
	return locate->getRow();
}
Cell* Item::getLocate() const{
	return locate;
}
void Item::setLocate(Cell* newlocate){
	locate=newlocate;
}
void Item::free(){
	isCollectable = true;
}

void Item::usedBy(Player*& pl){}

void Item::pickedUpBy(Player* pl){}

void Item::sawBy(Player* pl){}

void Item::attachObserver(Observer* observer){
	observers.emplace_back(observer);
}

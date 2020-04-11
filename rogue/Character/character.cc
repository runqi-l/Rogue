#include "character.h"
#include "../Display/observer.h"
#include "../Factory/cell.h"
using namespace std;

//ctor & dtor;
Character::Character(){}
Character::Character(char sym, int HP, int Atk, int Def, int gold): sym{sym}, HP{HP}, maxHP{HP}, Atk{Atk}, Def{Def}, gold{gold}{}
Character::~Character(){}
//getters
char Character::getSym() const{
	return sym;
}
int Character::getColumn() const{
	return stand->getColumn();
}
int Character::getRow() const{
	return stand->getRow();
}
int Character::getHP() const{
	return HP;
}
int Character::getAtk() const{
	return Atk;
}
int Character::getDef() const{
	return Def;
}
Cell* Character::getStand() const{
	return stand;
}
int Character::getMaxHP() const{
	return maxHP;
}

//setters
void Character::setHP(const int hp) {
	if(hp>getMaxHP()){
		HP=getMaxHP();
	} else if(hp<0){
		HP=0;
	} else {HP=hp;}
}
void Character::setStand(Cell* newstand){
	stand=newstand;
}


vector<Observer*>& Character::getObservers(){
	return observers;
}

void Character::attach(Observer* ob){
	observers.emplace_back(ob);
}

void Character::moveTo(Cell* newstand){
	getStand()->detach();
	newstand->attach(this);
}

int Character::getGold() const{
	return gold;
}
string Character::getGoldValue() const{
	return to_string(gold);
}

void Character::setGold(const int newgold){
	gold=newgold;
}

bool Character::attackedBy(Enemy* attacker){return true;}
bool Character::attackedBy(Player* attacker){return true;}

void Character::sawBy(Player*){}
void Character::sellTo(Player*& buyer){}


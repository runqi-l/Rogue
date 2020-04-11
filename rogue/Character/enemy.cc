#include "enemy.h"
#include "player.h"
#include "../Factory/cell.h"
#include "../Display/observer.h"
#include "../Item/gold.h"
#include "../Item/potion.h"
#include <cmath>
using namespace std;

Enemy::Enemy(char sym, int HP, int Atk, int Def, int gold):Character(sym, HP, Atk, Def, gold){}
Enemy::~Enemy(){}



bool Enemy::attackedBy(Player* attacker){
	if (!attacker->attack(this)){
		getStand()->detach();
		return false;
	}
	return true;
}

bool Enemy::attack(Player* defender){
	if(rand()%2==1){
		notifyMissObservers();
		return true;
	}
	int damage = ceil((double(100)/double(100+defender->getDef()))*double(getAtk()));
	if(damage>=defender->getHP()){
		notifyAttackObservers(defender->getHP());
		defender->setHP(0);
		return false;//meaning defender died
	} else {
		notifyAttackObservers(damage);
		defender->setHP(defender->getHP()-damage);
		return true;//meaning defender survived
	}
}

void Enemy::notifyAttackObservers(int damage){
	for (unsigned int i=0; i<getObservers().size(); ++i){
		getObservers()[i]->notify(this, damage);
	}
}

void Enemy::notifyMissObservers(){
	for (unsigned int i=0; i<getObservers().size(); ++i){
		getObservers()[i]->notify(this);
	}
}

bool Enemy::isClosedTo(Player* p)const{
	return (getRow()-p->getRow()<2 && getRow()-p->getRow()>-2 && getColumn()-p->getColumn()<2 && getColumn()-p->getColumn()>-2);
}


Vampire::Vampire(): Enemy{'V', 50, 25, 25}{}

Werewolf::Werewolf(): Enemy{'W', 120, 30, 5}{}

Troll::Troll(): Enemy{'T', 120, 25, 15}{}

Goblin::Goblin(): Enemy{'N', 70, 5, 10}{}

Phoenix::Phoenix(): Enemy{'X', 50, 35, 20}{}

Merchant::Merchant(): Enemy{'M', 30, 70, 5, 0}{
	int random = rand()%3;
	if (random==0){
		goods = new RH{nullptr};
	} else if (random==1){
		goods = new BA{nullptr};
	} else {
		goods = new BD{nullptr};
	}
}
Merchant::~Merchant(){
	delete goods;
}
void Merchant::sawBy(Player* p){
	if (!(p->merchantHostile()||goods==nullptr)) {
		goods->sawBy(p);
	}
}
bool Merchant::attack(Player* defender){
	if (!defender->merchantHostile()){
		return true;
	}
	if(rand()%2==1){
		notifyMissObservers();
		return true;
	}
	int damage = ceil((double(100)/double(100+defender->getDef()))*double(getAtk()));
	if(damage>=defender->getHP()){
		notifyAttackObservers(defender->getHP());
		defender->setHP(0);
		return false;//meaning defender died
	} else {
		notifyAttackObservers(damage);
		defender->setHP(defender->getHP()-damage);
		return true;//meaning defender survived
	}
}
bool Merchant::attackedBy(Player* attacker){
	attacker->slainMerchant();
	if (!attacker->attack(this)){
		Cell* goldpos = getStand();
		getStand()->detach();
		Gold *g = new MerchantHoard{goldpos};
		for (auto ob : observers){
			g->attachObserver(ob);
		}
		goldpos->attach(g);
		return false;
	}
	return true;
}
void Merchant::attach(Observer* ob){
	observers.emplace_back(ob);
	goods->attachObserver(ob);
}
void Merchant::sellTo(Player*& buyer){
	if (!buyer->merchantHostile()&&goods!=nullptr&&buyer->spend(2)) {
		goods->usedBy(buyer);
		delete goods;
		goods = nullptr;
	}
}

Dragon::Dragon(Cell* guarding): Enemy{'D', 150, 20, 20, 0}, guarding{guarding}{}
bool Dragon::isClosedTo(Player* p)const{
	return (guarding->getRow()-p->getRow()<2 && guarding->getRow()-p->getRow()>-2 && guarding->getColumn()-p->getColumn()<2 && guarding->getColumn()-p->getColumn()>-2);
}
bool Dragon::attackedBy(Player* attacker){
	if (!attacker->attack(this)){
		guarding->getLocating()->free();
		getStand()->detach();
		return false;
	}
	//attack(attacker);
	return true;
}
void Dragon::moveTo(Cell* newstand){}

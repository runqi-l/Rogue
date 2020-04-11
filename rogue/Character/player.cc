#include "player.h"
#include "../Factory/cell.h"
#include "../Display/observer.h"
#include "../Item/potion.h"
#include "decorator.h"
#include "enemy.h"
#include <cmath>
using namespace std;
Player::Player(){}
Player::Player(char sym, int HP, int Atk, int Def, int gold):Character(sym, HP, Atk, Def, gold){}
Player::~Player(){}

Player * Player::getBasePlayer() {
	return this;
}
int Player::getPotionLayer() const{
	return potionLayer;
}
void Player::setDestroyable(){
	potionLayer=1;
}

void Player::learnPotion(RH*){
	RHKnowledge=true;
}
void Player::learnPotion(BA*){
	BAKnowledge=true;
}
void Player::learnPotion(BD*){
	BDKnowledge=true;
}
void Player::learnPotion(PH*){
	PHKnowledge=true;
}
void Player::learnPotion(WA*){
	WAKnowledge=true;
}
void Player::learnPotion(WD*){
	WDKnowledge=true;
}
bool Player::getPotionKnowledge(RH*)const{
	return RHKnowledge;
}
bool Player::getPotionKnowledge(BA*)const{
	return BAKnowledge;
}
bool Player::getPotionKnowledge(BD*)const{
	return BDKnowledge;
}
bool Player::getPotionKnowledge(PH*)const{
	return PHKnowledge;
}
bool Player::getPotionKnowledge(WA*)const{
	return WAKnowledge;
}
bool Player::getPotionKnowledge(WD*)const{
	return WDKnowledge;
}

bool Player::attackedBy(Enemy* attacker){
	if (!attacker->attack(this)){
		getStand()->detach();
		notifyStatusObservers();
		return false;
	}
	notifyStatusObservers();
	return true;
}

bool Player::attack(Enemy* defender){
	int damage = ceil((double(100)/double(100+defender->getDef()))*double(getAtk()));
	if(damage>=defender->getHP()){
		notifyAttackObservers(defender, defender->getHP());
		defender->setHP(0);
		setGold(getGold()+defender->getGold());
		notifyStatusObservers();
		return false;//meaning defender died
	} else {
		notifyAttackObservers(defender, damage);
		defender->setHP(defender->getHP()-damage);
		return true;//meaning defender survived
	}
}

void Player::notifyAttackObservers(Character *e, const int damage){
	for (unsigned int i=0; i<getObservers().size(); ++i){
		getObservers()[i]->notify(this, e, damage);
	}
}

void Player::notifyStatusObservers(){
	for (unsigned int i=0; i<getObservers().size(); ++i){
		getObservers()[i]->notify(this);
	}
}

void Player::usePotion(RH* pt, Player*& pl){
	setHP(getHP()+10);
}
void Player::usePotion(BA* pt, Player*& pl){
	pl = new BoostAtk(pl);
}
void Player::usePotion(BD* pt, Player*& pl){
	pl = new BoostDef(pl);
}
void Player::usePotion(PH* pt, Player*& pl){
	setHP(getHP()-10);
}
void Player::usePotion(WA* pt, Player*& pl){
	pl = new WoundAtk(pl);
}
void Player::usePotion(WD* pt, Player*& pl){
	pl = new WoundDef(pl);
}

bool Player::merchantHostile(){
	return merchantSlain;
}
void Player::slainMerchant(){
	merchantSlain=true;
}
int Player::score(){
	return getGold()*100;
}

bool Player::spend(const int gld){
	if (getGold()>=gld){
		setGold(getGold()-gld);
		return true;
	}
	return false;
}

Human::Human(): Player{'@', 140, 20, 20} {}
int Human::score(){
	return getGold()*150;
}


Dwarf::Dwarf(): Player{'@', 100, 20, 30} {}
string Dwarf::getGoldValue() const {
	return to_string(getGold())+"x2";
}
bool Dwarf::spend(const int gld){
	if (getGold()*2>=gld){
		setGold(getGold()-gld/2);
		return true;
	}
	return false;
}


Elf::Elf(): Player{'@', 140, 30, 10} {}
void Elf::usePotion(PH* pt, Player*& pl){
	setHP(getHP()+10);
}
void Elf::usePotion(WA* pt, Player*& pl){
	pl = new BoostAtk(pl);
}
void Elf::usePotion(WD* pt, Player*& pl){
	pl = new BoostDef(pl);
}


Orc::Orc(): Player{'@', 180, 30, 25} {}
string Orc::getGoldValue() const {
	return to_string(getGold())+"/2";
}
bool Orc::spend(const int gld){
	if (getGold()>=gld*2){
		setGold(getGold()-gld*2);
		return true;
	}
	return false;
}

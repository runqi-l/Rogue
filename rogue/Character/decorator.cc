#include "decorator.h"
#include "../Factory/cell.h"
#include "../Display/observer.h"
using namespace std;

Decorator::Decorator(Player *p): component{p} {}
Decorator::~Decorator() {
	if (component->getPotionLayer()>0) delete component;
}

Player* Decorator::getBasePlayer()  {
	return component->getBasePlayer();
}
int Decorator::getPotionLayer() const {
	return 1+component->getPotionLayer();
}
void Decorator::setDestroyable() {
	return component->setDestroyable();
}
char Decorator::getSym() const {
	return component->getSym();
}
int Decorator::getColumn() const {
	return component->getColumn();
}
int Decorator::getRow() const {
	return component->getRow();
}
int Decorator::getHP() const {
	return component->getHP();
}
int Decorator::getAtk() const {
	return component->getAtk();
}
int Decorator::getDef() const {
	return component->getDef();
}
Cell* Decorator::getStand() const {
	return component->getStand();
}
int Decorator::getMaxHP() const {
	return component->getMaxHP();
}

void Decorator::setHP(const int hp){
	component->setHP(hp);
}
void Decorator::setStand(Cell* newstand){
	component->setStand(newstand);
}

int Decorator::getGold() const {
	return component->getGold();
}
std::string Decorator::getGoldValue() const {
	return component->getGoldValue();
}
void Decorator::setGold(const int newgold){
	component->setGold(newgold);
}

void Decorator::learnPotion(RH* p){
	component->learnPotion(p);
}
void Decorator::learnPotion(BA* p){
	component->learnPotion(p);
}
void Decorator::learnPotion(BD* p){
	component->learnPotion(p);
}
void Decorator::learnPotion(PH* p){
	component->learnPotion(p);
}
void Decorator::learnPotion(WA* p){
	component->learnPotion(p);
}
void Decorator::learnPotion(WD* p){
	component->learnPotion(p);
}

bool Decorator::getPotionKnowledge(RH* p)const{
	return component->getPotionKnowledge(p);
}
bool Decorator::getPotionKnowledge(BA* p)const{
	return component->getPotionKnowledge(p);
}
bool Decorator::getPotionKnowledge(BD* p)const{
	return component->getPotionKnowledge(p);
}
bool Decorator::getPotionKnowledge(PH* p)const{
	return component->getPotionKnowledge(p);
}
bool Decorator::getPotionKnowledge(WA* p)const{
	return component->getPotionKnowledge(p);
}
bool Decorator::getPotionKnowledge(WD* p)const{
	return component->getPotionKnowledge(p);
}
vector<Observer*>& Decorator::getObservers(){
	return component->getObservers();
}
bool Decorator::merchantHostile(){
	return component->merchantHostile();
}
void Decorator::slainMerchant(){
	component->slainMerchant();
}
int Decorator::score(){
	return component->score();
}
bool Decorator::spend(const int gold){
	return component->spend(gold);
}


BoostAtk::BoostAtk(Player *p): Decorator{p}{}
int BoostAtk::getAtk()const {
	return 5+component->getAtk();
}


BoostDef::BoostDef(Player *p): Decorator{p}{}
int BoostDef::getDef()const {
	return 5+component->getDef();
}


WoundAtk::WoundAtk(Player *p): Decorator{p}{}
int WoundAtk::getAtk()const {
	int tmp = component->getAtk()-5;
	return (tmp>=0)? tmp : 0;
}


WoundDef::WoundDef(Player *p): Decorator{p}{}
int WoundDef::getDef()const {
	int tmp = component->getDef()-5;
	return (tmp>=0)? tmp : 0;
}

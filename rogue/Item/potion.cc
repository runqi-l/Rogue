#include "potion.h"
#include "../Factory/cell.h"
#include "../Character/decorator.h"
#include "../Display/observer.h"
#include <string>
using namespace std;
Potion::Potion(Cell* locate):Item{'P', locate, false}{}

RH::RH(Cell* locate):Potion{locate}{}
RH::~RH(){}
void RH::usedBy(Player*& pl){
	pl->learnPotion(this);
	pl->getBasePlayer()->usePotion(this, pl);
	pl->notifyStatusObservers();
	for (auto i : observers){
		i->notify(this, "Restore Health Potion");
	}
}
void RH::sawBy(Player* pl){
	if(getLocate()==nullptr){
		for (auto i : observers){
			i->saw(this, "Restore Health Potion");
		}
		return;
	}
	if(pl->getPotionKnowledge(this)){
		for (auto i : observers){
			i->saw(this, "Restore Health Potion");
		}
	} else {
		for (auto i : observers){
			i->saw(this, "unknown Potion");
		}
	}
}

BA::BA(Cell* locate):Potion{locate}{}
BA::~BA(){}
void BA::usedBy(Player*& pl){
	pl->learnPotion(this);
	pl->getBasePlayer()->usePotion(this, pl);
	pl->notifyStatusObservers();
	for (auto i : observers){
		i->notify(this, "Boost Atk Potion");
	}
	
}
void BA::sawBy(Player* pl){
	if(getLocate()==nullptr){
		for (auto i : observers){
			i->saw(this, "Boost Atk Potion");
		}
		return;
	}
	if(pl->getPotionKnowledge(this)){
		for (auto i : observers){
			i->saw(this, "Boost Atk Potion");
		}
	} else {
		for (auto i : observers){
			i->saw(this, "unknown Potion");
		}
	}
}

BD::BD(Cell* locate):Potion{locate}{}
BD::~BD(){}
void BD::usedBy(Player*& pl){
	pl->learnPotion(this);
	pl->getBasePlayer()->usePotion(this, pl);
	pl->notifyStatusObservers();
	for (auto i : observers){
		i->notify(this, "Boost Def Potion");
	}
}
void BD::sawBy(Player* pl){
	if(getLocate()==nullptr){
		for (auto i : observers){
			i->saw(this, "Boost Def Potion");
		}
		return;
	}
	if(pl->getPotionKnowledge(this)){
		for (auto i : observers){
			i->saw(this, "Boost Def Potion");
		}
	} else {
		for (auto i : observers){
			i->saw(this, "unknown Potion");
		}
	}
}

PH::PH(Cell* locate):Potion{locate}{}
PH::~PH(){}
void PH::usedBy(Player*& pl){
	pl->learnPotion(this);
	pl->getBasePlayer()->usePotion(this, pl);
	pl->notifyStatusObservers();
	for (auto i : observers){
		i->notify(this, "Poison Health Potion");
	}
}
void PH::sawBy(Player* pl){
	if(pl->getPotionKnowledge(this)){
		for (auto i : observers){
			i->saw(this, "Poison Health Potion");
		}
	} else {
		for (auto i : observers){
			i->saw(this, "unknown Potion");
		}
	}
}

WA::WA(Cell* locate):Potion{locate}{}
WA::~WA(){}
void WA::usedBy(Player*& pl){
	pl->learnPotion(this);
	pl->getBasePlayer()->usePotion(this, pl);
	pl->notifyStatusObservers();
	for (auto i : observers){
		i->notify(this, "Wound Atk Potion");
	}
}
void WA::sawBy(Player* pl){
	if(pl->getPotionKnowledge(this)){
		for (auto i : observers){
			i->saw(this, "Wound Atk Potion");
		}
	} else {
		for (auto i : observers){
			i->saw(this, "unknown Potion");
		}
	}
}

WD::WD(Cell* locate):Potion{locate}{}
WD::~WD(){}
void WD::usedBy(Player*& pl){
	pl->learnPotion(this);
	pl->getBasePlayer()->usePotion(this, pl);
	pl->notifyStatusObservers();
	for (auto i : observers){
		i->notify(this, "Wound Def Potion");
	}
}
void WD::sawBy(Player* pl){
	if(pl->getPotionKnowledge(this)){
		for (auto i : observers){
			i->saw(this, "Wound Def Potion");
		}
	} else {
		for (auto i : observers){
			i->saw(this, "unknown Potion");
		}
	}
}

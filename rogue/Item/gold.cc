#include "gold.h"
#include "../Factory/cell.h"
#include "../Character/enemy.h"
#include "../Character/player.h"
#include "../Display/observer.h"
#include <string>
using namespace std;
Gold::Gold(Cell* locate, int goldVal, bool isCollectable):Item{'G', locate, isCollectable}, goldVal{goldVal} {}

NormalPiece::NormalPiece(Cell* locate):Gold{locate, 1}{}
NormalPiece::~NormalPiece(){}
void NormalPiece::pickedUpBy(Player* pl){
	pl->setGold(pl->getGold()+goldVal);
	for (auto i : observers){
		i->notify(this, "Normal Pile");
	}
	pl->notifyStatusObservers();
}

SmallHoard::SmallHoard(Cell* locate):Gold{locate, 2}{}
SmallHoard::~SmallHoard(){}
void SmallHoard::pickedUpBy(Player* pl){
	pl->setGold(pl->getGold()+goldVal);
	for (auto i : observers){
		i->notify(this, "Small Hoard");
	}
	pl->notifyStatusObservers();
}

MerchantHoard::MerchantHoard(Cell* locate):Gold{locate, 4}{}
MerchantHoard::~MerchantHoard(){}
void MerchantHoard::pickedUpBy(Player* pl){
	pl->setGold(pl->getGold()+goldVal);
	for (auto i : observers){
		i->notify(this, "Merchant Hoard");
	}
	pl->notifyStatusObservers();
}

DragonHoard::DragonHoard(Cell* locate):Gold{locate, 6, false}{}
DragonHoard::~DragonHoard(){}
void DragonHoard::pickedUpBy(Player* pl){
	pl->setGold(pl->getGold()+goldVal);
	for (auto i : observers){
		i->notify(this, "Dragon Hoard");
	}
	pl->notifyStatusObservers();
}

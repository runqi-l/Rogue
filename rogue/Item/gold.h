#ifndef __GOLD_H__
#define __GOLD_H__
#include "item.h"
class Player;
class Gold: public Item{
  protected:
	const int goldVal;
  public:
	Gold(Cell* locate, int goldVal, bool isCollectable=true);
};

class NormalPiece: public Gold{
  public:
	NormalPiece(Cell* locate);
	~NormalPiece() override;
	void pickedUpBy(Player* pl) override;
};

class SmallHoard: public Gold{
  public:
	SmallHoard(Cell* locate);
	~SmallHoard() override;
	void pickedUpBy(Player* pl) override;
};

class MerchantHoard: public Gold{
  public:
	MerchantHoard(Cell* locate);
	~MerchantHoard() override;
	void pickedUpBy(Player* pl) override;
};

class DragonHoard: public Gold{
  public:
	DragonHoard(Cell* locate);
	~DragonHoard() override;
	void pickedUpBy(Player* pl) override;
};
#endif

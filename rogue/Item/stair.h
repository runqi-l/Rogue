#ifndef __STAIR_H__
#define __STAIR_H__
#include "item.h"
class Stair: public Item{
  public:
	Stair(Cell* locate);
	~Stair() override;
};
#endif

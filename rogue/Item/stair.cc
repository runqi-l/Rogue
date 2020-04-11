#include "stair.h"
#include "../Factory/cell.h"
using namespace std;
Stair::Stair(Cell* locate):Item{'\\', locate, true}{}
Stair::~Stair(){}

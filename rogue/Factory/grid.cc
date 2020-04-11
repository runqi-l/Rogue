#include <algorithm>
#include <fstream>
#include "grid.h"
#include "cell.h"
#include "../Character/enemy.h"
#include "../Character/player.h"
#include "../Item/item.h"
#include "../Display/textdisplay.h"
#include "../Display/graphicsdisplay.h"
#include "../Item/stair.h"
#include "../Item/potion.h"
#include "../Item/gold.h"
#include <ncurses.h>
using namespace std;
//std::sort (myvector.begin()+4, myvector.end(), myfunction);
bool gridCompare(Enemy* left, Enemy* right){
	if(left->getRow()==right->getRow()){
		return (left->getColumn()<right->getColumn());
	} else {
		return (left->getRow()<right->getRow());
	}
}

Grid::Grid(): PC{nullptr}, td{new TextDisplay}, floor{0} {
	vector<string> map{
		"|-----------------------------------------------------------------------------|",
		"|                                                                             |",
		"| |--------------------------|        |-----------------------|               |",
		"| |..........................|        |.......................|               |",
		"| |..........................+########+.......................|-------|       |",
		"| |..........................|   #    |...............................|--|    |",
		"| |..........................|   #    |..................................|--| |",
		"| |----------+---------------|   #    |----+----------------|...............| |",
		"|            #                 #############                |...............| |",
		"|            #                 #     |-----+------|         |...............| |",
		"|            #                 #     |............|         |...............| |",
		"|            ###################     |............|   ######+...............| |",
		"|            #                 #     |............|   #     |...............| |",
		"|            #                 #     |-----+------|   #     |--------+------| |",
		"|  |---------+-----------|     #           #          #              #        |",
		"|  |.....................|     #           #          #         |----+------| |",
		"|  |.....................|     ########################         |...........| |",
		"|  |.....................|     #           #                    |...........| |",
		"|  |.....................|     #    |------+--------------------|...........| |",
		"|  |.....................|     #    |.......................................| |",
		"|  |.....................+##########+.......................................| |",
		"|  |.....................|          |.......................................| |",
		"|  |---------------------|          |---------------------------------------| |",
		"|                                                                             |",
		"|-----------------------------------------------------------------------------|"
	};
	for (int i = 0; i < 25; ++i){
		vector<Cell*> temp;
		for(int j=0; j<79; ++j){
			if (map[i][j]=='|'){
				temp.emplace_back(new VirticalWall{i,j});
			} else if (map[i][j]=='-'){
				temp.emplace_back(new HorizontalWall{i,j});
			} else if (map[i][j]=='.'){
				temp.emplace_back(new FloorTile{i,j});
			} else if (map[i][j]=='+'){
				temp.emplace_back(new DoorWay{i,j});
			} else if (map[i][j]=='#'){
				temp.emplace_back(new Passage{i,j});
			} else if (map[i][j]==' '){
				temp.emplace_back(new Space{i,j});
			}
		}
		theGrid.emplace_back(temp);
	}
	for (int i = 0; i < 25; ++i){
		for(int j=0; j<79; ++j){
			theGrid[i][j]->attachObserver(td);
		}
	}
}

void Grid::open(const string& filename){
	ifstream file;
	file.exceptions(ios::failbit|ios::eofbit);
	try {
		file.open(filename);
		for (int n = 0; n < 5 ; ++n){
			for (int i = 0; i < 25; ++i){
				string s;
				getline(file, s);
				sourceMap.emplace_back(s);
			}
		}
		sourceGiven=true;
	} catch (...) {
		cerr<<filename<<" does not exist or has error in it. Character/Item generations will be random." << endl;
	}
}

Grid::Grid(Display *dpy, Window & w, GC &gc): PC{nullptr}, td{new TextDisplay}, gd{new GraphicsDisplay{dpy, w, gc}}, floor{0} {
	vector<string> map{
		"|-----------------------------------------------------------------------------|",
		"|                                                                             |",
		"| |--------------------------|        |-----------------------|               |",
		"| |..........................|        |.......................|               |",
		"| |..........................+########+.......................|-------|       |",
		"| |..........................|   #    |...............................|--|    |",
		"| |..........................|   #    |..................................|--| |",
		"| |----------+---------------|   #    |----+----------------|...............| |",
		"|            #                 #############                |...............| |",
		"|            #                 #     |-----+------|         |...............| |",
		"|            #                 #     |............|         |...............| |",
		"|            ###################     |............|   ######+...............| |",
		"|            #                 #     |............|   #     |...............| |",
		"|            #                 #     |-----+------|   #     |--------+------| |",
		"|  |---------+-----------|     #           #          #              #        |",
		"|  |.....................|     #           #          #         |----+------| |",
		"|  |.....................|     ########################         |...........| |",
		"|  |.....................|     #           #                    |...........| |",
		"|  |.....................|     #    |------+--------------------|...........| |",
		"|  |.....................|     #    |.......................................| |",
		"|  |.....................+##########+.......................................| |",
		"|  |.....................|          |.......................................| |",
		"|  |---------------------|          |---------------------------------------| |",
		"|                                                                             |",
		"|-----------------------------------------------------------------------------|"
	};
	for (int i = 0; i < 25; ++i){
		vector<Cell*> temp;
		for(int j=0; j<79; ++j){
			if (map[i][j]=='|'){
				temp.emplace_back(new VirticalWall{i,j});
			} else if (map[i][j]=='-'){
				temp.emplace_back(new HorizontalWall{i,j});
			} else if (map[i][j]=='.'){
				temp.emplace_back(new FloorTile{i,j});
			} else if (map[i][j]=='+'){
				temp.emplace_back(new DoorWay{i,j});
			} else if (map[i][j]=='#'){
				temp.emplace_back(new Passage{i,j});
			} else if (map[i][j]==' '){
				temp.emplace_back(new Space{i,j});
			}
		}
		theGrid.emplace_back(temp);
	}
	for (int i = 0; i < 25; ++i){
		for(int j=0; j<79; ++j){
			theGrid[i][j]->attachObserver(td);
			if(i<23&&i>=2&&j<77&&j>=2) theGrid[i][j]->attachObserver(gd);
		}
	}
}

Grid::~Grid(){
	if(PC!=nullptr){
		PC->setDestroyable();
	}
	delete PC;
	delete td;
	delete gd;
	for(unsigned int i=0; i<enemies.size(); ++i){
		delete enemies[i];
	}
	for(int i=0; i<25; ++i){
		for(int j=0; j<79; ++j){
			delete theGrid[i][j];
		}
	}
}

bool Grid::end() const{
	return (gameLost||gameWon);
}

void Grid::newFloor(){
	Player* temp = PC->getBasePlayer();
	if(PC->getPotionLayer()>0){
		delete PC;
	}
	PC = temp;
	PC->notifyStatusObservers();
	for(unsigned int i=0; i<enemies.size(); ++i){
		delete enemies[i];
	}
	enemies.clear();
	for(int i=0; i<25; ++i){
		for(int j=0; j<79; ++j){
			theGrid[i][j]->detach();
		}
	}
	++floor;
	td->setFloor(floor);
	if(gd!=nullptr)gd->setFloor(floor);
	if(!sourceGiven){
		spawn();
	} else {
		spawnFromSource();
	}
}

void Grid::newGame(const string& rc){
	floor = 0;
	if(PC!=nullptr){
		PC->setDestroyable();
	}
	delete PC;
	if (rc=="h"){
		PC = new Human;
		td->setRace("Human");
		if(gd!=nullptr)gd->setRace("Human");
	} else if(rc=="d"){
		PC = new Dwarf;
		td->setRace("Dwarf");
		if(gd!=nullptr)gd->setRace("Dwarf");
	} else if(rc=="e"){
		PC = new Elf;
		td->setRace("Elf  ");
		if(gd!=nullptr)gd->setRace("Elf  ");
	} else if(rc=="o"){
		PC = new Orc;
		td->setRace("Orc  ");
		if(gd!=nullptr)gd->setRace("Orc  ");
	}
	PC->attach(td);
	if(gd!=nullptr)PC->attach(gd);
	newFloor();
}

void Grid::clear(){
	gameLost = false;
	gameWon = false;
	td->action("");
	if(gd!=nullptr)gd->action("");
	for(unsigned int i=0; i<enemies.size(); ++i){
		delete enemies[i];
	}
	enemies.clear();
	for(int i=0; i<25; ++i){
		for(int j=0; j<79; ++j){
			theGrid[i][j]->detach();
		}
	}
	if(gd!=nullptr){
		gd->clear();
		gd->clearMsg();
	}
}

void Grid::enemyTurn(){
	for(auto e : enemies){
		if(e->isClosedTo(PC)){
			if (!PC->attackedBy(e)) gameLost = true;
		} else {
			int r=e->getRow();
			int c=e->getColumn();
			vector<Cell*> nextpos;
			for(int i=r-1; i<=r+1; ++i){
				for(int j=c-1; j<=c+1; ++j){
					if ((r!=i||c!=j)&&theGrid[i][j]->isFloorTile()&&theGrid[i][j]->getStanding()==nullptr&&theGrid[i][j]->getLocating()==nullptr) nextpos.emplace_back(theGrid[i][j]);
				}
			}
			if (nextpos.size()>0) e->moveTo(nextpos[rand()%nextpos.size()]);
		}
	}
	sort(enemies.begin(), enemies.end(), gridCompare);
	if(gd!=nullptr){
		//notifyGraphics();
		gd->clearMsg();
		gd->print();
	}
}

Cell* Grid::targetCell(const string& dir) const{
	int r=PC->getRow();
	int c=PC->getColumn();
	Cell* target=PC->getStand();
	if (dir=="no"){
		target=theGrid[r-1][c];
	} else if (dir=="so"){
		target=theGrid[r+1][c];
	} else if (dir=="ea"){
		target=theGrid[r][c+1];
	} else if (dir=="we"){
		target=theGrid[r][c-1];
	} else if (dir=="ne"){
		target=theGrid[r-1][c+1];
	} else if (dir=="nw"){
		target=theGrid[r-1][c-1];
	} else if (dir=="se"){
		target=theGrid[r+1][c+1];
	} else if (dir=="sw"){
		target=theGrid[r+1][c-1];
	}
	return target;
}

bool Grid::validMove(const string& dir) const{
	Cell* target=targetCell(dir);
	if (PC->getStand()==target)return false;
	if (target->isDoorWay()||target->isPassage()) return true;
	if (target->isFloorTile()){
		if(target->getStanding()!=nullptr){
			return false;
		} else if(target->getLocating()==nullptr || target->getLocating()->Collectable()) {
			return true;
		} else {return false;}
	}
	return false;
}

bool Grid::validAttack(const string& dir) const{
	Cell* target=targetCell(dir);
	if (PC->getStand()==target)return false;
	if (target->getStanding()!=nullptr) return true;
	return false;
}

bool Grid::validUse(const string& dir) const{
	Cell* target=targetCell(dir);
	if (PC->getStand()==target)return false;
	if (target->isDoorWay()||target->isPassage()) return false;
	if (target->isFloorTile()){
		if(target->getStanding()!=nullptr){
			return false;
		} else if(target->getLocating()!=nullptr && target->getLocating()->getSym()=='P') {
			return true;
		} else {return false;}
	}
	return false;
}

void Grid::move(string& dir){
	Cell* target = targetCell(dir);
	if (dir=="no"){
		dir="north";
	} else if (dir=="so"){
		dir="south";
	} else if (dir=="ea"){
		dir="east";
	} else if (dir=="we"){
		dir="west";
	} else if (dir=="ne"){
		dir="northeast";
	} else if (dir=="nw"){
		dir="northwest";
	} else if (dir=="se"){
		dir="southeast";
	} else if (dir=="sw"){
		dir="southwest";
	}
	td->action("PC moves "+dir+". ");
	if(gd!=nullptr)gd->action("PC moves "+dir+". ");
	if (target->getLocating()==nullptr){
	} else if (target->getLocating()->getSym()=='\\'){
		target->detach();
		PC->moveTo(target);
		if (floor == 5){
			gameWon = true;
			return;
		}
		newFloor();
		return;
	} else {
		target->getLocating()->pickedUpBy(PC);
	}
	target->detach();
	PC->moveTo(target);
	detect();
	enemyTurn();
}

void Grid::attack(const string& dir){
	Cell* target = targetCell(dir);
	if (!target->getStanding()->attackedBy(PC)) {
		for (auto e = enemies.begin(); e < enemies.end(); ++e){
			if (((*e)->getRow() == target->getRow()) && ((*e)->getColumn() == target->getColumn())){
				delete *e;
				enemies.erase(e);
				break;
			}
		}
	}
	enemyTurn();
}

void Grid::use(const string& dir){
	Cell* target = targetCell(dir);
	target->getLocating()->usedBy(PC);
	target->detach();
	PC->moveTo(target);
	if (PC->getHP()==0){
		gameLost = true;
		return;
	}
	enemyTurn();
}

void Grid::buy(){
	int r = PC->getRow();
	int c = PC->getColumn();
	for(int i=r-1; i<=r+1; ++i){
		for(int j=c-1; j<=c+1; ++j){
			if((theGrid[i][j]->getRow()!=r||theGrid[i][j]->getColumn()!=c)&&(theGrid[i][j]->getStanding()!=nullptr)){
				td->action("");
				theGrid[i][j]->getStanding()->sellTo(PC);
			}
		}
	}
	enemyTurn();
}

void Grid::spawn(){
	if(gd!=nullptr) gd->clear();
	chamberInit();
	//PC spawn
	int random=rand()%5;
	int cellrand=rand()%chambers[random].size();
	chambers[random][cellrand]->attach(PC);
	chambers[random].erase(chambers[random].begin() + cellrand);
	int random_stair=rand()%5;
	//stair spawn
	while(random_stair==random){random_stair=rand()%5;}
	cellrand=rand()%chambers[random_stair].size();
	new Stair{chambers[random_stair][cellrand]};
	chambers[random_stair].erase(chambers[random_stair].begin() + cellrand);
	//potion spawn
	int potrand;
	for (int i=0; i<10; ++i){
		random=rand()%5;
		cellrand=rand()%chambers[random].size();
		potrand=rand()%6;
		if (potrand==0){
			Potion * p = new RH{chambers[random][cellrand]};
			p->attachObserver(td);
			if(gd!=nullptr)p->attachObserver(gd);
			chambers[random].erase(chambers[random].begin() + cellrand);
		} else if (potrand==1){
			Potion * p = new BA{chambers[random][cellrand]};
			p->attachObserver(td);
			if(gd!=nullptr)p->attachObserver(gd);
			chambers[random].erase(chambers[random].begin() + cellrand);
		} else if (potrand==2){
			Potion * p = new BD{chambers[random][cellrand]};
			p->attachObserver(td);
			if(gd!=nullptr)p->attachObserver(gd);
			chambers[random].erase(chambers[random].begin() + cellrand);
		} else if (potrand==3){
			Potion * p = new PH{chambers[random][cellrand]};
			p->attachObserver(td);
			if(gd!=nullptr)p->attachObserver(gd);
			chambers[random].erase(chambers[random].begin() + cellrand);
		} else if (potrand==4){
			Potion * p = new WA{chambers[random][cellrand]};
			p->attachObserver(td);
			if(gd!=nullptr)p->attachObserver(gd);
			chambers[random].erase(chambers[random].begin() + cellrand);
		} else {
			Potion * p = new WD{chambers[random][cellrand]};
			p->attachObserver(td);
			if(gd!=nullptr)p->attachObserver(gd);
			chambers[random].erase(chambers[random].begin() + cellrand);
		}
	}
	//gold spawn
	for (int i=0; i<10; ++i){
		potrand=rand()%8;
		if (potrand<5){
			random=rand()%5;
			cellrand=rand()%chambers[random].size();
			Gold* g = new NormalPiece{chambers[random][cellrand]};
			g->attachObserver(td);
			if(gd!=nullptr)g->attachObserver(gd);
			chambers[random].erase(chambers[random].begin() + cellrand);
		} else if (potrand<7){
			random=rand()%5;
			cellrand=rand()%chambers[random].size();
			Gold* g = new SmallHoard{chambers[random][cellrand]};
			g->attachObserver(td);
			if(gd!=nullptr)g->attachObserver(gd);
			chambers[random].erase(chambers[random].begin() + cellrand);
		} else {
			vector<Cell*> dragonpos;
			while (dragonpos.size()==0) {
				random=rand()%5;
				cellrand=rand()%chambers[random].size();
				for(auto cll : chambers[random]){
					if (((cll)!=chambers[random][cellrand])&&
						((cll)->getRow()-chambers[random][cellrand]->getRow()<2)&&
						((cll)->getRow()-chambers[random][cellrand]->getRow()>-2)&&
						((cll)->getColumn()-chambers[random][cellrand]->getColumn()<2)&&
						((cll)->getColumn()-chambers[random][cellrand]->getColumn()>-2)){
						dragonpos.emplace_back(cll);
					}
				}
			}
			int dragonrand = rand()%dragonpos.size();
			Enemy* e = new Dragon{chambers[random][cellrand]};
			e->attach(td);
			if(gd!=nullptr)e->attach(gd);
			enemies.emplace_back(e);
			dragonpos[dragonrand]->attach(e);
			Gold* g = new DragonHoard{chambers[random][cellrand]};
			g->attachObserver(td);
			if(gd!=nullptr)g->attachObserver(gd);
			chambers[random].erase(chambers[random].begin() + cellrand);
			for(unsigned int i=0; i<chambers[random].size(); ++i){
				if (chambers[random][i] == dragonpos[dragonrand]){
					chambers[random].erase(chambers[random].begin()+i);
				}
			}
		}
		if (chambers[random].size()==0) chambers.erase(chambers.begin()+random);
	}
	//enemy spawn
	while (enemies.size()<=20){
		potrand=rand()%18;
		random=rand()%5;
		cellrand=rand()%chambers[random].size();
		if (potrand<3){
			Enemy* e = new Vampire;
			enemies.emplace_back(e);
			chambers[random][cellrand]->attach(e);
			chambers[random].erase(chambers[random].begin() + cellrand);
			e->attach(td);
			if(gd!=nullptr)e->attach(gd);
		} else if (potrand<7){
			Enemy* e = new Werewolf;
			enemies.emplace_back(e);
			chambers[random][cellrand]->attach(e);
			chambers[random].erase(chambers[random].begin() + cellrand);
			e->attach(td);
			if(gd!=nullptr)e->attach(gd);
		} else if (potrand<9){
			Enemy* e = new Troll;
			enemies.emplace_back(e);
			chambers[random][cellrand]->attach(e);
			chambers[random].erase(chambers[random].begin() + cellrand);
			e->attach(td);
			if(gd!=nullptr)e->attach(gd);
		} else if (potrand<14){
			Enemy* e = new Goblin;
			enemies.emplace_back(e);
			chambers[random][cellrand]->attach(e);
			chambers[random].erase(chambers[random].begin() + cellrand);
			e->attach(td);
			if(gd!=nullptr)e->attach(gd);
		} else if (potrand<16){
			Enemy* e = new Phoenix;
			enemies.emplace_back(e);
			chambers[random][cellrand]->attach(e);
			chambers[random].erase(chambers[random].begin() + cellrand);
			e->attach(td);
			if(gd!=nullptr)e->attach(gd);
		} else {
			Enemy* e = new Merchant;
			enemies.emplace_back(e);
			chambers[random][cellrand]->attach(e);
			chambers[random].erase(chambers[random].begin() + cellrand);
			e->attach(td);
			if(gd!=nullptr)e->attach(gd);
		}
		if (chambers[random].size()==0) chambers.erase(chambers.begin()+random);
	}
	sort(enemies.begin(), enemies.end(), gridCompare);
	td->action("Player character has spawned.");
	if(gd!=nullptr){
		gd->action("Player character has spawned.");
		//notifyGraphics();
	}
}

void Grid::spawnFromSource(){
	if(gd!=nullptr) gd->clear();
	for (int i=0; i<25; ++i){
		for (int j=0; j<79; ++j){
			char c = sourceMap[(floor-1)*25+i][j];
			if(c=='@'){
				theGrid[i][j]->attach(PC);
			} else if(c=='\\'){
				new Stair{theGrid[i][j]};
			} else if(c=='0'){
				Potion * p = new RH{theGrid[i][j]};
				p->attachObserver(td);
				if(gd!=nullptr)p->attachObserver(gd);
			} else if(c=='1'){
				Potion * p = new BA{theGrid[i][j]};
				p->attachObserver(td);
				if(gd!=nullptr)p->attachObserver(gd);
			} else if(c=='2'){
				Potion * p = new BD{theGrid[i][j]};
				p->attachObserver(td);
				if(gd!=nullptr)p->attachObserver(gd);
			} else if(c=='3'){
				Potion * p = new PH{theGrid[i][j]};
				p->attachObserver(td);
				if(gd!=nullptr)p->attachObserver(gd);
			} else if(c=='4'){
				Potion * p = new WA{theGrid[i][j]};
				p->attachObserver(td);
				if(gd!=nullptr)p->attachObserver(gd);
			} else if(c=='5'){
				Potion * p = new WD{theGrid[i][j]};
				p->attachObserver(td);
				if(gd!=nullptr)p->attachObserver(gd);
			} else if(c=='6'){
				Gold* g = new NormalPiece{theGrid[i][j]};
				g->attachObserver(td);
				if(gd!=nullptr)g->attachObserver(gd);
			} else if(c=='7'){
				Gold* g = new SmallHoard{theGrid[i][j]};
				g->attachObserver(td);
				if(gd!=nullptr)g->attachObserver(gd);
			} else if(c=='8'){
				Gold* g = new MerchantHoard{theGrid[i][j]};
				g->attachObserver(td);
				if(gd!=nullptr)g->attachObserver(gd);
			} else if(c=='9'){
				Enemy* e = new Dragon{theGrid[i][j]};
				e->attach(td);
				if(gd!=nullptr)e->attach(gd);
				enemies.emplace_back(e);
				for (int r = i+1; r >= i-1; --r){
					for (int c = j+1; c >= j-1; --c){
						if(sourceMap[(floor-1)*25+r][c]=='D'){
							theGrid[r][c]->attach(e);
							break;
						}
					}
				}
				Gold* g = new DragonHoard{theGrid[i][j]};
				g->attachObserver(td);
				if(gd!=nullptr)g->attachObserver(gd);
			} else if(c=='V'){
				Enemy* e = new Vampire;
				enemies.emplace_back(e);
				theGrid[i][j]->attach(e);
				e->attach(td);
				if(gd!=nullptr)e->attach(gd);
			} else if(c=='W'){
				Enemy* e = new Werewolf;
				enemies.emplace_back(e);
				theGrid[i][j]->attach(e);
				e->attach(td);
				if(gd!=nullptr)e->attach(gd);
			} else if(c=='T'){
				Enemy* e = new Troll;
				enemies.emplace_back(e);
				theGrid[i][j]->attach(e);
				e->attach(td);
				if(gd!=nullptr)e->attach(gd);
			} else if(c=='N'){
				Enemy* e = new Goblin;
				enemies.emplace_back(e);
				theGrid[i][j]->attach(e);
				e->attach(td);
				if(gd!=nullptr)e->attach(gd);
			} else if(c=='X'){
				Enemy* e = new Phoenix;
				enemies.emplace_back(e);
				theGrid[i][j]->attach(e);
				e->attach(td);
				if(gd!=nullptr)e->attach(gd);
			} else if(c=='M'){
				Enemy* e = new Merchant;
				enemies.emplace_back(e);
				theGrid[i][j]->attach(e);
				e->attach(td);
				if(gd!=nullptr)e->attach(gd);
			}
		}
	}
	sort(enemies.begin(), enemies.end(), gridCompare);
	td->action("Player character has spawned.");
	if(gd!=nullptr){
		gd->action("Player character has spawned.");
		//notifyGraphics();
	}
}

void Grid::chamberInit(){
	chambers.clear();
	vector<Cell*> chamber1,chamber2,chamber3,chamber4,chamber5;
	for (int i=3; i<7; ++i){
		for (int j=3; j<29; ++j){
			chamber1.emplace_back(theGrid[i][j]);
		}
	}
	for (int i=15; i<22; ++i){
		for (int j=4; j<25; ++j){
			chamber2.emplace_back(theGrid[i][j]);
		}
	}
	for (int i=10; i<13; ++i){
		for (int j=38; j<50; ++j){
			chamber3.emplace_back(theGrid[i][j]);
		}
	}
	for (int i=16; i<19; ++i){
		for (int j=65; j<76; ++j){
			chamber4.emplace_back(theGrid[i][j]);
		}
	}
	for (int i=19; i<22; ++i){
		for (int j=37; j<76; ++j){
			chamber4.emplace_back(theGrid[i][j]);
		}
	}
	for (int i=3; i<5; ++i){
		for (int j=39; j<62; ++j){
			chamber5.emplace_back(theGrid[i][j]);
		}
	}
	for (int j=39; j<70; ++j){
		chamber5.emplace_back(theGrid[5][j]);
	}
	for (int j=39; j<73; ++j){
		chamber5.emplace_back(theGrid[6][j]);
	}
	for (int i=7; i<13; ++i){
		for (int j=61; j<76; ++j){
			chamber5.emplace_back(theGrid[i][j]);
		}
	}
	chambers.emplace_back(chamber1);
	chambers.emplace_back(chamber2);
	chambers.emplace_back(chamber3);
	chambers.emplace_back(chamber4);
	chambers.emplace_back(chamber5);
}

void Grid::detect()const{
	int r = PC->getRow();
	int c = PC->getColumn();
	for(int i=r-1; i<=r+1; ++i){
		for(int j=c-1; j<=c+1; ++j){
			if(theGrid[i][j]->getRow()!=r||theGrid[i][j]->getColumn()!=c){
				if (theGrid[i][j]->getLocating()!=nullptr){
					theGrid[i][j]->getLocating()->sawBy(PC);
				} else if (theGrid[i][j]->getStanding()!=nullptr){
					theGrid[i][j]->getStanding()->sawBy(PC);
				}
			}
		}
	}
}

void Grid::notifyGraphics(){
	int r = PC->getRow();
	int c = PC->getColumn();
	for(int i=r-3; i<=r+3; ++i){
		if(i>=23) break;
		if(i<2) continue;
		for(int j=c-3; j<=c+3; ++j){
			if(j>=77) break;
			if(j<2) continue;
			if(i==r-3||i==r+3||j==c-3||j==c+3){
				gd->notifybound(theGrid[i][j]);
			} else {
				gd->notify(theGrid[i][j]);
			}
		}
	}
}

void Grid::refreshScreen(){
	gd->refreshScreen();
}

ostream &operator<<(ostream &out, const Grid &g){
	out << *(g.td);
	if (g.gameLost) out << "You've lost!! Try harder next time!" << endl;
	if (g.gameWon) out << "You've won!! Congratulations!" << endl << "Your Score is: " << g.PC->score() << endl;
	return out;
}

void print(const Grid &g){
	mvprintw(25,0,"Race:");
	mvprintw(25,14,"Gold:");
	mvprintw(25,72,"Floor");
	mvprintw(26,0,"HP:");
	mvprintw(27,0,"Atk:");
	mvprintw(28,0,"Def:");
	mvprintw(29,0,"Action:");
	//print(*(g.td), g.PC);
}

#include "textdisplay.h"
#include "../Factory/cell.h"
#include "../Character/enemy.h"
#include "../Character/player.h"
#include "../Item/item.h"
#include "../Item/gold.h"
#include "../Item/potion.h"
#include <ncurses.h>
using namespace std;

TextDisplay::TextDisplay(string race, string gold, int floor, int HP, int Atk, int Def):
	theDisplay{
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
	}, race{race}, gold{gold}, floor{floor}, HP{HP}, Atk{Atk}, Def{Def} {}

void TextDisplay::setFloor(int newfloor){
	floor = newfloor;
	Action = "";
}
void TextDisplay::setRace(string r){
	race=r;
}

void TextDisplay::notify(Cell *c){
	if(c->getStanding()!=nullptr){
		theDisplay[c->getRow()][c->getColumn()]=c->getStanding()->getSym();
	} else if(c->getLocating()!=nullptr){
		theDisplay[c->getRow()][c->getColumn()]=c->getLocating()->getSym();
	} else {
		theDisplay[c->getRow()][c->getColumn()]=c->getSym();
	}
}

void TextDisplay::notify(Enemy *e, int damage){
	Action=Action+e->getSym()+" deals "+to_string(damage)+" damage to PC. ";
}

void TextDisplay::notify(Player *p, Character *e, int damage) {
	Action="PC deals "+to_string(damage)+" damage to "+e->getSym()+"("+to_string(e->getHP()-damage)+")"+". ";
}

void TextDisplay::notify(Player *p) {
	gold=p->getGoldValue();
	HP=p->getHP();
	Atk=p->getAtk();
	Def=p->getDef();
}

void TextDisplay::notify(Enemy *e){
	Action=Action+e->getSym()+" attacked PC but missed. ";
}

void TextDisplay::notify(Gold *e, string name){
	Action=Action+"PC picked up "+name+". ";
}

void TextDisplay::notify(Potion *p, std::string name){
	if (p->getLocate()!=nullptr){
		Action="PC used a "+name+". ";
	} else {
		Action="PC purchased a "+name+". ";
	}
}
void TextDisplay::saw(Potion *p, std::string name){
	if (p->getLocate()!=nullptr){
		Action=Action+"PC sees a "+name+". ";
	} else {
		Action=Action+"PC sees a Merchant selling a "+name+" for 2 gold. ";
	}
}

void TextDisplay::action(string msg){
	Action = msg;
}

ostream &operator<<(ostream &out, const TextDisplay &td){
	for(unsigned int i=0; i<td.theDisplay.size(); ++i){
		out << td.theDisplay[i] << endl;
	}
	out << "Race: " << td.race << "   Gold: " << td.gold;
	out << "                                                   Floor " << td.floor << endl;
	out << "HP: " << td.HP << endl;
	out << "Atk: " << td.Atk << endl;
	out << "Def: " << td.Def << endl;
	out << "Action: " << td.Action << endl;
	return out;
}

void print(const TextDisplay &td, Player* PC){
	if(PC==nullptr){for(unsigned int i=0; i<td.theDisplay.size(); ++i){
		mvprintw(i,0,td.theDisplay[i].c_str());
	}}else{
	int row = PC->getRow();
	int column = PC->getColumn();
	for(int i=0; i<25; ++i){
		for(int j=0; j<79; ++j){
			if (i>row-5&&i<row+5&&j>column-5&&j<column+5){
				char tab[1] = {td.theDisplay[i][j]};
				mvprintw(i,j,tab);
			} else {
				mvprintw(i,j," ");
			}
	}}
	}
	/*for(unsigned int i=0; i<td.theDisplay.size(); ++i){
		mvprintw(i,0,td.theDisplay[i].c_str());
	}*/
	mvprintw(25,6,td.race.c_str());
	mvprintw(25,20,(td.gold+" ").c_str());
	mvprintw(25,78,(to_string(td.floor)+"  ").c_str());
	mvprintw(26,4,(to_string(td.HP)+" ").c_str());
	mvprintw(27,5,(to_string(td.Atk)+" ").c_str());
	mvprintw(28,5,(to_string(td.Def)+" ").c_str());
	mvprintw(29,8,(td.Action+"                                                                                                                                                  ").c_str());
}

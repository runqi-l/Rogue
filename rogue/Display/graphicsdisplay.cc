#include "graphicsdisplay.h"
#include "../Factory/cell.h"
#include "../Character/enemy.h"
#include "../Character/player.h"
#include "../Item/item.h"
#include "../Item/gold.h"
#include "../Item/potion.h"
#include <ncurses.h>
using namespace std;

GraphicsDisplay::GraphicsDisplay(Display *dpy, Window & w, GC & gc, string race, string gold, int floor, int HP, int Atk, int Def):
	dpy{dpy}, w{w}, gc{gc}, race{race}, gold{gold}, floor{floor}, HP{HP}, Atk{Atk}, Def{Def} {
		/*w.drawString(0, 8*24*2+2, "Race:", Xwindow::Black);
		w.drawString(150, 8*24*2+2, "Gold:", Xwindow::Black);
		w.drawString(1000, 8*24*2+2, "Floor:", Xwindow::Black);
		w.drawString(0, 8*24*2+17, "HP:", Xwindow::Black);
		w.drawString(0, 8*24*2+32, "Atk:", Xwindow::Black);
		w.drawString(0, 8*24*2+47, "Def:", Xwindow::Black);
		w.drawString(0, 8*24*2+62, "Action", Xwindow::Black);*/
		char black_bits[] = "#000000";
		char white_bits[] = "#FFFFFF";
		char red_bits[] = "#FF0000";
		char green_bits[] = "#00FF00";
		char blue_bits[] = "#0000FF";
		char yellow_bits[] = "#FFFF00";
		// Define the colors we want to use
		colormap = DefaultColormap(dpy, 0);
		XParseColor(dpy, colormap, black_bits, &black_col); XAllocColor(dpy, colormap, &black_col);
		XParseColor(dpy, colormap, white_bits, &white_col); XAllocColor(dpy, colormap, &white_col);
		XParseColor(dpy, colormap, red_bits, &red_col); XAllocColor(dpy, colormap, &red_col);
		XParseColor(dpy, colormap, green_bits, &green_col);XAllocColor(dpy, colormap, &green_col);
		XParseColor(dpy, colormap, blue_bits, &blue_col);XAllocColor(dpy, colormap, &blue_col);
		XParseColor(dpy, colormap, yellow_bits, &yellow_col);XAllocColor(dpy, colormap, &yellow_col);
		
	}
	
GraphicsDisplay::~GraphicsDisplay(){}

void GraphicsDisplay::setFloor(int newfloor){
	floor = newfloor;
	
	/*w.fillRectangle(1070-1, 8*24*2+2-13, 100, 15, Xwindow::White);
	
	w.drawString(1070, 8*24*2+2, to_string(floor), Xwindow::Blue);*/
	Action = "";
}
void GraphicsDisplay::setRace(string r){
	race=r;
	
	/*w.fillRectangle(50-1, 8*24*2+2-13, 100, 15, Xwindow::White);
	
	w.drawString(50, 8*24*2+2, race, Xwindow::Blue);*/
}
void GraphicsDisplay::notifybound(Cell* c){
	int i = c->getRow();
	int j = c->getColumn();
	/*if(c->getSym()=='|'||c->getSym()=='-'){
		w.fillRectangle((j-2)*blockWidth*pixel, (i-2)*blockHeight*pixel, blockWidth*pixel, blockHeight*pixel, Xwindow::Orange);
		return;
	} else if (c->getSym()=='+'||c->getSym()=='#'){
		w.fillRectangle((j-2)*blockWidth*pixel, (i-2)*blockHeight*pixel, blockWidth*pixel, blockHeight*pixel, Xwindow::Blue);
		return;
	} else if (c->getSym()=='.'){
		w.fillRectangle((j-2)*blockWidth*pixel, (i-2)*blockHeight*pixel, blockWidth*pixel, blockHeight*pixel, Xwindow::Blue);
	}
	if(c->getLocating()!=nullptr){
		if(c->getLocating()->getSym()=='\\'){
			drawStair(i-2,j-2);
		} else if (c->getLocating()->getSym()=='G'){
			drawTreasure(i-2,j-2,4);
		} else if(c->getLocating()->getSym()=='P'){
			drawPotion(i-2,j-2,4);
		}
	}*/
}
void GraphicsDisplay::notify(Cell *c){
	int i = c->getRow();
	int j = c->getColumn();
	if(c->getStanding()!=nullptr){
		drawFloor(i-2,j-2);
		if(c->getStanding()->getSym()=='@'){
			drawPC(i-2,j-2);
		} else if(c->getStanding()->getSym()=='V'){
			drawVampire(i-2,j-2);
		} else if(c->getStanding()->getSym()=='W'){
			drawWerewolf(i-2,j-2);
		} else if(c->getStanding()->getSym()=='T'){
			drawTroll(i-2,j-2);
		} else if(c->getStanding()->getSym()=='N'){
			drawGoblin(i-2,j-2);
		} else if(c->getStanding()->getSym()=='X'){
			drawPhoenix(i-2,j-2);
		} else if(c->getStanding()->getSym()=='M'){
			drawMerchant(i-2,j-2);
		} else if(c->getStanding()->getSym()=='D'){
			drawDragon(i-2,j-2);
		}
	} else if(c->getLocating()!=nullptr){
		drawFloor(i-2,j-2);
		if(c->getLocating()->getSym()=='P'){
			drawPotion(i-2,j-2);
		} else if(c->getLocating()->getSym()=='G'){
			drawTreasure(i-2,j-2);
		} else if(c->getLocating()->getSym()=='\\'){
			drawStair(i-2,j-2);
		}
	} else {
		if(c->getSym()=='|'||c->getSym()=='-'){
			drawWall(i-2,j-2);
		} else if (c->getSym()=='.'||c->getSym()=='+'||c->getSym()=='#'){
			drawFloor(i-2,j-2);
		}
	}
}

void GraphicsDisplay::notify(Enemy *e, int damage){
	Action=Action+e->getSym()+" deals "+to_string(damage)+" damage to PC. ";
}

void GraphicsDisplay::notify(Player *p, Character *e, int damage) {
	Action="PC deals "+to_string(damage)+" damage to "+e->getSym()+"("+to_string(e->getHP()-damage)+")"+". ";
}

void GraphicsDisplay::notify(Player *p) {
	gold=p->getGoldValue();
	HP=p->getHP();
	Atk=p->getAtk();
	Def=p->getDef();
	
	/*w.fillRectangle(200-1, 8*24*2+2-13, 100, 15, Xwindow::White);
	w.fillRectangle(50-1, 8*24*2+17-13, 100, 45, Xwindow::White);
	
	w.drawString(200, 8*24*2+2, gold, Xwindow::Blue);
	w.drawString(50, 8*24*2+17, to_string(HP), Xwindow::Blue);
	w.drawString(50, 8*24*2+32, to_string(Atk), Xwindow::Blue);
	w.drawString(50, 8*24*2+47, to_string(Def), Xwindow::Blue);*/
}

void GraphicsDisplay::notify(Enemy *e){
	Action=Action+e->getSym()+" attacked PC but missed. ";
}

void GraphicsDisplay::notify(Gold *e, string name){
	Action=Action+"PC picked up "+name+". ";
}

void GraphicsDisplay::notify(Potion *p, std::string name){
	if (p->getLocate()!=nullptr){
		Action="PC used a "+name+". ";
	} else {
		Action="PC purchased a "+name+". ";
	}
}
void GraphicsDisplay::saw(Potion *p, std::string name){
	if (p->getLocate()!=nullptr){
		Action=Action+"PC sees a "+name+". ";
	} else {
		Action=Action+"PC sees a Merchant selling a "+name+" for 2 gold. ";
	}
}

void GraphicsDisplay::action(string msg){
	Action = msg;
}

void GraphicsDisplay::drawWall(int row, int column){
	/*vector<string> icon {
		"110110110",
		"000000000",
		"011011011",
		"000000000",
		"110110110",
		"000000000",
		"011011011",
		"000000000"
		
	};
	for (int i = 0; i < blockHeight; ++i) {
		for (int j = 0; j < blockWidth; ++j){
			if(icon[i][j]=='1') {
				w.fillRectangle((column*blockWidth+j)*pixel, (row*blockHeight+i)*pixel, pixel, pixel, Xwindow::White);
			} else {
				w.fillRectangle((column*blockWidth+j)*pixel, (row*blockHeight+i)*pixel, pixel, pixel, Xwindow::Black);
				}
		}
	}*/
	
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+5)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+8)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+4)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+5)*pixel, (row*blockHeight+4)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+8)*pixel, (row*blockHeight+4)*pixel, 1*pixel, 1*pixel);
	
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+2)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+2)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+6)*pixel, (row*blockHeight+2)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+6)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+6)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+6)*pixel, (row*blockHeight+6)*pixel, 1*pixel, 1*pixel);
	
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+1)*pixel, 9*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+3)*pixel, 9*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+5)*pixel, 9*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+7)*pixel, 9*pixel, 1*pixel);
	
	//XSetForeground(dpy, gc, blue_col.pixel);
	//XFillRectangle(dpy, w, gc, column*blockWidth*pixel, row*blockHeight*pixel, blockWidth*pixel, blockHeight*pixel);
}

void GraphicsDisplay::drawFloor(int row, int column){
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, column*blockWidth*pixel, row*blockHeight*pixel, blockWidth*pixel, blockHeight*pixel);
}

void GraphicsDisplay::drawPC(int row, int column){
	XSetForeground(dpy, gc, green_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth)*pixel, (row*blockHeight+2)*pixel, 9*pixel, 4*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+0)*pixel, 5*pixel, 8*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+1)*pixel, 7*pixel, 6*pixel);
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+3)*pixel, 2*pixel, 2*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+6)*pixel, (row*blockHeight+3)*pixel, 2*pixel, 2*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+5)*pixel, (row*blockHeight+7)*pixel, pixel, pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+7)*pixel, pixel, pixel);
}

void GraphicsDisplay::drawPotion(int row, int column, int col){
	XSetForeground(dpy, gc, yellow_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+0)*pixel, 3*pixel, 2*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+2)*pixel, 5*pixel, 6*pixel);
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+4)*pixel, (row*blockHeight+1)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+4)*pixel, (row*blockHeight+3)*pixel, 2*pixel, 1*pixel);
}

void GraphicsDisplay::drawTreasure(int row, int column, int col){
	XSetForeground(dpy, gc, yellow_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth)*pixel, (row*blockHeight+1)*pixel, 9*pixel, 7*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+0)*pixel, 6*pixel, 1*pixel);
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+2)*pixel, 4*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+1)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+4)*pixel, 4*pixel, 3*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+7)*pixel, (row*blockHeight+7)*pixel, 2*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+8)*pixel, (row*blockHeight+6)*pixel, 1*pixel, 1*pixel);
	
}

void GraphicsDisplay::drawStair(int row, int column){
	XSetForeground(dpy, gc, white_col.pixel);	
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+1)*pixel, 4*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+3)*pixel, 4*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+5)*pixel, 4*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+4)*pixel, (row*blockHeight+7)*pixel, 4*pixel, 1*pixel);
}

void GraphicsDisplay::drawVampire(int row, int column){
	XSetForeground(dpy, gc, red_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+0)*pixel, 5*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+1)*pixel, 7*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+2)*pixel, 1*pixel, 2*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+8)*pixel, (row*blockHeight+2)*pixel, 1*pixel, 2*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+4)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+4)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+5)*pixel, (row*blockHeight+4)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+7)*pixel, (row*blockHeight+4)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+5)*pixel, 5*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth)*pixel, (row*blockHeight+6)*pixel, 9*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+7)*pixel, 7*pixel, 1*pixel);
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+5)*pixel, 3*pixel, 2*pixel);
	XSetForeground(dpy, gc, red_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+4)*pixel, (row*blockHeight+2)*pixel, 1*pixel, 1*pixel);
}

void GraphicsDisplay::drawGoblin(int row, int column){
	XSetForeground(dpy, gc, red_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+0)*pixel, 8*pixel, 2*pixel);
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+4)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+1)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+1)*pixel, 1*pixel, 1*pixel);
	XSetForeground(dpy, gc, red_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+2)*pixel, 8*pixel, 4*pixel);
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+3)*pixel, 1*pixel, 3*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+8)*pixel, (row*blockHeight+5)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+2)*pixel, 5*pixel, 2*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+4)*pixel, (row*blockHeight+4)*pixel, 3*pixel, 2*pixel);
	XSetForeground(dpy, gc, red_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+4)*pixel, (row*blockHeight+3)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+6)*pixel, (row*blockHeight+3)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+5)*pixel, (row*blockHeight+4)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+6)*pixel, 7*pixel, 2*pixel);
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+6)*pixel, 1*pixel, 1*pixel);
}

void GraphicsDisplay::drawWerewolf(int row, int column){
	XSetForeground(dpy, gc, red_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+0)*pixel, 6*pixel, 6*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+6)*pixel, 7*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+7)*pixel, 9*pixel, 1*pixel);
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 2*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+5)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 2*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+6)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+4)*pixel, (row*blockHeight+3)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+6)*pixel, (row*blockHeight+3)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+6)*pixel, (row*blockHeight+5)*pixel, 1*pixel, 1*pixel);
}

void GraphicsDisplay::drawTroll(int row, int column){
	XSetForeground(dpy, gc, red_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+0)*pixel, 5*pixel, 7*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+1)*pixel, 7*pixel, 5*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+2)*pixel, 9*pixel, 3*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+7)*pixel, (row*blockHeight+6)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+7)*pixel, 4*pixel, 1*pixel);
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+1)*pixel, 5*pixel, 5*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+2)*pixel, 7*pixel, 3*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+6)*pixel, 4*pixel, 1*pixel);
	XSetForeground(dpy, gc, red_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+4)*pixel, (row*blockHeight+2)*pixel, 2*pixel, 4*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+4)*pixel, 4*pixel, 1*pixel);
}

void GraphicsDisplay::drawPhoenix(int row, int column){
	XSetForeground(dpy, gc, red_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+6)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 2*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+5)*pixel, (row*blockHeight+2)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+6)*pixel, (row*blockHeight+3)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+3)*pixel, 3*pixel, 5*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+4)*pixel, 6*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+5)*pixel, (row*blockHeight+7)*pixel, 4*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+6)*pixel, (row*blockHeight+6)*pixel, 2*pixel, 1*pixel);
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+4)*pixel, 1*pixel, 1*pixel);
}

void GraphicsDisplay::drawDragon(int row, int column){
	XSetForeground(dpy, gc, red_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+0)*pixel, 7*pixel, 4*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+2)*pixel, 2*pixel, 3*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+5)*pixel, 9*pixel, 3*pixel);
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+6)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+5)*pixel, (row*blockHeight+2)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+7)*pixel, (row*blockHeight+2)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+3)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+5)*pixel, 3*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+6)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+8)*pixel, (row*blockHeight+5)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+5)*pixel, (row*blockHeight+6)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+4)*pixel, (row*blockHeight+7)*pixel, 2*pixel, 1*pixel);
}

void GraphicsDisplay::drawMerchant(int row, int column){
	XSetForeground(dpy, gc, red_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+0)*pixel, 7*pixel, 3*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+3)*pixel, 9*pixel, 5*pixel);
	XSetForeground(dpy, gc, black_col.pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+1)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+7)*pixel, (row*blockHeight+0)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+2)*pixel, (row*blockHeight+2)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+4)*pixel, (row*blockHeight+3)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+6)*pixel, (row*blockHeight+3)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+3)*pixel, (row*blockHeight+4)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+7)*pixel, (row*blockHeight+4)*pixel, 1*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+4)*pixel, (row*blockHeight+6)*pixel, 3*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+0)*pixel, (row*blockHeight+7)*pixel, 2*pixel, 1*pixel);
	XFillRectangle(dpy, w, gc, (column*blockWidth+8)*pixel, (row*blockHeight+6)*pixel, 1*pixel, 2*pixel);
}

void GraphicsDisplay::clear(){
	//w.fillRectangle(0, 0, 9*75*2, 8*22*2, Xwindow::White);
}
void GraphicsDisplay::print(){
	clearMsg();
	//w.drawString(50, 8*24*2+62, Action, Xwindow::Blue);
}
void GraphicsDisplay::clearMsg(){
	//w.fillRectangle(50-1, 8*24*2+62-13, 9*75*2-50, 15, Xwindow::White);
}

void GraphicsDisplay::refreshScreen(){
	XFlush(dpy);
}

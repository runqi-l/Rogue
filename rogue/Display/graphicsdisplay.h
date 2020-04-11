#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <string>
#include <vector>
#include "observer.h"

#include <X11/Xlib.h> // Every Xlib program must include this
#include <assert.h>   // I include this to test return values the lazy way
#include <unistd.h>   // So we got the profile for 10 seconds
#include <stdio.h>           // This has the keyboard and file IO functions
#define NIL (0)       // A name for the void pointer
class Cell;
class Enemy;
class Player;
class Character;
class Gold;
class GraphicsDisplay: public Observer {
	//block width=9;
	//block height=8;
	// ((9*(3+74+2)+78) x ((8*25) + 25 + 150)
	//all columns minus 3
	//empty = 0;
	//pixel=2;
	Display *dpy;
	Window & w;
	GC &gc;
	XColor black_col,white_col,red_col,green_col,blue_col,yellow_col;
	Colormap colormap;
	
	std::string race;
	std::string gold;
	int floor;
	int HP;
	int Atk;
	int Def;
	std::string Action="";
	const int blockWidth=9;
	const int blockHeight=8;
	const int pixel=2;
	
  public:
	GraphicsDisplay(Display *dpy, Window & w, GC & gc, std::string race="Human", std::string gold="0", int floor=0, int HP=140, int Atk=20, int Def=20);
	~GraphicsDisplay();
	void setFloor(int newfloor);
	void setRace(std::string r);
	void notifybound(Cell*);
	void notify(Cell *c) override;
	void notify(Enemy *e, int damage) override;
	void notify(Player *p, Character *e, int damage) override;
	void notify(Player *p) override;
	void notify(Enemy *e) override;
	void notify(Gold *e, std::string name)override;
	void notify(Potion *p, std::string name)override;
	void saw(Potion *p, std::string name)override;
	void action(std::string msg);
	
	void drawWall(int row, int column);
	
	void drawFloor(int row, int column);
;
	void drawPC(int row, int column);

	void drawPotion(int row, int column, int col=1);

	void drawTreasure(int row, int column, int col=1);

	void drawStair(int row, int column);

	void drawVampire(int row, int column);

	void drawGoblin(int row, int column);

	void drawWerewolf(int row, int column);

	void drawTroll(int row, int column);

	void drawPhoenix(int row, int column);

	void drawDragon(int row, int column);

	void drawMerchant(int row, int column);
	
	void clear();
	void clearMsg();
	void print();
	void refreshScreen();
};
#endif

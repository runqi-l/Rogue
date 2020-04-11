//spawn move attack pickup enemyattack
//vector.sort(vector.begin(), vector.end())
#ifndef __GRID_H__
#define __GRID_H__
#include <string>
#include <vector>

#include <X11/Xlib.h> // Every Xlib program must include this
#include <assert.h>   // I include this to test return values the lazy way
#include <unistd.h>   // So we got the profile for 10 seconds
#include <stdio.h>           // This has the keyboard and file IO functions
#define NIL (0)       // A name for the void pointer
class Cell;
class Enemy;
class Potion;
class Gold;
class Player;
class TextDisplay;
class Stair;
class GraphicsDisplay;
class Grid {
	std::vector<std::vector<Cell*>> theGrid,chambers;
	std::vector<Enemy*> enemies;
	/*std::vector<Potion*> potions;
	std::vector<Gold*> golds;*/
	Player* PC;
	/*Stair* stair;*/
	TextDisplay* td;
	GraphicsDisplay* gd = nullptr;
	int floor;
	bool gameLost = false;
	bool gameWon = false;
	bool sourceGiven = false;
	std::vector<std::string> sourceMap;
  public:
	Grid();
	Grid(Display *dpy, Window& w, GC & gc);
	~Grid();
	void open(const std::string& filename);
	bool end() const;
	void newGame(const std::string& rc);
	void clear();
	bool validMove(const std::string& dir) const;
	bool validAttack(const std::string& dir) const;
	bool validUse(const std::string& dir) const;
	void move(std::string& dir);
	void attack(const std::string& dir);
	void use(const std::string& dir);
	void buy();
	void refreshScreen();
  private:
	void newFloor();
	void enemyTurn();
	Cell* targetCell(const std::string& dir) const;
	void spawn();
	void spawnFromSource();
	void chamberInit();
	void detect()const;
	void notifyGraphics();
	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
	friend void print(const Grid &g);
};

std::ostream &operator<<(std::ostream &out, const Grid &g);
void print(const Grid &g);
#endif

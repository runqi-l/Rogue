#include "Factory/grid.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <ncurses.h>
#include <sstream>

#include <X11/Xlib.h> // Every Xlib program must include this
#include <assert.h>   // I include this to test return values the lazy way
#include <unistd.h>   // So we got the profile for 10 seconds
#include <stdio.h>           // This has the keyboard and file IO functions
#define NIL (0)       // A name for the void pointer

using namespace std;

int main(int argc, char** argv) {
	srand(time(NULL));
	
	if (argc>1&&strcmp(argv[1], "DLC")==0){
		
		
		
		
		
		GC gc;   //This will be the "graphics context"  It remembers the colors and window and various details.
		XColor black_col,white_col,red_col,green_col,blue_col,yellow_col;
		Colormap colormap;
		char black_bits[] = "#000000";
		char white_bits[] = "#FFFFFF";
		char red_bits[] = "#FF0000";
		char green_bits[] = "#00FF00";
		char blue_bits[] = "#0000FF";
		char yellow_bits[] = "#FFFF00";
		Display *dpy = XOpenDisplay(NIL); assert(dpy);   // Open the display
		// Get the only two predefined colors in xwindows:  Black and White
		int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));
		//int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));
		// Define the colors we want to use
		colormap = DefaultColormap(dpy, 0);
		XParseColor(dpy, colormap, black_bits, &black_col); XAllocColor(dpy, colormap, &black_col);
		XParseColor(dpy, colormap, white_bits, &white_col); XAllocColor(dpy, colormap, &white_col);
		XParseColor(dpy, colormap, red_bits, &red_col); XAllocColor(dpy, colormap, &red_col);
		XParseColor(dpy, colormap, green_bits, &green_col);XAllocColor(dpy, colormap, &green_col);
		XParseColor(dpy, colormap, blue_bits, &blue_col);XAllocColor(dpy, colormap, &blue_col);
		XParseColor(dpy, colormap, yellow_bits, &yellow_col);XAllocColor(dpy, colormap, &yellow_col);
		// Create the window  The numbers are the x and y locations on the screen, the width and height, 
		// border width (which is usually zero)
		Window w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), -2, -2, 9*75*2+20, 8*24*2, 0, whiteColor, whiteColor);
		XSelectInput(dpy, w, StructureNotifyMask);        // We want to get MapNotify events
		XMapWindow(dpy, w);         // "Map" the window (that is, make it appear on the screen)
		for(;;){XEvent e; XNextEvent(dpy,&e); if(e.type == MapNotify) break;} //Wait for the MapNotify event
		// which means that the window has appeared on the screen.
		gc = XCreateGC(dpy, w, 0, NIL);        // Create a "Graphics Context"
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		Grid g = {dpy, w, gc};
		if (argc>2){
			g.open(argv[2]);
		}
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	cbreak();
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);
		
	print(g);
	mvprintw(30,0,"Welcome to Chamber Crawler 3000!! Please select a character race to play: ");
	mvprintw(31,0,"[h]uman   (140 HP, 20 Atk, 20 Def, a 50% increase to score)");
	mvprintw(32,0,"[d]warf   (100 HP, 20 Atk, 30 Def, gold is doubled in value)");
	mvprintw(33,0,"[e]lf     (140 HP, 30 Atk, 10 Def, negative potions have positive effect)");
	mvprintw(34,0,"[o]rc     (180 HP, 30 Atk, 25 Def, gold is worth half value)");
	refresh();
		while (true) {
			char command = getch();
			if (command=='h'||command=='d'||command=='e'||command=='o'){
				stringstream ss;
				string s;
				ss << command;
				ss >> s;
				g.newGame(s);
				print(g);
				mvprintw(30,0,"                                                                          ");
				mvprintw(31,0,"                                                           ");
				mvprintw(32,0,"                                                            ");
				mvprintw(33,0,"                                                                         ");
				mvprintw(34,0,"                                                            ");
				refresh();
				
				g.refreshScreen();
				
				break;
			} else if (command=='q') {
				endwin();
				cout << g;
				cout << "You've lost!! Try harder next time!"<<endl;
				XFreeGC(dpy, gc);
				XCloseDisplay(dpy);
				return 0;
			}
		}
		while (!g.end()){
			string com;			
			char command1 = getch();
			if (command1 == 'q'){
				endwin();
				cout << g;
				cout << "You've lost!! Try harder next time!"<<endl;
				XFreeGC(dpy, gc);
				XCloseDisplay(dpy);
				return 0;
			} else if (command1 == 'r') {
				g.clear();
				print(g);
				mvprintw(30,0,"Welcome to Chamber Crawler 3000!! Please select a character race to play: ");
				mvprintw(31,0,"[h]uman   (140 HP, 20 Atk, 20 Def, a 50% increase to score)");
				mvprintw(32,0,"[d]warf   (100 HP, 20 Atk, 30 Def, gold is doubled in value)");
				mvprintw(33,0,"[e]lf     (140 HP, 30 Atk, 10 Def, negative potions have positive effect)");
				mvprintw(34,0,"[o]rc     (180 HP, 30 Atk, 25 Def, gold is worth half value)");
				refresh();
				while (true) {
					char command = getch();
					if (command=='h'||command=='d'||command=='e'||command=='o'){
						stringstream ss;
						string s;
						ss << command;
						ss >> s;
						g.newGame(s);
						print(g);
						mvprintw(30,0,"                                                                          ");
						mvprintw(31,0,"                                                           ");
						mvprintw(32,0,"                                                            ");
						mvprintw(33,0,"                                                                         ");
						mvprintw(34,0,"                                                            ");
						refresh();
						
						g.refreshScreen();
						
						break;
					} else if (command=='q') {
						endwin();
						cout << g;
						cout << "You've lost!! Try harder next time" << endl;
						XFreeGC(dpy, gc);
						XCloseDisplay(dpy);
						return 0;
					}
				}
				continue;
			} else if (command1=='j') {
				g.buy();
				print(g);
				refresh();
				
				g.refreshScreen();
				
				continue;
			}
			char command2;
			bool cross = false;
			if ((command2=getch())!=command1&&(command2=='w'||command2=='a'||command2=='s'||command2=='d')) {
				cross = true;
			}
			napms(180);
			if (cross) {
				if ((command1=='a'&&command2=='w')||(command2=='a'&&command1=='w')){
					com = "nw";
				} else if ((command1=='w'&&command2=='d')||(command2=='w'&&command1=='d')){
					com = "ne";
				} else if ((command1=='a'&&command2=='s')||(command2=='a'&&command1=='s')){
					com = "sw";
				} else if ((command1=='s'&&command2=='d')||(command2=='s'&&command1=='d')){
					com = "se";
				}
			} else {
				if(command1=='w'){
					com = "no";
				} else if (command1=='a'){
					com = "we";
				} else if (command1=='s'){
					com = "so";
				} else if (command1=='d'){
					com = "ea";
				}
			}
			if(g.validMove(com)){
				g.move(com);
				
				g.refreshScreen();
				
			} else if (g.validAttack(com)){
				g.attack(com);
				
				g.refreshScreen();
				
			} else if (g.validUse(com)){
				g.use(com);
				
				g.refreshScreen();
				
			}
			print(g);
			refresh();
		}
		XFreeGC(dpy, gc);
		XCloseDisplay(dpy);
		endwin();
		cout << g;
		
	} else {
	Grid g = {};
	if (argc > 1){
		g.open(argv[1]);
	}
	
	cin.exceptions(ios::failbit|ios::eofbit);
	cout << g;
	cout << "Welcome to Chamber Crawler 3000!! Please select a character race to play: " << endl;
	cout << "[h]uman   (140 HP, 20 Atk, 20 Def, a 50% increase to score)" << endl;
	cout << "[d]warf   (100 HP, 20 Atk, 30 Def, gold is doubled in value)" << endl;
	cout << "[e]lf     (140 HP, 30 Atk, 10 Def, negative potions have positive effect)" << endl;
	cout << "[o]rc     (180 HP, 30 Atk, 25 Def, gold is worth half value)" << endl;
	string command;
	try {
		while (true) {
			cin >> command;
			if (command=="h"||command=="d"||command=="e"||command=="o") {
				g.newGame(command);
				cout << g;
				break;
			} else if (command=="q") {
				cout << "You've lost!! Try harder next time!" << endl;
				return 0;
			} else {
				cout << "invalid Character. Please select a character race to play: " << endl;
				cout << "[h]uman   (140 HP, 20 Atk, 20 Def, a 50% increase to score)" << endl;
				cout << "[d]warf   (100 HP, 20 Atk, 30 Def, gold is doubled in value)" << endl;
				cout << "[e]lf     (140 HP, 30 Atk, 10 Def, negative potions have positive effect)" << endl;
				cout << "[o]rc     (180 HP, 30 Atk, 25 Def, gold is worth half value)" << endl;
			}
		}
		while (!g.end()){
			cin >> command;
			if (command == "a"){
				cin >> command;
				if (!g.validAttack(command)) {
						cout << "invalid command, please enter again: ";
				} else {
					g.attack(command);
					cout << g;
				}
			} else if (command == "u") {
				cin >> command;
				if (!g.validUse(command)) {
					cout << "invalid comman, please enter again: ";
				} else {
					g.use(command);
					cout << g;
				}
			} else if (command == "q") {
				cout << "You've lost!! Try harder next time!" << endl;
				break;
			} else if (command == "r") {
				g.clear();
				cout << g;
				cout << "Welcome to Chamber Crawler 3000!! Please select a character race to play: " << endl;
				cout << "[h]uman   (140 HP, 20 Atk, 20 Def, a 50% increase to score)" << endl;
				cout << "[d]warf   (100 HP, 20 Atk, 30 Def, gold is doubled in value)" << endl;
				cout << "[e]lf     (140 HP, 30 Atk, 10 Def, negative potions have positive effect)" << endl;
				cout << "[o]rc     (180 HP, 30 Atk, 25 Def, gold is worth half value)" << endl;
				while (true) {
					cin >> command;
					if (command=="h"||command=="d"||command=="e"||command=="o") {
						g.newGame(command);
						cout << g;
						break;
					} else {
						cout << "invalid Character. Please select a character race to play: " << endl;
						cout << "[h]uman   (140 HP, 20 Atk, 20 Def, a 50% increase to score)" << endl;
						cout << "[d]warf   (100 HP, 20 Atk, 30 Def, gold is doubled in value)" << endl;
						cout << "[e]lf     (140 HP, 30 Atk, 10 Def, negative potions have positive effect)" << endl;
						cout << "[o]rc     (180 HP, 30 Atk, 25 Def, gold is worth half value)" << endl;
					}
				}
			} else {
				if (!g.validMove(command)) {
					cout << "invalid command, please enter again: ";
				} else {
					g.move(command);
					cout << g;
				}
			}
		}
	} catch (ios::failure) {}
	}
}

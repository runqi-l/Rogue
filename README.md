# Cplusplus-dungeon-crawler

This is a C++ game.
It is a Rogue-like dungeon crawler.

Useing ncurse and X11 library.

use the command line option DLC to open a graphics display(make sure you have an X server):

```
$ cd dc3k
$ make
$ ./dc3k DLC
```

press H to start; use WASD to move in 8 directions; press Q to quit; press R to restart
press B to purchase a potion from merchant
potions are immediately consumed
moving towards an enemy will attack against it

I implemented graphics display using native X11 and captures user input using ncurse library (I know that user inputs can be captured by X11 as well, I'll fix it if I ever come around to it).
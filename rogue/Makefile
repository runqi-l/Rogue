CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -g -I/opt/X11/include
EXEC = rogue
OBJECTS = main.o Factory/cell.o Factory/grid.o Display/textdisplay.o Display/graphicsdisplay.o Character/character.o Character/player.o Character/enemy.o Character/decorator.o Item/item.o Item/potion.o Item/gold.o Item/stair.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lncurses -L/opt/X11/lib -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

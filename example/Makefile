# GEN BY ORHAN UYAR

CC=gcc
CFLAGS=-ansi -pedantic -Wall
MLFLAG=-lMLV
# OUT-PUT FILE
EXE=puzzle
SOURCE=sources/
OUT=out/
# ALL NEEDED OBJECT
OBJ= $(OUT)Plateau.o $(OUT)Launcher.o $(OUT)Graphics.o $(OUT)Events.o $(OUT)GameLogic.o

GRAPHICS=$(SOURCE)graphics/
PLATEAU=$(SOURCE)utils/plateau/
EVENTS=$(SOURCE)utils/events/
LOGIC=$(SOURCE)utils/game_logic/

all:
	make $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(MLFLAG)

$(OUT)Launcher.o: $(SOURCE)launcher.c

$(OUT)Plateau.o: $(PLATEAU)plateau.c $(PLATEAU)plateau.h

$(OUT)Graphics.o: $(GRAPHICS)plateau_drawer.c $(GRAPHICS)plateau_drawer.h

$(OUT)Events.o: $(EVENTS)events.c $(EVENTS)events.h

$(OUT)GameLogic.o: $(LOGIC)game_logic.c $(LOGIC)game_logic.h

$(OUT)%.o:
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f $(OUT)*.o

mrpropre: clean
	rm -f $(EXE)

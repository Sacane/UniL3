CC=gcc
CFLAGS=-ansi -pedantic -Wall -Wfatal-errors -lreadline -ldl

EXE=calc
SOURCE=sources/
OUT=out/
PLUGINS_SRC=$(SOURCE)components/
PLUGINS_OUT=plugins/
PLUGINS=$(wildcard $(PLUGINS_SRC)*.c)

OBJ=$(OUT)Main.o $(OUT)Pile.o $(OUT)Input.o $(OUT)PluginsLoader.o $(OUT)Plugin.o

all:
	make $(EXE)
	make install

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OUT)Main.o: $(SOURCE)main.c

$(OUT)Pile.o: $(SOURCE)pile/pile.c $(SOURCE)pile/pile.h

$(OUT)Input.o: $(SOURCE)user_input/input.c $(SOURCE)user_input/input.h

$(OUT)PluginsLoader.o: $(SOURCE)pluginsLoader/pluginsLoader.c $(SOURCE)pluginsLoader/pluginsLoader.h

$(OUT)Plugin.o: $(SOURCE)plugin/plugin.c $(SOURCE)plugin/plugin.h

$(OUT)%.o:
	$(CC) -c $< $(CFLAGS) -o $@

$(PLUGINS_OUT)%.so: $(PLUGINS_SRC)%.c
	$(CC) -shared -o $@ -fPIC $<

install: $(patsubst $(PLUGINS_SRC)%.c, $(PLUGINS_OUT)%.so, $(PLUGINS))

uninstall:
	rm -f $(PLUGINS_OUT)*.so

clean:
	rm -f $(OUT)*.o

mrpropre: clean uninstall
	rm -f $(EXE)

# Declaraciones de macros.

CC="gcc -c -Wall"
lib='command.h game_reader.h game.h graphic_engine.h libscreen.h object.h player.h space.h types.h'

# Declaraciones de reglas.

all: antgame clean

antgame: game.o game_reader.o command.o graphic_engine.o object.o player.o space.o libscreen.a game_loop.o
	gcc -g -Wall -o antgame $^
command.o: command.c command.h
	gcc -c -g -Wall command.c
game.o: game.c game.h
	gcc -c -g -Wall game.c
game_reader.o: game_reader.c game_reader.h
	gcc -c -g -Wall game_reader.c
graphic_engine.o: graphic_engine.c graphic_engine.h libscreen.h
	gcc -c -g -Wall graphic_engine.c
object.o: object.c object.h
	gcc -c -g -Wall object.c
player.o: player.c player.h
	gcc -c -g -Wall player.c
space.o: space.c space.h
	gcc -c -g -Wall space.c
game_loop.o: game_loop.c
	gcc -c -g -Wall game_loop.c

clean:
	echo "cleaning..."
	rm -rf *.o
	rm -rf *.gch
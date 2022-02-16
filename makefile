# Declaraciones de macros.

CC="gcc -c -Wall"
lib='command.h game_reader.h game.h graphic_engine.h libscreen.h object.h player.h space.h types.h'

# Declaraciones de reglas.

all: antgame clean

antgame: game_loop.o command.o game_reader.o game.o graphic_engine.o object.o player.o space.o libscreen.a
	gcc -Wall -o antgame $^
command.o: command.c command.h
	gcc -c -Wall $^
game_reader.o: game_reader.c game_reader.h
	gcc -c -Wall $^
game.o: game.c game.h
	gcc -c -Wall $^
graphic_engine.o: graphic_engine.c graphic_engine.h libscreen.h
	gcc -c -Wall $^
object.o: object.c object.h
	gcc -c -Wall $^
player.o: player.c player.h
	gcc -c -Wall $^
space.o: space.c space.h
	gcc -c -Wall $^
game_loop.o: game_loop.c
	gcc -c -Wall $^

clean:
	echo "cleaning..."
	rm -rf *.o
	rm -rf *.gch
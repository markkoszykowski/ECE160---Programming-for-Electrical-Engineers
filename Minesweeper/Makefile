make: main.o game.o board.o
	g++ -o Minesweeper main.o game.o board.o -I.

board.o: board.h board.cpp tile.h Global.h
	g++ -c board.cpp -I.

game.o: game.h game.cpp board.h
	g++ -c game.cpp -I.

main.o: main.cpp game.h
	g++ -c main.cpp -I.

clean:
	rm -rf *.o *.exe

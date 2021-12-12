FLAGS = -Wall -std=c++11

game: game.o TicTacToe.o
	g++ ${FLAGS} game.o TicTacToe.o -o game

game.o: game.cpp TicTacToe.hpp
	g++ ${FLAGS} -c game.cpp

TicTacToe.o: TicTacToe.cpp TicTacToe.hpp
	g++ ${FLAGS} -c TicTacToe.cpp

clean:
	rm -f *.o game

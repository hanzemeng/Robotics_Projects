FLAGS = -Wall -std=c++11

KnightMove: KnightMove.o Knight.o
	g++ ${FLAGS} KnightMove.o Knight.o -o KnightMove

KnightMove.o: KnightMove.cpp Knight.h
	g++ ${FLAGS} -c KnightMove.cpp

Knight.o: Knight.cpp Knight.h
	g++ ${FLAGS} -c Knight.cpp

clean:
	rm -f *.o KnightMove

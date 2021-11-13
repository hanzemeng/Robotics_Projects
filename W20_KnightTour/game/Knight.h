#include <iostream>
#include <iomanip>

class Knight
{
	public:
		Knight(int, int, int); // size of board, start Y, start X
        void move(int, int);
        bool check(); // use warnsdorffMove() to determine if it is possible to visit all places in the board
        int getNum(int, int); // return board[y][x]
        int getCurrentY();
        int getCurrentX();
        void startScreen(char);
    
		void showBoard(); // just for debugging
    
	private:
		int dimension;
		int moveCount = 0;
        int currentY;
        int currentX;
		int** board;
        int moveY[8] = {1,2,2,1,-1,-2,-2,-1};
        int moveX[8] = {2,1,-1,-2,-2,-1,1,2};
        
    
        bool warnsdorffMove(int, int, int); // doesn't always work
        int checkSurround(int, int); // used for tie breaking in warnsdorffMove()
		void shuffleMoves(); // not used in final version
		bool moveKnight(int, int, int); // not used in final version
};

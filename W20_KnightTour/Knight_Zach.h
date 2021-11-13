#include <vector>
#include <iostream>
class Knight
{
	public:
		Knight(int, int, int);
        void move(int, int);
        bool check();
        
		void showBoard();
    
	private:
		int dimension;
		int moveCount = 0;
        int currentY;
        int currentX;
		std::vector<std::vector<int> > board;
        std::vector<int> moveY{1,2,2,1,-1,-2,-2,-1};
        std::vector<int> moveX{2,1,-1,-2,-2,-1,1,2};
        
    
        bool warnsdorffMove(int, int, int);
		void shuffleMoves();
		bool moveKnight(int, int, int);
};

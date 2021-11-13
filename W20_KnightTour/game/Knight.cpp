#include "Knight.h"

Knight::Knight(int size, int startY, int startX)
{
	dimension = std::max(5, size);
    board = new int* [dimension];
    for(int i=0; i<dimension; i++)
    {
        board[i] = new int[dimension];
    }
    for(int i=0; i<dimension; i++)
    {
        for(int j=0; j<dimension; j++)
        {
            board[i][j] = 0;
        }
    }
    
    move(startY, startX);
}

void Knight::move(int y, int x)
{
    currentY = y;
    currentX = x;
    moveCount++;
    board[y][x] = moveCount;
}

bool Knight::check()
{
    if(warnsdorffMove(currentY, currentX, moveCount))
    {
        return true;
    }
    return false;
}

int Knight::getNum(int y, int x)
{
    if(y<0 || y>=dimension || x<0 || x>=dimension)
    {
        return -1;
    }
    return board[y][x];
}

int Knight::getCurrentY()
{
    return currentY;
}
int Knight::getCurrentX()
{
    return currentX;
}

bool Knight::warnsdorffMove(int y, int x, int count)
{
    int original = board[y][x];
    board[y][x] = count;
    if(count == dimension*dimension)
    {
        board[y][x] = original;
        return true;
    }
    int neighborCount = 8;
    int nextMoveIndex = -1;
    for(int i=0; i<8; i++)
    {
        int newY = y+moveY[i];
        int newX = x+moveX[i];
        if(newY<0 || newY>=dimension || newX<0 || newX>=dimension || 0 != board[newY][newX])
        {
            continue;
        }
        int count = 0;
        for(int j=0; j<8; j++)
        {
            int neighborY = newY+moveY[j];
            int neighborX = newX+moveX[j];
            if(neighborY<0 || neighborY>=dimension || neighborX<0 || neighborX>=dimension || 0 != board[neighborY][neighborX])
            {
                continue;
            }
            count++;
        }
        if(count<neighborCount)
        {
            neighborCount = count;
            nextMoveIndex = i;
        }
        else if(count == neighborCount)
        {
            int previousSurround = checkSurround(y+moveY[nextMoveIndex], x+moveX[nextMoveIndex]);
            int currentSurround = checkSurround(y+moveY[i], x+moveX[i]);
            if(currentSurround<previousSurround)
            {
                nextMoveIndex = i;
            }
        }
    }
    if(-1 != nextMoveIndex)
    {
        if(warnsdorffMove(y+moveY[nextMoveIndex], x+moveX[nextMoveIndex], count+1))
        {
            board[y][x] = original;
            return true;
        }
    }
    board[y][x] = original;
    return false;
}

int Knight::checkSurround(int y, int x)
{
    int count = 0;
    for(int i=-1; i<=1; i++)
    {
        for(int j=-1; j<=1; j++)
        {
            if(0 == getNum(y+i, x+j))
            {
                count++;
            }
        }
    }
    return count;
}

void Knight::showBoard()
{
    int spotSize = 10;
    while(dimension * dimension > spotSize)
    {
        spotSize *= 10;
    }
    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            int num = board[i][j];
            std::cout << num << ' ';
            if(0 == num)
            {
                num = 1;
            }
            while(num < spotSize)
            {
                std::cout << ' ';
                num *= 10;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Total spots visited: " << moveCount << std::endl;
}

void Knight::shuffleMoves()
{
    srand(int(time(NULL)));
	for(int i=0; i<8; i++)
    {
        int newIndex = rand() % 8;
        int temp = moveY[newIndex];
        moveY[newIndex] = moveY[i];
        moveY[i] = temp;
        temp = moveX[newIndex];
        moveX[newIndex] = moveX[i];
        moveX[i] = temp;
    }
    for(int i=0; i<8; i++)
    {
        std::cout << moveY[i] << ' ';
    }
	std::cout << std::endl;
    for(int i=0; i<8; i++)
    {
        std::cout << moveX[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

bool Knight::moveKnight(int y, int x, int count)
{
	moveCount++;
	if(y<0 || y>=dimension || x<0 || x>=dimension || 0 != board[y][x])
	{
		return false;
	}
	board[y][x] = count;
	if(count == dimension*dimension)
	{
		return true;
	}
    for(int i=0; i<8; i++)
    {
        if(moveKnight(y+moveY[i], x+moveX[i], count+1))
        {
            return true;
        }
    }
    
	board[y][x] = 0;
	return false;
}

void Knight::startScreen(char playerChoice)
{
        if ( tolower(playerChoice) == 'p' )
        {
                return;
        }
        else if ( tolower(playerChoice) == 'e' ) 
        { 
                std::cout << " _________________________________________ " << std::endl; 
                std::cout << "|                                         |" << std::endl; 
                std::cout << "|              - Game Info -              |" << std::endl; 
                std::cout << "|                                         |" << std::endl; 
                std::cout << "|   Thank you for playing Knight Move!    |" << std::endl; 
                std::cout << "|                                         |" << std::endl; 
                std::cout << "|   This goal of this game is to see if   |" << std::endl; 
                std::cout << "|   you, the players, can take a Knight   |" << std::endl; 
                std::cout << "|   piece around the entire chess board   |" << std::endl; 
                std::cout << "|   with out touching the same slot twice |" << std::endl; 
                std::cout << "|                                         |" << std::endl; 
                std::cout << "|              - How to play -            |" << std::endl; 
                std::cout << "|                                         |" << std::endl; 
                std::cout << "|   This game contains a local 1 vs 1     |" << std::endl; 
                std::cout << "|   multiplayer gameplay.                 |" << std::endl; 
                std::cout << "|                                         |" << std::endl; 
                std::cout << "|   Each player's board movement is       |" << std::endl; 
                std::cout << "|   centered around the F key and J key   |" << std::endl; 
                std::cout << "|                                         |" << std::endl; 
                std::cout << "|          -                -             |" << std::endl; 
                std::cout << "|        | F |            | J |           |" << std::endl; 
                std::cout << "|          -                -             |" << std::endl; 
                std::cout << "|_________________________________________|" << std::endl; 
 
                exit(1); 
        } 
        else 
        { 
                exit(1); 
        }        
}

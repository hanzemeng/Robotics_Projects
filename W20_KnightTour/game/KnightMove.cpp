#include <iostream>
#include <stdlib.h>
#include "Knight.h"

using namespace std;

const int PLAYER_CODE = 11111;
const int PLAYER_NUM = 2;

void printBoard(int** board , int size, Knight* player){
    cout << "    ";
    for(int i = 65; i < 65 + size; i++)
    {
        char letter = i;
        cout << letter << "     ";
    }
    cout << endl;
    for(int i = 0; i < size; i++)
    {
        cout << i+1;
        if(i < 9)
        {
            cout << "  ";
        }
        else
        {
            cout << " ";
        }
        for(int j = 0; j < size; j++)
        {
            if(board[i][j] == PLAYER_CODE)
            {
                if(i == player->getCurrentY() && j == player->getCurrentX())
                {
                    cout << "[K]   ";
                }
                else
                {
                    cout << "[E]   ";
                }
            }
            else if(player->getNum(i, j) == 0)
            {
                cout << "[ ]   ";
            }
            else
            {
                cout << "[O]   ";
            }
        }
        cout << endl << endl;
    }
}

bool updateMove(char s, int& playerY, int& playerX)
{
    if('e' == s)
    {
        playerY -= 1;
        playerX -= 2;
    }
    else if('c' == s)
    {
        playerY += 1;
        playerX -= 2;
    }
    else if('r' == s)
    {
        playerY -= 2;
        playerX -= 1;
    }
    else if('v' == s)
    {
        playerY += 2;
        playerX -= 1;
    }
    else if('o' == s)
    {
        playerY -= 1;
        playerX += 2;
    }
    else if('m' == s)
    {
        playerY += 1;
        playerX += 2;
    }
    else if('i' == s)
    {
        playerY -= 2;
        playerX += 1;
    }
    else if('n' == s)
    {
        playerY += 2;
        playerX += 1;
    }
    else
    {
        return false;
    }
    return true;
}

int main()
{
    // initialize board
    char playerChoice;
    int size;
    Knight* players[PLAYER_NUM];
    cout << "      ________________ " << endl;
    cout << "     |                |" << endl;
    cout << "     |      Play      |" << endl;
    cout << "     |     Explain    |" << endl;
    cout << "     |      Quit      |" << endl;
    cout << "     |________________|" << endl;

    cin >> playerChoice;
    players[0] -> startScreen(playerChoice);

    cout << " ________________________________ " << endl;
    cout << "|                                |" << endl;
    cout << "|        Input Board Size:       |" << endl;
    cout << "|                                |" << endl;
    cout << "|________________________________|" << endl;

    cin >> size;
    
    size = std::max(5, size);
    int** board;
    board = new int *[size];
    for(int i = 0; i < size; i++)
    {
        board[i] = new int[size];
    }
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            board[i][j] = 0;
        }
    }
    
    // initialize players
    srand(time(NULL));
    for(int i=0; i<PLAYER_NUM; i++)
    {
        int playerY = rand()%size;
        int playerX = rand()%size;
        if(PLAYER_CODE == board[playerY][playerX])
        {
            i--;
            continue;
        }
        players[i] = new Knight(size, playerY, playerX);
        if(!players[i]->check())
        {
            delete players[i];
            i--;
            continue;
        }
        board[playerY][playerX] = PLAYER_CODE;
    }
    
    // game body
    while(true)
    {
        int winner = -1;
        for(int i=0; i<PLAYER_NUM; i++)
        {
            printBoard(board, size, players[i]);
            
            // get input
            cout << "Player " << i+1 << ", enter your next coordinate: ";
            system("stty raw");
            char s;
            cin >> s;
            system("stty cooked");
            cout << endl;
            
            // check input errors
            int tempY = players[i]->getCurrentY();
            int tempX = players[i]->getCurrentX();
            if(!updateMove(s, tempY, tempX))
            {
                cout << "Enter something else" << endl;
                i--;
                continue;
            }
            if(size<=tempY || tempY<0 || size<=tempX || tempX<0)
            {
                cout << "Out of range" << endl;
                i--;
                continue;
            }
            if(PLAYER_CODE == board[tempY][tempX])
            {
                cout << "Can't take your opponent's knight" << endl;
                i--;
                continue;
            }
            if(players[i]->getNum(tempY, tempX) != 0)
            {
                cout << "You came here before" << endl;
                i--;
                continue;
            }
            
            // do the move
            board[players[i]->getCurrentY()][players[i]->getCurrentX()] = 0;
            board[tempY][tempX] = PLAYER_CODE;
            players[i]->move(tempY, tempX);
            
            // check if current player loses or not
            if(!players[i]->check())
            {
                printBoard(board, size, players[i]);
                cout << "Player " << i+1 << ", you just lost" << endl;
                winner = (i+1)%2;
                break;
            }
        }
        if(-1 != winner)
        {
            cout << "Player " << winner+1 << ", you win" << endl;
            break;
        }
    }
    return 0;
}

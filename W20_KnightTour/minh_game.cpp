#include <iostream>
#include <string>
using namespace std;

bool makeMove(int& x, int& y, string input) {
    if(input.length() > 2) return false;
    if(input[0] == 'W') {
        if(input[1] == 'Q') {
            x+=-1;
            y+=2;
        }
        if(input[1] == 'E') {
            x+=1;
            y+=2;
        }
    }
    else if(input[0] == 'A') {
        if(input[1] == 'Q') {
            x+=-2;
            y+=1;
        }
        if(input[1] == 'Z') {
            x+=-2;
            y+=-1;
        }
    }
    else if(input[0] == 'D') {
        if(input[1] == 'E') {
            x+=2;
            y+=1;
        }
        if(input[1] == 'C') {
            x+=2;
            y+=-1;
        }
    }
    else if(input[0] == 'X') {
        if(input[1] == 'C') {
            x+=1;
            y+=-2;
        }
        if(input[1] == 'Z') {
            x+=-1;
            y+=-2;
        }
    }
}

bool checkMove(int x, int y, int size) {
    if(x > size || y > size) return false;
    if(x < 0 || y < size) return false;
}

int main() {
    int x(0),y(0);
    int board[5][5] = {0};
    bool gameOver = true;
    cout << "Instructions: Use WADX to indicate direction left-right-top-bottom \n And use QEZC to indicate direction after WADX" << endl;
    while(!gameOver) {
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Enter a move: " << endl;
    }
}
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void printBoard(int** board , int size){
    cout << "    ";
    for(int i = 65; i < 65 + size; i++)
    {
        char letter = i;
        cout << letter << "     ";
    }
    cout << endl;
    for(int x = 0; x < size; x++)
    {
        cout << x+1;
        if(x < 9)
        {
            cout << "  ";
        }
        else
        {
            cout << " ";
        }
        for(int j = 0; j < size; j++)
        {
            if(board[x][j] == 0)
            {
                cout << "[ ]   ";
            }
            else if(board[x][j] == 1)
            {
                cout << "[O]   ";
            }
            else
            {
                cout << "[K]   ";
            }
        }
        cout << endl << endl;
    }
}
int main(){
    int size;
    cout << "Input a size: ";
    cin >> size;
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
    board[0][0] = 2;
    printBoard(board, size);
    string s;
    for(int i = 0; i < 100; i++)
    {
        if(i == 0)
        {
            board[0][0] = 1;
        }
        else
        {
            if(s.length() == 2)
            {
                board[s[1]-49][s[0]-65] = 1;
            }
            else
            {
                string num = s.substr(1,2);
                stringstream geek(num);
                int x = 0;
                geek >> x;
                board[x-1][s[0]-65] = 1;
            }
        }
        cout << "Enter your next coordinate: ";
        cin >> s;
        char first = s[0];
        char second = s[1];
        if(s.length() == 2)
        {
            board[s[1]-49][s[0]-65] = 2;
        }
        else
        {
            string num = s.substr(1,2);
            stringstream geek(num);
            int x = 0;
            geek >> x;
            cout << x << endl;;
            board[x-1][s[0]-65] = 2;
        }
        printBoard(board, size);
    }
    

}

/*#include <iostream>
#include <conio.h>
using namespace std;

int main() {

    cout << "Press a key." << endl;

    char input = _getch();

    cout << endl << "Did you type: " << input << "?" << endl;
    return 0;

}*/



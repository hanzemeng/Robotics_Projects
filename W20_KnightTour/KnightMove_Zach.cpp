#include <iostream>
#include "Knight.h"

int main()
{

    while(true)
    {
        int num;
        std::cout << "A positive integer please" << std::endl;
        std::cin >> num;
        std::cout << std::endl;
        
        if(0 == num)
        {
            break;
        }
        Knight game = Knight(num, 0, 0);
        game.move(2, 1);
        game.move(1, 3);
        game.move(3, 4);
        game.move(5, 5);

        
        if(game.check())
        {
            std::cout << "WORK" << std::endl;
        }
        else
        {
            std::cout << "FAIL" << std::endl;
        }
        
        game.showBoard();
    }
    
    return 0;
}


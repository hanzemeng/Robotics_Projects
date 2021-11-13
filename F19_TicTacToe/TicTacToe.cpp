#include "TicTacToe.hpp"
#include <time.h>
#include <iostream>

TicTacToe::TicTacToe()
{
	srand(time(NULL));  // initialize random number generator

	// use random condition to determine the first player
	if (rand()>(RAND_MAX/2)) {
		teamSide = 1;       // team blue plays first
	} else {
		teamSide = -1;      // team red plays first
	}

	actionsLeft = 2;    // set number of actions in the first turn
	victory = 0;    //set victory to false
	removedBall = false;	//player has not removed any ball at the beginning of a game
}

bool TicTacToe::add(int x, int y)
{
	// if there are not already three balls in the pole, add ball to top
	if (field[y][x].size() < 3) {
		field[y][x].push_back(teamSide);
		actionsLeft--;
		checkVictory();

		if ((getVictory() == 0) && (actionsLeft == 0))
		{
			changeTurn();
		}

		return true;
	} else return false;
}

bool TicTacToe::remove(int x, int y)
{
	// if there is at least one ball to remove, remove ball from bottom of the pole
	if (!removedBall && field[y][x].size() > 0) {
		field[y][x].pop_front();
		actionsLeft--;
		removedBall = true;
		checkVictory();

		if ((getVictory() == 0) && (actionsLeft == 0))
		{
			changeTurn();
		}

		return true;
	} else return false;
}

int TicTacToe::getTeamSide() {
	return teamSide;
}

int TicTacToe::getVictory() {
	return victory;
}

void TicTacToe::checkVictory() {
	int blue = 1,red = -1,blue_points,red_points;
	blue_points = checkVictoryHorizontal(blue) + checkVictoryDiagonal(blue) + checkVictoryVertical(blue);
	red_points = checkVictoryHorizontal(red) + checkVictoryDiagonal(red) + checkVictoryVertical(red);
	if(blue_points > 3) {
		victory = 1;
	}
	else if(red_points > 3) {
		victory = -1;
	}
	else{
		victory = 0;
	}
}

int TicTacToe::checkVictoryHorizontal(int teamSide)
{
	int point = 0;
	for(int y = 0; y <= 2; y = y + 1){
		for(int z = 0; z < field[y][0].size(); z = z + 1){
			if(field[y][0][z] == teamSide){
				if(field[y][1].size() >= (z + 1) && field[y][1][z] == teamSide){
					if(field[y][2].size() >= (z + 1) && field[y][2][z] == teamSide){
						point = point + 1;
					}
				}
			}
		}
	}

	for(int x = 0; x <= 2; x = x + 1){
		for(int z = 0; z < field[0][x].size(); z = z + 1){
			if(field[0][x][z] == teamSide){
				if(field[1][x].size() >= (z + 1) && field[1][x][z] == teamSide){
					if(field[2][x].size() >= (z + 1) && field[2][x][z] == teamSide){
						point = point + 1;
					}
				}
			}
		}
	}
	return point;
}

int TicTacToe::checkVictoryVertical(int teamSide) // check all (9) vertical columns; 9 for bottom to top.
{
	int numVictory = 0;
	for (int y = 0; y < 3; y++) // loop through y coordinates
	{
		for (int x = 0; x < 3; x++) // loop through x coordinates
		{
			int numItems = 0; // initialize to 0
			for (int item = 0; item < field[y][x].size(); item++) // loop through each individual item in the column
			{
				if (field[y][x][item] == teamSide) // check if the value of the item is equal to the teamID (-1 or 1)
				{
					numItems++; // increment number of items
				}
			}
			if (numItems == 3) // check if number of items is equal to 3
			{
				numVictory++; // if so, increment number of victories
			}
		} // x
	} // y
	return numVictory; // return number of victories (total possible = 9)
}

int TicTacToe::checkVictoryDiagonal(int teamSide)
{
	using namespace std;
	int count = 0;
	int frontBack = 0;
	int leftRight = 0;
	int sameLayer = 0;
	for(int i = 0; i < 3; i++)
	{
		if(field[0][i].size() > 0 && field[1][i].size() > 1 && field[2][i].size() > 2 && teamSide == field[0][i][0] && teamSide == field[1][i][1] && teamSide == field[2][i][2])
		{
			frontBack++;
		}
		if(field[0][i].size() > 2 && field[1][i].size() > 1 && field[2][i].size() > 0 && teamSide == field[0][i][2] && teamSide == field[1][i][1] && teamSide == field[2][i][0])
		{
			frontBack++;
		}
	}
	//cout << "Front Back: " << frontBack << endl;
	count += frontBack;
	for(int i = 0; i < 3; i++)
	{
		if(field[i][0].size() > 0 && field[i][1].size() > 1 && field[i][2].size() > 2 && teamSide == field[i][0][0] && teamSide == field[i][1][1] && teamSide == field[i][2][2])
		{
			leftRight++;
		}
		if(field[i][0].size() > 2 && field[i][1].size() > 1 && field[i][2].size() > 0 && teamSide == field[i][0][2] && teamSide == field[i][1][1] && teamSide == field[i][2][0])
		{
			leftRight++;
		}
	}
	//cout << "Left Right: " << leftRight << endl;
	count += leftRight;
	for(int i = 0; i < 3; i++)
	{
		if(field[0][0].size() > i && field[1][1].size() > i && field[2][2].size() > i && teamSide == field[0][0][i] && teamSide == field[1][1][i] && teamSide == field[2][2][i])
		{
			sameLayer++;
		}
		if(field[2][0].size() > i && field[1][1].size() > i && field[0][2].size() > i && teamSide == field[2][0][i] && teamSide == field[1][1][i] && teamSide == field[0][2][i])
		{
			sameLayer++;
		}
	}
	//cout << "Same Layer Diagonal: " << sameLayer << endl;
	count += sameLayer;

	if(field[0][0].size() > 0 && field[1][1].size() > 1 && field[2][2].size() > 2 && teamSide == field[0][0][0] && teamSide == field[1][1][1] && teamSide == field[2][2][2])
	{
		count++;
	}
	if(field[0][0].size() > 2 && field[1][1].size() > 1 && field[2][2].size() > 0 && teamSide == field[0][0][2] && teamSide == field[1][1][1] && teamSide == field[2][2][0])
	{
		count++;
	}
	if(field[2][0].size() > 0 && field[1][1].size() > 1 && field[0][2].size() > 2 && teamSide == field[2][0][0] && teamSide == field[1][1][1] && teamSide == field[0][2][2])
	{
		count++;
	}
	if(field[2][0].size() > 2 && field[1][1].size() > 1 && field[0][2].size() > 0 && teamSide == field[2][0][2] && teamSide == field[1][1][1] && teamSide == field[0][2][0])
	{
		count++;
	}
	return count;
}

void TicTacToe::viewAll()
{
	char hold[27];   //create array to hold field integers
	int count = 0;  //create counter to store integers in the array
	for (int i = 0; i < 3; i++) {
	//loop through the field and store integers
		for (int j = 0; j < 3; j++) {
			int l = field[i][j].size();
			for (int k = 0; k < 3; k++) {
				if(k<l){
					if(field[i][j][k]==1){
						hold[count] = 'B';
					}
					else{
						hold[count] = 'R';
					}	
				}
				else{
					hold[count] = 'N';
				}
				count++;	//updating the counter
			}
		}
	}

	//Prints out the field
	std::cout << "    " << hold[20] << " --- " << hold[23] << " --- " << hold[26] << std::endl;
	std::cout << "   /     /     /|" << std::endl;
	std::cout << "  " << hold[11] << " --- " << hold[14] << " --- " << hold[17] << " |" << std::endl;
	std::cout << " /     /     /  |" << std::endl;
	std::cout << hold[2] << " --- " << hold[5] << " --- " << hold[8] << "   |" << std::endl;
	std::cout << "|               |" << std::endl;
	std::cout << "|   " << hold[19] << " --- " << hold[22] << " --- " << hold[25] << std::endl;
	std::cout << "|  /     /     /|" << std::endl;
	std::cout << "| " << hold[10] << " --- " << hold[13] << " --- " << hold[16] << " |" << std::endl;
	std::cout << "|/     /     /  |" << std::endl;
	std::cout << hold[1] << " --- " << hold[4] << " --- " << hold[7] << "   |" << std::endl;
	std::cout << "|               |" << std::endl;
	std::cout << "|   " << hold[18] << " --- " << hold[21] << " --- " << hold[24] << std::endl;
	std::cout << "|  /     /     / " << std::endl;
	std::cout << "| " << hold[9] << " --- " << hold[12] << " --- " << hold[15] << "  " << std::endl;
	std::cout << "|/     /     /   " << std::endl;
	std::cout << hold[0] << " --- " << hold[3] << " --- " << hold[6] << "    " << std::endl;
}

void TicTacToe::changeTurn(){
	actionsLeft = 3;
	teamSide = teamSide * (-1);
	removedBall = false;
}

void TicTacToe::viewTop() {
	for (int y = 2; y >= 0; y--) {
		for (int x = 0; x < 3; x++) {
			int value;

			if (field[y][x].size() == 0) {
				value = 0;
			}
			else {
				value = field[y][x].back(); // will be 1 (blue) or -1 (red) or 0 (empty)
			}
			
			if (value == 1) {
				std::cout << "b";
			}
			else if (value == -1) {
				std::cout << "r";
			}
			else if (value == 0) {
				std::cout << "x";
			}
			else {
				std::cout << "?";
			}   
			std::cout << " ";
		}
		std::cout << "\n";
	}
}

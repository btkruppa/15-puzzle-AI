/*
Creator: Blake Kruppa

The purpose of this application is to play a virtual 15 puzzle game or
to have an AI solve it. 

*/////////////////////////////////////////////////////////

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <string>
#include <array>
#include <queue>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;
int sleepAmount = 0; //the pause between moves
int AIsleep = 100; //the pause between moves for the AI
bool mixing = false; //so that we don't output when the board is being mixed
bool trackWin = false; //this is for a win tracking mode that doesn't output the board

//initialize the board as a global array
int board[17] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0 };

//function to show current state of the board at any given time
void outputBoard() {
	if (mixing == true) {
		return;
	}
	if (trackWin == true) {
		return;
	}
	cout << string(20, '\n');
	cout << setw(2) << board[1] << " " << setw(2) << board[2] << " " << setw(2) << board[3] << " " << setw(2) << board[4] << endl;
	cout << setw(2) << board[5] << " " << setw(2) << board[6] << " " << setw(2) << board[7] << " " << setw(2) << board[8] << endl;
	cout << setw(2) << board[9] << " " << setw(2) << board[10] << " " << setw(2) << board[11] << " " << setw(2) << board[12] << endl;
	cout << setw(2) << board[13] << " " << setw(2) << board[14] << " " << setw(2) << board[15] << " " << setw(2) << board[16] << endl;
	Sleep(sleepAmount);
}

//find location in the array of the tile requested
int findTile(int tile) {
	for (int i = 1; i <= 16; i++) {
		if (board[i] == tile) {
			return i;
		}
	}
	return 0;
}

//function to move the 0 tile in a specified direction
void move(int direction) { //direction 0 moves up, 1 moves right, 2 moves down, 3 moves left
	int temp;					   
	int current = 0; //current is the current location of the 0 tile

	//locate the 0 tile so that it can be moved
	current = findTile(0);

	//if the 0 tile somehow no longer exists it will terminate function
	if (current == 0) {
		cout << "0 tile lost";
		return;
	}
	
	//switch statement to move based on given direction call
	switch (direction) {
	case 0: {
		if (current <= 4) {
			return;
		}
		else {
			temp = board[current];
			board[current] = board[current - 4];
			board[current - 4] = temp;
			outputBoard();
			return;
		}
	}
	case 1: {
		if (current == 4 || current == 8 || current == 12 || current == 16) {
			return;
		}
		else {
			temp = board[current];
			board[current] = board[current + 1];
			board[current + 1] = temp;
			outputBoard();
			return;
		}
	}
	case 2: {
		if (current >= 13) {
			return;
		}
		else {
			temp = board[current];
			board[current] = board[current + 4];
			board[current + 4] = temp;
			outputBoard();
			return;
		}
	}
	case 3: {
		if (current == 1 || current == 5 || current == 9 || current == 13) {
			return;
		}
		else {
			temp = board[current];
			board[current] = board[current - 1];
			board[current - 1] = temp;
			outputBoard();
			return;
		}
	}
	}

}

//function to randomly mix the board up to be solved
void mixBoard() {
	mixing = true;
	srand(time(NULL));
	int mixAmount = rand() % 1000 + 1000;
	for (int i = 0; i <= mixAmount; i++) {
		move(rand() % 4);
	}
	mixing = false;
	return;
}

//function to see if the game is won, returns true if game is won
bool checkWin() { 
	for (int i = 1; i <= 15; i++) {
		if (board[i] != i) {
			return false;
		}
	}
	if (!trackWin) {
		for (int i = 1; i <= 10; i++) {
			cout << "GAME WON!!!!!!!!!\n";
		}
	}
	
	return true;
}

//get the row of a "tile"
int row(int tile) {
	tile = findTile(tile);
	if (tile <= 4) {
		return 1;
	}
	if (tile > 4 && tile <= 8) {
		return 2;
	}
	if (tile > 8 && tile <= 12) {
		return 3;
	}
	//if all others fail it is in row 4
	return 4;
}

//get the column of a "tile"
int column(int tile) {
	tile = findTile(tile);
	if (tile == 1 || tile == 5 || tile == 9 || tile == 13) {
		return 1;
	}
	if (tile == 2 || tile == 6 || tile == 10 || tile == 14) {
		return 2;
	}
	if (tile == 3 || tile == 7 || tile == 11 || tile == 15) {
		return 3;
	}
	//if all others fail it is in column 4
	return 4;
}

//function for AI to move tile 1,2,5 or 6 into correct positions
void move1_2_5_6(int tile) {
	int rowGoal;
	int columnGoal;
	if (tile == 1 || tile == 2) {
		rowGoal = 1;
		columnGoal = tile;
	}
	else if(tile == 5){
		rowGoal = 2;
		columnGoal = 1;
	}
	else if (tile == 6) {
		rowGoal = 2;
		columnGoal = 2;
	}
	/*int row(0)t = getRow(0);
	int row(tile)t = getRow(tile);
	int col0t = getColumn(0);
	int col1t = getColumn(tile);*/
	int looper = 0;
	if (tile == 2 || tile == 6) {
		//this fixes a problem where 1 could get moved without this in cases
		if (column(0) == 1 && column(tile) != 1 ) {
			if (!(column(tile) == 1 && row(tile) == rowGoal+1)) {
				move(1);
			}

		}
		else if (column(tile) == 1) {
			if (column(0) == 1) {
				move(1);
			}
			while (row(0) < row(tile)) {
				move(2);
			}
			while (row(0) > row(tile)) {
				move(0);
			}
			while (column(0) >= column(tile)) {
				move(3);
			}
		}
		if (column(0) == 2 && column(tile) == 1 && row(0) == rowGoal+1 && row(tile) == rowGoal+1) {
			move(3);
		}
		if (column(0) == 1 && column(tile) == 2 && row(0) == rowGoal+1 && row(tile) == rowGoal+1) {
			move(2);
			move(1);
			move(1);
			move(0);
			move(0);
			move(3);
			move(2);
			return;
		}
	}
	
	while (row(tile) != rowGoal) {
		looper++;
		if (looper >= 50) {
			/*cout << "row 0 : " << row(0)t << endl;
			cout << "col 0 : " << col0t << endl;
			cout << "row 1 : " << row(tile)t << endl;
			cout << "col 1 : " << col1t << endl;*/
			return;
		}
		if (column(0) == column(tile)) {
			while (column(0) == column(tile)) {
				if (row(0) < row(tile)) {
					move(2);
					if (row(tile) == rowGoal && column(tile) == columnGoal) {
						return;
					}
				}
				else if (column(0) == 4) {
					move(3);
				}
				else {
					move(1);
				}
			}
		}
		else if(row(0) >= row(tile)){
			while (row(0) >= row(tile)) {
				move(0);
			}
		}
		else if (row(0) < row(tile)) {
			while (column(0) < column(tile)) {
				move(1);
			}
			while (column(0) > column(tile)) {
				move(3);
			}
		}
		Sleep(sleepAmount);
	}
	while (column(tile) != columnGoal) {
		looper++;
		if (looper >= 50) {
			/*cout << "row 0 : " << row(0)t << endl;
			cout << "col 0 : " << col0t << endl;
			cout << "row 1 : " << row(tile)t << endl;
			cout << "col 1 : " << col1t << endl;*/
			return;
		}
		if (row(0) == rowGoal) {
			if (column(0) < column(tile)) {
				move(1);
			}
			if (column(0) > column(tile)) {
				move(2);
			}
		}
		else if (column(0) >= column(tile)) {
			move(3);
		}
		else if (column(0) < column(tile)) {
			move(0);
		}
	}
}

//function for AI to move tile 3 or 7 into correct positon
void move3_7(int tile) {
	int rowGoal = 0;
	if (tile == 3) {
		rowGoal = 1;
	}
	else {
		rowGoal = 2;
	}
	while (column(tile) != 4) {
		if (column(0) > column(tile)) {
			while (row(0) < row(tile)) {
				move(2);
			}
			while (row(0) > row(tile)) {
				move(0);
			}
			if (row(0) == row(tile)) {
				move(3);
			}
		}
		else if (column(0) <= column(tile)) {
			if (row(0) != row(tile)) {
				while (column(0) <= column(tile)) {
					move(1);
				}
			}
			else if (row(0) == row(tile)) {
				if (row(0) == 4) {
					move(0);
				}
				else {
					move(2);
				}
			}
		}
	}
	while (row(tile) != rowGoal) {
		if (column(0) == column(tile)) {
			while (row(0) < row(tile)) {
				move(2);
			}
			if (row(0) > row(tile)) {
				move(3);
			}
		}
		else {
			while (column(0) != 3) {
				move(1);
			}
			while (row(0) >= row(tile)) {
				move(0);
			}
			move(1);
		}
	}
}

//function for AI to move tile 4 or 8 into correct position
void move4_8(int tile) {
	int rowGoal = 0;
	if (tile == 4) {
		rowGoal = 1;
	}
	else {
		rowGoal = 2;
	}
	if (row(tile) == rowGoal && row(tile - 1) == rowGoal && column(tile) == 3 && column(tile - 1) == 4) {
		while (column(0) != 4) {
			move(1);
		}
		while (row(0) != rowGoal + 1) {
			move(0);
		}
		move(0);
		move(3);
		move(2);
		move(2);
		move(1);
		move(0);
		move(3);
		move(2);
		move(1);
		move(0);
		move(3);
		move(0);
		move(1);
		move(2);
		move(3);
		move(2);
		move(1);
		move(0);
		move(0);
		move(3);
		move(2);
		return;

	}
	else if (row(0) == rowGoal) {
		move(2);
		move4_8(tile);
	}
	else {
		while (column(tile) != 4) {
			if (row(0) == row(tile)) {
				while (column(0) > column(tile)) {
					move(3);
				}
				if (column(0) < column(tile)) {
					if (row(0) == 4) {
						move(0);
					}
					else {
						move(2);
					}
				}
			}
			else {
				while (column(0) <= column(tile)) {
					move(1);
				}
				while (row(0) < row(tile)) {
					move(2);
				}
				while (row(0) > row(tile)) {
					move(0);
				}
			}
		}
		while (row(tile) != rowGoal + 1) {
			if (column(0) == column(tile)) {
				while (row(0) < row(tile)) {
					move(2);
				}
				if (row(0) > row(tile)) {
					move(3);
				}
			}
			else {
				while (column(0) != 3) {
					move(1);
				}
				if (row(0) >= row(tile)) {
					move(0);
				}
				else {
					move(1);
				}
			}
		}
		if (column(0) == 4) {
			move(3);
		}
		else {
			while (column(0) != 3) {
				move(1);
			}
		}
		while (row(0) != rowGoal) {
			move(0);
		}
		move(1);
		move(2);
	}
}

//function for AI to move tile 9 into correct position
void move9() {
	if (row(9) == 4) {
		if (row(0) == 4) {
			move(0);
		}
		while (column(0) < column(9)) {
			move(1);
		}
		while (column(0) > column(9)) {
			move(3);
		}
		move(2);
	}
	while (column(9) != 1) {
		if (row(0) == 3) {
			while (column(0) < column(9)) {
				move(1);
			}
			move(2);
		}
		while (column(0) >= column(9)) {
			move(3);
			if (column(9) == 1) {
				return;
			}
		}
		if (column(0) < column(9) && row(0) == 4) {
			move(0);
		}
	}
}

//function for AI to move tile 10 into correct position
void move10() {
	if (column(0) == 1) {
		move(1);
	}
	if (column(10) == 1) {
		while (column(0) != 2) {
			move(3);
		}
		if (row(0) == 3) {
			move(2);
		}
		move(3);
		move(0);
		move(1);
		move(2);
		move(1);
		move(0);
		move(3);
		move(3);
		move(2);
		move(1);
		move(0);
		move(1);
		return;
	}
	else {
		if (row(10) == 4) {
			if (row(0) == 4) {
				move(0);
			}
			while (column(0) < column(10)) {
				move(1);
			}
			while (column(0) > column(10)) {
				move(3);
			}
			move(2);
		}
		while (column(10) != 2) {
			if (row(0) == 3) {
				while (column(0) < column(10)) {
					move(1);
				}
				move(2);
			}
			while (column(0) >= column(10)) {
				move(3);
			}
			if (column(0) < column(10)) {
				if (column(10) == 2) {
					return;
				}
				move(0);
			}
		}
	}
}

//function for AI to move 9 and 10 to side to work on 11 and 12
void move9_10side() {
	if (row(0) == 3) {
		move(2);
	}
	while (column(0) != 1) {
		move(3);
	}
	move(0);
	move(1);
}

//function for AI to move tile 12 into correct position
void move12() {
	if (row(12) == 4) {
		if (row(0) == 4) {
			move(0);
		}
		while (column(0) < column(12)) {
			move(1);
		}
		while (column(0) > column(12)) {
			move(3);
		}
		move(2);
	}
	while (column(12) != 4) {
		if (row(0) == 3) {
			while (column(0) > column(12)) {
				move(3);
			}
			move(2);
		}
		else {
			while (column(0) <= column(12)) {
				move(1);
			}
			move(0);
		}

	}
}

//function for AI to move tile 11 into correct position
void move11() {
	if (column(0) == 4) {
		move(3);
	}
	if (column(11) == 4) {
		if (row(0) == 3) {
			move(2);
		}
		while (column(0) != 3) {
			move(1);
		}
		move(1);
		move(0);
		move(3);
		move(2);
		move(3);
		move(0);
		move(1);
		move(1);
		move(2);
		move(3);
		move(0);
		move(3);
		return;
	}
	else {
		if (row(11) == 4) {
			if (row(0) == 4) {
				move(0);
			}
			if (column(0) < column(11)) {
				move(1);
			}
			else if (column(0) > column(11)) {
				move(3);
			}
			move(2);
		}
		if (column(11) == 3) {
			return;
		}
		else {
			if (row(0) == 4) {
				if (column(0) == 2) {
					move(1);
				}
				if (column(0) == 3) {
					move(0);
					move(3);
					return;
				}
			}
		}

	}
}

//function for AI to move 11 and 12 to other side to finish 13-15
void move11_12side() {
	if (row(0) == 3) {
		move(2);
	}
	while (column(0) != 4) {
		move(1);
	}
	move(0);
	move(3);
}

//function for AI to finish the puzzle after all previous steps
void moveFinish() {
	if (column(0) == 3) {
		move(3);
	}
	if (row(0) == 4) {
		move(0);
	}
	while (board[14] != 13) {
		move(2);
		move(1);
		move(0);
		move(3);
	}
	move(3);
	move(2);
	move(1);
	move(1);
	move(0);
	move(1);
	move(2);
	return;
}

//function to solve the puzzle by AI
void AI_solve() {
	for (int i = 0; i <= 10; i++) {
		outputBoard();
	}

	sleepAmount = AIsleep;
	char choice = ' ';

	move1_2_5_6(1);
	move1_2_5_6(2);
	//3 is moved to top right corner instead of slot 3 so that 4 can be moved below it and then both into correct positions
	move3_7(3);
	move4_8(4);
	move1_2_5_6(5);
	move1_2_5_6(6);
	//7 and 8 are similar movements to 3 and 4
	move3_7(7);
	move4_8(8);
	move9();
	move10();
	//after 1-10 are in position it is best to move 9 and 10 to the left side before working with 11 and 12
	move9_10side();
	move12();
	move11();
	//move 11 and 12 to the right side now
	move11_12side();
	moveFinish();
	if (!checkWin()) {
		cout << "AI failed, sad day :(" << endl;
		choice = _getch();
	}
	if (!trackWin) {
		cout << "press any key to return to the game menu" << endl;
		choice = _getch();
	}
	return;
}

//function for user play mode
void userPlay() {
	sleepAmount = 0;
	char choice = ' ';
	//w is for up, s is for down, d is for right, a is for left
	while (choice != '0') {
		choice = _getch();
		switch (choice) {
		case 'w': {
			move(0);
			break;
		}
		case 'd': {
			move(1);
			break;
		}
		case 's': {
			move(2);
			break;
		}
		case 'a': {
			move(3);
			break;
		}
		case 'q': {
			return;
			break;
		}
		}
		outputBoard();

		//cout << choice << endl;
		if (board[16] == 0) {
			if (checkWin()) {
				cout << "press any key to return to the game menu" << endl;
				choice = _getch();
				return;
			}
		}
	}
}

//main function running the game
int main()
{
	
	char choice = ' '; //the users choice for game mode or to quit
	
	//loop for playing the game multiple times
	while (choice != '0') {
		mixBoard(); //call function to mix the game board
		outputBoard(); //call function to output the game board
		cout << "Enter u to play the game yourself\nEnter i to have the AI solve it\nEnter z to enter a win counting mode\nEnter 0 to quit at anytime\nEnter any other key to remix the gameboard\n";
		choice = _getch(); //get users selection
		if (choice == 'u') {
			sleepAmount = 0; //user mode does not need a wait between moves

			//output board several times, this allows the game to store in memory so that display is faster
			for (int i = 0; i <= 10; i++) {
				cout << string(20, '\n');
				outputBoard();
			}

			cout << "game begun" << endl;
			cout << "Only the 0 tile moves" << endl;
			cout << "Press 'w' to move it up, 'd' for right" << endl;
			cout << "'s' for down, 'a' for left" << endl;
			userPlay(); //enter user play mode
		}
		else if (choice == 'i') {
			AI_solve();
		}
		else if (choice == '0') {
			return 0;
		}
		else if (choice == 'z') { //win track mode has no output but keeps solving the puzzle over and over endlessly and
								//outputs how many times it has been solved
			trackWin = true;
			sleepAmount = 0;
			int solves = 0;
			while (1) {
				solves++;
				cout << solves << endl;
				AI_solve();
				mixBoard();
			}
		}
		else {
			cout << endl << "not a valid choice" << endl;
		}
	}
	return 0;
}
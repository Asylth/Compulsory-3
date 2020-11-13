#include "Declarations.h"
#include "Battleship.h"


void battleship() {
	makeEmptyBoard();
	makeBoard(numberOfShips);
	play();
}

void shoot() {
	std::string cell;
	int x;
	int y;
	std::cout << "Please use the standard Chess format with big letters! \n";
	std::cout << "What cell do you want to shoot: ";
	std::cin >> cell;
	std::cout << std::endl;
	x = cell.front() - 65;
	y = cell.back() - 49;
	std::cout << "x: " << x << " y: " << y << std::endl;

	if (board[y][x] == 'S') {
		std::cout << "Hit! \n";
		board[y][x] = 'H' ;
		numberOfShots++;
		numberOfHits++;
	}
	else if (board[y][x] == 'H' || board[y][x] == 'M') {
		numberOfShots++;
	}
	else {
		std::cout << "Miss! \n";
		board[y][x] = 'M';
		numberOfShots++;
	}
}

void printPlayerBoard() {
	std::cout << std::endl;
	std::cout << "Number of Hits: " << numberOfHits << std::endl;
	std::cout << "Number of Shots: " << numberOfShots << std::endl;
	for (int i = 0; i < M; i++) {
		std::cout << numCollum[i][0];
		for (int j = 0; j < N; j++) {
			std::cout << '|';
			if (board[i][j] == 'S') {
				std::cout << ' ';
			}
			else {
				std::cout << board[i][j];
			}
			//std::cout << pboard[i][j];
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	writeLetters();
}

void printboard() {
	for (int i = 0; i < M; i++) {
		std::cout << numCollum[i][0];
		for (int j = 0; j < N; j++){
			std::cout << '|';
			std::cout << board[i][j];
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	writeLetters();
}

void writeLetters() {
	std::cout << " -------------" << std::endl << " ";
	for (int l = 0; l < N; l++) {
		std::cout << "|";
		std::cout << numRow[0][l];
	}
	std::cout << "|";
	std::cout << std::endl;
}

int getrandom() {
	return rand() % M;
}

int randomRow() {
	bool temp = false;
	int x;
	while (temp == false) {
		x = getrandom();
		for (int i = 0; i < M; i++) {
			if (board[x][i] == ' ') {
				return x;
			}else{}
		}
	}
}

int randomColumn() {
	bool temp = false;
	int y;
	while (temp == false) {
		y = getrandom();
		for (int i = 0; i < M; i++) {
			if (board[i][y] == ' ') {
				return y;
			}else {}

		}
	}
}

void makeBoard(int numberOfShips) { //does not print 11 ships, is seems to be random and i cannot figure it out.
	int nr = 0;
	while (nr <= numberOfShips) {//makes sure the for loop
		//for (int i = 0; i <= numberOfShips; i++) {
			int y = randomColumn();
			int x = randomRow();
			board[y][x] = 'S';
			if (board[y][x] == 'S') {
				nr++;
			}
		//}
	}
}



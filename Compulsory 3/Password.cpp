#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <Windows.h>

#include "Declarations.h"

bool passcode();
void printpass();
void lockmove();
void resetpos();
void paschange();

std::string password;
std::string userpass;
const int lockh = 4;
const int lockl = 4;
char lockArray[lockh][lockl] = {
	{'*', 'B', 'C', 'D'},
	{'E', 'F', 'G', 'H'},
	{'I', 'J', 'K', 'L'},
	{'M', 'N', 'O', 'P'}
};
const char lockvalArray[lockh][lockl] = {
	{'A', 'B', 'C', 'D'},
	{'E', 'F', 'G', 'H'},
	{'I', 'J', 'K', 'L'},
	{'M', 'N', 'O', 'P'}
};
int lockmoves = 0;
int attempts = 0;
int lockposx = 0;
int lockposy = 0;
bool rightpas = false;
int length;
std::string input;

int startpass() {

	std::srand(time(nullptr));
	std::fstream Passf("Password.txt", std::ios::in);
	Passf >> password;
	length = password.length();
	passcode();
	if (attempts == 3) {
		exit(0);
	}
	else if (rightpas == true) {
		system("CLS");
		return 0;
	}
}


bool passcode() {
	do {
		while (lockmoves < 10) {
			std::fstream File1("Userpass.txt", std::ios::out, std::ios::trunc);
			File1.close();
			std::cout.unsetf(std::ios::trunc);
			printpass();
			lockmove();
			lockmoves++;
			int res = password.compare(userpass);
			if (res == 0){
				return true;
			}
		};
		resetpos();
		std::cout << "Wrong password! Try again\n";
		Sleep(1000);
		lockmoves = 0;
		attempts++;
	} while (attempts <= 3);

}

void printpass() {
	system("CLS");
	std::cout << "------------------" << std::endl;
	for (int j = 0; j < lockh; j++) {
		for (int i = 0; i < lockl; i++) {
			std::cout << " | ";
			std::cout << lockArray[j][i];
			if (i == 3) {
				std::cout << " | " << std::endl;
			}
		}
		std::cout << std::endl;
		
	}
	std::cout << userpass;
}


void lockmove() {
	char ch;
	if (lockmoves == 0) {
		std::fstream Rfile("Userpass.txt", std::ios::out | std::ios::app);
		Rfile << lockvalArray[lockposy][lockposx];
		Rfile.close();
	}
	if (lockposx != 3) {
		lockArray[lockposy][lockposx] = lockvalArray[lockposy][lockposx + 1] - 1;
	}
	else {
		lockArray[lockposy][lockposx] = lockvalArray[lockposy][lockposx - 1] + 1;
	}


	ch = _getch();
	switch (_getch()) {
	case 'w': case 'W': case 'H': //up
		if (lockposy != 0) {
			lockposy = lockposy - 1;
		}
		break;
	case 's': case 'S': case 'P': //down
		if (lockposy != 3) {
			lockposy = lockposy + 1;
		}
		break;
	case 'a': case 'A': case 'K': // left
		if (lockposx != 0) {
			lockposx = lockposx - 1;
		}
		break;
	case 'd': case 'D': case 'M': //right
		if (lockposx != 3) {
			lockposx = lockposx + 1;
		}
		break;
	}

	
	std::fstream File2("Userpass.txt", std::ios::out | std::ios::app);
	File2 << lockvalArray[lockposy][lockposx];
	File2.close();

	std::fstream Wfile("Userpass.txt", std::ios::in);
	while (!Wfile.eof()) {
		std::getline(Wfile, userpass);
	};

	lockArray[lockposy][lockposx] = '*';
}


void resetpos() {
	char restr = 'B';
	//std::fstream File1("Userpass.txt", std::ios::out | std::ios::trunc);
	//File1.close();
	lockposx = 0;
	lockposy = 0;
	lockArray[lockposy][lockposx] = '*';
	for (int j = 0; j < lockh; j++) {
		for (int i = 0; i < lockl; i++) {
			if (i == 0 && j == 0) {
			}
			else {
				lockArray[j][i] = restr;
				restr++;
			}
		}
	}
}


void changepas() {
	char pchoice;
	int newpas;
	std::cout << "\n Do you want to change the password? (Y/N) \n";
	std::cin >> pchoice;
	switch (pchoice) {
	case 'y':case 'Y':
		std::cout << "Only letters will work! \n";
		std::cout << "Type in the new password: ";
		while (!std::cin.eof()) {
		std::getline(std::cin, input);
		}

		std::cout << input << std::endl;
		paschange();
		break;
	case 'n':case 'N':
		break;
	}
}

void paschange() {
	for (int i = 0; i < input.length(); i++) {
		input[i] = toupper(input[i]);
	}
	std::fstream Passfile("Password.txt", std::ios::out);
	Passfile << input;
	Passfile.close();
	std::cout << input << std::endl;
}
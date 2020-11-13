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
	std::fstream Passf("Password.txt", std::ios::in); //loads password from file
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


bool passcode() { //for locking the number of moves and logic for making it work
	do {
		while (lockmoves < 10) {
			//std::fstream File1("Userpass.txt", std::ios::out); //To clean userpass
			//File1.close();
			std::cout.unsetf(std::ios::trunc);
			//std::ofstream outf{ "Userpass.txt" };
			printpass(); //prints the board
			lockmove();
			lockmoves++;
			int res = password.compare(userpass); //checks if passwords match
			if (res == 0){
				return true;
			}
		};
		resetpos(); //resets the arrays and vars
		std::cout << "Wrong password! Try again\n";
		Sleep(1000);
		lockmoves = 0;
		attempts++;
	} while (attempts <= 3);

}

void printpass() { //prints the array
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
	if (lockmoves == 0) { //places A at the start of the file
		//std::fstream Rfile("Userpass.txt", std::ios::out | std::ios::app);
		//Rfile << lockvalArray[lockposy][lockposx];
		//Rfile.close();
		std::ofstream File{ "Userpass.txt" };
		File << lockvalArray[lockposy][lockposx];
		File.close();
	}
	if (lockposx != 3) { //changes player pos to its actuall value
		lockArray[lockposy][lockposx] = lockvalArray[lockposy][lockposx + 1] - 1;
	}
	else {
		lockArray[lockposy][lockposx] = lockvalArray[lockposy][lockposx - 1] + 1;
	}


	ch = _getch(); //condition check and moves player pos
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

	
	//std::fstream File2("Userpass.txt", std::ios::out | std::ios::app);
	std::ofstream File1{ "Userpass.txt", std::ios::app}; //opens userpass to append the char the player moved to
	File1 << lockvalArray[lockposy][lockposx];
	File1.close();

	std::ifstream File2{ "Userpass.txt" }; //takes everything in the file and writes it to userpass variable for later comparison
	//std::fstream Wfile("Userpass.txt", std::ios::in);
	while (!File2.eof()) {
		std::getline(File2, userpass);
	};
	File2.close();


	lockArray[lockposy][lockposx] = '*'; //moves player icon to new pos
}


void resetpos() { //resets the player pos when you enter a wrong password
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


//void changepas() {//for changing the password, not sure if working yet
//	char pchoice;
//	int newpas;
//	std::cout << "\n Do you want to change the password? (Y/N) \n";
//	std::cin >> pchoice;
//	switch (pchoice) {
//	case 'y':case 'Y':
//		std::cout << "Only letters will work! \n";
//		std::cout << "Type in the new password: ";
//		while (!std::cin.eof()) {
//		std::getline(std::cin, input);
//		}
//		std::cout << input << std::endl;
//		paschange();
//		break;
//	case 'n':case 'N':
//		break;
//	}
//}
//
//void paschange() {//had to make this a separate funtion because it did not work inside a switch function
//	for (int i = 0; i < input.length(); i++) {
//		input[i] = toupper(input[i]);
//	}
//	std::fstream Passfile("Password.txt", std::ios::out);
//	Passfile << input;
//	Passfile.close();
//	std::cout << input << std::endl;
//}

void changepas() {//for changing the password
	char pchoice;
	int newpas;
	std::cout << "\n Do you want to change the password? (Y/N) \n";
	std::cin >> pchoice;
	switch (pchoice) {
	case 'y':case 'Y':
		std::cout << "Only letters will work! \n";
		std::cout << "Type in the new password: ";
		std::cin >> input;
		std::cout << input << std::endl;
		paschange();
		break;
	case 'n':case 'N':
		break;
	}
}

void paschange() {//had to make this a separate funtion because it did not work inside a switch function
	for (int i = 0; i < input.length(); i++) {
		input[i] = toupper(input[i]);
	}
	std::fstream Passfile("Password.txt", std::ios::out | std::ios::trunc);
	Passfile << input << std::endl;
	Passfile.close();
	std::cout << input << std::endl;
}
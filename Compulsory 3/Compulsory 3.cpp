#include "Declarations.h"




int main()
{
	srand(time(NULL));
	std::fstream File1("Userpass.txt", std::ios::out); //To clean userpass
	File1.close();
	startpass();
	menu();
	battleship();

}

void menu() {
	char temp;
	std::cout << "Main menu" << std::endl;
	std::cout << "1. Change password" << std::endl;
	std::cout << "2. Play battleship" << std::endl;
	std::cout << "3. Quit" << std::endl;
	std::cout << "Select an option (1-3): " << std::endl;
	switch (_getch()) {
	case 1:
		changepas();
		break;
	case 2:
		battleship();
		break;
	case 3:
		exit(0);
		break;
	}

}
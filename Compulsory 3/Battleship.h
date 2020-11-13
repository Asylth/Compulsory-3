
const int M = 6;
const int N = 6;
const int numberOfShips = 11;

//struct boards {
//	char board; // for printing
//}pboard, vboard;
char board[M][N];
//= { {' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' '} };
//char pboard[M][N] = { {' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' '} };
int numCollum[M][1];
//= { { 1 }, { 2 }, { 3 }, { 4 }, { 5 }, { 6 } };
char numRow[1][N];
//= { 'A', 'B', 'C', 'D', 'E', 'F' };
int posx;
int posy;
int numberOfHits;
int numberOfShots;
int amountOfShots;


void play();
void makeEmptyBoard();
void printboard();
int randomRow();
int randomColumn();
void writeLetters();
int getrandom();
void makeBoard(int numberOfShips);
void makeEmptyBoard() { //fills out the arrays
	int temp = 1;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = ' ';
		}
	}
	for (int k = 0; k < M; k++) {
		numCollum[k][0] = temp++;
	}
	for (int l = 0; l < N; l++) {
		numRow[0][l] = 'A' + l;
	}
}
void printPlayerBoard();
void shoot();

void play() {
	amountOfShots = 25;
	do {
		printboard();
		printPlayerBoard();
		shoot();
	} while (numberOfShots < amountOfShots || numberOfHits < numberOfShips);
}
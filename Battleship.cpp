#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

// All fuction's prototypes in alphabetical order
bool confirm();
void arrStage();
void attack(char[]);
void battleStage();
void checkError(char[], int);
void computerTurn();
void createGrid();
void credits();
void defeat();
void emptySlot();
void hitSlot();
void input(char &);
void instructions();
void playersGrid();
void printGrid(); // print the current grid
void printSea(char[][11], bool);
void reset(char[][11]);
void settings();
void shipNumber();
void showGameMenu();
void showSettingsMenu();
void startFirst();
void startGame();
void userInput(char [], int);
void userTurn();
void victory();
void welcome();
void winning();
void PCship();


// All global variables

bool hidden = 0; // default ship position of PC
bool turn = 0; // default attack priority - player first
bool higherP = 0;
int row, column, ship, shipC;
int seaSize = 10; // default sea size
int carrier = 1, battleship = 2, submarine = 3, destroyer = 4; // default number of ships
const int maxShip = 5; // maximum amount of ships
const int maxInput = 3; // acceptable maximum inputs for user
const int carrierSize = 5; //size of carrier
const int battleshipSize = 4; // size of battleship
const int submarineSize = 3; // size of submarine
const int destroyerSize = 2; // size of destroyer
char corner = '+', vBound = '-', hBound = '|'; // symbols of corner, vertical and horizontal boundary 
char coordinate[11][11];
char coordinateC[11][11];
char grid[10][10];

// Carrier class definition
class Carrier
{
public:
	void initialize() {
		sink = 0;
		sinkC = 0;
	}

	// User's
	void arrange() {
		printSea(coordinate, 0);
		cout << "Please choose a coordinate to place your carrier(size: 5): ";
		checkError(arrC, carrierSize);
		r = row;
		c = column;
		
		if (arrC[0] == 'V') {
			for (int i = 0; i < carrierSize; i++)
				coordinate[r + i][c] = 'O';
		}	
		else {
			for (int i = 0; i < carrierSize; i++)
				coordinate[r][c + i] = 'O';
		}
		system("cls");
	}
	
	void check() {
		count = 0;
		if (sink == 0) {
			if (arrC[0] == 'V') {
				for (int i = 0; i < carrierSize; i++) {
					if (coordinate[r + i][c] == 'H')
						count++;
				}
			}
			else {
				for (int i = 0; i < carrierSize; i++)
					if (coordinate[r][c + i] == 'H')
						count++;
			}
		}
		else
			return;

		if (count == carrierSize) {
			sink = 1;
			ship -= 1;
			cout << "Your carrier sunk!\n" << endl;
		}
	}

	// PC's
	void arrangeC() {
		d = rand() % 2;
		rC = rand() % (seaSize - carrierSize + 1);
		cC = rand() % (seaSize - carrierSize + 1);
		random = rand() % 10;

		if (d == 0) {
			for (int i = 0; i < carrierSize; i++)
				coordinateC[rC + i][random] = 'O';
		}
		else {
			for (int i = 0; i < carrierSize; i++)
				coordinateC[random][cC + i] = 'O';
		}
	}

	void checkC() {
		countC = 0;
		if (sinkC == 0) {
			if (d == 0) {
				for (int i = 0; i < carrierSize; i++) {
					if (coordinateC[rC + i][random] == 'H')
						countC++;
					else
						break;
				}
			}
			else {
				for (int i = 0; i < carrierSize; i++) {
					if (coordinateC[random][cC + i] == 'H')
						countC++;
					else
						break;
				}
			}
		}
		else
			return;

		if (countC == carrierSize) {
			sinkC = 1;
			shipC -= 1;
			cout << "A PC's carrier sunk!\n" << endl;
		}
	}

private:
	bool sink, sinkC;
	int r, c, d, rC, cC, count, countC ,random;
	char arrC[4]; // array arrangement of user's carrier
};

// Battleship class definition
class Battleship
{
public:
	void initialize() {
		sink = 0;
		sinkC = 0;
	}

	// User's
	void arrange() {
		printSea(coordinate, 0);
		cout << "Please choose a coordinate to place your battleship(size: 4): ";
		checkError(arrB, battleshipSize);
		r = row;
		c = column;

		if (arrB[0] == 'V') {
			for (int i = 0; i < battleshipSize; i++)
				coordinate[r + i][c] = 'O';
		}
		else {
			for (int i = 0; i < battleshipSize; i++)
				coordinate[r][c + i] = 'O';
		}
		system("cls");
	}

	void check() {
		count = 0;
		if (sink == 0) {
			if (arrB[0] == 'V') {
				for (int i = 0; i < battleshipSize; i++) {
					if (coordinate[r + i][c] == 'H')
						count++;
				}
			}
			else {
				for (int i = 0; i < battleshipSize; i++)
					if (coordinate[r][c + i] == 'H')
						count++;
			}
		}
		else
			return;

		if (count == battleshipSize) {
			sink = 1;
			ship -= 1;
			cout << "Your battleship sunk!\n" << endl;
		}
	}

	// PC's
	void arrangeC() {
		d = rand() % 2;
		rC = rand() % (seaSize - battleshipSize + 1);
		cC = rand() % (seaSize - battleshipSize + 1);
		random = rand() % 10;

		if (d == 0) {
			for (int i = 0; i < battleshipSize; i++)
				coordinateC[rC + i][random] = 'O';
		}
		else {
			for (int i = 0; i < battleshipSize; i++)
				coordinateC[random][cC + i] = 'O';
		}
	}

	void checkC() {
		countC = 0;

		if (sinkC == 0) {
			if (d == 0) {
				for (int i = 0; i < battleshipSize; i++) {
					if (coordinateC[rC + i][random] == 'H')
						countC++;
					else
						break;
				}
			}
			else {
				for (int i = 0; i < battleshipSize; i++) {
					if (coordinateC[random][cC + i] == 'H')
						countC++;
					else
						break;
				}
			}
		}
		else
			return;

		if (countC == battleshipSize) {
			sinkC = 1;
			shipC -= 1;
			cout << "A PC's battleship sunk!\n" << endl;
		}
	}

private:
	bool sink, sinkC;
	int r, c, d, rC, cC, count, countC, random;
	char arrB[4]; // array arrangement of user's battleship
};

// Submarine class definition 
class Submarine
{
public:
	void initialize() {
		sink = 0;
		sinkC = 0;
	}

	// User's
	void arrange() {
		printSea(coordinate, 0);
		cout << "Please choose a coordinate to place your submarine(size: 3): ";
		checkError(arrS, submarineSize);
		r = row;
		c = column;

		if (arrS[0] == 'V') {
			for (int i = 0; i < submarineSize; i++)
				coordinate[r + i][c] = 'O';
		}
		else {
			for (int i = 0; i < submarineSize; i++)
				coordinate[r][c + i] = 'O';
		}
		system("cls");
	}

	void check() {
		count = 0;
		if (sink == 0) {
			if (arrS[0] == 'V') {
				for (int i = 0; i < submarineSize; i++) {
					if (coordinate[r + i][c] == 'H')
						count++;
				}
			}
			else {
				for (int i = 0; i < submarineSize; i++)
					if (coordinate[r][c + i] == 'H')
						count++;
			}
		}
		else
			return;

		if (count == submarineSize) {
			sink = 1;
			ship -= 1;
			cout << "Your submarine sunk!\n" << endl;
		}
	}

	// PC's
	void arrangeC() {
		d = rand() % 2;
		rC = rand() % (seaSize - submarineSize + 1);
		cC = rand() % (seaSize - submarineSize + 1);
		random = rand() % 10;

		if (d == 0) {
			for (int i = 0; i < submarineSize; i++)
				coordinateC[rC + i][random] = 'O';
		}
		else {
			for (int i = 0; i < submarineSize; i++)
				coordinateC[random][cC + i] = 'O';
		}
	}

	void checkC() {
		countC = 0;

		if (sinkC == 0) {
			if (d == 0) {
				for (int i = 0; i < submarineSize; i++) {
					if (coordinateC[rC + i][random] == 'H')
						countC++;
					else
						break;
				}
			}
			else {
				for (int i = 0; i < submarineSize; i++) {
					if (coordinateC[random][cC + i] == 'H')
						countC++;
					else
						break;
				}
			}
		}
		else
			return;

		if (countC == submarineSize) {
			sinkC = 1;
			shipC -= 1;
			cout << "A PC's submarine sunk!\n" << endl;
		}
	}

private:
	bool sink, sinkC;
	int r, c, d, rC, cC, count, countC, random;
	char arrS[4]; // array arrangement of user's submarine
};

// Destroyer class definition
class Destroyer
{
public:
	void initialize() {
		sink = 0;
		sinkC = 0;
	}

	// User's
	void arrange() {
		printSea(coordinate, 0);
		cout << "Please choose a coordinate to place your destroyer(size: 2): ";
		checkError(arrD, destroyerSize);
		r = row;
		c = column;

		if (arrD[0] == 'V') {
			for (int i = 0; i < destroyerSize; i++)
				coordinate[r + i][c] = 'O';
		}
		else {
			for (int i = 0; i < destroyerSize; i++)
				coordinate[r][c + i] = 'O';
		}
		system("cls");
	}

	void check() {
		count = 0;
		if (sink == 0) {
			if (arrD[0] == 'V') {
				for (int i = 0; i < destroyerSize; i++) {
					if (coordinate[r + i][c] == 'H')
						count++;
				}
			}
			else {
				for (int i = 0; i < destroyerSize; i++)
					if (coordinate[r][c + i] == 'H')
						count++;
			}
		}
		else
			return;

		if (count == destroyerSize) {
			sink = 1;
			ship -= 1;
			cout << "Your destroyer sunk!\n" << endl;
		}
	}

	// PC's
	void arrangeC() {
		d = rand() % 2;
		rC = rand() % (seaSize - destroyerSize + 1);
		cC = rand() % (seaSize - destroyerSize + 1);
		random = rand() % 10;

		if (d == 0) {
			for (int i = 0; i < destroyerSize; i++)
				coordinateC[rC + i][random] = 'O';
		}
		else {
			for (int i = 0; i < destroyerSize; i++)
				coordinateC[random][cC + i] = 'O';
		}
	}

	void checkC() {
		countC = 0;

		if (sinkC == 0) {
			if (d == 0) {
				for (int i = 0; i < destroyerSize; i++) {
					if (coordinateC[rC + i][random] == 'H') {
					countC++;
					}
				}
			}
			else {
				for (int i = 0; i < destroyerSize; i++) {
					if (coordinateC[random][cC + i] == 'H') {
						countC++;
					}
				}
			}
		}
		else
			return;

		if (countC == destroyerSize) {
			sinkC = 1;
			shipC -= 1;
			cout << "A PC's destroyer sunk!\n" << endl;
		}
	}

private:
	bool sink, sinkC;
	int r, c, d, rC, cC, count, countC, random;
	char arrD[4]; // array arrangement of user's destroyer
};

// Begin
int main()
{
	welcome();
	double option;

	do {
		system("cls");
		showGameMenu();
		cout << "\nOption (1 - 5): ";
		cin >> option;  // ask for user input

		while (cin.fail() || option != (int)option) {
			system("cls");
			showGameMenu();

			if (cin.fail())
				cout << "\n[!] Please input an integer(1-5) instead of character(s).\n";
			else
				cout << "\n[!] Please input an integer(1-5) without any decimal digit(s).\n";

			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Option (1 - 5): ";
			cin >> option;
		}
		cin.ignore(1024, '\n');

		switch ((int)option) {
		case 1: startGame(); break;
		case 2: settings(); break;
		case 3: instructions(); break;
		case 4: credits(); break;
		case 5: cout << "Hope you enjoy the game. Goodbye!" << endl; break;
		default: system("cls");
				 printSea(coordinate, 0);
				 cout << "Please input an integer in a valid range within 1-5." << endl;
		}
	} while (option != 5);
    return 0;
}
// End

void reset(char co[][11]) {
	for (int r = 0; r < seaSize; r++) {
		for (int c = 0; c < seaSize; c++)
			co[r][c] = ' ';
		co[r][seaSize] = '\0'; // append '\0' to coordinate's contents
	}
}

void printSea(char co[][11],bool computer) // print out the sea with coordinates
{
	int temp;
	int length = seaSize * 2; // length of the vertical boundaries

	cout << "   ";
	for (int i = 0; i < seaSize; i++)
		cout << ' ' << i;
	cout << endl << "  " << corner;
	for (int j = 0; j <= length; j++)
		cout << vBound;
	cout << corner << endl;
	
	for (int r = 0; r < seaSize; r++) {
		temp = r + (int)'A';
		cout << (char)temp << ' ' << hBound;
	
		for (int c = 0; c < seaSize; c++) {
			if (computer == 1 && hidden == 0 && co[r][c] == 'O')
				cout << "  ";
			else
				cout << ' ' << co[r][c];
		}
	
		cout << ' ' << hBound << endl;
	}

	cout << "  " << corner;
	for (int j = 0; j <= length; j++)
		cout << vBound;
	cout << corner << endl; 
	cout << endl;
}

void userInput(char arrange[], int type) // check the validation of user input
{
	do {
		switch (type) {
		case 0: break;
		case 1: system("cls");
				printSea(coordinate, 0);
				cout << "[!] Invalid location.\n";
				cout << "You should input a location with one direction and one coordinate.\n";
				cout << "e.g. ""VA0""(with no space) for vertically placed the ship on coordinate A0.\n\n"; break;
		case 2: 
				system("cls");
				printSea(coordinate, 0);
				cout << "[!] The ship has overlapped on other ships.\n\n"; break;
		case 3: system("cls");
				printSea(coordinate, 0);
				cout << "[!] The ship is placed out of boundaries.\n\n"; break;
		}

		if (type != 0)
			cout << "Place it again: ";
		
		for (int i = 0; i < maxInput; i++) {
			cin >> arrange[i];
			if (arrange[i] >= 'a' && arrange[i] <= 'z')
				arrange[i] = arrange[i] - 'a' + 'A';
		}

		cin.ignore(1024, '\n');
		arrange[maxInput] = '\0';

		if ((arrange[0] == 'V' || arrange[0] == 'H') &&
			(arrange[1] >= 'A' && arrange[1] <= 'A' + (seaSize - 1)) &&
			(arrange[2] >= '0' && arrange[2] <= '9'))
			return;
		else
			type = 1;
	} while (true);
}

// Check the validation of user input
void attack(char att[]) {
	do {
		cout << "Input coordinate: ";
		for (int i = 0; i < 2; i++) {
			cin >> att[i];
			if (att[i] >= 'a' && att[i] <= 'z')
				att[i] = att[i] - 'a' + 'A';
		}
		
		cin.ignore(1024, '\n');
		att[2] = '\0';

		if (att[0] >= 'A' && att[0] <= 'A' + (seaSize - 1)) {
			if (att[1] >= '0' && att[1] <= '9') {
				system("cls");
				return;
			}
		}
		system("cls");
		cout << "PC's" << setw(seaSize * 2 - 6) << setfill(' ') << ' ';
		cout << "Ship:" << setw(2) << setfill('0') << shipC << endl;
		printSea(coordinateC, 1);
		cout << endl;
		cout << "Yours" << setw(seaSize * 2 - 8) << setfill(' ') << ' ';
		cout << "Ship: " << setw(2) << setfill('0') << ship << endl;
		printSea(coordinate, 0);
		cout << "Invalid coordinate. Try again." << endl;
	} while (true);
}

void checkError(char arr[],int size) {
	int count = 0;
	userInput(arr, 0);
	do {
		row = (int)(arr[1] - 'A');
		column = (int)(arr[2] - '0');

		if (arr[0] == 'V') {
			if ((row + size) <= seaSize) {
				for (int i = 0; i < size; i++) {
					if (coordinate[row + i][column] == ' ')
						count++;
					else
						break;
				}
				if (count == size)
					return;
				else {
					userInput(arr, 2);
					continue;
				}
			}
			else {
				userInput(arr, 3);
				continue;
			}
		}
		else {
			if ((column + size) <= seaSize) {
				for (int i = 0; i < size; i++) {
					if (coordinate[row][column + i] == ' ')
						count++;
					else
						break;
				}
				if (count == size)
					return;
				else {
					userInput(arr, 2);
					continue;
				}
			}
			else {
				userInput(arr, 3);
				continue;
			}
		}
	} while (true);
}

void userTurn() {
	char attackShip[4];

	cout << "It's your turn to attack!" << endl;
	attack(attackShip);

	row = attackShip[0] - 'A';
	column = attackShip[1] - '0';

	if (coordinateC[row][column] == 'O')
		coordinateC[row][column] = 'H';
	else if (coordinateC[row][column] == ' ')
		coordinateC[row][column] = '*';
	else
		cout << "[!] You hit the same coordinate before! You lost one chance!\n\n";
}

void arrStage() {
	cout << "\n\n\n\n\n   ";
	cout << "-";	Sleep(100);
	cout << "A";	Sleep(100);
	cout << "R";	Sleep(100);
	cout << "R";	Sleep(100);
	cout << "A";	Sleep(100);
	cout << "N";	Sleep(100);
	cout << "G";	Sleep(100);
	cout << "E";	Sleep(100);
	cout << "M";	Sleep(100);
	cout << "E";	Sleep(100);
	cout << "N";	Sleep(100);
	cout << "T";	Sleep(100);
	cout << " ";	Sleep(100);
	cout << "S";	Sleep(100);
	cout << "T";	Sleep(100);
	cout << "A";	Sleep(100);
	cout << "G";	Sleep(100);
	cout << "E";	Sleep(100);
	cout << "-";	Sleep(1000);
}

void battleStage() {
	cout << "\n\n\n\n\n   ";
	cout << "-";	Sleep(100);
	cout << "B";	Sleep(100);
	cout << "A";	Sleep(100);
	cout << "T";	Sleep(100);
	cout << "T";	Sleep(100);
	cout << "L";	Sleep(100);
	cout << "E";	Sleep(100);
	cout << " ";	Sleep(100);
	cout << "S";	Sleep(100);
	cout << "T";	Sleep(100);
	cout << "A";	Sleep(100);
	cout << "G";	Sleep(100);
	cout << "E";	Sleep(100);
	cout << "-";	Sleep(1000);
}

void computerTurn() {
	bool hit = 0;
	int markR = 0, markC = 0;

	do {
		if (higherP == 0) {
			row = rand() % (seaSize + 1);
			column = rand() % (seaSize + 1);

			if (coordinate[row][column] == 'O') {
				coordinate[row][column] = 'H';
				markR = row;
				markC = column;
				higherP = 1;
				hit = 1;
			}

			else if (coordinate[row][column] == ' ') {
				coordinate[row][column] = '*';
				hit = 1;
			}
		}
		else {
			switch (rand() % 4) {
				case 1: markR += 1; break;
				case 2: markR -= 1; break;
				case 3: markC += 1; break;
				case 4: markC -= 1; break;
			}

			if (coordinate[markR][markC] == 'O') {
				coordinate[markR][markC] = 'H';
				hit = 1;
			}
			else if (coordinate[row][column] == ' ') {
				coordinate[markR][markC] = '*';
				higherP = 0;
				hit = 1;
			}
		}
	} while (hit == 0);
}

void createGrid() {
	int b = 66;
	cout << "The occupied slots will be marked with a capital letter 'O'\n";
	cout << "Remember that first stage will continue until all ships are placed.\n";
	cout << "For example, player inputs a coordinate of A5 for placing a destroyer horizontally:\n";
	cout << endl;
	cout << setw(6) << "0";

	for (int i = 1; i < 10; i++) {
		cout << setw(2) << i;
	}
	
	cout << endl;
	cout << "   +---------------------+\n";
	cout << " A |           O O       |\n";
	
	for (int x = 0; x < 9; x++) {
		cout << setw(2) << (char)b << setw(2) << "|" << setw(22) << "|";
		b++;

		for (int y = 0; y < 10; y++) {
			cout << setw(2) << grid[x][y];
		}
		cout << endl;
	}
	
	cout << "   +---------------------+\n";
	cout << endl;
	cout << "   Press 'N' to next page." << endl;
	cout << "   Press 'P' to previous page." << endl;
}

void credits() {
	int num[22] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 };
	int list[5] = { 35, 41, 43, 33, 27 }; // declare an array for setw
	const char *credits[44] = { " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "Credits", " ", "Programmers:", " ", "Chan Yan Yi", "16124144A", "204B", "Kwok Pui Yan", "16088860A", "204A", "Ng Ching Yan", "16080315A", "204A", "To Chi Wai Vicki", "16113990A", "204B", "Yeung Kwok Him", "16153809A", "204B", "Yip Yuen Yu", "16191408A", "204A" };

	for (int i = 0; i < 22; i++) {
		system("cls"); // clean the screen before each round

		for (int j = i; j < 22 + num[i]; j++) {
			int x;
			if (j % 3 == 2)
				x = 0;
			if (j % 3 == 0)
				x = 1;
			if (j % 3 == 1)
				x = 2;
			if (j == 22)
				x = 3;
			if (j == 24)
				x = 4;
			cout << setw(list[x]) << credits[j] << endl;
		} Sleep(500); // show string after 0.5 second
	}
	cout << endl << endl << endl;
	system("pause");
	system("cls");
	return;
}

void defeat() {
	system("cls");
	cout << "\n\n\n\n\n   ";
	cout << "-";	Sleep(100);
	cout << "D";	Sleep(100);
	cout << "E";	Sleep(100);
	cout << "F";	Sleep(100);
	cout << "E";	Sleep(100);
	cout << "A";	Sleep(100);
	cout << "T";	Sleep(100);
	cout << ".";	Sleep(100);
	cout << "!";	Sleep(100);
	cout << "\n\n\n\n\n";
	system("pause");
}

void emptySlot() {
	cout << "Player and PC take turns to attack by inputting the slot coordinates.\n";
	cout << "If an empty slot was hit, a '*' will display on screen." << endl;
	cout << "For example, inputting A0.\n";
	cout << endl;
	cout << setw(6) << "0";

	for (int i = 1; i < 10; i++) {
		cout << setw(2) << i;
	}

	cout << "            0 1 2 3 4 5 6 7 8 9";
	cout << endl;
	cout << "   Yours          Ship: 04" << "        PC's           Ship: 04";
	cout << "   +---------------------+" << "        +---------------------+\n";
	cout << " A |           O O       |" << "      A | *                   |\n";
	cout << " B |   O                 |" << "      B |                     |\n";
	cout << " C |   O                 |" << "      C |                     |\n";
	cout << " D |   O               O |" << "      D |                     |\n";
	cout << " E |   O               O |" << "      E |                     |\n";
	cout << " F |   O               O |" << "      F |                     |\n";
	cout << " G |                   O |" << "      G |                     |\n";
	cout << " H |                     |" << "      H |                     |\n";
	cout << " I |                     |" << "      I |                     |\n";
	cout << " J | O O O O             |" << "      J |                     |\n";
	cout << "   +---------------------+" << "        +---------------------+\n";
	cout << setw(18) << "Your sea" << setw(32) << "PC's sea\n";
	cout << endl << endl;
	cout << "   Press 'N' to next page." << endl;
	cout << "   Press 'P' to previous page." << endl;
}

void hitSlot() {
	cout << endl;
	cout << setw(6) << "0";

	for (int i = 1; i < 10; i++)
		cout << setw(2) << i;
	cout << "If a ship was hit, a 'H' displayed." << endl;
	cout << "            0 1 2 3 4 5 6 7 8 9";
	cout << endl;
	cout << "   Yours          Ship: 04" << "        PC's           Ship: 04";
	cout << "   +---------------------+" << "        +---------------------+\n";
	cout << " A |           O O       |" << "      A |                     |\n";
	cout << " B |   O                 |" << "      B |                     |\n";
	cout << " C |   O                 |" << "      C |                     |\n";
	cout << " D |   O               O |" << "      D |                     |\n";
	cout << " E |   O               O |" << "      E |                     |\n";
	cout << " F |   O               O |" << "      F |         H           |\n";
	cout << " G |                   O |" << "      G |                     |\n";
	cout << " H |                     |" << "      H |                     |\n";
	cout << " I |                     |" << "      I |                     |\n";
	cout << " J | O O O O             |" << "      J |                     |\n";
	cout << "   +---------------------+" << "        +---------------------+\n";
	cout << setw(18) << "Your sea" << setw(32) << "PC's sea\n";
	cout << endl << endl;
	cout << "   Press 'N' to next page." << endl;
	cout << "   Press 'P' to previous page." << endl;
}

void input(char &option) {
	cin >> option;

	if (option == 'n' || option == 'p' || option == 'N' || option == 'P') {
		option = option - 'a' + 'A';
		cin.ignore(1024, '\n');
		return;
	}

	if (option != 'N' || option != 'P') {
		cout << "Invalid input. Please input again.\n";
		cin.ignore(1024, '\n');
		input(option);
	}
}

void instructions() {
	char option;
	system("cls");

Page1:
	printGrid(); // calling the fuction to display the default sea size
	input(option);
	system("cls");

Page2:
	createGrid(); //displaying occupied slots
	input(option);
	if (option == 'P') {
		system("cls");
		goto Page1;
	}
	system("cls");

Page3:
	playersGrid(); // proceeds to Battle stage
	input(option);
	if (option == 'P') {
		system("cls");
		goto Page2;
	}
	system("cls");

Page4:
	emptySlot();
	input(option);
	if (option == 'P') {
		system("cls");
		goto Page3;
	}
	system("cls");

Page5:
	hitSlot();
	input(option);
	if (option == 'P') {
		system("cls");
		goto Page4;
	}
	system("cls");

Page6:
	winning();
	input(option);
	if (option == 'P') {
		system("cls");
		goto Page5;
	}
	system("cls");
	cout << endl;
	return;
}

// Setting of showing PC's ship or not
void PCShip() {
	char ans;
	system("cls"); // clear everything on the screen
	cout << "Default setting: Do not display PC's ship\n" << endl; // show default setting

	do {
		cout << "Change setting?(Y/N): "; // ask user change setting or not
		cin >> ans;
		if ((ans == 'y') || (ans == 'n'))
			ans = ans - 'a' + 'A';

		if ((ans == 'Y') || (ans == 'N'))
			break;
		else
			cout << "Invalid input. Please input again\n" << endl;
	} while ((ans != 'Y') && (ans != 'N'));

	if ((ans == 'Y' && hidden == 0) || (ans == 'N' && hidden == 1)) {
		hidden = 1;
		cout << "\nSetting changes to: 'Do not display PC's ship'\n" << endl; // show final setting
	}
	else {
		hidden = 0;
		cout << "\nSetting changes to: 'Display PC's ship'\n" << endl; // show final setting
	}

	system("pause");
	return;
}

void playersGrid() {
	cout << "2) Battle stage\n\n";
	cout << "Both sea of Player and PC will be displayed.\n";
	cout << "But the ships of PC will be hidden by default and can be changed in Setting.\n";
	cout << "Also, remaining ship will daisplay on each sea's on top right-hand-corner.";
	cout << endl;
	cout << setw(6) << "0";

	for (int i = 1; i < 10; i++) {
		cout << setw(2) << i;
	}

	cout << "            0 1 2 3 4 5 6 7 8 9";
	cout << endl;
	cout << "   Yours          Ship: 04" << "        PC's           Ship: 04";
	cout << "   +---------------------+" << "        +---------------------+\n";
	cout << " A |           O O       |" << "      A |                     |\n";
	cout << " B |   O                 |" << "      B |                     |\n";
	cout << " C |   O                 |" << "      C |                     |\n";
	cout << " D |   O               O |" << "      D |                     |\n";
	cout << " E |   O               O |" << "      E |                     |\n";
	cout << " F |   O               O |" << "      F |                     |\n";
	cout << " G |                   O |" << "      G |                     |\n";
	cout << " H |                     |" << "      H |                     |\n";
	cout << " I |                     |" << "      I |                     |\n";
	cout << " J | O O O O             |" << "      J |                     |\n";
	cout << "   +---------------------+" << "        +---------------------+\n";
	cout << setw(18) << "Your sea" << setw(32) << "PC's sea\n";
	cout << endl << endl;
	cout << "   Press 'N' to next page." << endl;
	cout << "   Press 'P' to previous page." << endl;
}

void printGrid() {
	int a = 65;
	cout << "There is two stages of game.\n";
	cout << "Arrangement Stage\n\n";
	cout << "Player arranges ships either horizontally and vertically on their own sea secretly.\n";
	cout << endl;
	cout << setw(6) << "0";

	for (int i = 1; i < 10; i++) {
		cout << setw(2) << i;
	}
	cout << endl;
	cout << "   +---------------------+\n";

	for (int x = 0; x < 10; x++) {
		cout << setw(2) << (char)a << setw(2) << "|" << setw(22) << "|";
		a++;

		for (int y = 0; y < 10; y++) {
			cout << setw(2) << grid[x][y];
		}
		cout << endl;
	}
	cout << "   +---------------------+\n";
	cout << endl << endl;
	cout << "   Press 'N' or 'P' to next page." << endl;
}

// Function of setting the sea size
void seaSizeArrange(int &n) {
	int ans;
	int validsize = carrierSize * carrier + battleshipSize * battleship + submarineSize * submarine + destroyerSize * destroyer;
	system("cls"); // clear everything on the screen
	cout << "Current setting: Seasize is " << seaSize << " x " << seaSize << "." << endl; // show default setting

	do {
		cout << "\nWhat is your desired sea size: "; // ask user to input sea size
		cin >> ans;
		if (cin.fail())
			cout << "Input should be an integer." << endl;
		n = ans;
		if ((ans <= 10) && (ans >= 5) && (ans * ans >= validsize))
			break; // if the input is within the range, jump out the loop
		else {
			cin.clear();
			cin.ignore(1024, '\n');
			if (ans * ans < validsize)
				cout << "The desired sea size is not large enough to hold all ships." << endl;
			else
				cout << "\nInvalid input. Please input again." << endl; // if the input is without the range, ask user to input again
		}
	} while ((ans > 10) || (ans < 5) || (ans * ans < validsize));

	cout << "\nFinalized setting:" << endl << "\nSeasize is " << seaSize << " x " << seaSize << ".\n" << endl; // show final setting
	system("pause");
	return;
}

void settings() {
	int option;

	do {
		system("cls");
		showSettingsMenu();
		cin >> option;

		// Avoid wrong option
		while (cin.fail() || option != (int)option) {
			if (cin.fail())
				cout << "Please input an integer(1-5) instead of character(s)." << endl;
			else
				cout << "Please input an integer(1-5) without any decimal digit(s)." << endl;

			cin.clear();
			cin.ignore(1024, '\n');
			showSettingsMenu();
			cin >> option;
		}
		cin.ignore(1024, '\n');

		// Move to function by each option
		switch ((int)option) {
			case 1:startFirst(); break;
			case 2:PCShip(); break;
			case 3:seaSizeArrange(seaSize); break;
			case 4:shipNumber(); break;
			case 5:showGameMenu(); break;
		}
	} while (option != 5);
}

void showSettingsMenu() {
	cout << "**** Settings Menu ****" << endl;
	cout << "[1] Who starts first" << endl;  // player start first or PC start first
	cout << "[2] Display PC's ships" << endl;  // show PC's ships or not
	cout << "[3] Sea size" << endl;  // what is the size of the ship
	cout << "[4] Number of ships" << endl;  // how many ship can player input
	cout << "[5] Return to Game Menu" << endl;  // end of setting and back to the game menu
	cout << "***********************\n" << endl;
	cout << "Option (1 - 5):";  // ask user to choose for doing which setting
}

// Function for setting player start first or PC start first
void startFirst() {
	char ans;
	system("cls"); // clear everything on the screen
	cout << "Current setting: \n" << endl;

	if (turn == 0) // show default setting
		cout << "User starts first. \n" << endl;
	else
		cout << "PC starts first. \n" << endl;
	do {
		cout << "Change setting?(Y/N): "; // ask user change setting or not
		cin >> ans;

		if ((ans == 'y') || (ans == 'n'))
			ans = ans - 'a' + 'A';

		if ((ans == 'Y') || (ans == 'N'))
			break; // if user input is inside the range, jump out the loop
		else
			cout << "Invalid input. Please input again\n" << endl; // if user input is outside the range, ask user to input again
	
		cin.ignore(1024, '\n');
	} while ((ans != 'Y') || (ans != 'N'));

	if (turn == 0) {
		if (ans == 'Y') {
			turn = 1; // when user choose to change the setting
			cout << "\nFinalized setting:\n\nPC starts first.\n" << endl; // show final setting
		}
		else
			cout << "\nFinalized setting:\n\nUser starts first.\n" << endl; // show final setting
	}
	else {
		if (ans == 'Y') {
			turn = 0;// when user choose to change the setting
			cout << "\nFinalized setting:\n\nUser starts first.\n" << endl; // show final setting
		}
		else
			cout << "\nFinalized setting:\n\nPC starts first.\n" << endl; // show final setting
	}
	system("pause");
	return;
}

// Function of setting the number of ship
void shipNumber() {
	char ans;
	char option;
	system("cls"); // clear everything on the screen
	cout << "Current setting: " << endl;
	cout << "Type of ship         Number" << endl; // show default setting
	cout << "Carrier    (size 5):   " << carrier << endl;
	cout << "Battleship (size 4):   " << battleship << endl;
	cout << "Submarine  (size 3):   " << submarine << endl;
	cout << "Destroyer  (size 2):   " << destroyer << endl;
	cout << "Need to make changes?(Y/N): ";

	do {
		cin >> ans;

		if ((ans == 'y') || (ans == 'n'))
			ans = ans - 'a' + 'A';

		if (ans == 'Y') {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << endl << "Note that: " << endl << " 1. 'c' for Carrier, 'b' for Battleship, 's' for Submarine, 'd' for Destroyer, " << endl
				<< " 2. The acceptable number of each type of ship is from 1 to 5 only" << endl
				<< "and the total number of ships should not exceed the capacity of the sea\n" << endl;

			do {
				do {
					do {
						cout << "Enter the type of ship you want to change: ";
						cin >> option; // can keep change the type and amount of ship
						cout << endl;
				
						if (option >= 'a' && option <= 'z')
							option = option - 'a' + 'A';
						
						if ((option == 'C') || (option == 'B') || (option == 'S') || (option == 'D'))
							break;
						
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Invalid input. Please input again\n" << endl;
					} while (true);
					
					cin.clear();
					cin.ignore(1024, '\n');

					switch (option) {
					case 'C': do {
								cout << "Number of carrier you like to set: ";
								cin >> carrier;
								cout << endl;
								
								if (cin.fail() || carrier != (int)carrier || carrier < 1 || carrier > 5) {
									cout << "Invalid input. Please input again\n" << endl;
									cout << "Note that:\nThe input Value should be an integer that is within the range (1-5).\n" << endl;
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								
								cin.clear();
								cin.ignore(1024, '\n');
								break;
							} while (true); break;
					
					case 'B': do {
								cout << "Number of battleship you like to set: ";
								cin >> battleship;
								cout << endl;
								if (cin.fail() || battleship != (int)battleship || battleship < 1 || battleship > 5) {
									cout << "Invalid input. Please input again\n" << endl;
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								cin.clear();
								cin.ignore(1024, '\n');
								if (battleship == (int)battleship)
									break;
							} while (true); break;
					
					case 'S': do {
								cout << "Number of submarine you like to set: ";
								cin >> submarine;
								cout << endl;
								if (cin.fail() || submarine != (int)submarine || submarine < 1 || submarine > 5) {
									cout << "Invalid input. Please input again\n" << endl;
									cout << "(The input Value should be an integer that is within the range (1-5).)\n" << endl;
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								cin.clear();
								cin.ignore(1024, '\n');
								break;
							} while (true); break;
					
					case 'D': do {
								cout << "Number of destroyer you like to set: ";
								cin >> destroyer;
								cout << endl;
								if (cin.fail() || destroyer != (int)destroyer || destroyer < 1 || destroyer > 5) {
									cout << "Invalid input. Please input again\n" << endl;
									cout << "(The input Value should be an integer that is within the range (1-5).)\n" << endl;
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								cin.clear();
								cin.ignore(1024, '\n');
								break;
							} while (true); break;
					}
	
					do {
						cout << "Any other ships?(Y/N) : ";
						cin >> option;
						cout << endl;
						if (option == 'Y' || option == 'y' || option == 'N' || option == 'n')
							break;
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Invalid input. Please input again\n" << endl;
					} while (true);
				} while (option == 'Y' || option == 'y');
				
				if ((carrier * 5 + battleship * 4 + submarine * 3 + destroyer * 2) > seaSize * seaSize) { // avoid the total number of ships exceeds the capacity of the sea
					cout << "The total number of ships exceeds the capacity of the sea. Reset again.\n" << endl;
					carrier = 1, battleship = 2, submarine = 3, destroyer = 4;
				}
			} while ((option == 'C') || (option == 'B') || (option == 'S') || (option == 'D'));
			
			cout << endl << "Finishing the changes . . .\n" << endl << endl;
		}
		else if (ans == 'N') {
			cin.clear();
			cin.ignore(1024, '\n');
			return;
		}
		else {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Invalid input. Please input again.\n" << endl; // avoid wrong option apart from yes or no
		}
	} while ((ans != 'Y') && (ans != 'N'));

	cout << "Finalized setting: \n" << endl;
	cout << "Type of ship         Number" << endl; // show final setting
	cout << "Carrier    (size 5):   " << carrier << endl;
	cout << "Battleship (size 4):   " << battleship << endl;
	cout << "Submarine  (size 3):   " << submarine << endl;
	cout << "Destroyer  (size 2):   " << destroyer << endl;
	system("pause");
}

// Show game menu
void showGameMenu() {
	cout << "*** Game Menu ***\n";
	cout << "[1] Start Game\n";
	cout << "[2] Settings\n";
	cout << "[3] Instructions\n";
	cout << "[4] Credits\n";
	cout << "[5] Exit\n";
	cout << "*****************\n";
}


void victory() {
	system("cls");
	cout << "\n\n\n\n\n   ";
	cout << "-";	Sleep(100);
	cout << "V";	Sleep(100);
	cout << "I";	Sleep(100);
	cout << "C";	Sleep(100);
	cout << "T";	Sleep(100);
	cout << "O";	Sleep(100);
	cout << "R";	Sleep(100);
	cout << "Y";	Sleep(100);
	cout << "!";	Sleep(100);
	cout << "-";	Sleep(100);
	cout << "\n\n\n\n\n";
	system("pause");
}

void welcome() {
	cout << "\n\n\n   ";
	cout << "W";	Sleep(100);		cout << "E";	Sleep(100);		cout << "L";	Sleep(100);
	cout << "C";	Sleep(100);		cout << "O";	Sleep(100);		cout << "M";	Sleep(100);
	cout << "E";	Sleep(100);		cout << " ";	Sleep(100);		cout << "T";	Sleep(100);
	cout << "O";	Sleep(100);		cout << " ";	Sleep(100);		cout << "S";	Sleep(100);
	cout << "U";	Sleep(100);		cout << "N";	Sleep(100);		cout << "'";	Sleep(100);
	cout << "S";	Sleep(100);		cout << " ";	Sleep(100);		cout << "B";	Sleep(100);
	cout << "A";	Sleep(100);		cout << "T";	Sleep(100);		cout << "T";	Sleep(100);
	cout << "L";	Sleep(100);		cout << "E";	Sleep(100);		cout << "S";	Sleep(100);
	cout << "H";	Sleep(100);		cout << "I";	Sleep(100);		cout << "P";	Sleep(100);
	cout << "!";	Sleep(100);	
	cout << "\n\n   ";
	cout << "L";	Sleep(100);		cout << "e";	Sleep(100);		cout << "t";	Sleep(100);
	cout << "'";	Sleep(100);		cout << "s";	Sleep(100);		cout << " ";	Sleep(100);
	cout << "h";	Sleep(100);		cout << "a";	Sleep(100);		cout << "v";	Sleep(100);
	cout << "e";	Sleep(100);		cout << " ";	Sleep(100);		cout << "s";	Sleep(100);
	cout << "o";	Sleep(100);		cout << "m";	Sleep(100);		cout << "e";	Sleep(100);
	cout << " ";	Sleep(100);		cout << "f";	Sleep(100);		cout << "u";	Sleep(100);
	cout << "n";	Sleep(100);		cout << ",";	Sleep(100);		cout << " ";	Sleep(100);
	cout << "s";	Sleep(100);		cout << "h";	Sleep(100);		cout << "a";	Sleep(100);
	cout << "l";	Sleep(100);		cout << "l";	Sleep(100);		cout << " ";	Sleep(100);
	cout << "w";	Sleep(100);		cout << "e";	Sleep(100);		cout << "?";	Sleep(100);
	cout << " ";	Sleep(100);		cout << ":";	Sleep(100);		cout << ")";	Sleep(100);
	cout << "\n\n\n\n\n\n\n\n\n   " << endl << "   ";
	system("pause");
}

void winning() {
	cout << "When the entire ship has been marked by 'H', the ship is destroyed.\n";
	cout << "When you destroyed all PC's ships, you wins.\n";
	cout << "Otherwise, PC wins!\n";
	cout << endl;
	cout << setw(6) << "0";

	for (int i = 1; i < 10; i++) {
		cout << setw(2) << i;
	}

	cout << "            0 1 2 3 4 5 6 7 8 9";
	cout << endl;
	cout << "   Yours          Ship: 04" << "        PC's           Ship: 00";
	cout << "   +---------------------+" << "        +---------------------+\n";
	cout << " A |           O O       |" << "      A | H                   |\n";
	cout << " B |   O                 |" << "      B | H              H    |\n";
	cout << " C |   O                 |" << "      C |                H    |\n";
	cout << " D |   O               O |" << "      D |                H    |\n";
	cout << " E |   O               O |" << "      E |                H    |\n";
	cout << " F |   O               O |" << "      F |   H H H H H         |\n";
	cout << " G |                   O |" << "      G |             H       |\n";
	cout << " H |                     |" << "      H |             H       |\n";
	cout << " I |                     |" << "      I |             H       |\n";
	cout << " J | O O O O             |" << "      J |                     |\n";
	cout << "   +---------------------+" << "        +---------------------+\n";
	cout << setw(18) << "Your sea" << setw(32) << "PC's sea\n";
	cout << endl << endl;
	cout << "   Press 'N' to the end." << endl;
	cout << "   Press 'P' to previous page." << endl;
}

void startGame() // option 1 from game menu
{
	Carrier c[maxShip];
	Battleship b[maxShip];
	Submarine s[maxShip];
	Destroyer d[maxShip];

	shipC = ship = carrier + battleship + submarine + destroyer;
	srand(time(0));
	reset(coordinate);
	reset(coordinateC);
	for (int i = 0; i < carrier; i++) {
		c[i].initialize();
		c[i].arrangeC();
	}
	for (int i = 0; i < battleship; i++) {
		b[i].initialize();
		b[i].arrangeC();
	}
	for (int i = 0; i < submarine; i++) {
		s[i].initialize();
		s[i].arrangeC();
	}
	for (int i = 0; i < destroyer; i++) {
		d[i].initialize();
		d[i].arrangeC();
	}

	// Arrangement stage
	system("cls");
	arrStage();

	do {
		system("cls");
		reset(coordinate);
		for (int i = 0; i < carrier; i++) {
			c[i].arrange();
		}
		for (int i = 0; i < battleship; i++) {
			b[i].arrange();
		}

		for (int i = 0; i < submarine; i++) {
			s[i].arrange();
		}

		for (int i = 0; i < destroyer; i++) {
			d[i].arrange();
		}
		printSea(coordinate, 0);
	} while (confirm() == 1);


	// Battle stage
	system("cls");
	battleStage();
	system("cls");

	do {
		for (int i = 0; i < carrier; i++) {
			c[i].checkC();
			c[i].check();
		}

		for (int i = 0; i < battleship; i++) {
			b[i].checkC();
			b[i].check();
		}

		for (int i = 0; i < submarine; i++) {
			s[i].checkC();
			s[i].check();
		}

		for (int i = 0; i < destroyer; i++) {
			d[i].checkC();
			d[i].check();
		}

		cout << "PC's" << setw(seaSize * 2 - 6) << setfill(' ') << ' ';
		cout << "Ship:" << setw(2) << setfill('0') << shipC << endl;
		printSea(coordinateC, 1);
		cout << "Yours" << setw(seaSize * 2 - 8) << setfill(' ') << ' ';
		cout << "Ship: " << setw(2) << setfill('0') << ship << endl;
		printSea(coordinate, 0);

		if (turn == 0 && ship != 0 && shipC != 0) {
			userTurn();
			computerTurn();
		}
		else if (turn == 1 && ship != 0 && shipC != 0) {
			computerTurn();
			userTurn();
		}
	} while (ship != 0 && shipC != 0);

	if (shipC == 0) {
		victory();
	}
	else {
		defeat();
	}
}

bool confirm() {
	char option1, option2;

	do {
		cout << "Confirm your arrangement? 'Y'/'N' (Yes/No): ";
		cin >> option1;
		cin.ignore(1024, '\n');

		if (option1 == 'n' || option1 == 'y')
			option1 = option1 - 'a' + 'A';

		if (option1 == 'N') {
			cout << "Do you wanna give up your masterpiece? 'Y'/'N' (Yes/No): ";
			cin >> option2;
			cin.ignore(1024, '\n');
			if (option2 == 'n' || option2 == 'y')
				option2 = option2 - 'a' + 'A';
			if (option2 == 'N')
				continue;
			else if (option2 == 'Y') {
				return 1;
			}
			else {
				cout << "Invalid input. I guess you don't wanna discard your arrangement." << endl;
				continue;
			}
		}
		else if (option1 != 'Y')
			cout << "Invalid input. Please press (y) for 'Yes'/ (n) for 'No'." << endl;
		else
			break;
	} while (true);

	return 0;
}



#include <iostream	>
#include <conio.h>
#include <windows.h>

using namespace std;

//Initialize Variables
bool snakeGame;
const int width = 25;
const int height = 25;
//user variables
int x, y,spd=1;
int tailX[100], tailY[100], tailLength;
//tail position
int fposX, fposY, sposX, sposY;
//target variables
int targetX, targetY;
//game variables
int score=0;
enum directions { STOP = 0, UP, DOWN, LEFT, RIGHT };
directions dir;


void gameSetup() {
	snakeGame = true;
	dir = STOP;

	x = rand() % width;
	y = rand() % height;
	targetX = rand() % width;
	targetY = rand() % height;

	while (x == targetX && y == targetY) {
		x = rand() % width;
		y = rand() % height;
		targetX = rand() % width;
		targetY = rand() % height;
	}
	score = 0;
}

void gameWindow() {
	system("cls");
	int i, j, k;
	for (i = 0; i < width; i++) {
		cout << "-";
	}
	cout << endl;

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "|";
			}
			else if (i == y && j == x) {
				cout << "O";
			}
			else if (i == targetY && j == targetX) {
				cout << "X";
			}
			else {
				bool tail = false;
				for (k = 0; k < tailLength; k++)
				{
					if (j == tailX[k] && i == tailY[k]) {
						cout << "o";
						tail = true;
					}
				}
				if (!tail)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (i = 0; i < width; i++) {
		cout << "-";
	}
	cout << endl;
	cout << "YOUR SCORE: " << score;
}

void gameInput() {

	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			if (dir != DOWN) {
				dir = UP;
			}
			break;
		case 'a':
			if (dir != RIGHT) {
				dir = LEFT;
			}
			break;
		case 's':
			if (dir != UP) {
				dir = DOWN;
			}
			break;
		case 'd':
			if (dir != LEFT) {
				dir = RIGHT;
			}
			break;
		case '0':
			snakeGame = false;
			break;
		}
	}

}

void gameProgram() {

	fposX = tailX[0];
	fposY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLength; i++) {
		sposX = tailX[i];
		sposY = tailY[i];
		tailX[i] = fposX;
		tailY[i] = fposY;
		fposX = sposX;
		fposY = sposY;
	}

	switch (dir) {
	case UP:
		y -= spd;
		break;
	case LEFT:
		x -= spd;
		break;
	case DOWN:
		y += spd;
		break;
	case RIGHT:
		x += spd;
		break;
	}

	//Snake hit border
	if (x < 0 || x == width || y < 0 || y == height) {
		snakeGame = false;
	}

	for (int i = 0; i < tailLength; i++) {
		if (x == tailX[i] && y == tailY[i])
			snakeGame = false;
	}

	//snake hit target
	if (x == targetX && y == targetY) {
		targetX = rand() % width;
		targetY = rand() % height;
		score++;
		tailLength++;
	}
}



int main()
{
	gameSetup();
	while (snakeGame == true) {
		gameWindow();
		gameInput();
		gameProgram();
		Sleep(30);
	}
}


#include"CollisionDetection.h"
#include"SinglePlayGame.h"
#include"MultiPlayer.h"


char ColGrid[10][5];
int loop = 0;

int CollisionDetection::enemyCollisionDetect(int x, int y, char c) {
	
	//Creates grid and adds the char N into each space
	//Using N to stand for Not Taken, can be changed later
	if (loop == 0) {
		for (int i = 0;i < 10;i++) {
			for (int j = 0;j < 5;j++) {
				ColGrid[i][j] = 'N';
			}
		}
		this->loop = 1;
	}

	//checks to see if the available space is clear
	if (ColGrid[x][y - 1] == 'N') {
		ColGrid[x][y - 1] = c;
		ColGrid[x][y] = 'N';
		CCLOG("Returning 0");
		return 0;
	}
	//returns a value of 2 if it finds a Player Sprite in next space
	else if (ColGrid[x][y - 1] == 'P') {
		CCLOG("Returning 2");
		return 2;
	}
	//returns a value of one if another enemy is in front of it
	else {
		CCLOG("Returning 1");
		return 1;
	}

}

void CollisionDetection::registerObject(int x, int y, char c) {

	//creates the grid if it is not made
	if (loop == 0) {
		for (int i = 0;i < 10;i++) {
			for (int j = 0;j < 5;j++) {
				ColGrid[i][j] = 'N';
			}
		}
		this->loop = 1;
	}

	//can register with the colision manager if the grid is available
	if (ColGrid[x][y] == 'N') {
		ColGrid[x][y] = c;
	}
	else {
		CCLOG("Postion already took");
	}
	CCLOG("registerObject Completed");

}

#include"CollisionDetection.h"
#include"SinglePlayGame.h"
#include"MultiPlayer.h"


char ColGrid[10][5];
char TowerGrid[5][5];
char EnemyTowerGrid[5][5];

CollisionDetection::CollisionDetection() {}
CollisionDetection::~CollisionDetection() {}

int CollisionDetection::enemyCollisionDetect(int x, int y, char c) {

	//checks to see if the available space is clear
	if (ColGrid[x - 1][y] == 'N') {
		ColGrid[x - 1][y] = c;
		ColGrid[x][y] = 'N';
		CCLOG("Returning 0");
		return 0;
	}
	//returns a value of 2 if it finds a Player Sprite in next space
	else if (ColGrid[x - 1][y] == 'P') {
		CCLOG("Returning 2");
		return 1;
	}
	//returns a value of one if another enemy is in front of it
	else {
		CCLOG("Returning 1");
		return 2;
	}

}

int CollisionDetection::playerCollisionDetect(int x, int y, char c) {

	//checks to see if the available space is clear
	if (ColGrid[x + 1][y] == 'N') {
		ColGrid[x + 1][y] = c;
		ColGrid[x][y] = 'N';
		CCLOG("Returning 0");
		return 0;
	}
	//returns a value of 2 if it finds a Enemy Sprite in next space
	else if (ColGrid[x + 1][y] == 'E') {
		CCLOG("Returning 2");
		return 1;
	}
	//returns a value of one if another player is in front of it
	else {
		CCLOG("Returning 1");
		return 2;
	}

}


int CollisionDetection::registerObject(int x, int y, char c) {

	//can register with the colision manager if the grid is available
	if (ColGrid[x][y] == 'N') {
		ColGrid[x][y] = c;
		return 0;
	}
	else {
		CCLOG("Postion already took");
		return 1;
	}
	CCLOG("registerObject Completed");

}

int CollisionDetection::registerTower(int x, int y, char c) {

	//can register with the colision manager if the grid is available
	if (TowerGrid[x][y] == 'N') {
		TowerGrid[x][y] = c;
		return 0;
	}
	else {
		return 1;
		CCLOG("Postion already took");
	}
	CCLOG("registerObject Completed");

}

int CollisionDetection::CheckTower(int x, int y) {
    //check to see Tower postions available
	if (TowerGrid[x][y] == 'N') {
		return 0;
	}
	else {
		return 1;
	}
}

void CollisionDetection::registerEnemyTower(int x, int y, char c) {

	//Needs to be fixed up later
	if (TowerGrid[x][y] == 'N') {
		TowerGrid[x][y] = c;
	}
	else {
		CCLOG("Postion already took");
	}
	CCLOG("registerObject Completed");

}

void CollisionDetection::CreateGrids() {

	//Creates grid and adds the char N into each space
	//Using N to stand for Not Taken, can be changed later

	//creates the Tower grid if it is not made
		for (int i = 0;i < 5;i++) {
			for (int j = 0;j < 5;j++) {
				TowerGrid[i][j] = 'N';
			}
		}
	//creates the Enemy Tower grid if it is not made
		for (int i = 0;i < 5;i++) {
			for (int j = 0;j < 5;j++) {
				EnemyTowerGrid[i][j] = 'N';
			}
		}
	//creates the Collision grid if it is not made
		for (int i = 0;i < 10;i++) {
			for (int j = 0;j < 5;j++) {
				ColGrid[i][j] = 'N';
			}
		}
}
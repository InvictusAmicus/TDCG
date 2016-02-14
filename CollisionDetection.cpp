#include "CollisionDetection.h"
#include "SinglePlayGame.h"
#include "MultiPlayer.h"
#include <utility>
#include <iostream>
#include <vector>

char ColGrid[10][5];
char TowerGrid[5][5];
char EnemyTowerGrid[5][5];

CollisionDetection::CollisionDetection() {}
CollisionDetection::~CollisionDetection() {}

int CollisionDetection::enemyCollisionDetect(std::pair<int, int> TestPostion, char c) {

	int x = std::get<0>(TestPostion);
	int y = std::get<1>(TestPostion);

	//checks to see if the available space is clear
	if (ColGrid[x - 1][y] == 'N') {
		ColGrid[x - 1][y] = c;
		ColGrid[x][y] = 'N';
		CCLOG("Returning 0");
		return 0;
	}
	//returns a value of 2 if it finds a Player Sprite in next space
	else if (ColGrid[x - 1][y] == 'P') {
		CCLOG("Returning 1");
		//call attack on player sprite
		return 1;
	}
	//returns a value of one if another enemy is in front of it
	else {
		CCLOG("Returning 2");
		return 2;
	}

}

int CollisionDetection::playerCollisionDetect(std::pair<int, int> TestPostion, char c) {
	
	int x = std::get<0>(TestPostion);
	int y = std::get<1>(TestPostion);
	CCLOG("Running playerCollisionDetect on %d  %d", x, y);
	//checks to see if the available space is clear
	if (ColGrid[x + 1][y] == 'N') {
		ColGrid[x + 1][y] = c;
		ColGrid[x][y] = 'N';
		CCLOG("Returning 0");
		return 0;
	}
	//returns a value of 2 if it finds a Enemy Sprite in next space
	else if (ColGrid[x + 1][y] == 'E') {
		CCLOG("Returning 1");
		//Enemy in front call attack enemy
		return 1;
	}
	//returns a value of one if another player is in front of it
	else {
		CCLOG("Returning 2");
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

void CollisionDetection::removeObject(std::pair<int, int> RemovePostion)
{
	int x = std::get<0>(RemovePostion);
	int y = std::get<1>(RemovePostion);
	ColGrid[x][y] = 'N';
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

int CollisionDetection::registerEnemyTower(int x, int y, char c) {

	//Needs to be fixed up later
	if (EnemyTowerGrid[x][y] == 'N') {
		EnemyTowerGrid[x][y] = c;
		return 0;
	}
	else {
		return 1;
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
		Q();
}

//Enemy life and Tower attack needs to be added
void CollisionDetection::PlayerTowerAttack() 
{
	for (int i = 0; i <= 3; i++) 
	{
		for (int j = 0; j <= 3; j++) 
		{
			if (TowerGrid[i][j] == 'T') 
			{
				CCLOG("PlayerTowerAttack is ready");
				if (ColGrid[i][j] == 'E') 
				{
					CCLOG("Attacking enemy at %d-%d",i,j);
				}
				if (ColGrid[i][j + 1] == 'E')
				{
					CCLOG("Attacking enemy at %d-%d", i, j + 1);
				}
				if (ColGrid[i + 1][j] == 'E')
				{
					CCLOG("Attacking enemy at %d-%d", i + 1, j);
				}
				if (ColGrid[i + 1][j + 1] == 'E')
				{
					CCLOG("Attacking enemy at %d-%d", i + 1, j + 1);
				}
			}
		}
	}
}

//Player sprite life and Tower attack needs to be added
void CollisionDetection::EnemyTowerAttack() 
{
	int a = 5;

	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			if (EnemyTowerGrid[i][j] == 'T')
			{
				CCLOG("EnemyTowerAttack is ready");
				if (ColGrid[a][j] == 'P')
				{
					CCLOG("Attacking player at %d-%d", a, j);
				}
				if (ColGrid[a][j + 1] == 'P')
				{
					CCLOG("Attacking player at %d-%d", a, j + 1);
				}
				if (ColGrid[a + 1][j] == 'P')
				{
					CCLOG("Attacking player at %d-%d", a + 1, j);
				}
				if (ColGrid[a + 1][j + 1] == 'P')
				{
					CCLOG("Attacking player at %d-%d", a + 1, j + 1);
				}
			}
		}
		a++;
	}
}

void CollisionDetection::EnemyAttackLife()
{
	if (ColGrid[0][0] == 'E') 
	{
	  //Remove sprite and take away from player life
	}
	if (ColGrid[0][1] == 'E')
	{
		//Remove sprite and take away from player life
	}
	if (ColGrid[0][2] == 'E')
	{
		//Remove sprite and take away from player life
	}
	if (ColGrid[0][3] == 'E')
	{
		//Remove sprite and take away from player life
	}
	if (ColGrid[0][4] == 'E')
	{
		//Remove sprite and take away from player life
	}
}

void CollisionDetection::playerAttackLife()
{
	if (ColGrid[9][0] == 'P')
	{
		//Remove sprite and take away from enemy life
	}
	if (ColGrid[9][1] == 'P')
	{
		//Remove sprite and take away from enemy life
	}
	if (ColGrid[9][2] == 'P')
	{
		//Remove sprite and take away from enemy life
	}
	if (ColGrid[9][3] == 'P')
	{
		//Remove sprite and take away from enemy life
	}
	if (ColGrid[9][4] == 'P')
	{
		//Remove sprite and take away from enemy life
	}
}

void CollisionDetection::Q() 
{
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 5; j++)
		{
			CCLOG("%c ",ColGrid[i][j]);
		}
	}
}

int CollisionDetection::countPlayerTowers()
{
	int TowerC = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (TowerGrid[i][j] == 'T') {
				TowerC++;
			}
		}
	}
    CCLOG("PLAYERTOWER, %d", TowerC);
	return TowerC;
}

int CollisionDetection::countPlayerSprites()
{
	int SpriteC = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			if (ColGrid[i][j] == 'P') {
				SpriteC++;
			}
		}
	}
	return SpriteC;
}

int CollisionDetection::countEnemyTowers()
{
	int TowerC = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (EnemyTowerGrid[i][j] == 'T') {
				TowerC++;
			}
		}
	}
	CCLOG("ENEMYTOWER, %d", TowerC);
	return TowerC;
}

int CollisionDetection::countEnemySprites()
{
	int SpriteC = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			if (ColGrid[i][j] == 'E') {
				SpriteC++;
			}
		}
	}
	return SpriteC;

}

int CollisionDetection::PlayersInEnemyArea() 
{
	int PlayersInEnemyArea = 0;

	for (int i = 5; i < 10; i++)
	{
		for (int j = 0; j < 5;j++)
		{
			if (ColGrid[i][j] == 'P')
			{
				PlayersInEnemyArea++;
			}
		}
	}
	return PlayersInEnemyArea;
}

int CollisionDetection::EnemiesInPlayerArea() 
{
	int EnemiesInPlayerArea = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5;j++)
		{
			if (ColGrid[i][j] == 'E')
			{
				EnemiesInPlayerArea++;
			}
		}
	}
	return EnemiesInPlayerArea;
}

char CollisionDetection::getEnemyTowerGrid(int x, int y) 
{
	return EnemyTowerGrid[x][y];
}

char CollisionDetection::getColGrid(int x, int y)
{
	return ColGrid[x][y];
}

//Declan trying something
void CollisionDetection::removeObject(int r, int t)
{
	ColGrid[r][t] = 'N';
}

int CollisionDetection::enemyCollisionDetect(int r, int t, char c)
{
	int x = r;
	int y = t;

	//checks to see if the available space is clear
	if (ColGrid[x - 1][y] == 'N')
	{
		ColGrid[x - 1][y] = c;
		ColGrid[x][y] = 'N';
		CCLOG("Returning 0");
		return 0;
	}
	//returns a value of 2 if it finds a Player Sprite in next space
	else if (ColGrid[x - 1][y] == 'P')
	{
		CCLOG("Returning 1");
		//call attack on player sprite
		return 1;
	}
	//returns a value of one if another enemy is in front of it
	else
	{
		CCLOG("Returning 2");
		return 2;
	}

}

int CollisionDetection::playerCollisionDetect(int r, int t, char c)
{
	int x = r;
	int y = t;

	//checks to see if the available space is clear
	if (ColGrid[x + 1][y] == 'N')
	{
		ColGrid[x + 1][y] = c;
		ColGrid[x][y] = 'N';
		CCLOG("Returning 0");
		return 0;
	}
	//returns a value of 2 if it finds a Player Sprite in next space
	else if (ColGrid[x + 1][y] == 'P')
	{
		CCLOG("Returning 1");
		//call attack on player sprite
		return 1;
	}
	//returns a value of one if another enemy is in front of it
	else
	{
		CCLOG("Returning 2");
		return 2;
	}
}
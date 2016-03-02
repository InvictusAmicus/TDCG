#ifndef __COLLISIONDETECTION_H__
#define __COLLISIONDETECTION_H__

#include <utility>
#include <iostream>

class CollisionDetection
{
public:
	CollisionDetection();
	~CollisionDetection();
	

	bool init();

	/*!
	*Creates three grids, the first being for the Player tower grid which is a 4*4 grid. 
	*The second grid created is the enemy tower grid which is a 4*4 grid. The last grid that is created 
	*is the soldier grid which is a 10*5 grid. All grids are filled with the letter N to indicate that the
	*spaces are not yet taken.
	*/
	void CreateGrids();

	void PlayerTowerAttack();
    
	void playerAttackLife();
	
	void EnemyAttackLife();
   
	void removeObject(std::pair<int, int> RemovePostion);
	
	/*
	*Outputs the contents of the ColGrid. Used only for testing to see what is at each position
	*/
	void Q();
	
	void removeObject(int, int);

	/*!
	*Registers soldier sprites to the map grid. 
	*Int x and y refer to the postion on the grid. 
	*char c refers to the type being registered. 
	*Returns 0 if successful and 1 if posistion is already taken
    */
	int registerObject(int x, int y, char c);
	
	/*!
	*Checks to see if the enemy can move forward. returns 0 if nothing is in front of the enemy. 1 is
	*returned if the player sprite is in front of the enemy. Returns 2 is another enemy sprite is in front
	*/
	int enemyCollisionDetect(std::pair<int, int> TestPostion, char c);
	
	/*!
	*Checks to see if the player can move forward. returns 0 if nothing is in front of the player. 1 is
	*returned if the enemy sprite is in front of the player. Returns 2 is another player sprite is in front
	*/
	int playerCollisionDetect(std::pair<int, int> TestPostion, char c);
	
	/*!
	*Registers a tower on the tower grid. 0 is returned is the position is free and 1 is returned if it is not free.
	*/
	int registerTower(int x, int y, char c);
	
	/*
	*Checks to see the tower positions available 
	*/
	int CheckTower(int x, int y);

	int registerEnemyTower(int x, int y, char c);
	
	int countPlayerTowers();
	
	int countPlayerSprites();
	
	/*
	*Counts the number of towers in the tower grid
	*/
	int countEnemyTowers();
	
	/*
	*Counts the number of enemy sprites on the grid
	*/
	int countEnemySprites();
	
	/*
	*Checks the number of enemy sprites that are in the player area
	*/
	int EnemiesInPlayerArea();
	
	/*
	Checks the number of players in the enemy area.
	*/
	int PlayersInEnemyArea();
	

	int enemyCollisionDetect(int, int, char);
	
	int playerCollisionDetect(int, int, char);

	int enemyTowerAttacks(int, int);
	
	int towerAttacks(int, int);
	
	int playerTowerBulletX(int x);
	
	int TowerBulletY(int y);
	
    int enemyTowerBulletX(int x);

	char getEnemyTowerGrid(int x, int y);
	
	/*
	*Returns the contents of the ColGrid based on the parameters passed in
	*/
	char getColGrid(int x, int y);
	
	//void EnemyTowerAttack();
	
	//int enemyTowerBulletY(int y);
	//char ColGrid[10][5];
	//char TowerGrid[5][5];
	//char EnemyTowerGrid[5][5];
};

#endif // __COLLISIONDETECTION_H__
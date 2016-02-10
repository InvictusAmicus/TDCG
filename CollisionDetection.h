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

	int registerObject(int x, int y, char c);
	int enemyCollisionDetect(std::pair<int, int> TestPostion, char c);
	int playerCollisionDetect(std::pair<int, int> TestPostion, char c);
	int registerTower(int x, int y, char c);
	int CheckTower(int x, int y);
	int registerEnemyTower(int x, int y, char c);
	void CreateGrids();
	char getEnemyTowerGrid(int x, int y);
	char getColGrid(int x, int y);
	void PlayerTowerAttack();
	void EnemyTowerAttack();
	void playerAttackLife();
	void EnemyAttackLife();
	int countPlayerTowers();
	int countPlayerSprites();
	int countEnemyTowers();
	int countEnemySprites();
	int EnemiesInPlayerArea();
	int PlayersInEnemyArea();
	void removeObject(std::pair<int, int> RemovePostion);
	void Q();

	void removeObject(int, int);
	int enemyCollisionDetect(int, int, char);
	int playerCollisionDetect(int, int, char);

	
	//char ColGrid[10][5];
	//char TowerGrid[5][5];
	//char EnemyTowerGrid[5][5];
};

#endif // __COLLISIONDETECTION_H__
#ifndef __ENEMYAI_H__
#define __ENEMYAI_H__

#include "cocos2d.h"
#include <tuple>
#include <iostream>

class EnemyAI
{
public:
	
	void OpenPostions();
	void CopyTowerGrid();
	void CopyColGridMap();
	
	/*!
	*Finds if a player sprite is in the second last row, returns an int value between 0-4 if true and 10000 if false
	*/
	int PlayerAtSecondLastRow();

	/*!
	*Spawns the enemy on the second column of their grid if false
	*/
	int PlayerAttackSecondRow();
	
	std::pair <int, int> PlayerTowerCreate();
	std::pair <int, int>  EnemySpritePlacements(int x, int y);
	std::pair <int, int> EnemyTowerPlacements(int x, int y);
	std::tuple <int, int, int, int, int> checkVariables(int PlayerResource, int EnemyResource);
	std::tuple<int, int, int> CreateEnemy(int PlayerResource, int EnemyResource, int PS, int PT, int ES, int ET, int PIEA, int EIPA);
};

#endif // __ENEMYAI_H__
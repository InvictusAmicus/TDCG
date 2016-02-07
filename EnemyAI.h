#ifndef __ENEMYAI_H__
#define __ENEMYAI_H__

#include "cocos2d.h"
#include <tuple>
#include <iostream>

class EnemyAI
{
public:
	std::tuple <int, int, int> checkVariables(int PlayerResource, int EnemyResource);
	void FieldPostions();
	void OpenPostions();
	void EnemySpritePlacements(int x, int y);
	std::pair <int, int> EnemyTowerPlacements(int x, int y);
	void test();
	std::tuple<int, int, int> CreateEnemy(int PlayerResource, int EnemyResource, int PS, int PT, int ES, int ET, int PIEA, int EIPA);
};

#endif // __ENEMYAI_H__
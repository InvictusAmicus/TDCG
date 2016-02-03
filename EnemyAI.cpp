#include"EnemyAI.h"
#include"CollisionDetection.h"

USING_NS_CC;

int PlayersInEnemyArea;
int EnemysInPlayerArea;

//x variable will be the enemy resources
void EnemyAI::checkVariables(int PlayerResource, int EnemyResource) 
{
	test();
	//PS = Player Sprite, PT = Player Tower
	//ES = Enemy Sprite, ET = Enemy Tower
	int PS = 0, PT = 0, ES = 0, ET = 0;
	CollisionDetection FieldState;
	PS = FieldState.countPlayerSprites();
	PT = FieldState.countPlayerTowers();
	ES = FieldState.countEnemySprites();
	ET = FieldState.countEnemyTowers();
	CCLOG("PR %d", PlayerResource);
	CCLOG("ER %d", EnemyResource);
	CCLOG("%d, %d, %d, %d", PS,PT,ES,ET);
	FieldPostions();
}

void EnemyAI::FieldPostions() {
	PlayersInEnemyArea = 0;
	EnemysInPlayerArea = 0;
	CollisionDetection SpritesAtOtherArea;

	for (int i = 5; i < 10; i++)
	{
		for (int j = 0; j < 5;j++)
		{
			//if (SpritesAtOtherArea.ColGrid[i][j] == 'P')
			//{
			//	PlayersInEnemyArea++;
			//}
		}

	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5;j++)
		{
			//if (SpritesAtOtherArea.ColGrid[i][j] == 'E')
			//{
			//	EnemysInPlayerArea++;
			//}
		}
	}
	CCLOG("Players in enemy area %d", PlayersInEnemyArea);
	CCLOG("Enemies in player area %d", EnemysInPlayerArea);
}
	

	void EnemyAI::test()
	{
		CollisionDetection testArea;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				//CCLOG("%c ", testArea.Q());
			}
		}
		testArea.Q();
	}
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
	//PIEA = Players In enemy area, EIPA = Enemies In Player Area
	int PS = 0, PT = 0, ES = 0, ET = 0, PIEA = 0, EIPA = 0;
	CollisionDetection FieldState;
	PS = FieldState.countPlayerSprites();
	PT = FieldState.countPlayerTowers();
	ES = FieldState.countEnemySprites();
	ET = FieldState.countEnemyTowers();
	PIEA = FieldState.PlayersInEnemyArea();
	EIPA = FieldState.EnemiesInPlayerArea();
	CCLOG("PR %d", PlayerResource);
	CCLOG("ER %d", EnemyResource);
	//CCLOG("%d, %d, %d, %d", PS,PT,ES,ET);
	CCLOG("PS %d", PS);
	CCLOG("PT %d", PT);
	CCLOG("ES %d", ES);
	CCLOG("ET %d", ET);
	CCLOG("PIEA %d", PIEA);
	CCLOG("EIPA %d", EIPA);
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
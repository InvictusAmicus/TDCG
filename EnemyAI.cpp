#include"EnemyAI.h"
#include"CollisionDetection.h"

//x variable will be the enemy resources
void EnemyAI::checkVariables(int x) 
{
	//PS = Player Sprite, PT = Player Tower
	//ES = Enemy Sprite, ET = Enemy Tower
	int PS = 0, PT = 0, ES = 0, ET = 0;
	CollisionDetection FieldState;
	PS = FieldState.countPlayerSprites();
	PT = FieldState.countPlayerTowers();
	ES = FieldState.countEnemySprites();
	ET = FieldState.countEnemyTowers();


}
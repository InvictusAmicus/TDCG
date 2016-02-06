#include"EnemyAI.h"
#include"CollisionDetection.h"
#include<iostream>
#include<tuple>

#define NoMove 10000

USING_NS_CC;

int PlayersInEnemyArea;
int EnemysInPlayerArea;

//x variable will be the enemy resources
std::tuple <int, int, int> EnemyAI::checkVariables(int PlayerResource, int EnemyResource)
{
	//PS = Player Sprite, PT = Player Tower
	//ES = Enemy Sprite, ET = Enemy Tower
	//PIEA = Players In enemy area, EIPA = Enemies In Player Area
	int PS = 0, PT = 0, ES = 0, ET = 0, PIEA = 0, EIPA = 0;
	CollisionDetection FieldState;
	FieldState.Q();

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
	std::tuple<int, int, int> EnemyCreation = CreateEnemy(PlayerResource, EnemyResource,
		                                                  PS, PT, ES, ET, PIEA, EIPA);
	int EnemyNumber = std::get<0>(EnemyCreation);
	int EnemyPostionX = std::get<1>(EnemyCreation);
	int EnemyPostionY = std::get<2>(EnemyCreation);

	return std::make_tuple(EnemyNumber, EnemyPostionX, EnemyPostionY);

}

void EnemyAI::OpenPostions() 
{
	CollisionDetection GridField;
	
}

std::tuple <int, int, int>EnemyAI::CreateEnemy(int PlayerResource, int EnemyResource, int PS, int PT, int ES, int ET, int PIEA, int EIPA) 
{
	int Enemy, PostionX, PostionY;

	//first statement if no sprites or towers can be made
	//value will be the lowest card value, current value 40
    if (EnemyResource<200)
	{
		CCLOG("Return first EnemyCreate Statement");
		return std::make_tuple(NoMove, NoMove, NoMove);
	}


	else if (EnemyResource>PlayerResource && (ES>PS || ET>PT)) 
	{
		if (((ES - PS)>3) && ((ET - PT)>3) && PIEA == 0)
		{
			//return in order to save resources
			//no player sprites will be in the area
			return std::make_tuple(NoMove, NoMove, NoMove);
		}
	    else if ((ES-PS)>3) 
		{
		
		}
		else if ((ET-PT)>3) 
		{
		
		}
		else if ((ET - PT)<3 || (ES - PS)<3)
		{

		}

	}
	else if (EnemyResource>PlayerResource && (ES<PS || ET<PT))
	{

	}
	else if (EnemyResource<PlayerResource && (ES<PS || ET<PT))
	{

	}
	else if (EnemyResource<PlayerResource && (ES>PS || ET>PT))
	{
	
	}

	return  std::make_tuple(NoMove,NoMove,NoMove);
}
#include"EnemyAI.h"
#include"CollisionDetection.h"
#include<iostream>
#include<tuple>

#define NoMove 10000

USING_NS_CC;

int PlayersInEnemyArea;
int EnemysInPlayerArea;
char ColGrid2[10][5];


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

//might need to add the open gird postions from the colgrid in CollsionDetection
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
			if (PIEA!=0) 
			{
			  //create tower to help defend against enemy
			}
			else if (PIEA == 0) 
			{
			//create sprite to attack enemy
			}
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

//x and y value will be for the ColGrid postion
std::pair <int, int> EnemySpritePlacements(int x, int y)
{
	int xCoordinate, yCoordinate;
	//5
	if (x == 5 && y == 0) 
	{
		xCoordinate = 518;
		yCoordinate = 508;
	}
	else if (x == 5 && y == 1) 
	{ 
		xCoordinate = 518; 
		yCoordinate = 434;
	}
	else if (x == 5 && y == 2) 
	{ 
		xCoordinate = 518; 
		yCoordinate = 359;
	}
	else if (x == 5 && y == 3) 
	{ 
		xCoordinate = 518; 
		yCoordinate = 287;
	}
	else if (x == 5 && y == 4) 
	{ 
		xCoordinate = 518; 
		yCoordinate = 209;
	}
	//6
	else if (x == 6 && y == 0) 
	{ 
		xCoordinate = 597; 
		yCoordinate = 508;
	}
	else if (x == 6 && y == 1) 
	{ 
		xCoordinate = 597; 
		yCoordinate = 434;
	}
	else if (x == 6 && y == 2) 
	{ 
		xCoordinate = 597;
		yCoordinate = 359;
	}
	else if (x == 6 && y == 3) 
	{ 
		xCoordinate = 597; 
		yCoordinate = 287;
	}
	else if (x == 6 && y == 4) 
	{ 
		xCoordinate = 597; 
		yCoordinate = 209;
	}
	//7
	else if (x == 7 && y == 0) 
	{ 
		xCoordinate = 674; 
		yCoordinate = 508;
	}
	else if (x == 7 && y == 1) 
	{ 
		xCoordinate = 674;
		yCoordinate = 434;
	}
	else if (x == 7 && y == 2) 
	{ 
		xCoordinate = 674; 
		yCoordinate = 359;
	}
	else if (x == 7 && y == 3) 
	{ 
		xCoordinate = 674; 
		yCoordinate = 287;
	}
	else if (x == 7 && y == 4) 
	{ 
		xCoordinate = 674; 
		yCoordinate = 209;
	}
	//8
	else if (x == 8 && y == 0) 
	{ 
		xCoordinate = 747; 
		yCoordinate = 508;
	}
	else if (x == 8 && y == 1) 
	{
		xCoordinate = 747;
		yCoordinate = 434;
	}
	else if (x == 8 && y == 2) 
	{ 
		xCoordinate = 747;
		yCoordinate = 359;
	}
	else if (x == 8 && y == 3) 
	{ 
		xCoordinate = 747; 
		yCoordinate = 287;
	}
	else if (x == 8 && y == 4) 
	{ 
		xCoordinate = 747; 
		yCoordinate = 209;
	}
	//9
	else if (x == 9 && y == 0) 
	{ 
		xCoordinate = 828; 
		yCoordinate = 508;
	}
	else if (x == 9 && y == 1) 
	{ 
		xCoordinate = 828; 
		yCoordinate = 434;
	}
	else if (x == 9 && y == 2) 
	{ 
		xCoordinate = 828; 
		yCoordinate = 359;
	}
	else if (x == 9 && y == 3) 
	{ 
		xCoordinate = 828; 
		yCoordinate = 287;
	}
	else if (x == 9 && y == 4) 
	{ 
		xCoordinate = 828; 
		yCoordinate = 209;
	}

	return std::make_pair(xCoordinate, yCoordinate);
}

//x and y value will be for the EnemyTowerlGrid postion
std::pair <int, int> EnemyTowerPlacements(int x, int y)
{
	int xCoordinate, yCoordinate;
	//0 Column
	if (x == 0 && y == 0) 
	{
		xCoordinate = 557;
		yCoordinate = 470;
	}
	else if (x == 0 && y == 1) 
	{
		xCoordinate = 557;
		yCoordinate = 395;
	}
	else if (x == 0 && y == 2) 
	{
		xCoordinate = 557;
		yCoordinate = 323;
	}
	else if (x == 0 && y == 3) 
	{
		xCoordinate = 557;
		yCoordinate = 249;
	}
	//1 Column
	else if (x == 1 && y == 0) 
	{
		xCoordinate = 634;
		yCoordinate = 470;
	}
	else if (x == 1 && y == 1) 
	{
		xCoordinate = 634;
		yCoordinate = 395;
	}
	else if (x == 1 && y == 2) 
	{
		xCoordinate = 634;
		yCoordinate = 323;
	}
	else if (x == 1 && y == 3) 
	{
		xCoordinate = 634;
		yCoordinate = 249;
	}
	//2 Column
	else if (x == 2 && y == 0) 
	{
		xCoordinate = 711;
		yCoordinate = 470;
	}
	else if (x == 2 && y == 1) 
	{
		xCoordinate = 711;
		yCoordinate = 395;
	}
	else if (x == 2 && y == 2) 
	{
		xCoordinate = 711;
		yCoordinate = 323;
	}
	else if (x == 2 && y == 3) 
	{
		xCoordinate = 711;
		yCoordinate = 249;
	}
	//3 Column
	else if (x == 3 && y == 0) 
	{
		xCoordinate = 787;
		yCoordinate = 470;
	}
	else if (x == 3 && y == 1) 
	{
		xCoordinate = 787;
		yCoordinate = 395;
	}
	else if (x == 3 && y == 2) 
	{
		xCoordinate = 787;
		yCoordinate = 323;
	}
	else if (x == 3 && y == 3) 
	{
		xCoordinate = 787;
		yCoordinate = 249;
	}
	return std::make_pair(xCoordinate, yCoordinate);
}
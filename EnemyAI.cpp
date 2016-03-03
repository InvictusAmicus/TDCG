#include"EnemyAI.h"
#include"CollisionDetection.h"
#include<iostream>
#include<tuple>

#define NoMove 10000

USING_NS_CC;

int PlayersInEnemyArea;
int EnemysInPlayerArea;
char CopyEnemyTowerGrid[5][5];
char CopyColGrid[10][5];
int EnemyStartX = 6;
int EnemyStartY = 0;


void EnemyAI::OpenPostions() 
{
	CollisionDetection GridField;
	
}

void EnemyAI::CopyTowerGrid()
{
	CollisionDetection FieldState;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			CopyEnemyTowerGrid[i][j] = FieldState.getEnemyTowerGrid(i,j);
		}
	}
}

void EnemyAI::CopyColGridMap()
{
	CollisionDetection FieldState;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			CopyColGrid[i][j] = FieldState.getColGrid(i, j);
		}
	}
}

int EnemyAI::PlayerAtSecondLastRow() 
{
	int x = 8;
	for (int y = 0; y < 5; y++) 
	{
		if (CopyColGrid[x][y] == 'P') 
		{
			if (CopyColGrid[x+1][y] == 'E')
			{
			    return NoMove;
			}
			else 
			{
				return y;
			}
		}
	}
	return NoMove;
}

int EnemyAI::PlayerAttackSecondRow() 
{
	int NumOfP = 0;
	for (int x = 5; x < 10; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (CopyColGrid[x][y] == 'P')
			{
				NumOfP++;			
			}
		}
	}
    CCLOG("NumOfP, %d", NumOfP);
	if (NumOfP==0 || NumOfP == 1)
	{
		CCLOG("CHECKING IF");
		if (CopyColGrid[EnemyStartX][EnemyStartY] == 'N') 
		{
			if (EnemyStartY == 4) 
			{
				CCLOG("CHECKING IF 0");
				EnemyStartY = 0;
			}
			else 
			{
				CCLOG("CHECKING ELSE");
				EnemyStartY++;
			}
			CCLOG("EnemyStartY, %d", EnemyStartY);
			return EnemyStartY;
		}
	}
	return NoMove;
}

std::pair <int, int> EnemyAI::PlayerTowerCreate()
{
	for (int x = 5; x < 10; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (CopyColGrid[x][y] == 'P')
			{
				if (y == 4) 
				{
					y = 3; 
				}
				if (CopyEnemyTowerGrid[x-5][y] == 'T')
				{
					return std::make_pair(NoMove,NoMove);
				}
				
				else 
				{
					return std::make_pair(x-5, y);
				}
			}
		}
	}
}

//x and y value will be for the ColGrid postion
std::pair <int, int> EnemyAI::EnemySpritePlacements(int x, int y)
{
	int xCoordinate, yCoordinate;
	//5
	if (x == 5 && y == 0) 
	{
		xCoordinate = 518;
		yCoordinate = 508;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 5 && y == 1) 
	{ 
		xCoordinate = 518; 
		yCoordinate = 434;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 5 && y == 2) 
	{ 
		xCoordinate = 518; 
		yCoordinate = 359;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 5 && y == 3) 
	{ 
		xCoordinate = 518; 
		yCoordinate = 287;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 5 && y == 4) 
	{ 
		xCoordinate = 518; 
		yCoordinate = 209;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	//6
	else if (x == 6 && y == 0) 
	{ 
		xCoordinate = 597; 
		yCoordinate = 508;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 6 && y == 1) 
	{ 
		xCoordinate = 597; 
		yCoordinate = 434;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 6 && y == 2) 
	{ 
		xCoordinate = 597;
		yCoordinate = 359;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 6 && y == 3) 
	{ 
		xCoordinate = 597; 
		yCoordinate = 287;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 6 && y == 4) 
	{ 
		xCoordinate = 597; 
		yCoordinate = 209;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	//7
	else if (x == 7 && y == 0) 
	{ 
		xCoordinate = 674; 
		yCoordinate = 508;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 7 && y == 1) 
	{ 
		xCoordinate = 674;
		yCoordinate = 434;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 7 && y == 2) 
	{ 
		xCoordinate = 674; 
		yCoordinate = 359;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 7 && y == 3) 
	{ 
		xCoordinate = 674; 
		yCoordinate = 287;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 7 && y == 4) 
	{ 
		xCoordinate = 674; 
		yCoordinate = 209;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	//8
	else if (x == 8 && y == 0) 
	{ 
		xCoordinate = 747; 
		yCoordinate = 508;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 8 && y == 1) 
	{
		xCoordinate = 747;
		yCoordinate = 434;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 8 && y == 2) 
	{ 
		xCoordinate = 747;
		yCoordinate = 359;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 8 && y == 3) 
	{ 
		xCoordinate = 747; 
		yCoordinate = 287;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 8 && y == 4) 
	{ 
		xCoordinate = 747; 
		yCoordinate = 209;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	//9
	else if (x == 9 && y == 0) 
	{ 
		xCoordinate = 828; 
		yCoordinate = 508;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 9 && y == 1) 
	{ 
		xCoordinate = 828; 
		yCoordinate = 434;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 9 && y == 2) 
	{ 
		xCoordinate = 828; 
		yCoordinate = 359;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 9 && y == 3) 
	{ 
		xCoordinate = 828; 
		yCoordinate = 287;
		return std::make_pair(xCoordinate, yCoordinate);
	}
	else if (x == 9 && y == 4) 
	{ 
		xCoordinate = 828; 
		yCoordinate = 209;
		return std::make_pair(xCoordinate, yCoordinate);
	}

	return std::make_pair(xCoordinate, yCoordinate);
}

//x and y value will be for the EnemyTowerlGrid postion
std::pair <int, int> EnemyAI::EnemyTowerPlacements(int x, int y)
{
	int xCoordinate, yCoordinate;
	//0 Column
	if (x == 0 && y == 0) 
	{
		xCoordinate = 557;
		yCoordinate = 478;
	}
	else if (x == 0 && y == 1) 
	{
		xCoordinate = 557;
		yCoordinate = 402;
	}
	else if (x == 0 && y == 2) 
	{
		xCoordinate = 557;
		yCoordinate = 330;
	}
	else if (x == 0 && y == 3) 
	{
		xCoordinate = 557;
		yCoordinate = 258;
	}
	//1 Column
	else if (x == 1 && y == 0) 
	{
		xCoordinate = 634;
		yCoordinate = 478;
	}
	else if (x == 1 && y == 1) 
	{
		xCoordinate = 634;
		yCoordinate = 402;
	}
	else if (x == 1 && y == 2) 
	{
		xCoordinate = 634;
		yCoordinate = 330;
	}
	else if (x == 1 && y == 3) 
	{
		xCoordinate = 634;
		yCoordinate = 258;
	}
	//2 Column
	else if (x == 2 && y == 0) 
	{
		xCoordinate = 711;
		yCoordinate = 478;
	}
	else if (x == 2 && y == 1) 
	{
		xCoordinate = 711;
		yCoordinate = 402;
	}
	else if (x == 2 && y == 2) 
	{
		xCoordinate = 711;
		yCoordinate = 330;
	}
	else if (x == 2 && y == 3) 
	{
		xCoordinate = 711;
		yCoordinate = 258;
	}
	//3 Column
	else if (x == 3 && y == 0) 
	{
		xCoordinate = 787;
		yCoordinate = 478;
	}
	else if (x == 3 && y == 1) 
	{
		xCoordinate = 787;
		yCoordinate = 402;
	}
	else if (x == 3 && y == 2) 
	{
		xCoordinate = 787;
		yCoordinate = 330;
	}
	else if (x == 3 && y == 3) 
	{
		xCoordinate = 787;
		yCoordinate = 258;
	}
	return std::make_pair(xCoordinate, yCoordinate);
}

//x variable will be the enemy resources
std::tuple <int, int, int, int, int> EnemyAI::checkVariables(int PlayerResource, int EnemyResource)
{
	//PS = Player Sprite, PT = Player Tower
	//ES = Enemy Sprite, ET = Enemy Tower
	//PIEA = Players In enemy area, EIPA = Enemies In Player Area
	int PS = 0, PT = 0, ES = 0, ET = 0, PIEA = 0, EIPA = 0;
	CollisionDetection FieldState;
	//FieldState.Q();

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
	CopyTowerGrid();
	CopyColGridMap();
	
	/*
	//check the contents of the two grid arrays
	for (int x = 0; x < 5;x++) { 
		for (int j = 0; j < 5;j++) 
		{
			CCLOG("Tower Grid %d,%d :: %c", x,j,CopyEnemyTowerGrid[x][j]);
		} 
	}
	for (int x = 0; x < 10;x++) {
		for (int j = 0; j < 5;j++)
		{
			CCLOG("ColGrid Grid %d,%d :: %c", x, j, CopyColGrid[x][j]);
		}
	}
	*/
	
	//std::tuple<int, int, int> EnemyCreation = CreateEnemy(PlayerResource, EnemyResource,
	//	                                                  PS, PT, ES, ET, PIEA, EIPA);
	//int EnemyNumber = std::get<0>(EnemyCreation);
	//int EnemyPostionX = std::get<1>(EnemyCreation);
	//int EnemyPostionY = std::get<2>(EnemyCreation);
	
	//hardcoded test data
	int EnemyNumber = 1;
	int EnemyPostionX = 635;
	int EnemyPostionY = 478;
	int last = PlayerAtSecondLastRow();
	int attack = PlayerAttackSecondRow();
	int testX = 0;
	int testY = 0;
	CCLOG("ENEMYR %d", EnemyResource);
	if (last!=10000 && EnemyResource>=200)
	{
		CCLOG("ENEMYR>200");
		testX = 9;
		testY = last;
		EnemyNumber = 1;
		std::pair<int, int> location = EnemySpritePlacements(testX, last);
		//std::pair<int, int> location = EnemySpritePlacements(6,6);
		EnemyPostionX = std::get<0>(location);
		EnemyPostionY = std::get<1>(location);
	}
	else if (attack!=10000 && EnemyResource >= 200 && PIEA <= 2)
	{
		CCLOG("ENEMYR2>200");
		testX = 6;
		testY = attack;
		EnemyNumber = 1;
		std::pair<int, int> location = EnemySpritePlacements(6, attack);
		//std::pair<int, int> location = EnemySpritePlacements(6,6);
		EnemyPostionX = std::get<0>(location);
		EnemyPostionY = std::get<1>(location);
	}
	else if (EnemyResource >= 300 && PIEA > 2)
	{
		std::pair<int, int> TowerCreate = PlayerTowerCreate();
		int TowerX = std::get<0>(TowerCreate);
		int TowerY = std::get<1>(TowerCreate);
		if (TowerX != 10000) 
		{
			EnemyNumber = 0;
			testX = TowerX;
			testY = TowerY;
			CCLOG("testX %d",TowerX);
			CCLOG("testY %d",TowerY);
			std::pair<int, int> location = EnemyTowerPlacements(testX, testY);
			EnemyPostionX = std::get<0>(location);
			EnemyPostionY = std::get<1>(location);
		}
	}
	else 
	{
		CCLOG("ENEMYR>Else");
		EnemyNumber = NoMove;
		EnemyPostionX = NoMove;
		EnemyPostionY = NoMove;
	}
	//int EnemyPostionX = 635;
	//int EnemyPostionY = 478;
    //if (PlayerResource >= 200) { EnemyNumber = 1; }
    //if (PlayerResource >= 200) { EnemyPostionX = 672; }
	//if (PlayerResource >= 200) { EnemyPostionY = 286; }
	//EnemyNumber = NoMove;

	CCLOG("1- %d", EnemyNumber);
	CCLOG("2- %d", EnemyPostionX);
	CCLOG("3- %d", EnemyPostionY);
	CCLOG("4- %d", testX);
	CCLOG("5- %d", last);

	return std::make_tuple(EnemyNumber, EnemyPostionX, EnemyPostionY, testX, testY);
	
	//return std::make_tuple(NoMove, NoMove, NoMove);
}

//might need to add the open gird postions from the colgrid in CollsionDetection
std::tuple <int, int, int>EnemyAI::CreateEnemy(int PlayerResource, int EnemyResource, int PS, int PT, int ES, int ET, int PIEA, int EIPA) 
{
	//int Enemy, PostionX, PostionY;
	bool CanCreateEnemy = false, CanCreateTower = true, make = false;
	
	
	//first statement if no sprites or towers can be made
	if (EnemyResource<100)
	{
		CCLOG("Return first EnemyCreate Statement");
		return std::make_tuple(NoMove, NoMove, NoMove);
	}

	//makes the boolean variable true if the Soldier sprites can be made
	if (EnemyResource >= 100) 
	{ 
		CanCreateEnemy = true; 
	}
	//makes the boolean variable true if the Tower sprites can be made
    if (EnemyResource >= 200) 
	{ 
		CanCreateTower = true; 
	}
	
	if (EnemyResource > PlayerResource && (ES > PS || ET > PT))
	{
		//EnemySprites - PlayerSprites > 3 && EnemyTower - PlayerTower > 3 && Players in enemy area = 0
		if (((ES - PS) > 3) && ((ET - PT) > 3) && PIEA == 0)
		{
			//return in order to save resources
			//no player sprites will be in the area
			return std::make_tuple(NoMove, NoMove, NoMove);
		}
		else if ((ES - PS) > 3 && PIEA != 0 && CanCreateTower == true)
		{
			for (int i = 5; i < 10; i++) {
				for (int j = 0; j < 5; j++) {
					if (CopyColGrid[i][j] = 'P' && make != true)
					{
						if (CopyEnemyTowerGrid[i - 5][j] == 'N')
						{
							make = true;
							//std::pair<int, int> TCreate = EnemyTowerPlacements(i - 5, j);
							//int EnemyPostionX = std::get<0>(TCreate);
							//int EnemyPostionY = std::get<1>(TCreate);
							//return std::make_tuple(0, EnemyPostionX, EnemyPostionY);
						}
					}
				}
			}
		}
		else if ((ES - PS) > 3 && PIEA == 0 && CanCreateEnemy == true)
		{
			for (int j = 0; j < 5; j++) {
				for (int i = 5; i < 10; i++) {
					if (CopyColGrid[i][j] == 'N' && make != true)
					{
						//make = true;
						//std::tuple<int, int> SCreate = EnemySpritePlacements(i, j);
						//int EnemyPostionX = std::get<0>(SCreate);
						//int EnemyPostionY = std::get<1>(SCreate);
						//return std::make_tuple(1, EnemyPostionX, EnemyPostionY);
					}
				}
			}
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


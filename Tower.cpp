#include "Tower.h"
#include "Soldier.h"

bool Tower::checkSurroundings()
{
	if (positionX - 1 == NULL && positionX == NULL)
	{
		if (positionY-1 == NULL && positionY == NULL)
		{
			return false;
		}
	}
	return true;
}

void Tower::move()
{
	if (checkSurroundings() == false)
	{
		// do nothing
	}
	else
	{
		Soldier* s;
		//findSoldier and initialise him to s
		shoot();
	}
}

void Tower::shoot()
{

}
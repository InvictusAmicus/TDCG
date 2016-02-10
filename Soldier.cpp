#include "Soldier.h"
#include "Player.h"

Soldier::Soldier()
{
	type = 's';
}

Soldier::~Soldier()
{
	health = 1;
	attack = 1;
	positionX = 0;
	positionY = 0;
	delete this;
}

/*void Soldier::attackPlayer(Player* p)
{
	p->setLife(attack);
}*/

void Soldier::move()
{
	positionY += 1;
}

int Soldier::getPositionX()
{
	return positionX;
}

int Soldier::getPositionY()
{
	return positionY;
}
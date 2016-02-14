#include "Soldier.h"
#include "Player.h"

Soldier::Soldier()
{
	type = 's';
	health = 1;
	attack = 1;
}

Soldier::~Soldier()
{
	//positionX = 0;
	//positionY = 0;
	delete this;
}

/*void Soldier::attackPlayer(Player* p)
{
	p->setLife(attack);
}*/

void Soldier::move()
{
	positionX += 1;
}

int Soldier::getPositionX()
{
	return positionX;
}

int Soldier::getPositionY()
{
	return positionY;
}

void Soldier::setHealth(int d)
{
	health -= d;
}

int Soldier::getAttack()
{
	return attack;
}
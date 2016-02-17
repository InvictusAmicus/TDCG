#include "Soldier.h"
#include "Player.h"

Soldier::Soldier()
{
	type = 's';
	health = 4;
	attack = 1;
	ability = 1;
}

Soldier::Soldier(std::string n)
{
	setSprite(n);
	type = 's';
	health = 4;
	attack = 1;
	ability = 2;
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

void Soldier::activateAbility(Player* p)
{
	if (ability == 1)
	{
		p->drawCard();
	}
	else if (ability == 2)
	{
		p->setLife(-20);
	}
}
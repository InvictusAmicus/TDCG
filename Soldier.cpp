#include "Soldier.h"
#include "Player.h"
#include <ctime>
#include <time.h>

Soldier::Soldier()
{
	type = 's';
	health = 4;
	attack = 1;
	ability = 1;
	moving = false;
	attacking = false;
}

Soldier::Soldier(std::string n)
{
	setSprite(n);
	
	//Card Name to be changed later
	if (n == "SampleCard2.png")
	{
		type = 's';
		health = 5;
		attack = 5;
		ability = 0;
		moving = false;
		attacking = false;
	}

	else if (n == "BringerOfRest.png")
	{
		type = 's';
		health = 8;
		attack = 2;
		ability = 0;
		moving = false;
		attacking = false;
	}

	//Card Name to be changed later
	else if (n == "Archfiend.png")
	{
		type = 's';
		health = 7;
		attack = 3;
		ability = 1;
		moving = false;
		attacking = false;
	}

	//Card Name to be changed later
	else if (n == "A.I.P.png")
	{
		type = 's';
		health = 11;
		attack = 1;
		ability = 1;
		moving = false;
		attacking = false;
	}

	//Card Name to be changed later
	else if (n == "Aviater.png")
	{
		type = 's';
		health = 5;
		attack = 10;
		ability = 2;
		moving = false;
		attacking = false;
	}

	//Card Name to be changed later
	else if (n == "Cain.png")
	{
		type = 's';
		health = 9;
		attack = 5;
		ability = 1;
		moving = false;
		attacking = false;
	}

	else if (n == "Eltanin.png")
	{
		type = 's';
		health = 7;
		attack = 5;
		ability = 1;
		moving = false;
		attacking = false;
	}

	//Card Name to be changed later
	else if (n == "Indicted.png")
	{
		type = 's';
		health = 7;
		attack = 5;
		ability = 1;
		moving = false;
		attacking = false;
	}

	//Card Name to be changed later
	else if (n == "MoltonCore.png")
	{
		type = 's';
		health = 7;
		attack = 10;
		ability = 1;
		moving = false;
		attacking = false;
	}

	//Card Name to be changed later
	else if (n == "IceDemon.png")
	{
		type = 's';
		health = 5;
		attack = 5;
		ability = 1;
		moving = false;
		attacking = false;
	}

	//Card Name to be changed later
	else if (n == "Tariq.png")
	{
		type = 's';
		health = 12;
		attack = 2;
		ability = 2;
		moving = false;
		attacking = false;
	}

	//Card Name to be changed later
	else if (n == "Wisp.png")
	{
		type = 's';
		health = 6;
		attack = 3;
		ability = 2;
		moving = false;
		attacking = false;
	}
	else if (n == "testEnemy.png")
	{
		type = 's';
		health = 3;
		attack = 1;
		ability = 0;
		moving = false;
		attacking = false;
	} 
	else if (n == "testEnemy2.png")
	{
		type = 's';
		health = 1;
		attack = 2;
		ability = 0;
		moving = false;
		attacking = false;
	}
	else
	{
		health = 4;
		attack = 1;
		ability = 0;
		moving = false;
		attacking = false;
	}
}

Soldier::~Soldier()
{
	delete this;
}

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
	srand(time(NULL));

	if (ability == 1)
	{
		p->drawCard();
	}
	else if (ability == 2)
	{
		p->setLife(-20);
	}
	else if (ability == 3)
	{
		int x = rand()%p->getHandSize();
		p->removeFromHand(x);
	}
}

bool Soldier::getMoving() 
{
	return moving;
}

bool Soldier::getAttacking() 
{
	return attacking;
}
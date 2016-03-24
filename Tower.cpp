//Worked on by Ciaran Clerkin K00191500 and Declan Cordial K00184439

#include "Tower.h"

Tower::Tower()
{
	damage = 1;
}

Tower::~Tower()
{
	
}

Tower::Tower(std::string name)
{
	setSprite(name);
	damage = 1;
	type = 't';
}
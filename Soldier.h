#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "NewSinglePlayGame.h"
#include "Card.h"
#include "Player.h"

class Soldier : public Card
{
private:
	int ability;
	int attack;
	int health;
	int positionX;
	int positionY;

public:
	Soldier();
	Soldier(std::string name);

	~Soldier();
	virtual bool init() { return true; }
	virtual void activateAbility(Player*);
	virtual void attackPlayer(Player*) {}
	virtual void move();
	virtual int getPositionX();
	virtual int getPositionY();
	virtual void setPositionX(int x) { positionX = x; }
	virtual void setPositionY(int y) { positionY = y; }
	virtual int getHealth() { return health; }
	virtual void setHealth(int);
	virtual int getAttack();
};

#endif // __SOLDIER_H__
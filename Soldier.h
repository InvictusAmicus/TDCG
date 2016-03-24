//Worked on by Ciaran Clerkin K00191500 and Declan Cordial K00184439

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
	bool moving;
	bool attacking;

public:
	Soldier();
	Soldier(std::string name);

	~Soldier();
	virtual bool init() { return true; }
	virtual bool getMoving();
	virtual bool getAttacking();
	virtual void isAttacking(bool attack) { attacking = attack; }
	virtual void isMoving(bool move) { moving = move; }
	virtual void activateAbility(Player*);
	virtual void attackPlayer(Player*) {}
	virtual void move();
	virtual void setPositionX(int x) { positionX = x; }
	virtual void setPositionY(int y) { positionY = y; }
	virtual void setHealth(int);
	virtual int getAttack();
	virtual int getPositionX();
	virtual int getPositionY();
	virtual int getHealth() { return health; }
};

#endif // __SOLDIER_H__
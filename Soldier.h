#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "Character.h"
#include "Player.h"
class Soldier : public Character
{
private:
	int attack; 
	int positionX;
	int positionY;

public:
	Soldier();
	~Soldier();
	virtual bool init() { return true; }
	virtual void attackPlayer(Player*) {}
	virtual void move();
	virtual int getPositionX();
	virtual int getPositionY();

};

#endif // __SOLDIER_H__
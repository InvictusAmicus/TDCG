#ifndef __TOWER_H__
#define __TOWER_H__

#include "Card.h"
#include <iostream>

class Tower : public Card
{
private:
	int damage;
	int positionX;
	int positionY;
public:
	Tower();
	~Tower();
	Tower(std::string name);

//	bool init();
	virtual int getDamage() { return damage; }
	virtual int getPositionX() { return positionX; }
	virtual int getPositionY() { return positionY; }

	virtual void setPositionX(int x) { positionX = x; }
	virtual void setPositionY(int y) { positionY = y; }
};

#endif // __TOWER_H__
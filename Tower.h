#ifndef __TOWER_H__
#define __TOWER_H__

#include"Character.h"

class Tower : public Card
{
private:
	int damage;
	int positionX;
	int positionY;
public:
	Tower();
	~Tower();
	Tower(std::string name)
	{
		setSprite(name);
	}

//	bool init();
	void move();
	void shoot();
	bool checkSurroundings();

	virtual int getDamage() { return damage; }
	virtual int getPositionX() { return positionX; }
	virtual int getPositionY() { return positionY; }

	virtual void setPositionX(int x) { positionX = x; }
	virtual void setPositionY(int y) { positionY = y; }
};

#endif // __TOWER_H__
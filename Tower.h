#ifndef __TOWER_H__
#define __TOWER_H__

#include"Character.h"

class Tower : public Character
{
private:
	int damage;
	int positionX;
	int positionY;
public:
	Tower();
	~Tower();
	bool init();
	void move();
	void shoot();
	bool checkSurroundings();
};

#endif // __TOWER_H__
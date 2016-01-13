#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include"Card.h"

class Character
{
private:

public:
	Character() {};
	~Character() {};
	virtual bool init() = 0;
	virtual void move() = 0;
};

#endif // __CHARACTER_H__

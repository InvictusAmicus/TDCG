#pragma once

#ifndef _CARD_H_
#define _CARD_H_

#include "cocos2d.h"

class Card
{
private:
	cocos2d::Sprite cardSprite;
	int refNo;
	int cost;

public:
	Card();
	~Card();
	bool init();

};

#endif // !_CARD_H_
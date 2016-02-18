#ifndef _CARD_H_
#define _CARD_H_

#include "cocos2d.h"
#include <iostream>
#include <string>

class Card
{
private:
	int refNo;
	int cost;
	cocos2d::Sprite* cardSprite;
	std::string name;
	std::string lore;
	
public:
	Card();
	Card(std::string s);
	~Card();
	bool init() {}
	
	char type;
	char getType();
	cocos2d::Sprite* getSprite() { return cardSprite; }
	std::string getSpriteName() { return name; }
	std::string getLore() { return lore; }

	int getCost() { return cost; }
	void setCost(int c) { cost = c; }

	//move card to battlefield position (a1,a2)
	void moveTo(int a1, int a2);

	void setSprite(std::string name) { cardSprite = cocos2d::Sprite::create(name); }

};

#endif // !_CARD_H_
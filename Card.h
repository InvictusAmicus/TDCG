//Worked on by Ciaran Clerkin K00191500 and Declan Cordial K00184439

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
	std::string Health;
	std::string Attack;
	std::string DisplayName;
	
public:
	Card();
	Card(std::string s);
	~Card();
	bool init() {}
	
	char type;
	/*!
	* Returns card type based off of name
	*/
	char getType();

	/*!
	* get the sprite variable of the card
	*/
	cocos2d::Sprite* getSprite() { return cardSprite; }

	/*!
	* Get the name of the sprite card
	*/
	std::string getSpriteName() { return name; }
	
	/*!
	* Get the lore of the card
	*/
	std::string getLore() { return lore; }

	/*!
	* Get the Health of the card
	*/
	std::string getHealth() { return Health; }

	/*!
	* Get the lore of the card
	*/
	std::string getAttack() { return Attack; }

	/*!
	* Get the DisplayName of the card
	*/
	std::string getDisplayName() { return DisplayName; }

	/*!
	* Return the cost of the card
	*/
	int getCost() { return cost; }

	/*!
	* Set the cost of the card
	*/
	void setCost(int c) { cost = c; }
	
	/*!
	* Create the sprite of the card
	*/
	void setSprite(std::string name) { cardSprite = cocos2d::Sprite::create(name); }
};

#endif // !_CARD_H_
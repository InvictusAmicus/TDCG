#ifndef _CARD_H_
#define _CARD_H_

#include "cocos2d.h"
#include <iostream>

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

	//move card to battlefield position (a1,a2)
	void moveTo(int a1, int a2);

	void touched(cocos2d::EventMouse* t)
	{
		/*bool TouchScene::onTouchBegan(Touch* touch, Event* event)
		{
		labelTouchInfo->setPosition(touch->getLocation());
		labelTouchInfo->setString("You Touched Here");
		return tr*/
		moveTo(t->getCursorX(), t->getCursorY());
	}

};

#endif // !_CARD_H_
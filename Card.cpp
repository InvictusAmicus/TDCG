#include "Card.h"
#include "cocos2d.h"
#include <iostream>

Card::Card()
{
	cardSprite = cocos2d::Sprite::create("HelloWorld.png");
	name = "HelloWorld";
	lore = "Default Lore";
}

Card::Card(std::string s)
{
	cardSprite = cocos2d::Sprite::create(s);
	name = s;
	lore = "Unique Lore";
}

Card::~Card()
{
	refNo = 0;
	cost = 0;
	delete cardSprite;
	delete this;
}

void Card::moveTo(int a1, int a2)
{
	cardSprite->setPosition(a1, a2);
}


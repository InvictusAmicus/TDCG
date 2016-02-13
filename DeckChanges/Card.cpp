#include "Card.h"
#include "cocos2d.h"
#include <iostream>

int x = 0;

Card::Card()
{
	cardSprite = cocos2d::Sprite::create("SampleCard.png");
	name = "SampleCard.png";
	lore =	"Sir Galahad of Dirpe had fought a thousand wars. Many\n"
			"against himself, a few against the enemies of his kingdom,\n"
			"and one against the denizen plaguing his king's mind.";
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

char Card::getType() 
{

	type = 's';

	if (x >= 200) {
		type = 't';
	}
	x++;
	CCLOG("%d", x);
	return type;
}
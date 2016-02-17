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
	
	/*
	Remove the comments relating to the cards when they have the appropriate name and lore assigned
	*/
	
	//Card Name to be changed later
	if (name == "SampleCard.png")
	{
		//Remove when proper lore is added
		lore = "SampleCard.png";
	}

	//Card Name to be changed later
	else if (name == "SampleCard2.png")
	{
		//Remove when proper lore is added
		lore = "SampleCard2.png";
	}

	//Card Name to be changed later
	else if (name == "Archfiend.png")
	{
		//Remove when proper lore is added
		lore = "Archfiend.png";
	}

	//Card Name to be changed later
	else if (name == "A.I.P.png")
	{
		//Remove when proper lore is added
		lore = "A.I.P.png";
	}

	//Card Name to be changed later
	else if (name == "Aviater.png")
	{
		//Remove when proper lore is added
		lore = "Aviater.png";
	}

	//Card Name to be changed later
	else if (name == "Cain.png")
	{
		//Remove when proper lore is added
		lore = "Cain.png";
	}

	//Card Name to be changed later
	else if (name == "Indicted.png")
	{
		//Remove when proper lore is added
		lore = "Indicted.png";
	}

	//Card Name to be changed later
	else if (name == "MoltonCore.png")
	{
		//Remove when proper lore is added
		lore = "MoltonCore.png";
	}

	//Card Name to be changed later
	else if (name == "IceDemon.png")
	{
		//Remove when proper lore is added
		lore = "IceDemon.png";
	}

	//Card Name to be changed later
	else if (name == "Tariq.png")
	{
		//Remove when proper lore is added
		lore = "Tariq.png";
	}

	//Card Name to be changed later
	else if (name == "Wisp.png")
	{
		//Remove when proper lore is added
		lore = "Wisp.png";
	}
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
	/*type = 's';

	if (x >= 200) {
		type = 't';
	}
	x++;
	CCLOG("%d", x);*/
	if (name == "SampleCard.png")
	{
		return 't';
	}
	else
	{
		return 's';
	}
	return type;
}
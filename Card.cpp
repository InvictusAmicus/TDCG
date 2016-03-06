#include "Card.h"
#include "cocos2d.h"
#include <iostream>

int x = 0;
int CostMultiplier = 50;

Card::Card()
{
	cardSprite = cocos2d::Sprite::create("SampleCard.png");
	name = "SampleCard.png";
	lore =	"Sir Galahad of Dirpe had fought a thousand wars. Many\n"
			"against himself, a few against the enemies of his kingdom,\n"
			"and one against the denizen plaguing his king's mind.";
	cost = 50;
	Health = "4";
	Attack = "1";
	DisplayName = "Default";
}

Card::Card(std::string s)
{
	cardSprite = cocos2d::Sprite::create(s);
	name = s;
	lore = "Unique Lore";
	/*
	Remove the comments relating to the cards when they have the appropriate name and lore assigned
	*/
	cost = 100;

	if (name == "BringerOfRest.png")
	{
		cost = (CostMultiplier * 4);
	}

	else if (name == "Cain.png")
	{
		cost = (CostMultiplier * 6);
	}

	else if (name == "Eltanin.png")
	{
		cost = (CostMultiplier * 5);
	}

	else if (name == "EternalDestruction.png")
	{
		cost = (CostMultiplier * 9);
	}

	else if (name == "HauntedHero.png")
	{
		cost = (CostMultiplier * 3);
	}

	else if (name == "HellDemon.png")
	{
		cost = (CostMultiplier * 6);
	}

	else if (name == "HiddenInTheDark.png")
	{
		cost = (CostMultiplier * 3);
	}

	else if (name == "HolyCrusader.png")
	{
		cost = (CostMultiplier * 5);
	}

	else if (name == "IceDemon.png")
	{
		cost = (CostMultiplier * 6);
	}

	else if (name == "Indicted.png")
	{
		cost = (CostMultiplier * 2);
	}

	else if (name == "Invidia.png")
	{
		cost = (CostMultiplier * 3);
	}

	else if (name == "MagmaSpawn.png")
	{
		cost = (CostMultiplier * 3);
	}

	else if (name == "RemnantofDragons.png")
	{
		cost = (CostMultiplier * 7);
	}

	else if (name == "SpiritOfTheFallen.png")
	{
		cost = (CostMultiplier * 1);
	}

	else if (name == "Tariq.png")
	{
		cost = (CostMultiplier * 2);
	}

	else if (name == "TheConverter.png")
	{
		cost = (CostMultiplier * 4);
	}

	else if (name == "ThrallOfMagma.png")
	{
		cost = (CostMultiplier * 2);
	}

	else if (name == "Tower.png")
	{
		cost = (CostMultiplier * 2);
	}

	else if (name == "VampiricBeast.png")
	{
		cost = (CostMultiplier * 5);
	}

	else if (name == "VoidAbomination.png")
	{
		cost = (CostMultiplier * 4);
	}

	else if (name == "VoidWarrior.png")
	{
		cost = (CostMultiplier * 5);
	}

	else if (name == "Xenomorph.png")
	{
		cost = (CostMultiplier * 3);
	}

	else if (name == "YoungSquire.png")
	{
		cost = (CostMultiplier * 2);
	}


	//
	//Collection Display info
	//
	if (name == "D_BringerOfRest.png")
	{
		lore = "Sample Lore";
		Health = "8";
		Attack = "2";
		DisplayName = "Bringer Of Rest";
	}

	else if (name == "D_Cain.png")
	{
		lore = "Sample Lore";
		Health = "9";
		Attack = "5";
		DisplayName = "Cain";
	}

	else if (name == "D_Eltanin.png")
	{
		lore = "Sample Lore";
		Health = "7";
		Attack = "5";
		DisplayName = "Eltanin";
	}

	else if (name == "D_EternalDestruction.png")
	{
		lore = "Sample Lore";
		Health = "8";
		Attack = "12";
		DisplayName = "Eternal Destruction";
	}

	else if (name == "D_HauntedHero.png")
	{
		lore = "Sample Lore";
		Health = "7";
		Attack = "1";
		DisplayName = "Haunted Hero";
	}

	else if (name == "D_HellDemon.png")
	{
		lore = "Sample Lore";
		Health = "6";
		Attack = "8";
		DisplayName = "Hell Demon";
	}

	else if (name == "D_HiddenInTheDark.png")
	{
		lore = "Sample Lore";
		Health = "3";
		Attack = "5";
		DisplayName = "Hidden In The Dark";
	}

	else if (name == "D_HolyCrusader.png")
	{
		lore = "Sample Lore";
		Health = "6";
		Attack = "5";
		DisplayName = "Holy Crusader";
	}

	else if (name == "D_IceDemon.png")
	{
		lore = "Sample Lore";
		Health = "8";
		Attack = "6";
		DisplayName = "Ice Demon";
	}

	else if (name == "D_Indicted.png")
	{
		lore = "Sample Lore";
		Health = "3";
		Attack = "3";
		DisplayName = "Indicted";
	}

	else if (name == "D_Invidia.png")
	{
		lore = "Sample Lore";
		Health = "6";
		Attack = "2";
		DisplayName = "Invidia";
	}

	else if (name == "D_MagmaSpawn.png")
	{
		lore = "lore";
		Health = "3";
		Attack = "4";
		DisplayName = "Magma Spawn";
	}

	else if (name == "D_RemnantofDragons.png")
	{
		lore = "lore";
		Health = "12";
		Attack = "4";
		DisplayName = "Remnant of Dragons";
	}

	else if (name == "D_SpiritOfTheFallen.png")
	{
		lore = "lore";
		Health = "2";
		Attack = "2";
		DisplayName = "Spirit Of The Fallen";
	}

	else if (name == "D_Tariq.png")
	{
		lore = "lore";
		Health = "5";
		Attack = "1";
		DisplayName = "Tariq";
	}

	else if (name == "D_TheConverter.png")
	{
		lore = "lore";
		Health = "9";
		Attack = "1";
		DisplayName = "The Converter";
	}

	else if (name == "D_ThrallOfMagma.png")
	{
		lore = "lore";
		Health = "2";
		Attack = "4";
		DisplayName = "Thrall Of Magma";
	}

	else if (name == "D_Tower.png")
	{
		lore = "lore";
		Health = "--";
		Attack = "1";
		DisplayName = "Tower";
	}

	else if (name == "D_VampiricBeast.png")
	{
		lore = "lore";
		Health = "5";
		Attack = "7";
		DisplayName = "Vampiric Beast";
	}

	else if (name == "D_VoidAbomination.png")
	{
		lore = "lore";
		Health = "7";
		Attack = "3";
		DisplayName = "Void Abomination";
	}

	else if (name == "D_VoidWarrior.png")
	{
		lore = "This is the lore for the Void Warrior";
		Health = "11";
		Attack = "2";
		DisplayName = "Void Warrior";
	}

    else if (name == "D_Xenomorph.png")
	{
		lore = "This is the lore for Xenomorph";
		Health = "4";
		Attack = "4";
		DisplayName = "Xenomorph";
	}
	
	else if (name == "D_YoungSquire.png")
	{
		lore = "YoungSquire lore";
		Health = "7";
		Attack = "0";
		DisplayName = "YoungSquire";
	}
	
	
}

Card::~Card()
{
	refNo = 0;
	cost = 0;
	delete cardSprite;
	delete this;
}

char Card::getType() 
{
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
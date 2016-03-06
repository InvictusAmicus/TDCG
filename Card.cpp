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
		lore = "They said the angel would appear on empty battlefields, taking the souls of the defeated to rest. "
				"None knew that the bodies ended up as her dinner.";
		Health = "8";
		Attack = "2";
		DisplayName = "Bringer Of Rest";
	}

	else if (name == "D_Cain.png")
	{
		lore = "Cain VI, Vampire Demon Lord of the Abyss was brooding. The demons were slaughtering his prey. "
				"And he was hungry. So hungry. He sighed. He didn't want to join a losing battle. "
				"But the thought of dying in battle was much preferable to this hunger. He picked up his sword"
				" and left his humble abode.";
		Health = "9";
		Attack = "5";
		DisplayName = "Cain";
	}

	else if (name == "D_Eltanin.png")
	{
		lore = "Cain stood before the primal beast, and sighed once more. The beast was like him, just with sub-human "
				"intelligence. They shared the same hunger. Just that Cain could control his impulses. With a heavy heart, "
				"he clashed with the beast, steel colliding with hardened claws.";
		Health = "7";
		Attack = "5";
		DisplayName = "Eltanin";
	}

	else if (name == "D_EternalDestruction.png")
	{
		lore = "What could be said? It thought to Itself. He was the embodiment of suffering and torment. All ended "
				"with destruction. It just brought such devestation sooner than others. It saw nothing wrong with that. "
				"It was a merciful act.";
		Health = "8";
		Attack = "12";
		DisplayName = "Eternal Destruction";
	}

	else if (name == "D_HauntedHero.png")
	{
		lore = "She had fallen. While he was protecting the town, she had been taken in the night. Taken by the foul fiend that "
				"haunted his town. She died in his arms, as he cradled her slowly cooling body. He saw vengeance that night. "
				"Nowadays, the people cheered his name, 'Invictus, The Hero of Veritas', but he didn't care. He hadn't yet slain "
				"the fiend, so he would continue to fight.";
		Health = "7";
		Attack = "1";
		DisplayName = "Haunted Hero";
	}

	else if (name == "D_HellDemon.png")
	{
		lore = "It would burn the bodies.It liked the smell of burning flesh. The only thing that could get in It's "
			"way was It's own kind. The Ice Demon wanted to preserve bodies in ice, immortalizing them. How foolish. "
			"Destruction was obviously the only way forward.";
		Health = "6";
		Attack = "8";
		DisplayName = "Hell Demon";
	}

	else if (name == "D_HiddenInTheDark.png")
	{
		lore = "Cain watched them walk by, picking targets based on the hue of their neck. The hunger that drove him "
				"would be sated soon, and he would resume the hunt tonight.";
		Health = "3";
		Attack = "5";
		DisplayName = "Hidden In The Dark";
	}

	else if (name == "D_HolyCrusader.png")
	{
		lore = "Your corrupt leader has been slain! I command you so-called holy knights now! And we will rid the world of the "
				"demonic blight!\n-Invictus, The Hero of Veritas";
		Health = "6";
		Attack = "5";
		DisplayName = "Holy Crusader";
	}

	else if (name == "D_IceDemon.png")
	{
		lore = "It liked to look at It's victims. Encasing them in ice to preserve them so that It could look at its leisure "
			"It liked to take It's time, unlike that imbecilic Hell Demon. It would not let the world turn to ash. Not while "
			"It was around anyway.";
		Health = "8";
		Attack = "6";
		DisplayName = "Ice Demon";
	}

	else if (name == "D_Indicted.png")
	{
		lore = "'A human, battered by his own. How amusing. I will immortalize you as a reward for your persistence.'\n"
				"-Tali, Ice Demon";
		Health = "3";
		Attack = "3";
		DisplayName = "Indicted";
	}

	else if (name == "D_Invidia.png")
	{
		lore = "Invidia, Fog Whisperer only had one wish. To be left alone. Those who encroached on his territory were not"
				" given a second chance, demon or mortal.";
		Health = "6";
		Attack = "2";
		DisplayName = "Invidia";
	}

	else if (name == "D_MagmaSpawn.png")
	{
		lore = "The Hell Demon, Ea commanded an army of minions, all intent on doing his bidding. The magma spawn was "
				"the most plentiful, and they ravaged the land, burning what they could to less than rubble";
		Health = "3";
		Attack = "4";
		DisplayName = "Magma Spawn";
	}

	else if (name == "D_RemnantofDragons.png")
	{
		lore = "The dragon had slept for centuries under the sea, awoken by the battle between Cain and Ea. Angered, it entered"
				" the battlefield, only to be incinerated as it got caught in the crossfire.";
		Health = "12";
		Attack = "4";
		DisplayName = "Remnant of Dragons";
	}

	else if (name == "D_SpiritOfTheFallen.png")
	{
		lore = "The unnamed casualties of constant war litter the world, searching for a new home or a way to find salvation. "
				"Many get caught in the war again, and their spirit disintegrates in the minds and hearts of those they knew.";
		Health = "2";
		Attack = "2";
		DisplayName = "Spirit Of The Fallen";
	}

	else if (name == "D_Tariq.png")
	{
		lore = "'Hehehehe, if I stay down here, I can take over the land when everyone else has died! It's genius!\n"
			"-Tariq, the eternal coward";
		Health = "5";
		Attack = "1";
		DisplayName = "Tariq";
	}

	else if (name == "D_TheConverter.png")
	{
		lore = "The constant fear plaguing the land led many to turn to faith. Some took advantage of this, while others "
				"did what they could to soothe their weary hearts.";
		Health = "9";
		Attack = "1";
		DisplayName = "The Converter";
	}

	else if (name == "D_ThrallOfMagma.png")
	{
		lore = "'Oh my, it's hot here. There's even clumps of magma scattered around. Wait a second! Did that one just move?'"
				"\n-Last words of failed explorer, Cathal McGrath.";
		Health = "2";
		Attack = "4";
		DisplayName = "Thrall Of Magma";
	}

	else if (name == "D_Tower.png")
	{
		lore = "The best defences the humans could come up with was quickly adopted by the demons as a way of killing more and more";
		Health = "--";
		Attack = "1";
		DisplayName = "Tower";
	}

	else if (name == "D_VampiricBeast.png")
	{
		lore = "Woof";
		Health = "5";
		Attack = "7";
		DisplayName = "Vampiric Beast";
	}

	else if (name == "D_VoidAbomination.png")
	{
		lore = "Beings of the void rarely materialized in the world. When they did, things got ugly.";
		Health = "7";
		Attack = "3";
		DisplayName = "Void Abomination";
	}

	else if (name == "D_VoidWarrior.png")
	{
		lore = "Beings of the void resented the living, and dragged many back with them, humans and demons alike. None didn't fear them";
		Health = "11";
		Attack = "2";
		DisplayName = "Void Warrior";
	}

    else if (name == "D_Xenomorph.png")
	{
		lore = "'I don't know what they are, and I don't want to know. I just care about how many we kill.'\nInvictus"
			" The Hero of Veritas";
		Health = "4";
		Attack = "4";
		DisplayName = "Xenomorph";
	}
	
	else if (name == "D_YoungSquire.png")
	{
		lore = "Young, shaking, and covered in blood. The squires that survived their first day of training always turned into"
				" fine soldiers.";
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
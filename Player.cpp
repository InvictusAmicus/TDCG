#include "Player.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <time.h>
#include "GameOverScreen.h"

Player::Player()
{
	srand(time(NULL));

	life = 100;
	resource = 0;
	
	/*
	for (int i = 0; i < 10; i++)
	{
		deck.push_back(new Card("SampleCard.png"));
		deck.push_back(new Card("Cain.png"));
		deck.push_back(new Card("A.I.P.png"));
		deck.push_back(new Card("Archfiend.png"));
	}
	*/

	deck.push_back(new Card("Cain.png"));
	deck.push_back(new Card("Cain.png"));
	deck.push_back(new Card("BringerOfRest.png"));
	deck.push_back(new Card("BringerOfRest.png"));
	deck.push_back(new Card("EternalDestruction.png"));
	deck.push_back(new Card("EternalDestruction.png"));
	deck.push_back(new Card("Tower.png"));
	deck.push_back(new Card("Tower.png"));
	deck.push_back(new Card("Tower.png"));
	deck.push_back(new Card("Tower.png"));
	deck.push_back(new Card("Tower.png"));
	deck.push_back(new Card("Tower.png"));
	deck.push_back(new Card("Tower.png"));
	deck.push_back(new Card("Tower.png"));
	deck.push_back(new Card("Tower.png"));
	deck.push_back(new Card("Tower.png"));
	deck.push_back(new Card("HauntedHero.png"));
	deck.push_back(new Card("HauntedHero.png"));
	deck.push_back(new Card("HauntedHero.png"));
	deck.push_back(new Card("HauntedHero.png"));
	deck.push_back(new Card("ThrallOfMagma.png"));
	deck.push_back(new Card("ThrallOfMagma.png"));
	deck.push_back(new Card("ThrallOfMagma.png"));
	deck.push_back(new Card("ThrallOfMagma.png"));
	deck.push_back(new Card("Indicted.png"));
	deck.push_back(new Card("Indicted.png"));
	deck.push_back(new Card("Indicted.png"));
	deck.push_back(new Card("Indicted.png"));
	deck.push_back(new Card("Invidia.png"));
	deck.push_back(new Card("Invidia.png"));
	deck.push_back(new Card("Invidia.png"));
	deck.push_back(new Card("Invidia.png"));
	deck.push_back(new Card("VampiricBeast.png"));
	deck.push_back(new Card("VampiricBeast.png"));
	deck.push_back(new Card("Xenomorph.png"));
	deck.push_back(new Card("Xenomorph.png"));
	deck.push_back(new Card("Xenomorph.png"));
	deck.push_back(new Card("Xenomorph.png"));
	deck.push_back(new Card("VoidWarrior.png"));
	deck.push_back(new Card("VoidWarrior.png"));
	//deck.push_back(new Card("HauntedHero"));
	//deck.push_back(new Card("HauntedHero"));

	std::random_shuffle(deck.begin(), deck.end());

    for (int i = 0; i < 4; i++)
	{
		hand.push_back(deck[0]);
		deck.erase(deck.begin());
		CCLOG("deck size %d", deck.size());
		CCLOG("hand size %d", hand.size());
	}

}

Player::~Player()
{
	hand.clear();
	deck.clear();
	life = 0;
//	delete this;
}

bool Player::init()
{
	return true;
}

void Player::drawCard()
{
	if(hand.size() < (unsigned) maxHandSize)
	{
		//for (int a = hand.size(); a < (unsigned)maxHandSize; a++)
		//{
			if (deck.size() > 0)
			{
				hand.push_back(deck[0]);
				deck.erase(deck.begin());
			}
			else
			{
				auto GameOverScene = GameOverScreen::createScene();
				Director::getInstance()->pushScene(GameOverScene);
			}
		//}	
	}
}

void Player::playCard(int i)
{
	hand.clear();
}

void Player::declareAttack()
{

}

void Player::endTurn()
{

}

void Player::setLife(int d)
{
	life -= d;
}

int Player::getLife()
{
	return life;
}

int Player::getHandSize()
{
	return hand.size();
}

int Player::getDeckSize() 
{
	return deck.size();
}

Card* Player::getCardInHand(int i)
{
	return hand[i];
}

void Player::reset()
{
	hand.clear();
	deck.clear();
	life = 100;
	resource = 0;
	for (int i = 0; i < 4; i++)
	{
		hand.push_back(new Card("SampleCard.png"));
	}
	for (int i = 0; i < 40; i++)
	{
		deck.push_back(new Card("SampleCard2.png"));
	}
}

void Player::setResource(int d)
{
	resource += d;
}

int Player::getResource()
{
	return resource;
}

void Player::removeFromHand(int x) 
{
	if (x == 2000) 
	{
		hand.erase(hand.begin());
	}
	else if (x == 2001) 
	{
		hand.erase(hand.begin() + 1);
	}
	else if (x == 2002) 
	{
		hand.erase(hand.begin() + 2);
	}
	else if (x == 2003) 
	{
		hand.erase(hand.begin() + 3);
	}
	else if (x == 2004) 
	{
		hand.erase(hand.begin() + 4);
	}
	else if (x == 2005) 
	{
		hand.erase(hand.begin() + 5);
	}
	else if (x == 20000)
	{
		hand.erase(hand.begin());
	}
	else if (x == 20001)
	{
		hand.erase(hand.begin() + 1);
	}
	else if (x == 20002)
	{
		hand.erase(hand.begin() + 2);
	}
	else if (x == 20003)
	{
		hand.erase(hand.begin() + 3);
	}
	else if (x == 20004)
	{
		hand.erase(hand.begin() + 4);
	}
	else if (x == 20005)
	{
		hand.erase(hand.begin() + 5);
	}
}

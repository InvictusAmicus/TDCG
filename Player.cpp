#include "Player.h"


Player::Player()
{
	life = 100;
	for (int i = 0; i < 4; i++)
	{
		hand.push_back(new Card("SampleCard.png"));
	}
	for (int i = 0; i < 40; i++)
	{
		deck.push_back(new Card("SampleCard2.png"));
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
	/*	for (int i = 0; i < 6; i++)
		{
			if (i < hand.size())
			{
			}
			else
			{
				return new Card();
			}
		}*/
		Card* c = deck[deck.size()-1];
		hand.push_back(c);
		
	}
//	return new Card();
	deck.pop_back();
	
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

Card* Player::getCardInHand(int i)
{
	return hand[i];
}

void Player::reset()
{
	hand.clear();
	deck.clear();
	life = 100;
	for (int i = 0; i < 4; i++)
	{
		hand.push_back(new Card("SampleCard.png"));
	}
	for (int i = 0; i < 40; i++)
	{
		deck.push_back(new Card("SampleCard2.png"));
	}
}
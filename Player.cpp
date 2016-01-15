#include <vector>
#include "Card.h"
#include "Player.h"


Player::Player()
{
	life = 100;
	for (int i = 0; i < 4; i++)
	{
		hand.push_back(new Card("SampleCard.png"));
	}
}

Player::~Player()
{
	hand.clear();
	life = 0;
	delete this;
}

bool Player::init()
{
	return true;
}

Card* Player::drawCard()
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
		return new Card();
	}
}

void Player::playCard(Card* c)
{
	
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
#include "Card.h"
#include "Player.h"

Player::Player()
{
	life = 100;
	for (int i = 0; i < 4; i++)
	{
		hand[i] = new Card();
	}
}

Player::~Player()
{
	delete hand;
	life = 0;
	delete this;
}

bool Player::init()
{
	return true;
}

Card* Player::drawCard()
{
	if (hand[5] == NULL)
	{
		for (int i = 0; i < 6; i++)
		{
			if (hand[i] != NULL)
			{
			}
			else
			{
				return new Card();
			}
		}
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
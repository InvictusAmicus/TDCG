#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "Card.h"

USING_NS_CC;

class Player // : public User
{
private:
	std::vector<Card*> hand;
	std::vector<Card*> deck;
	const int maxHandSize = 6;
	int life;
	int resource;

public:
	Player();
	~Player();
	virtual bool init();
	
	//card dependant methods
	void drawCard();
	void playCard(int i);
	void removeFromHand(int x);
	
	//end of turn choice methods
	void declareAttack();
	void endTurn();

	void reset();

	//other methods if needed
	void setLife(int);
	int getLife();
	void setResource(int);
	int getResource();

	int getHandSize();
	int getDeckSize();
	Card* getCardInHand(int);
};

#endif //__Player_H__
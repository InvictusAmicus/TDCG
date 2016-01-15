#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "Card.h"

class Player // : public User
{
private:
	std::vector<Card*> hand;
	const int maxHandSize = 6;
	int life;

public:
	Player();
	~Player();
	virtual bool init();
	
	//card dependant methods
	void drawCard(/*Deck*?*/);
	void playCard(int i);
	
	//end of turn choice methods
	void declareAttack();
	void endTurn();

	//other methods if needed
	void setLife(int d);
	int getLife();
	int getHandSize();
	Card* getCardInHand(int);
};

#endif //__Player_H__
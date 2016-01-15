#ifndef __PLAYER_H__
#define __PLAYER_H__

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
	Card* drawCard(/*Deck*?*/);
	void playCard(Card* c);
	
	//end of turn choice methods
	void declareAttack();
	void endTurn();

	//other methods if needed
	void setLife(int d);
	int getLife();
	int getHandSize();
};

#endif //__Player_H__
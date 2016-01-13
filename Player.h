#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player // : public User
{
private:

public:
	Player();
	~Player();
	virtual bool init();
	
	//card dependant methods
	void drawCard(/*Deck*?*/);
	void playCard(Card* c);

	//end of turn choice methods
	void declareAttack();
	void endTurn();

	//other methods if needed

};

#endif //__Player_H__
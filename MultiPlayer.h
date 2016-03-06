#ifndef __MULTIPLAYER_H__
#define __MULTIPLAYER_H__

#include "cocos2d.h"
#include "Player.h"

class MultiPlayer : public cocos2d::Layer
{
private:
	Player* player1;
	Player* player2;
//	Player* p;
	bool isPlayer1;
	MenuItemImage* EndTurn;
public:
	/*!
	*Creates the scene for the Single player game
	*/
	static cocos2d::Scene* createScene();

	/*!
	*Called to initialize the scene
	*/
	virtual bool init();

	/*!
	*Checks to see if players can move or attack, Checks to see if towers can attack
	*/
	void EndRoundTurn(cocos2d::Ref* pSender);

	/*!
	*Adds resources to the player and the enemy and changes to label for the player resources, calls the display hand method
	*/
	void startTurn();
	
	/*!
	*Checks to see if the Player or enemy life is less than zero. Calls the WonGame or LostGame method
	*if the conditions are meet
	*/
	void GameState();

	/*!
	*Brings the user to the GameOverScreen
	*/
	void LostGame();

	/*!
	*Brings the user to the GameWonScreen
	*/
	void WonGame();

	/*!
	*Displays the cards the player currently has, has a listener for when the player touches a card
	*/
	void displayHand(Player*);

	void SpriteRemove(float ct);

	void MenuDisable(float ct);
	
	int TowerGridLoop;

	// implement the "static create()" method manually
	
	// a selector callback
	void returnToTitle(cocos2d::Ref* pSender);
	void LastPage(cocos2d::Ref* pSender);
	
	CREATE_FUNC(MultiPlayer);
};

#endif // __MULTIPLAYER_H__

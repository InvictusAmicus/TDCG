#ifndef __SINGLEPLAYGAME_H__
#define __SINGLEPLAYGAME_H__

#include "cocos2d.h"
#include "Player.h"

class NewSinglePlayGame : public cocos2d::Layer
{
private:
	Player* p;
	MenuItemImage *EndTurn;

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
	*Calls the EnemyAI class and places a sprite or tower on the map
	*/
	void enemyAI();

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


	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	

	int getScore();
	int TowerGridLoop;
	
	// implement the "static create()" method manually
	CREATE_FUNC(NewSinglePlayGame);
};

#endif // __SINGLEPLAYGAME_H__
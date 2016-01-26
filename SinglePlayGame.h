#ifndef __SINGLEPLAYGAME_H__
#define __SINGLEPLAYGAME_H_

#include "cocos2d.h"
#include "Player.h"

class SinglePlayGame : public cocos2d::Layer
{
private:

public:
	static cocos2d::Scene* createScene();
	
	virtual bool init();

	// a selector callback
	void returnToTitle(cocos2d::Ref* pSender);
	void LastPage(cocos2d::Ref* pSender);
	void EndRoundTurn(cocos2d::Ref* pSender);
	void LostGame();
	void WonGame();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	int TowerGridLoop;
	void enemyAI();
	void GameState();

	//cocos2d::Label *LifeLabelValue;

void displayHand(Player*/*, int i*/);

	// implement the "static create()" method manually
	CREATE_FUNC(SinglePlayGame);
};

#endif // __SINGLEPLAYGAME_H__
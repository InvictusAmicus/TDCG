#ifndef __MULTIPLAYER_H__
#define __MULTIPLAYER_H_

#include "cocos2d.h"

class MultiPlayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	//void menuCloseCallback(cocos2d::Ref* pSender);
	//void menuNewGame(cocos2d::Ref* pSender);
	//void menuContinue(cocos2d::Ref* pSender);
	//void menuOptions(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(MultiPlayer);
};

#endif // __MULTIPLAYER_H__

#ifndef __CONTINUE_H__
#define __CONTINUE__

#include "cocos2d.h"

class Continue : public cocos2d::Layer
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
	CREATE_FUNC(Continue);
};

#endif // __CONTINUE_H__

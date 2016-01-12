#ifndef __OPTIONS_H__
#define __OPTIONS_H_

#include "cocos2d.h"

class Options : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuReturn(cocos2d::Ref* pSender);
	//void menuNewGame(cocos2d::Ref* pSender);
	//void menuContinue(cocos2d::Ref* pSender);
	//void menuOptions(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(Options);
};

#endif // __OPTIONS_H__

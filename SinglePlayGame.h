#ifndef __SINGLEPLAYGAME_H__
#define __SINGLEPLAYGAME_H_

#include "cocos2d.h"

class SinglePlayGame : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	//void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(SinglePlayGame);
};

#endif // __SINGLEPLAYGAME_H__
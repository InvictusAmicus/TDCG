#ifndef __MULTIPLAYER_H__
#define __MULTIPLAYER_H__

#include "cocos2d.h"

class MultiPlayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void returnToTitle(cocos2d::Ref* pSender);
	void LastPage(cocos2d::Ref* pSender);
	
	CREATE_FUNC(MultiPlayer);
};

#endif // __MULTIPLAYER_H__

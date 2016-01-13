#ifndef __SINGLEPLAYGAME_H__
#define __SINGLEPLAYGAME_H_

#include "cocos2d.h"

class SinglePlayGame : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void returnToTitle(cocos2d::Ref* pSender);
	void LastPage(cocos2d::Ref* pSender);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	// implement the "static create()" method manually
	CREATE_FUNC(SinglePlayGame);
};

#endif // __SINGLEPLAYGAME_H__
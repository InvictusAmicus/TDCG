#pragma once
#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include "cocos2d.h"

class Collection : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void returnToTitle(cocos2d::Ref* pSender);
	//void menuCloseCallback(cocos2d::Ref* pSender);
	//void menuNewGame(cocos2d::Ref* pSender);
	//void menuMultiPlayer(cocos2d::Ref* pSender);
	//void menuOptions(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(Collection);
};

#endif // __COLLECTION_H__

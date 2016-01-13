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
	void NextPage(cocos2d::Ref* pSender);

	CREATE_FUNC(Collection);
};

#endif // __COLLECTION_H__

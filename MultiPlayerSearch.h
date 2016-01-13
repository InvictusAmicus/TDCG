#ifndef __MULTIPLAYERSEARCH_H__
#define __MULTIPLAYERSEARCH_H_

#include "cocos2d.h"

class MultiPlayerSearch : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void returnToTitle(cocos2d::Ref* pSender);
	void Next(cocos2d::Ref* pSender);

	CREATE_FUNC(MultiPlayerSearch);
};

#endif // __MULTIPLAYERSEARCH_H__

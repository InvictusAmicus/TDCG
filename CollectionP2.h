#ifndef __COLLECTIONP2_H__
#define __COLLECTIONP2_H__

#include "cocos2d.h"

class CollectionP2 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void returnToTitle(cocos2d::Ref* pSender);
	void LastPage(cocos2d::Ref* pSender);

	CREATE_FUNC(CollectionP2);
};

#endif // __COLLECTIONP2_H__
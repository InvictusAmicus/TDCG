#ifndef __HOWTOPLAY_H__
#define __HOWTOPLAY_H_

#include "cocos2d.h"

class HowToPlay : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void returnToTitle(cocos2d::Ref* pSender);

	CREATE_FUNC(HowToPlay);
};

#endif // __HOWTOPLAY_H__
#ifndef __GAMEWONSCREEN_H__
#define __GAMEWONSCREEN_H_

#include "cocos2d.h"

class GameWonScreen : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void returnToTitleScreen(cocos2d::Ref* pSender);

	CREATE_FUNC(GameWonScreen);
};

#endif // __GAMEWONSCREEN_H__
#ifndef __GAMEOVERSCREEN_H__
#define __GAMEOVERSCREEN_H_

#include "cocos2d.h"

class GameOverScreen : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void returnToTitleScreen(cocos2d::Ref* pSender);

	CREATE_FUNC(GameOverScreen);
};

#endif // __GAMEOVERSCREEN_H__
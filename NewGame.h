#ifndef __NEWGAME_H__
#define __NEWGAME_H_

#include "cocos2d.h"

class NewGame : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	//void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(NewGame);
};

#endif // __NEWGAME_H__
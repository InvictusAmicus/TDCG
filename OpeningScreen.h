//Worked on by Ciaran Clerkin K00191500

#ifndef __OPENINGSCREEN_H__
#define __OPENINGSCREEN_H__

#include "cocos2d.h"

class OpeningScreen : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void GoToTitle();

	void PlayerAttack(cocos2d::Ref* pSender);
	

	CREATE_FUNC(OpeningScreen);
};

#endif // __OPENINGSCREEN_H__
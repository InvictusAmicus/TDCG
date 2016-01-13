
#ifndef __OPENINGSCREEN_H__
#define __OPENINGSCREEN_H_

#include "cocos2d.h"

class OpeningScreen : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();


	virtual bool init();

	// a selector callback
	void GoToTitle();
	
	CREATE_FUNC(OpeningScreen);
};

#endif // __OPENINGSCREEN_H__
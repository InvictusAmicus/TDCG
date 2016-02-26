#ifndef __GAMEWONSCREEN_H__
#define __GAMEWONSCREEN_H_

#include "cocos2d.h"

class GameWonScreen : public cocos2d::Layer
{
public:
	
	/*!
	*Creates the scene for the GameWonScreen
	*/
	static cocos2d::Scene* createScene();

	/*!
	*Called to initialize the scene
	*/
	virtual bool init();

	/*!
	*Returns the user to the Main Menu
	*/
	void returnToTitleScreen(cocos2d::Ref* pSender);

	CREATE_FUNC(GameWonScreen);
};

#endif // __GAMEWONSCREEN_H__
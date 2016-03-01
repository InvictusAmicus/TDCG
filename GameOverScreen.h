#ifndef __GAMEOVERSCREEN_H__
#define __GAMEOVERSCREEN_H__

#include "cocos2d.h"

class GameOverScreen : public cocos2d::Layer
{
public:
	
	/*!
	*Creates the scene for the GameOverScreen
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

	CREATE_FUNC(GameOverScreen);
};

#endif // __GAMEOVERSCREEN_H__
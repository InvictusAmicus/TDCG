//Worked on by Ciaran Clerkin K00191500

#ifndef __MGAMEOVERSCREEN_H__
#define __MGAMEOVERSCREEN_H__

#include "cocos2d.h"

class MGameOverScreen : public cocos2d::Layer
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

	CREATE_FUNC(MGameOverScreen);
};

#endif // __MGAMEOVERSCREEN_H__
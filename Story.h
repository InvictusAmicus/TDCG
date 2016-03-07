#ifndef __STORY_H__
#define __STORY_H__

#include "cocos2d.h"

class Story : public cocos2d::Layer
{
private:

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

	void toGame(Ref*);

	CREATE_FUNC(Story);
};

#endif // __STORY_H__

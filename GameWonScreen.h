//Worked on by Ciaran Clerkin K00191500 and Declan Cordial K00184439

#ifndef __GAMEWONSCREEN_H__
#define __GAMEWONSCREEN_H__

#include "cocos2d.h"

class GameWonScreen : public cocos2d::Layer
{
private:
	std::string StringLength;

public:
	/*!
	*Creates the scene for the GameWonScreen
	*/
	static cocos2d::Scene* createScene();

	static cocos2d::Scene* createScene(int);

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
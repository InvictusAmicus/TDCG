//Worked on by Ciaran Clerkin K00191500

#ifndef __HOWTOPLAY_H__
#define __HOWTOPLAY_H__

#include "cocos2d.h"

class HowToPlay : public cocos2d::Layer
{
public:

	/*!
	*Creates the scene for the How to Play
	*/
	static cocos2d::Scene* createScene();

	/*!
	*Called to initialize the scene
	*/
	virtual bool init();

	/*!
	*Returns the user to the Main Menu
	*/
	void returnToTitle(cocos2d::Ref* pSender);

	CREATE_FUNC(HowToPlay);
};

#endif // __HOWTOPLAY_H__
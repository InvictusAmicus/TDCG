//Worked on by Ciaran Clerkin K00191500 and Declan Cordial K00184439

#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
	
	/*!
	*Creates the scene for the Main Menu
	*/
	static cocos2d::Scene* createScene();

	/*!
	*Called to initialize the scene
	*/
    virtual bool init();
    
	/*!
	*Quits the game
	*/
    void menuCloseCallback(cocos2d::Ref* pSender);

	/*!
	*Go to the Single player screen when called
	*/
	void menuNewGame(cocos2d::Ref* pSender);

	/*!
	*Go to the MultiPlayer screen when called
	*/
	void menuMultiPlayer(cocos2d::Ref* pSender);

	/*!
	*Got to the LeaderboardScreen when called
	*/
	void MainMenu::menuLeaderboard(Ref* pSender);

	/*!
	*Go to the Collection screen when called
	*/
	void menuCollection(cocos2d::Ref* pSender);

	/*!
	*Go to the Options screen when called
	*/
	void menuOptions(cocos2d::Ref* pSender);

	/*!
	*Go to the How to Play screen when called
	*/
	void menuHowToPlay(cocos2d::Ref* pSender);

	/*!
	*Retrieves the values from the system file and sets the values in Options
	*/
	void SystemFile();

	/*!
	*Sets the volume of the background music
	*/
	void PlayMusic();
    
    CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_H__

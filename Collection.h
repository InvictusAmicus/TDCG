#pragma once
#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include "cocos2d.h"
#include "Card.h"
#include <vector>

class Collection : public cocos2d::Layer
{
private:
	std::vector<Card*> listOfCards;
    int DisplayNumber;
	int PgNum;
	int EventNum;
public:

	/*!
	*Creates the scene for the Collection menu
	*/
	static cocos2d::Scene* createScene();
	
	/*!
	*Sets the max amount of cards on each row
	*/
	const int maxCardsPerLine = 4;

	/*!
	*Called to initialize the scene. Pushes the cards that will be displayed on screen into a vector
	*/
	virtual bool init();

	/*!
	*Displays the cards on the screen. Has a listener for when cards are touched that gets the cards lore
	*/
	void displayCards(int x);

	/*!
	*Displays the lore on the screen using a label
	*/
	void displayLore(Card*);

	/*!
	*Returns the user to the Main Menu
	*/
	void returnToTitle(cocos2d::Ref* pSender);

	CREATE_FUNC(Collection);
};

#endif // __COLLECTION_H__

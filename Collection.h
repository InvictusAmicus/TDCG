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

public:
	static cocos2d::Scene* createScene();
	const int maxCardsPerLine = 4;

	virtual bool init();

	void displayCards();
	void displayLore(Card*);

	// a selector callback
	void returnToTitle(cocos2d::Ref* pSender);
	void NextPage(cocos2d::Ref* pSender);
	
	CREATE_FUNC(Collection);
};

#endif // __COLLECTION_H__

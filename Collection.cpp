#include "Collection.h"
#include "CollectionP2.h"
#include "MainMenu.h"

USING_NS_CC;

#define LabelTagLore 1236
#define DisplaySprite0 3000
#define DisplaySprite1 3001
#define DisplaySprite2 3002
#define DisplaySprite3 3003
#define DisplaySprite4 3004
#define DisplaySprite5 3005
#define DisplaySprite6 3006
#define DisplaySprite7 3007

Scene* Collection::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Collection::create();

	// add layer as a child to scene
	scene->addChild(layer);
	
	// return the scene
	return scene;
}


bool Collection::init()
{
	
	if (!Layer::init())
	{
		return false;
	}

	auto loreLabel = Label::createWithTTF("Click a card to see its lore.", "fonts/Marker Felt.ttf", 24);

	loreLabel->setPosition(400, 150);
	loreLabel->setColor(ccc3(0, 0, 0));
	this->addChild(loreLabel, true, LabelTagLore);
    
	listOfCards.push_back(new Card("SampleCard.png"));
    listOfCards.push_back(new Card("SampleCard2.png"));
	listOfCards.push_back(new Card("Archfiend.png"));
	listOfCards.push_back(new Card("A.I.P.png"));
	listOfCards.push_back(new Card("Aviater.png"));
	listOfCards.push_back(new Card("Cain.png"));
	listOfCards.push_back(new Card("Indicted.png"));
	listOfCards.push_back(new Card("MoltonCore.png"));
	//listOfCards.push_back(new Card("IceDemon.png"));
	//listOfCards.push_back(new Card("Tariq.png"));
	//listOfCards.push_back(new Card("Wisp.png"));

	//Testing to see the erasing and the insert at for the vector
	//listOfCards.erase(listOfCards.begin()+2);
	//listOfCards.insert(listOfCards.begin() + 2, new Card("closeNormal.png"));
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto Back = MenuItemImage::create("Back.png", "BackClicked.png", CC_CALLBACK_1(Collection::returnToTitle, this));
	Back->setPosition(Vec2(origin.x + visibleSize.width - Back->getContentSize().width, 70));
		//origin.y + visibleSize.height - Back->getContentSize().height * 8));
	auto menu = Menu::create(Back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

/*	//change lore label to the clicked card's lore
	auto LoreLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
	//label->setString(c->getLore());
	LoreLabel->setPosition(300, 150);
	LoreLabel->setColor(ccc3(0, 0, 0));
	this->addChild(LoreLabel, 1, LabelTagLore);
*/

	//auto SecondPage = MenuItemImage::create("ArrowSelection.png", "ArrowSelection.png", CC_CALLBACK_1(Collection::NextPage, this));
	//SecondPage->setPosition(Vec2(origin.x + visibleSize.width - SecondPage->getContentSize().width, 360));
	//origin.y + visibleSize.height - Back->getContentSize().height * 8));
	//auto NP = Menu::create(SecondPage, NULL);
	//NP->setPosition(Vec2::ZERO);
	//this->addChild(NP, 1);


	auto label = Label::createWithTTF("CardDatabase", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	auto sprite = Sprite::create("Background.png");

	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(sprite, 0);

	displayCards();
	
	return true;

}

void Collection::displayCards()
{
	/*auto sprite = cocos2d::Sprite::create("HelloWorld.png");
	int i;
	for (i = 0; (unsigned)i < listOfCards.size() && i < maxCardsPerLine; i++)
	{
		sprite = listOfCards[i]->getSprite();
		sprite->setPosition(Vec2(200 + (i * 100), 250));
		this->addChild(sprite, 1);
	}
	for (i = 0; (unsigned)i+4 < listOfCards.size() && i < maxCardsPerLine; i++)
	{
		sprite = listOfCards[i+4]->getSprite();
		sprite->setPosition(Vec2(200 + (i * 100), 500));
		this->addChild(sprite, 1);
	}*/
	// turn auto sprite into auto MenuItemImage
	int i;
	auto image = MenuItemImage::create();
	auto imageMenu = Menu::create();
	/*
	for (i = 0; (unsigned)i < listOfCards.size() && i < maxCardsPerLine;i++)
	{
		image = MenuItemImage::create(listOfCards[i]->getSpriteName(), listOfCards[i]->getSpriteName(),
			CC_CALLBACK_0(Collection::displayLore, this, listOfCards[i]));
		
		image->setPosition(Vec2(200+(i*100), 550));
		imageMenu = Menu::create(image, NULL);
		imageMenu->setPosition(Vec2::ZERO);
		this->addChild(imageMenu, 1);
	}
	
	for (i = 0; (unsigned)i+4 < listOfCards.size() && i < maxCardsPerLine; i++)
	{
		image = MenuItemImage::create(listOfCards[i+4]->getSpriteName(), listOfCards[i+4]->getSpriteName(),
			CC_CALLBACK_0(Collection::displayLore, this, listOfCards[i+4]));

		image->setPosition(Vec2(200 + (i * 100), 350));
		imageMenu = Menu::create(image, NULL);
		imageMenu->setPosition(Vec2::ZERO);
		this->addChild(imageMenu, 1);
	}
	*/

	///////////////////////////////////////////
	///////////////////////////////////////////
	for (i = 0; (unsigned)i < listOfCards.size() && i<maxCardsPerLine; i++)
	{
		auto sprite = cocos2d::Sprite::create(listOfCards[i]->getSpriteName());
		this->addChild(sprite, 1, DisplaySprite0 + i);
		this->getChildByTag(DisplaySprite0 + i)->setPosition(Vec2(200 + (i * 100), 550));
		CCLOG("TAG %d", (DisplaySprite0 + i));
	}

	for (i = 0; (unsigned)i + 4 < listOfCards.size() && i<maxCardsPerLine; i++)
	{
		auto sprite = cocos2d::Sprite::create(listOfCards[i + 4]->getSpriteName());
		this->addChild(sprite, 1, DisplaySprite0 + i + 4);
		this->getChildByTag(DisplaySprite0 + i + 4)->setPosition(Vec2(200 + (i * 100), 350));
		CCLOG("TAG %d", (DisplaySprite0 + i + 4));
	}
	
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	CCLOG("Test Touch before Began");
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		CCLOG("Test Touch Began");

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			target->setOpacity(180);
			CCLOG("Test Touch Began if");
			return true;
		}
		return false;
	};
	

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setOpacity(255);
		int tag = target->getTag();
		if (tag == 3000)
		{
			displayLore(listOfCards[0]);
		}
		else if (tag == 3001)
		{
			displayLore(listOfCards[1]);
		}
		else if (tag == 3002)
		{
			displayLore(listOfCards[2]);
		}
		else if (tag == 3003)
		{
			displayLore(listOfCards[3]);
		}
		else if (tag == 3004)
		{
			displayLore(listOfCards[4]);
		}
		else if (tag == 3005)
		{
			displayLore(listOfCards[5]);
		}
		else if (tag == 3006)
		{
			displayLore(listOfCards[6]);
		}
		else if (tag == 3007)
		{
			displayLore(listOfCards[7]);
		}

		
	};
	if (listOfCards.size() > 0)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this->getChildByTag(DisplaySprite0));
	}
	for (int j = 0; j < listOfCards.size(); j++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), this->getChildByTag(DisplaySprite0 + j));
	}



}

void Collection::displayLore(Card* c)
{

	//change lore label to the clicked card's lore
	//auto label = Label::createWithTTF(c->getLore(), "fonts/Marker Felt.ttf", 24);
	//label->setString(c->getLore());
	//label->setPosition(300, 150);
	//label->setColor(ccc3(0, 0, 0));
	//this->addChild(label,1);
	CCLabelBMFont* ChangeLore = (CCLabelBMFont*)getChildByTag(LabelTagLore);
	
	ChangeLore->setString(c->getLore());


//	loreLabel->setString(c->getLore());

}

void Collection::returnToTitle(cocos2d::Ref* pSender)
{
	Director::getInstance()->popToRootScene();
}

/*
void Collection::NextPage(cocos2d::Ref* pSender)
{
	auto CollectionP2Scene = CollectionP2::createScene();
	Director::getInstance()->pushScene(CollectionP2Scene);
}
*/
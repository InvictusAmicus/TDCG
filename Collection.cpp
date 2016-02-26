#include "Collection.h"
#include "CollectionP2.h"
#include "MainMenu.h"

USING_NS_CC;

#define LabelTagLore 1236
#define ChangeSprites 2998
#define ChangeSpritesBack 2999
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

	DisplayNumber = 0;
	PgNum = 0;
	auto loreLabel = Label::createWithTTF("Click a card to see its lore.", "fonts/Marker Felt.ttf", 24);

	loreLabel->setPosition(400, 150);
	loreLabel->setColor(ccc3(0, 0, 0));
	this->addChild(loreLabel, true, LabelTagLore);
    
	//Cards Pg 1, Card 1-8
	listOfCards.push_back(new Card("SampleCard.png"));
    listOfCards.push_back(new Card("SampleCard2.png"));
	listOfCards.push_back(new Card("Archfiend.png"));
	listOfCards.push_back(new Card("A.I.P.png"));
	listOfCards.push_back(new Card("Aviater.png"));
	listOfCards.push_back(new Card("Cain.png"));
	listOfCards.push_back(new Card("Indicted.png"));
	listOfCards.push_back(new Card("MoltonCore.png"));

	//Cards Pg 2, Card 9-16
	listOfCards.push_back(new Card("IceDemon.png"));
	listOfCards.push_back(new Card("Tariq.png"));
	listOfCards.push_back(new Card("Wisp.png"));
	listOfCards.push_back(new Card("SampleCard.png"));
	listOfCards.push_back(new Card("SampleCard2.png"));
	listOfCards.push_back(new Card("Archfiend.png"));
	listOfCards.push_back(new Card("A.I.P.png"));
	listOfCards.push_back(new Card("Aviater.png"));

	//Cards Pg 3, Card 17-24
	listOfCards.push_back(new Card("SampleCard.png"));
	listOfCards.push_back(new Card("SampleCard2.png"));
	listOfCards.push_back(new Card("Archfiend.png"));
	listOfCards.push_back(new Card("A.I.P.png"));
	listOfCards.push_back(new Card("IceDemon.png"));
	listOfCards.push_back(new Card("Tariq.png"));
	listOfCards.push_back(new Card("Wisp.png"));
	listOfCards.push_back(new Card("SampleCard.png"));
	
	//Cards Pg 4, Card 25-32
	listOfCards.push_back(new Card("SampleCard2.png"));
	listOfCards.push_back(new Card("Archfiend.png"));
	listOfCards.push_back(new Card("A.I.P.png"));
	listOfCards.push_back(new Card("Aviater.png"));
	listOfCards.push_back(new Card("Aviater.png"));
	listOfCards.push_back(new Card("Cain.png"));
	listOfCards.push_back(new Card("Indicted.png"));
	listOfCards.push_back(new Card("MoltonCore.png"));
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto Back = MenuItemImage::create("Back.png", "BackClicked.png", CC_CALLBACK_1(Collection::returnToTitle, this));
	Back->setPosition(Vec2(origin.x + visibleSize.width - Back->getContentSize().width, 70));
	auto menu = Menu::create(Back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto label = Label::createWithTTF("CardDatabase", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	auto NextSprites = cocos2d::Sprite::create("ArrowSelection.png");
	this->addChild(NextSprites, 1, ChangeSprites);
	this->getChildByTag(ChangeSprites)->setPosition(Vec2(origin.x + visibleSize.width - NextSprites->getContentSize().width, 360));

	auto PrevSprites = cocos2d::Sprite::create("ArrowSelection2.png");
	this->addChild(PrevSprites, 1, ChangeSpritesBack);
	this->getChildByTag(ChangeSpritesBack)->setPosition(Vec2(origin.x + visibleSize.width - (NextSprites->getContentSize().width * 2), 360));

	auto sprite = Sprite::create("Background.png");

	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(sprite, 0);
	
	displayCards(PgNum);
	
	return true;

}

void Collection::displayCards(int x)
{

	for (int i = 0; i < 8; i++)
	{
		CCLOG("Card No: %d", i);
		if (getChildByTag(DisplaySprite0 + i) != NULL)
		{
			auto fadeOut = FadeOut::create(1.0f);
			this->getChildByTag(DisplaySprite0 + i)->runAction(fadeOut);
			getChildByTag(DisplaySprite0 + i)->removeFromParentAndCleanup(true);
		}
	}

	if (x == 0) 
	{
	    int i;
		DisplayNumber = 0;
		EventNum = 0;
	    for (i = 0; (unsigned)i < listOfCards.size() && i < maxCardsPerLine; i++)
	    {
		    auto sprite = cocos2d::Sprite::create(listOfCards[i]->getSpriteName());
			sprite->setOpacity(0);
			sprite->setCascadeOpacityEnabled(true);
			auto fadeIn = FadeIn::create(1.0f);
			sprite->runAction(fadeIn);
			this->addChild(sprite, 1, DisplaySprite0 + i);
            this->getChildByTag(DisplaySprite0 + i)->setPosition(Vec2(200 + (i * 100), 550));
		    CCLOG("TAG %d", (DisplaySprite0 + i));
			EventNum++;
	    }

	    for (i = 0; (unsigned)i + 4 < listOfCards.size() && i < maxCardsPerLine; i++)
	    {
		    auto sprite = cocos2d::Sprite::create(listOfCards[i + 4]->getSpriteName());
			sprite->setOpacity(0);
			sprite->setCascadeOpacityEnabled(true);
			auto fadeIn = FadeIn::create(1.0f);
			sprite->runAction(fadeIn);
		    this->addChild(sprite, 1, DisplaySprite0 + i + 4);
		    this->getChildByTag(DisplaySprite0 + i + 4)->setPosition(Vec2(200 + (i * 100), 350));
		    CCLOG("TAG %d", (DisplaySprite0 + i + 4));
			EventNum++;
	    }
	}

	else if (x == 1)
	{
		int j;
		DisplayNumber = 8;
		EventNum = 0;
		CCLOG("Card size %d", listOfCards.size());
		for (j = 0; (unsigned)j + 8 < listOfCards.size() && j < maxCardsPerLine; j++)
		{
			auto sprite = cocos2d::Sprite::create(listOfCards[j + 8]->getSpriteName());
			sprite->setOpacity(0);
			sprite->setCascadeOpacityEnabled(true);
			auto fadeIn = FadeIn::create(1.0f);
			sprite->runAction(fadeIn);
			this->addChild(sprite, 1, DisplaySprite0 + j);
			this->getChildByTag(DisplaySprite0 + j)->setPosition(Vec2(200 + (j * 100), 550));
			CCLOG("TAG %d", (DisplaySprite0 + j));
			EventNum++;
		}
		for (j = 0; (unsigned)j + 12 < listOfCards.size() && j < maxCardsPerLine; j++)
		{
			auto sprite = cocos2d::Sprite::create(listOfCards[j + 12]->getSpriteName());
			sprite->setOpacity(0);
			sprite->setCascadeOpacityEnabled(true);
			auto fadeIn = FadeIn::create(1.0f);
			sprite->runAction(fadeIn);
			this->addChild(sprite, 1, DisplaySprite0 + j + 4);
			this->getChildByTag(DisplaySprite0 + j + 4)->setPosition(Vec2(200 + (j * 100), 350));
			CCLOG("TAG %d", (DisplaySprite0 + j + 4));
			EventNum++;
		}
	}

	else if (x == 2)
	{
		int j;
		DisplayNumber = 16;
		EventNum = 0;
		CCLOG("Card size %d", listOfCards.size());
		for (j = 0; (unsigned)j + 16 < listOfCards.size() && j < maxCardsPerLine; j++)
		{
			auto sprite = cocos2d::Sprite::create(listOfCards[j + 16]->getSpriteName());
			sprite->setOpacity(0);
			sprite->setCascadeOpacityEnabled(true);
			auto fadeIn = FadeIn::create(1.0f);
			sprite->runAction(fadeIn);
			this->addChild(sprite, 1, DisplaySprite0 + j);
			this->getChildByTag(DisplaySprite0 + j)->setPosition(Vec2(200 + (j * 100), 550));
			CCLOG("TAG %d", (DisplaySprite0 + j));
			EventNum++;
		}
		for (j = 0; (unsigned)j + 20 < listOfCards.size() && j < maxCardsPerLine; j++)
		{
			auto sprite = cocos2d::Sprite::create(listOfCards[j + 20]->getSpriteName());
			sprite->setOpacity(0);
			sprite->setCascadeOpacityEnabled(true);
			auto fadeIn = FadeIn::create(1.0f);
			sprite->runAction(fadeIn);
			this->addChild(sprite, 1, DisplaySprite0 + j + 4);
			this->getChildByTag(DisplaySprite0 + j + 4)->setPosition(Vec2(200 + (j * 100), 350));
			CCLOG("TAG %d", (DisplaySprite0 + j + 4));
			EventNum++;
		}
	}

	else if (x == 3)
	{
		int j;
		DisplayNumber = 24;
		EventNum = 0;
		CCLOG("Card size %d", listOfCards.size());
		for (j = 0; (unsigned)j + 24 < listOfCards.size() && j < maxCardsPerLine; j++)
		{
			auto sprite = cocos2d::Sprite::create(listOfCards[j + 24]->getSpriteName());
			sprite->setOpacity(0);
			sprite->setCascadeOpacityEnabled(true);
			auto fadeIn = FadeIn::create(1.0f);
			sprite->runAction(fadeIn);
			this->addChild(sprite, 1, DisplaySprite0 + j);
			this->getChildByTag(DisplaySprite0 + j)->setPosition(Vec2(200 + (j * 100), 550));
			CCLOG("TAG %d", (DisplaySprite0 + j));
			EventNum++;
		}
		for (j = 0; (unsigned)j + 28 < listOfCards.size() && j < maxCardsPerLine; j++)
		{
			auto sprite = cocos2d::Sprite::create(listOfCards[j + 28]->getSpriteName());
			sprite->setOpacity(0);
			sprite->setCascadeOpacityEnabled(true);
			auto fadeIn = FadeIn::create(1.0f);
			sprite->runAction(fadeIn);
			this->addChild(sprite, 1, DisplaySprite0 + j + 4);
			this->getChildByTag(DisplaySprite0 + j + 4)->setPosition(Vec2(200 + (j * 100), 350));
			CCLOG("TAG %d", (DisplaySprite0 + j + 4));
			EventNum++;
		}
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
		if (tag == 2998)
		{
			if (PgNum != 3) 
			{
				PgNum++;
				CCLabelBMFont* ChangeLore = (CCLabelBMFont*)getChildByTag(LabelTagLore);
				ChangeLore->setString("Click a card to see its lore.");
				displayCards(PgNum);
			}
			else 
			{
				CCLabelBMFont* ChangeLore = (CCLabelBMFont*)getChildByTag(LabelTagLore);
				ChangeLore->setString("Click a card to see its lore.");
			}
		}
		
		else if (tag == 2999)
		{
			if (PgNum != 0) 
			{
				PgNum--;
				CCLabelBMFont* ChangeLore = (CCLabelBMFont*)getChildByTag(LabelTagLore);
				ChangeLore->setString("Click a card to see its lore.");
				displayCards(PgNum);
			}
			else 
			{
				CCLabelBMFont* ChangeLore = (CCLabelBMFont*)getChildByTag(LabelTagLore);
				ChangeLore->setString("Click a card to see its lore.");
			}
		}

		else if (tag == 3000)
		{
			displayLore(listOfCards[0+ DisplayNumber]);
		}
		else if (tag == 3001)
		{
			displayLore(listOfCards[1 + DisplayNumber]);
		}
		else if (tag == 3002)
		{
			displayLore(listOfCards[2 + DisplayNumber]);
		}
		else if (tag == 3003)
		{
			displayLore(listOfCards[3 + DisplayNumber]);
		}
		else if (tag == 3004)
		{
			displayLore(listOfCards[4 + DisplayNumber]);
		}
		else if (tag == 3005)
		{
			displayLore(listOfCards[5 + DisplayNumber]);
		}
		else if (tag == 3006)
		{
			displayLore(listOfCards[6 + DisplayNumber]);
		}
		else if (tag == 3007)
		{
			displayLore(listOfCards[7 + DisplayNumber]);
		}
		
	};
	
	if (listOfCards.size() > 0)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this->getChildByTag(DisplaySprite0));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), this->getChildByTag(ChangeSprites));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), this->getChildByTag(ChangeSpritesBack));
	}
	for (int j = 0; j < EventNum; j++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), this->getChildByTag(DisplaySprite0 + j));
	}
}

void Collection::displayLore(Card* c)
{
	CCLabelBMFont* ChangeLore = (CCLabelBMFont*)getChildByTag(LabelTagLore);
	ChangeLore->setString(c->getLore());
}

void Collection::returnToTitle(cocos2d::Ref* pSender)
{
	Director::getInstance()->popToRootScene();
}
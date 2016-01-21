#include "SinglePlayGame.h"
#include "GameOverScreen.h"
#include "GameWonScreen.h"
#include "SimpleAudioEngine.h"
#include "Card.h"
#include "Player.h"
#include "CollisionDetection.h"


USING_NS_CC;

int life;
int resource;
//int TowerAreaArray[3][3];
#define LabelTagLife 1234
#define LabelTagResource 1235
#define CardsInHand 1237

#define handSprite1 2000
#define handSprite2 2001
#define handSprite3 2002
#define handSprite4 2003
#define handSprite5 2004
#define handSprite6 2005


#define T 1238
#define C 1239

#define T 1238
#define C 1239

enum 
{
	MoveSprite = 1,
};

Scene* SinglePlayGame::createScene()
{
	// 'scene' is an autorelease object
	auto NewGameScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SinglePlayGame::create();

	// add layer as a child to scene
	NewGameScene->addChild(layer);
	
	// return the scene
	return NewGameScene;
}

bool SinglePlayGame::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//for (int g = 0;g < 4;g++) {
	//	for (int h = 0;h < 4;h++) {
	//		TowerAreaArray[g][h] = 0;
	//	}
	//}

	life = 100;
	resource = 100;

	/*
		when moving to the GameOver screen, pass life in.
		if(life > 0)
		{
			print you win
		}
		else
		{
			print you lose
		}
	*/
	


	std::string StringLife = std::to_string(life);
	std::string StringResource = std::to_string(resource);

	auto label = Label::createWithTTF("Single Player Game", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);
	
	auto LifeLabel = Label::createWithTTF("Health", "fonts/Marker Felt.ttf", 24);
	LifeLabel->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width +10,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(LifeLabel, 1);

	auto LifeLabelValue = Label::createWithTTF(StringLife, "fonts/Marker Felt.ttf", 24);
	LifeLabelValue->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 70,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
    this->addChild(LifeLabelValue, 1, LabelTagLife);

	auto ResourceLabel = Label::createWithTTF("Resource", "fonts/Marker Felt.ttf", 24);
	ResourceLabel->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 150,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(ResourceLabel, 1);

	auto ResourceLabelValue = Label::createWithTTF(StringResource, "fonts/Marker Felt.ttf", 24);
	ResourceLabelValue->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 220,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(ResourceLabelValue,1, LabelTagResource);


	auto BackgroundSprite = Sprite::create("Background.png");
	BackgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(BackgroundSprite, 0);

	////////////////////////
	//REMOVED FOR END TURN
	//auto Back = MenuItemImage::create("Back.png", "BackClicked.png", CC_CALLBACK_1(SinglePlayGame::returnToTitle, this));
	//Back->setPosition(Vec2(origin.x + visibleSize.width - Back->getContentSize().width, 70));
	//auto menu = Menu::create(Back, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu,1);
	////////////////////////

	auto EndTurn = MenuItemImage::create("EndTurn.png", "EndTurn.png", CC_CALLBACK_1(SinglePlayGame::EndRoundTurn, this));
	EndTurn->setPosition(Vec2(origin.x + visibleSize.width - EndTurn->getContentSize().width, 70));
	auto menu = Menu::create(EndTurn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1);


	auto LastPage = MenuItemImage::create("ArrowSelection.png", "ArrowSelection.png", CC_CALLBACK_1(SinglePlayGame::LastPage, this));
	LastPage->setPosition(Vec2(origin.x + visibleSize.width - LastPage->getContentSize().width, 360));
	//origin.y + visibleSize.height - Back->getContentSize().height * 8));
	auto NP = Menu::create(LastPage, NULL);
	NP->setPosition(Vec2::ZERO);
	this->addChild(NP, 1);


	//auto Test = Sprite::create("ArrowSelection.png");
	//Test->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//this->addChild(Test, 2, MoveSprite);

	auto Grid = Sprite::create("GridTemplate2.png");
	Grid->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	Grid->setScale(1.5);
	this->addChild(Grid, 0);

	/////////////////////////////////////////////////////////////////////////////////////
    ////Tower Area

	auto TowerArea00 = Sprite::create("testTowerArea.png");
	TowerArea00->setPosition(Vec2(175, 468));
	TowerArea00->setOpacity(0);
	this->addChild(TowerArea00, 1);

	auto TowerArea01 = Sprite::create("testTowerArea.png");
	TowerArea01->setPosition(Vec2(250, 468));
	TowerArea01->setOpacity(0);
	this->addChild(TowerArea01, 1);

	auto TowerArea02 = Sprite::create("testTowerArea.png");
	TowerArea02->setPosition(Vec2(326, 468));
	TowerArea02->setOpacity(0);
	this->addChild(TowerArea02, 1);

	auto TowerArea03 = Sprite::create("testTowerArea.png");
	TowerArea03->setPosition(Vec2(401, 468));
	TowerArea03->setOpacity(0);
	this->addChild(TowerArea03, 1);

	auto TowerArea10 = Sprite::create("testTowerArea.png");
	TowerArea10->setPosition(Vec2(175, 395));
	TowerArea10->setOpacity(0);
	this->addChild(TowerArea10, 1);

	auto TowerArea11 = Sprite::create("testTowerArea.png");
	TowerArea11->setPosition(Vec2(250, 395));
	TowerArea11->setOpacity(0);
	this->addChild(TowerArea11, 1);

	auto TowerArea12 = Sprite::create("testTowerArea.png");
	TowerArea12->setPosition(Vec2(326, 395));
	TowerArea12->setOpacity(0);
	this->addChild(TowerArea12, 1);

	auto TowerArea13 = Sprite::create("testTowerArea.png");
	TowerArea13->setPosition(Vec2(401, 395));
	TowerArea13->setOpacity(0);
	this->addChild(TowerArea13, 1);

	auto TowerArea20 = Sprite::create("testTowerArea.png");
	TowerArea20->setPosition(Vec2(175, 321));
	TowerArea20->setOpacity(0);
	this->addChild(TowerArea20, 1);

	auto TowerArea21 = Sprite::create("testTowerArea.png");
	TowerArea21->setPosition(Vec2(250, 321));
	TowerArea21->setOpacity(0);
	this->addChild(TowerArea21, 1);

	auto TowerArea22 = Sprite::create("testTowerArea.png");
	TowerArea22->setPosition(Vec2(326, 321));
	TowerArea22->setOpacity(0);
	this->addChild(TowerArea22, 1);

	auto TowerArea23 = Sprite::create("testTowerArea.png");
	TowerArea23->setPosition(Vec2(401, 321));
	TowerArea23->setOpacity(0);
	this->addChild(TowerArea23, 1);

	auto TowerArea30 = Sprite::create("testTowerArea.png");
	TowerArea30->setPosition(Vec2(175, 246));
	TowerArea30->setOpacity(0);
	this->addChild(TowerArea30, 1);

	auto TowerArea31 = Sprite::create("testTowerArea.png");
	TowerArea31->setPosition(Vec2(250, 246));
	TowerArea31->setOpacity(0);
	this->addChild(TowerArea31, 1);

	auto TowerArea32 = Sprite::create("testTowerArea.png");
	TowerArea32->setPosition(Vec2(326, 246));
	TowerArea32->setOpacity(0);
	this->addChild(TowerArea32, 1);

	auto TowerArea33 = Sprite::create("testTowerArea.png");
	TowerArea33->setPosition(Vec2(401, 246));
	TowerArea33->setOpacity(0);
	this->addChild(TowerArea33, 1);


	/////////////////////////////////////////////////////////////////////////////////////

	/*Moves to the place you touch, Can remove later
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SinglePlayGame::onTouchBegan, this);

	//    life = life - 10;
	 //   resource = resource - 20;
	  //  StringLife = std::to_string(life);
	    //std::string StringResource = std::to_string(resource);
	   // LifeLabelValue->setString(StringLife);
	
	listener->onTouchEnded = CC_CALLBACK_2(SinglePlayGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	*/

	//auto containerForCards = Node::create();

	/*
    auto sprite4 = Sprite::create("SampleCard.png");
	sprite4->setPosition(origin + Vec2(((visibleSize.width / 2) - 150) - sprite4->getContentSize().width, (visibleSize.height / 2) - 200));
	this->addChild(sprite4, 21, C);

	auto sprite3 = Sprite::create("SampleTower.png");
	sprite3->setPosition(origin + Vec2((visibleSize.width / 2) - 100, (visibleSize.height / 2) - 200));
	this->addChild(sprite3, 20, T);
	*/


	/////////////////////////////////////
	//containerForCards->addChild(sprite3);
	//addChild(containerForCards, 10);
	//sprite3->setTag(T);

	
	//containerForCards->addChild(sprite4);
	//addChild(containerForCards, 10);
	//sprite4->setTag(C);
/*
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		CCLOG("Touch");
		//target->getTag();
		//add in code so it doesn't touch anything within the grid
		//if (target->getPosition().y > 300 && target->getPosition().y < 600 && target->getPosition().x > 200 && target->getPosition().x < 700) {
		//
		//}
		//else 
		//{

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
	
		//OriginalX = target->getPosition().x;
		//OriginalY = target->getPosition().y;

		log("Coordinates began... x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);

		CCLOG("Before if");
		if (rect.containsPoint(locationInNode))
		{
			log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			target->setOpacity(180);
			CCLOG("After If");
			return true;
		}
		return false;
		// }
	};

	listener1->onTouchMoved = [=](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
		for (int i = 0; i < 25;i++)
		{
			//if (CollisionGridArea[i] == 0)
			//{
				//TestArea->setOpacity(200);
				//TowerArea->setOpacity(200);
			//}
		}
		if (target->getTag() == T) 
		{
			target->setTexture("SampleTower.png");
		}
		else if (target->getTag() == C)
		{
			target->setTexture("testEnemy.png");
		}

		target->setScale(2.0);
	};

	listener1->onTouchEnded = [=](Touch* touch, Event* event) {

		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//TestArea->setOpacity(0);
		//TowerArea->setOpacity(0);
		//if (target->getPosition().y > 300 && target->getPosition().y < 600 && target->getPosition().x > 200 && target->getPosition().x < 700) {
			
		if(target->getPosition().x >100 && target->getPosition().x <859 && target->getPosition().y > 178 && target->getPosition().y <544)
		{
		    log("sprite onTouchesEnded.. ");
			target->setOpacity(255);

		}
		else
		{
			//target->setPosition(origin + Vec2((visibleSize.width / 2) + 100, (visibleSize.height / 2) - 200));
			//target->setPosition(Vec2(OriginalX, OriginalY));
			target->setTexture("SampleCard.png");
			target->setScale(1.0);
			target->setOpacity(255);
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite3);
<<<<<<< HEAD

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), cardInHand);

=======
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite4);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite);
	///////////////////////////////////////////////
	*/


	Player* p = new Player();
//	cardInHand->setPosition(50,100);
//	this->addChild(cardInHand, 1, CardsInHand);
	
//	for (int i = 0; i < p->getHandSize(); i++)
	//{
//		cards->addChild(drawHand(p, i),1);
	//}
//	cards->setPosition(Vec2::ZERO);
//	this->addChild(cards, 1);
	displayHand(p);
	//p->playCard(0);
	p->drawCard();
	p->drawCard();
	displayHand(p);
	return true;
}

void SinglePlayGame::displayHand(Player* p)
{
	this->removeChildByTag(handSprite1);
	this->removeChildByTag(handSprite2);
	this->removeChildByTag(handSprite3);
	this->removeChildByTag(handSprite4);
	this->removeChildByTag(handSprite5);
	this->removeChildByTag(handSprite6);

	auto sprite = cocos2d::Sprite::create("HelloWorld.png");
	int i;
	for (i = 0; (unsigned)i < p->getHandSize(); i++)
	{
		sprite = p->getCardInHand(i)->getSprite();
		sprite->setPosition(Vec2(100 + (i * 100), 50));
		this->addChild(sprite, 1, handSprite1 + i);
	}
	// turn auto sprite into auto MenuItemImage
/*	int i;
	auto image = MenuItemImage::create();
	auto imageMenu = Menu::create();
	for (i = 0; (unsigned)i < listOfCards.size() && i < maxCardsPerLine; i++)
	{
		image = MenuItemImage::create(listOfCards[i]->getSpriteName(), listOfCards[i]->getSpriteName(),
			CC_CALLBACK_0(Collection::displayLore, this, listOfCards[i]));

		image->setPosition(Vec2(200 + (i * 100), 500));
		imageMenu = Menu::create(image, NULL);
		imageMenu->setPosition(Vec2::ZERO);
		this->addChild(imageMenu, 1);
	}
	for (i = 0; (unsigned)i + 4 < listOfCards.size() && i < maxCardsPerLine; i++)
	{
		image = MenuItemImage::create(listOfCards[i + 4]->getSpriteName(), listOfCards[i + 4]->getSpriteName(),
			CC_CALLBACK_0(Collection::displayLore, this, listOfCards[i]));

<<<<<<< HEAD
		image->setPosition(Vec2(200 + (i * 100), 300));
		imageMenu = Menu::create(image, NULL);
		imageMenu->setPosition(Vec2::ZERO);
		this->addChild(imageMenu, 1);
=======
		auto cardInHand = (MenuItemImage*)getChildByTag(CardsInHand);
		
		cardInHand->setNormalImage(p->getCardInHand(i)->getSprite());
		cardInHand->setSelectedImage(p->getCardInHand(i)->getSprite());
		cardInHand->setPosition(50 + (100 * i), 100);
		//CCLOG("TEST");
>>>>>>> origin/master
	}
*/

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		CCLOG("Touch");
		//target->getTag();
		//add in code so it doesn't touch anything within the grid
		//if (target->getPosition().y > 300 && target->getPosition().y < 600 && target->getPosition().x > 200 && target->getPosition().x < 700) {
		//
		//}
		//else 
		//{
		if (target->getPosition().x >100 && target->getPosition().x <859 && target->getPosition().y > 178 && target->getPosition().y <544) {
			return false;
		}
		else 
		{

			Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);

			//OriginalX = target->getPosition().x;
			//OriginalY = target->getPosition().y;

			log("Coordinates began... x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);

			CCLOG("Before if");
			if (rect.containsPoint(locationInNode))
			{
				log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
				target->setOpacity(180);
				CCLOG("After If");
				return true;
			}
			return false;
			// }
		}
	};

	listener1->onTouchMoved = [=](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
		for (int i = 0; i < 25;i++)
		{
			//if (CollisionGridArea[i] == 0)
			//{
			//TestArea->setOpacity(200);
			//TowerArea->setOpacity(200);
			//}
		}
		CCLOG("BEFORE IF LOOP");
		if (p->getCardInHand(1)->getType() =='s') 
		{
			CCLOG("IF LOOP RUNNING");
			target->setTexture("testEnemy.png");
		}
		else if (p->getCardInHand(1)->getType() == 't')
		{
			CCLOG("IF LOOP RUNNING");
			target->setTexture("SampleTower.png");
		}
		/*
		if (target->getTag() == T)
		{
			target->setTexture("SampleTower.png");
		}
		else if (target->getTag() == C)
		{
			target->setTexture("testEnemy.png");
		}
		*/
		target->setScale(2.0);
	};

	listener1->onTouchEnded = [=](Touch* touch, Event* event) {

		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//TestArea->setOpacity(0);
		//TowerArea->setOpacity(0);
		//if (target->getPosition().y > 300 && target->getPosition().y < 600 && target->getPosition().x > 200 && target->getPosition().x < 700) {

        //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
	    //"pew-pew-lei.wav");


		if (target->getPosition().x >100 && target->getPosition().x <859 && target->getPosition().y > 178 && target->getPosition().y <544)
		{
			log("sprite onTouchesEnded.. ");
			target->setOpacity(255);

		}
		else
		{
			//target->setPosition(origin + Vec2((visibleSize.width / 2) + 100, (visibleSize.height / 2) - 200));
			//target->setPosition(Vec2(OriginalX, OriginalY));
			target->setTexture("SampleCard.png");
			target->setScale(1.0);
			target->setOpacity(255);
			
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->getChildByTag(handSprite1));

	for (int j = 0; (unsigned)j < p->getHandSize(); j++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->getChildByTag(handSprite1+j));

	}
	

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->getChildByTag(handSprite1));
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->getChildByTag(handSprite2));
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->getChildByTag(handSprite3));
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->getChildByTag(handSprite4));
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->getChildByTag(handSprite5));
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->getChildByTag(handSprite6));
	
}


void SinglePlayGame::returnToTitle(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

//TAKE OUT LATER IF NOT NEEDED, ONLY A TEMPLATE TO GO TO THE GAME WON SCREEN
void SinglePlayGame::LastPage(cocos2d::Ref* pSender)
{
	auto GameWonScene = GameWonScreen::createScene();
	Director::getInstance()->pushScene(GameWonScene);
}


bool SinglePlayGame::onTouchBegan(Touch* touch, Event  *event)
{
	//for (int g = 0;g < 4;g++) {
	//	for (int h = 0;h < 4;h++) {
	//		if (TowerAreaArray[g][h] == 0) {
	//		
	//		}
	//	}
	//}
	
	return true;
}

void SinglePlayGame::onTouchEnded(Touch* touch, Event  *event)
{
		auto location = touch->getLocation();

		auto s = getChildByTag(MoveSprite);
		s->stopAllActions();
		s->runAction(MoveTo::create(1, Vec2(location.x, location.y)));
		float o = location.x - s->getPosition().x;
		float a = location.y - s->getPosition().y;
		//auto LifeTag = getChildByTag(LabelTagLife);
		CCLabelBMFont* ChangeLife = (CCLabelBMFont*)getChildByTag(LabelTagLife);
		CCLabelBMFont* ChangeResource = (CCLabelBMFont*)getChildByTag(LabelTagResource);
		life = life - 10;
		if (life <= 0)
		{
			//auto GameOverScene = GameOverScreen::createScene();
			//Director::getInstance()->pushScene(GameOverScene);
			LostGame();
		}

		resource = resource - 20;
		std::string StringLife = std::to_string(life);
		std::string StringResource = std::to_string(resource);
	    ChangeLife->setString(StringLife);
		ChangeResource->setString(StringResource);
		CCLOG("%d ", life);
		CCLOG(" %d", resource);
}


void SinglePlayGame::WonGame()
{
	auto GameWonScene = GameWonScreen::createScene();
	Director::getInstance()->pushScene(GameWonScene);
}

void SinglePlayGame::LostGame()
{
	auto GameOverScene = GameOverScreen::createScene();
	Director::getInstance()->pushScene(GameOverScene);
}

void SinglePlayGame::EndRoundTurn(cocos2d::Ref* pSender)
{
	//auto GameWonScene = GameWonScreen::createScene();
	//Director::getInstance()->pushScene(GameWonScene);
	CCLOG("Test For End Turn");
}

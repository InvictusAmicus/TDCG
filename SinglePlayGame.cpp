#include "SinglePlayGame.h"
#include "GameOverScreen.h"

USING_NS_CC;

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
	
	auto label = Label::createWithTTF("Single Player Game", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	auto sprite = Sprite::create("Background.png");

	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(sprite, 0);

	auto Back = MenuItemImage::create("Back.png", "BackClicked.png", CC_CALLBACK_1(SinglePlayGame::returnToTitle, this));
	Back->setPosition(Vec2(origin.x + visibleSize.width - Back->getContentSize().width, 70));
	auto menu = Menu::create(Back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto LastPage = MenuItemImage::create("ArrowSelection.png", "ArrowSelection.png", CC_CALLBACK_1(SinglePlayGame::LastPage, this));
	LastPage->setPosition(Vec2(origin.x + visibleSize.width - LastPage->getContentSize().width, 360));
	//origin.y + visibleSize.height - Back->getContentSize().height * 8));
	auto NP = Menu::create(LastPage, NULL);
	NP->setPosition(Vec2::ZERO);
	this->addChild(NP, 1);


	auto Test = Sprite::create("ArrowSelection.png");
	Test->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(Test, 1, MoveSprite);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SinglePlayGame::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SinglePlayGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	return true;

}

void SinglePlayGame::returnToTitle(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}


void SinglePlayGame::LastPage(cocos2d::Ref* pSender)
{
	auto GameOverScene = GameOverScreen::createScene();
	Director::getInstance()->pushScene(GameOverScene);
}


bool SinglePlayGame::onTouchBegan(Touch* touch, Event  *event)
{
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
}
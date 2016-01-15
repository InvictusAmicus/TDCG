#include "SinglePlayGame.h"
#include "GameOverScreen.h"
//#include "Player.h"

USING_NS_CC;

int life = 100;
int resource = 100;
#define LabelTagLife 1234
#define LabelTagResource 1235

enum
{
	MoveSprite = 1, LifeChange = 1,
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

	//    life = life - 10;
	 //   resource = resource - 20;
	  //  StringLife = std::to_string(life);
	    //std::string StringResource = std::to_string(resource);
	   // LifeLabelValue->setString(StringLife);
	
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
		//auto LifeTag = getChildByTag(LabelTagLife);
		CCLabelBMFont* ChangeLife = (CCLabelBMFont*)getChildByTag(LabelTagLife);
		CCLabelBMFont* ChangeResource = (CCLabelBMFont*)getChildByTag(LabelTagResource);
		life = life - 10;
		resource = resource - 20;
		std::string StringLife = std::to_string(life);
		std::string StringResource = std::to_string(resource);
	    ChangeLife->setString(StringLife);
		ChangeResource->setString(StringResource);
		CCLOG("%d ", life);
		CCLOG(" %d", resource);
}
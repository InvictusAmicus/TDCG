#include"HowToPlay.h"

USING_NS_CC;

Scene* HowToPlay::createScene()
{
	// 'scene' is an autorelease object
	auto HowToPlayScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HowToPlay::create();

	// add layer as a child to scene
	HowToPlayScene->addChild(layer);

	// return the scene
	return HowToPlayScene;
}

// on "init" you need to initialize your instance
bool HowToPlay::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("How To Play", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	auto Back = MenuItemImage::create("Back.png", "BackClicked.png", CC_CALLBACK_1(HowToPlay::returnToTitle, this));
	Back->setPosition(Vec2(origin.x + visibleSize.width - Back->getContentSize().width, 70));

	auto menu = Menu::create(Back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//Simple background added
	auto sprite = Sprite::create("Background.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	return true;
}

void HowToPlay::returnToTitle(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}
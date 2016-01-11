#include"NewGame.h"

USING_NS_CC;

Scene* NewGame::createScene()
{
	// 'scene' is an autorelease object
	auto NewGameScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = NewGame::create();

	// add layer as a child to scene
	NewGameScene->addChild(layer);

	// return the scene
	return NewGameScene;
}

// on "init" you need to initialize your instance
bool NewGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto label = Label::createWithTTF("NewGame", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	//Simple background added
	auto sprite = Sprite::create("Background.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);


	return true;

}
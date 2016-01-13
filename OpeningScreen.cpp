#include "OpeningScreen.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* OpeningScreen::createScene()
{
	// 'scene' is an autorelease object
	auto OpeingScreenScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = OpeningScreen::create();

	// add layer as a child to scene
	OpeingScreenScene->addChild(layer);

	// return the scene
	return OpeingScreenScene;
}

bool OpeningScreen::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("OpeningScreen", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	auto sprite = Sprite::create("Background.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	//Sleep(2);
	GoToTitle();

	return true;
}

void OpeningScreen::GoToTitle()
{
	auto MainMenuScene = MainMenu::createScene();
	Director::getInstance()->pushScene(MainMenuScene);
}
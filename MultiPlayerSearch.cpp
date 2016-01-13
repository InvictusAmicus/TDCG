#include "MultiPlayerSearch.h"
#include "MultiPlayer.h"

USING_NS_CC;

Scene* MultiPlayerSearch::createScene()
{
	// 'scene' is an autorelease object
	auto MultiPlayerScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MultiPlayerSearch::create();

	// add layer as a child to scene
	MultiPlayerScene->addChild(layer);

	// return the scene
	return MultiPlayerScene;
}

bool MultiPlayerSearch::init()
{
	
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("MultiPlayer Search", "fonts/Marker Felt.ttf", 24);

	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	this->addChild(label, 1);

	auto Back = MenuItemImage::create("Back.png", "BackClicked.png", CC_CALLBACK_1(MultiPlayerSearch::returnToTitle, this));
	Back->setPosition(Vec2(origin.x + visibleSize.width - Back->getContentSize().width, 70));
	auto menu = Menu::create(Back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto NextPage = MenuItemImage::create("ArrowSelection.png", "ArrowSelection.png", CC_CALLBACK_1(MultiPlayerSearch::Next, this));
	NextPage->setPosition(Vec2(origin.x + visibleSize.width - NextPage->getContentSize().width, 360));
	auto menu1 = Menu::create(NextPage, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);

	auto sprite = Sprite::create("Background.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	return true;
}

void MultiPlayerSearch::returnToTitle(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}
void MultiPlayerSearch::Next(cocos2d::Ref* pSender)
{
	auto NextScene = MultiPlayer::createScene();
	Director::getInstance()->pushScene(NextScene);
}
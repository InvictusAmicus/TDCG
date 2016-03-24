//Worked on by Ciaran Clerkin K00191500 and Declan Cordial K00184439

#include "Collection.h"
#include "CollectionP2.h"

USING_NS_CC;

Scene* CollectionP2::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CollectionP2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool CollectionP2::init()
{
	
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto Back = MenuItemImage::create("Back.png", "BackClicked.png", CC_CALLBACK_1(CollectionP2::returnToTitle, this));
	Back->setPosition(Vec2(origin.x + visibleSize.width - Back->getContentSize().width, 70));
	//origin.y + visibleSize.height - Back->getContentSize().height * 8));
	auto menu = Menu::create(Back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto SecondPage = MenuItemImage::create("ArrowSelection2.png", "ArrowSelection2.png", CC_CALLBACK_1(CollectionP2::LastPage, this));
	SecondPage->setPosition(Vec2(origin.x + SecondPage->getContentSize().width, 360));
	//origin.y + visibleSize.height - Back->getContentSize().height * 8));
	auto NP = Menu::create(SecondPage, NULL);
	NP->setPosition(Vec2::ZERO);
	this->addChild(NP, 1);


	auto label = Label::createWithTTF("CardDatabase Page 2", "fonts/Marker Felt.ttf", 24);

	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	this->addChild(label, 1);

	auto sprite = Sprite::create("Background.png");

	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(sprite, 0);

	return true;

}

void CollectionP2::returnToTitle(cocos2d::Ref* pSender)
{
	Director::getInstance()->popToRootScene();
}

void CollectionP2::LastPage(cocos2d::Ref* pSender)
{
	auto CollectionScene = Collection::createScene();
	Director::getInstance()->pushScene(CollectionScene);
}
#include "Collection.h"
#include "CollectionP2.h"
#include "MainMenu.h"

USING_NS_CC;

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
	listOfCards.push_back(new Card("SampleCard.png"));
	listOfCards.push_back(new Card("SampleCard.png"));
	listOfCards.push_back(new Card("SampleCard.png"));
	listOfCards.push_back(new Card("SampleCard.png"));
	listOfCards.push_back(new Card("SampleCard.png"));
	listOfCards.push_back(new Card("SampleCard.png"));
	listOfCards.push_back(new Card("SampleCard.png"));
	listOfCards.push_back(new Card("SampleCard.png"));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto Back = MenuItemImage::create("Back.png", "BackClicked.png", CC_CALLBACK_1(Collection::returnToTitle, this));
	Back->setPosition(Vec2(origin.x + visibleSize.width - Back->getContentSize().width, 70));
		//origin.y + visibleSize.height - Back->getContentSize().height * 8));
	auto menu = Menu::create(Back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto SecondPage = MenuItemImage::create("ArrowSelection.png", "ArrowSelection.png", CC_CALLBACK_1(Collection::NextPage, this));
	SecondPage->setPosition(Vec2(origin.x + visibleSize.width - SecondPage->getContentSize().width, 360));
	//origin.y + visibleSize.height - Back->getContentSize().height * 8));
	auto NP = Menu::create(SecondPage, NULL);
	NP->setPosition(Vec2::ZERO);
	this->addChild(NP, 1);


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
	auto sprite = cocos2d::Sprite::create("HelloWorld.png");
	int i;
	for (int i = 0; i < listOfCards.size() && i < maxCardsPerLine; i++)
	{
		sprite = listOfCards[i]->getSprite();
		sprite->setPosition(Vec2(200 + (i * 100), 250));
		this->addChild(sprite, 1);
	}
	for (int i = 0; i+4 < listOfCards.size() && i < maxCardsPerLine; i++)
	{
		sprite = listOfCards[i+4]->getSprite();
		sprite->setPosition(Vec2(200 + (i * 100), 500));
		this->addChild(sprite, 1);
	}

}


void Collection::returnToTitle(cocos2d::Ref* pSender)
{
	Director::getInstance()->popToRootScene();
}

void Collection::NextPage(cocos2d::Ref* pSender)
{
	auto CollectionP2Scene = CollectionP2::createScene();
	Director::getInstance()->pushScene(CollectionP2Scene);
}
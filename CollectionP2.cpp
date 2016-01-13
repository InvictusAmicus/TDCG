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
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	/*Original close
	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
	"CloseNormal.png",
	"CloseSelected.png",
	CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
	origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	*/

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



	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("CardDatabase", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	//Title sprite

	//Simple background added
	auto sprite = Sprite::create("Background.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
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
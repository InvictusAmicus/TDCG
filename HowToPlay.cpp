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

bool HowToPlay::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("How To Play", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	auto Back = MenuItemImage::create("Back.png", "BackClicked.png", CC_CALLBACK_1(HowToPlay::returnToTitle, this));
	Back->setPosition(Vec2(origin.x + visibleSize.width - Back->getContentSize().width, 70));
	auto menu = Menu::create(Back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto sprite = Sprite::create("Background.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	auto exampleCard = Sprite::create("Archfiend.png");
	exampleCard->setPosition(Vec2(visibleSize.width * (0.3), visibleSize.height * (0.7)));
	exampleCard->setScale(2.0);
	this->addChild(exampleCard, 1);

	auto cardExplanation = Label::createWithTTF("The card's cost is in the top left corner.\n"
		"The unit's cost is the number multiplied by 100\n"
		"The unit's attack and health are shown"
		, "fonts/Marker Felt.ttf", 20);
	cardExplanation->setColor(cocos2d::Color3B::BLACK);
	cardExplanation->setPosition(Vec2(visibleSize.width * (0.75), visibleSize.height * (0.7)));
	this->addChild(cardExplanation, 1);

	auto exampleGrid = Sprite::create("GridTemplate2.png");
	exampleGrid->setPosition(Vec2(visibleSize.width * (0.3), visibleSize.height * (0.3)));
	exampleGrid->setScale(0.5);
	this->addChild(exampleGrid,1);

	auto resourceExplanation = Label::createWithTTF("Players can see their health and resources in\n"
		"the upper leftmost corner of the screen.\n"
		"Resources are gained at the start of every\n"
		"turn and when an enemy soldier dies.\n"
		, "fonts/Marker Felt.ttf", 20);
	resourceExplanation->setPosition(Vec2(visibleSize.width * (0.75), visibleSize.height * (0.5)));
	resourceExplanation->setColor(cocos2d::Color3B::BLACK);
	this->addChild(resourceExplanation, 1);


	auto gridExplanation = Label::createWithTTF("Soldiers can be placed on the squares of the grid.\n"
		"Towers can be placed on the circles of the grid.\n"
		"The player can place soldiers and towers on the\nleft hand side of the screen.\n"
		"When playing multiplayer, the second player\nputs their cards on the right hand size."
		, "fonts/Marker Felt.ttf", 20);

	gridExplanation->setPosition(Vec2(visibleSize.width * (0.75), visibleSize.height * (0.3)));
	gridExplanation->setColor(cocos2d::Color3B::BLACK);
	this->addChild(gridExplanation, 1);
	return true;
}

void HowToPlay::returnToTitle(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}
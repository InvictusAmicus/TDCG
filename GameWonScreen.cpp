#include "GameWonScreen.h"
#include "AudioEngine.h"
#include "Options.h"

int GameWonTrack;
int GameMenu2;

USING_NS_CC;

Scene* GameWonScreen::createScene()
{
	// 'scene' is an autorelease object
	auto GameWonScreenScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameWonScreen::create();

	// add layer as a child to scene
	GameWonScreenScene->addChild(layer);

	// return the scene
	return GameWonScreenScene;
}

bool GameWonScreen::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Options gameMusic;
	if (gameMusic.getMusicMute() != 1) 
	{
		int V = gameMusic.getmusicVolume();
		GameWonTrack = cocos2d::experimental::AudioEngine::play2d("GameWon.mp3", true, gameMusic.getMusicFloatVolume(V), nullptr);
	}

	auto label = Label::createWithTTF("Game Won Screen", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	auto ReturnToTitle = MenuItemImage::create("Back.png", "BackClicked.png", CC_CALLBACK_1(GameWonScreen::returnToTitleScreen, this));
	ReturnToTitle->setPosition(Vec2(origin.x + visibleSize.width - ReturnToTitle->getContentSize().width, 70));
	auto menu = Menu::create(ReturnToTitle, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto sprite = Sprite::create("Background.png");

	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(sprite, 0);

	return true;
}

void GameWonScreen::returnToTitleScreen(cocos2d::Ref* pSender)
{
	cocos2d::experimental::AudioEngine::stopAll();
	Options gameMusic;
	if (gameMusic.getMusicMute() != 1) 
	{
		int V = gameMusic.getmusicVolume();
		GameMenu2 = cocos2d::experimental::AudioEngine::play2d("MainMenu.mp3", true, gameMusic.getMusicFloatVolume(V), nullptr);
	}
	Director::getInstance()->popToRootScene();
}
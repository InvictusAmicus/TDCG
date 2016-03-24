//Worked on by Ciaran Clerkin K00191500 and Declan Cordial K00184439

#include "GameWonScreen.h"
#include "AudioEngine.h"
#include "Options.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NewSinglePlayGame.h"
#include "Database.h"
#include <string>

int playerScore;
int GameWonTrack;
int GameMenu2;
std::string name = "Enter Name:";
ui::EditBox* e;

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

Scene* GameWonScreen::createScene(int s)
{
	// 'scene' is an autorelease object
	auto GameWonScreenScene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = GameWonScreen::create();

	// add layer as a child to scene
	GameWonScreenScene->addChild(layer);

	// return the scene

	//playerScore = s;
	return GameWonScreenScene;
}

bool GameWonScreen::init()
{

	if (!Layer::init())
	{
		return false;
	}
	NewSinglePlayGame game;
	playerScore = game.getScore();
	CCLOG("Score: init: %d", playerScore);

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
	
	auto ReturnToTitle = MenuItemImage::create("Submit.png", "Submit.png", CC_CALLBACK_1(GameWonScreen::returnToTitleScreen, this));
	ReturnToTitle->setPosition(Vec2(origin.x + visibleSize.width/2, 70));
	auto menu = Menu::create(ReturnToTitle, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto sprite = Sprite::create("Background.png");

	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	auto ed = ui::EditBox::create(Size(200, 40), "AreaCollision.png");
	ed->setPlaceHolder("Enter Name:");
	ed->setFontSize(20);
	ed->setMaxLength(10);
	ed->setPosition(Vec2(origin.x + visibleSize.width / 2, 150));
	this->addChild(ed, 1);

	e = ed;

	CCLOG("Score: %d", playerScore);
	auto nameLabel = Label::createWithTTF("Score: "+std::to_string(playerScore), "fonts/Marker Felt.ttf", 24);
	nameLabel->setColor(Color3B::BLACK);
	nameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, 200));
	this->addChild(nameLabel, 1);

	auto youWin = Label::createWithTTF("You won!\nSubmit your score below!", "fonts/Marker Felt.ttf", 70);
	youWin->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * (0.7)));
	youWin->setColor(cocos2d::Color3B::BLACK);
	this->addChild(youWin, 1);

	return true;
}

void GameWonScreen::returnToTitleScreen(cocos2d::Ref* pSender)
{
	//add database insert
	Database d;
	StringLength = e->getText();
	if (StringLength.length() == 0) 
	{
		e->setText("AAA");
	}
	d.write(e->getText(), playerScore);

	cocos2d::experimental::AudioEngine::stopAll();
	Options gameMusic;
	if (gameMusic.getMusicMute() != 1) 
	{
		int V = gameMusic.getmusicVolume();
		GameMenu2 = cocos2d::experimental::AudioEngine::play2d("MainMenu.mp3", true, gameMusic.getMusicFloatVolume(V), nullptr);
	}
	Director::getInstance()->popToRootScene();
}
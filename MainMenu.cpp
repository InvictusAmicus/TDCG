#include "Collection.h"
#include "MainMenu.h"
#include "MultiPlayerSearch.h"
#include "SinglePlayGame.h"
#include "Options.h"
#include "HowToPlay.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include<fstream>
#include "AudioEngine.h"

USING_NS_CC;
using namespace std;

int StartMusicVolume;
float SoundEffectsVolumeControl;
int MenuEffectsMute;
int MenuMusicMute;
int StartTrack;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool MainMenu::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	SystemFile();
	PlayMusic();

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
	//	"background-music-aac.wav", true);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0);

	auto Quit = MenuItemImage::create("Quit.png", "QuitClicked.png", CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
	Quit->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - Quit->getContentSize().height * 11));
	auto menu = Menu::create(Quit, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	
	auto Cards = MenuItemImage::create("Collection.png", "CollectionClicked.png", CC_CALLBACK_1(MainMenu::menuCollection, this));
	Cards->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - Cards->getContentSize().height * 9));
	auto menuCards = Menu::create(Cards, NULL);
	menuCards->setPosition(Vec2::ZERO);
	this->addChild(menuCards, 1);

    auto label = Label::createWithTTF("Title Screen", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

	auto spriteTitle = Sprite::create("TitleSprite.png");
	spriteTitle->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - spriteTitle->getContentSize().height));
	this->addChild(spriteTitle, 1);

	auto spriteNewGame = MenuItemImage::create("Play.png", "PlayClicked.png", CC_CALLBACK_1(MainMenu::menuNewGame, this));
	spriteNewGame->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - spriteNewGame->getContentSize().height * 6));
	auto menuNewGame = Menu::create(spriteNewGame, NULL);
	menuNewGame->setPosition(Vec2::ZERO);
	this->addChild(menuNewGame, 1);

	auto spriteContinue = MenuItemImage::create("Multiplayer.png", "MultiplayerClicked.png", CC_CALLBACK_1(MainMenu::menuMultiPlayer, this));
	
	spriteContinue->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - spriteContinue->getContentSize().height * 7));
	auto menuContinue = Menu::create(spriteContinue, NULL);
	menuContinue->setPosition(Vec2::ZERO);
	this->addChild(menuContinue, 1);
	
	auto spriteOptions = MenuItemImage::create("Options.png", "OptionsClicked.png", CC_CALLBACK_1(MainMenu::menuOptions, this));
	spriteOptions->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - spriteOptions->getContentSize().height * 10));
	auto menuOptions = Menu::create(spriteOptions, NULL);
	menuOptions->setPosition(Vec2::ZERO);
	this->addChild(menuOptions, 1);
	

	auto spriteHowToPlay = MenuItemImage::create("HowToPlay.png", "HowToPlayClicked.png", CC_CALLBACK_1(MainMenu::menuHowToPlay, this));
	spriteHowToPlay->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - spriteHowToPlay->getContentSize().height * 8));

	auto menuHowToPlay = Menu::create(spriteHowToPlay, NULL);
	menuHowToPlay->setPosition(Vec2::ZERO);
	this->addChild(menuHowToPlay, 1);


	auto sprite = Sprite::create("Background.png");

	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(sprite, 0);

    return true;

}


void MainMenu::menuCloseCallback(Ref* pSender)
{
	cocos2d::experimental::AudioEngine::stop(StartTrack);
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenu::menuNewGame(Ref* pSender)
{
	//cocos2d::experimental::AudioEngine::stop(StartTrack);
	cocos2d::experimental::AudioEngine::stopAll();
	//Director::getInstance()->end();
	auto NewGameScene = SinglePlayGame::createScene();
	//Director::getInstance()->runWithScene(NewGameScene);
	Director::getInstance()->pushScene(NewGameScene);
	//Director::getInstance()->popScene(NewGameScene);
	//Director::getInstance()->replaceScene(NewGameScene);


}

void MainMenu::menuMultiPlayer(Ref* pSender)
{
	//cocos2d::experimental::AudioEngine::stop(StartTrack);
	cocos2d::experimental::AudioEngine::stopAll();
	auto MultiPlayerScene = MultiPlayerSearch::createScene();
	Director::getInstance()->pushScene(MultiPlayerScene);
}

void MainMenu::menuCollection(Ref* pSender)
{
	cocos2d::experimental::AudioEngine::stop(StartTrack);
	auto CollectionScene = Collection::createScene();
	Director::getInstance()->pushScene(CollectionScene);
}

void MainMenu::menuOptions(Ref* pSender)
{
	cocos2d::experimental::AudioEngine::stop(StartTrack);
	auto OptionsScene = Options::createScene();
	Director::getInstance()->pushScene(OptionsScene);
}

void MainMenu::menuHowToPlay(Ref* pSender)
{
	cocos2d::experimental::AudioEngine::stop(StartTrack);
	auto HowToPlayScene = HowToPlay::createScene();
	Director::getInstance()->pushScene(HowToPlayScene);
}


void MainMenu::SystemFile() 
{
	CCLOG("START OF SYSTEM FILE");
	FileUtils::getInstance()->addSearchPath("SystemFile");
	string DataFileName = "System_File.txt";
	std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(DataFileName.c_str());
	//CCLOG("%s", fullpath);
	std::ifstream ReadFile(fullpath);
	string text;
	if (!ReadFile)
	{
		CCLOG("FILE NOT FOUND");
	}
	else
	{

		//
		//When compiled System_File being read from the debug win32, change values there
		//
		for (int x = 0; x < 4; x++)
		{
			if (x == 0)
			{
				getline(ReadFile, text);
				int testFileInt = atoi(text.c_str());
				std::string::size_type sz;
				StartMusicVolume = std::stof(text, &sz);
				CCLOG("MVC %d", StartMusicVolume);
				//	x++;
			}
			if (x == 1)
			{
				getline(ReadFile, text);
				int testFileInt = atoi(text.c_str());
				std::string::size_type sz;
				SoundEffectsVolumeControl = std::stof(text, &sz);
				CCLOG("SEVC %.2f", SoundEffectsVolumeControl);
				//	x++;
			}
			if (x == 2)
			{
				getline(ReadFile, text);
				MenuEffectsMute = atoi(text.c_str());
				CCLOG("EFFECTS MUTE %d", MenuEffectsMute);
			}
			if (x == 3)
			{
				getline(ReadFile, text);
				MenuMusicMute = atoi(text.c_str());
				CCLOG("MUSIC MUTE %d", MenuMusicMute);
			}

			CCLOG("X == %d", x);

		}

		ReadFile.close();
	}
	CCLOG("END OF System FILE");
}

void MainMenu::PlayMusic()
{
	CCLOG("START OF PLAY MUSIC");
	Options setMusic;
	setMusic.setMusicMute(MenuMusicMute);
	if (MenuMusicMute!=1){
		cocos2d::experimental::AudioEngine::stopAll();
	    StartTrack = cocos2d::experimental::AudioEngine::play2d("MainMenu.mp3", true, 1.0f, nullptr);
	//cocos2d::experimental::AudioEngine::setVolume(StartTrack, 1.0f);
    }
	if (StartMusicVolume == 0) {
		cocos2d::experimental::AudioEngine::setVolume(StartTrack, 0.0f);
	}
	else if (StartMusicVolume>0 && StartMusicVolume<10) {
		cocos2d::experimental::AudioEngine::setVolume(StartTrack, 0.1f);
	}
	else if (StartMusicVolume >= 10 && StartMusicVolume<20) {
		cocos2d::experimental::AudioEngine::setVolume(StartTrack, 0.2f);
	}
	else if (StartMusicVolume >= 20 && StartMusicVolume<30) {
		cocos2d::experimental::AudioEngine::setVolume(StartTrack, 0.3f);
	}
	else if (StartMusicVolume >= 30 && StartMusicVolume<40) {
		cocos2d::experimental::AudioEngine::setVolume(StartTrack, 0.4f);
	}
	else if (StartMusicVolume >= 40 && StartMusicVolume<50) {
		cocos2d::experimental::AudioEngine::setVolume(StartTrack, 0.5f);
	}
	else if (StartMusicVolume >= 50 && StartMusicVolume<60) {
		cocos2d::experimental::AudioEngine::setVolume(StartTrack, 0.6f);
	}
	else if (StartMusicVolume >= 60 && StartMusicVolume<70) {
		cocos2d::experimental::AudioEngine::setVolume(StartTrack, 0.7f);
	}
	else if (StartMusicVolume >= 70 && StartMusicVolume<80) {
		cocos2d::experimental::AudioEngine::setVolume(StartTrack, 0.8f);
	}
	else if (StartMusicVolume >= 80 && StartMusicVolume<90) {
		cocos2d::experimental::AudioEngine::setVolume(StartTrack, 0.9f);
	}
	else if (StartMusicVolume >= 90 && StartMusicVolume <= 100) {
		cocos2d::experimental::AudioEngine::setVolume(StartTrack, 1.0f);
	}
	
	CCLOG("END OF PLAY MUSIC");
}

#include "Collection.h"
#include "MainMenu.h"
#include "MultiPlayerSearch.h"
#include "SinglePlayGame.h"
#include "Options.h"
#include "HowToPlay.h"


USING_NS_CC;

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
	

	auto spriteHowToPlay = MenuItemImage::create("HowToPlay.png", "HowToPlay.png", CC_CALLBACK_1(MainMenu::menuHowToPlay, this));
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
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenu::menuNewGame(Ref* pSender)
{
	//Director::getInstance()->end();
	auto NewGameScene = SinglePlayGame::createScene();
	//Director::getInstance()->runWithScene(NewGameScene);
	Director::getInstance()->pushScene(NewGameScene);
	//Director::getInstance()->popScene(NewGameScene);
	//Director::getInstance()->replaceScene(NewGameScene);


}

void MainMenu::menuMultiPlayer(Ref* pSender)
{
	auto MultiPlayerScene = MultiPlayerSearch::createScene();
	Director::getInstance()->pushScene(MultiPlayerScene);
}

void MainMenu::menuCollection(Ref* pSender)
{
	auto CollectionScene = Collection::createScene();
	Director::getInstance()->pushScene(CollectionScene);
}

void MainMenu::menuOptions(Ref* pSender)
{
	auto OptionsScene = Options::createScene();
	Director::getInstance()->pushScene(OptionsScene);
}

void MainMenu::menuHowToPlay(Ref* pSender)
{
	auto HowToPlayScene = HowToPlay::createScene();
	Director::getInstance()->pushScene(HowToPlayScene);
}
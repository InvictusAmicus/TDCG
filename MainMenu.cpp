#include "MainMenu.h"
#include "NewGame.h"
#include "Options.h"
#include "MultiPlayer.h"


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

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
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

	auto Quit = MenuItemImage::create("Quit.png", "QuitClicked.png", CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
	Quit->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - Quit->getContentSize().height * 8));
	auto menu = Menu::create(Quit, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);



    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	//Title sprite
	auto spriteTitle = Sprite::create("TitleSprite.png");
	spriteTitle->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - spriteTitle->getContentSize().height));
	this->addChild(spriteTitle, 1);

	//New Game Sprite
	//auto spriteNewGame = Sprite::create("NewGame.png");
	//spriteNewGame->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - spriteNewGame->getContentSize().height * 4));
	//th+is->addChild(spriteNewGame, 1);
	auto spriteNewGame = MenuItemImage::create("NewGame.png", "NewGameClicked.png", CC_CALLBACK_1(MainMenu::menuNewGame, this));
	spriteNewGame->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - spriteNewGame->getContentSize().height * 4));
	auto menuNewGame = Menu::create(spriteNewGame, NULL);
	menuNewGame->setPosition(Vec2::ZERO);
	this->addChild(menuNewGame, 1);


	//Continue Sprite
	//auto spriteContinue = Sprite::create("Continue.png");
	//spriteContinue->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - spriteContinue->getContentSize().height * 8));
	//this->addChild(spriteContinue, 1);
	
<<<<<<< HEAD
	//CHANGE spriteContinue When MultiPlayerSprites Are made
	auto spriteContinue = MenuItemImage::create("Continue.png", "Options.png", CC_CALLBACK_1(MainMenu::menuMultiPlayer, this));
=======
	
	auto spriteContinue = MenuItemImage::create("Continue.png", "ContinueClicked.png", CC_CALLBACK_1(MainMenu::menuContinue, this));
>>>>>>> origin/master
	spriteContinue->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - spriteContinue->getContentSize().height * 8));
	auto menuContinue = Menu::create(spriteContinue, NULL);
	menuContinue->setPosition(Vec2::ZERO);
	this->addChild(menuContinue, 1);


	//Options Sprite
	//auto spriteOptions = Sprite::create("Options.png");
	//spriteOptions->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - spriteOptions->getContentSize().height * 7));
	//this->addChild(spriteOptions, 1);
	
	
	auto spriteOptions = MenuItemImage::create("Options.png", "OptionsClicked.png", CC_CALLBACK_1(MainMenu::menuOptions, this));
	spriteOptions->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - spriteOptions->getContentSize().height * 7));
	auto menuOptions = Menu::create(spriteOptions, NULL);
	menuOptions->setPosition(Vec2::ZERO);
	this->addChild(menuOptions, 1);
	

	/*Original background
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    */

	//Simple background added
	auto sprite = Sprite::create("Background.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
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
	auto NewGameScene = NewGame::createScene();
	//Director::getInstance()->runWithScene(NewGameScene);
	Director::getInstance()->pushScene(NewGameScene);
	//Director::getInstance()->popScene(NewGameScene);
	//Director::getInstance()->replaceScene(NewGameScene);


}

void MainMenu::menuMultiPlayer(Ref* pSender)
{
	auto MultiPlayerScene = MultiPlayer::createScene();
	Director::getInstance()->pushScene(MultiPlayerScene);
}

void MainMenu::menuOptions(Ref* pSender)
{
	auto OptionsScene = Options::createScene();
	Director::getInstance()->pushScene(OptionsScene);
}
#include "OpeningScreen.h"
#include "MainMenu.h"

USING_NS_CC;


//can move the sprite back to the origninal postion
//problem occurs when sprite is removed, after sprite is place on grid set it so it can't be moved
float OriginalX;
float OriginalY;
enum { T, C };

int row = 5;
int col = 5;
int CollisionGridArea[24];
int gap = 0;
int testGap = 0;
Scene* OpeningScreen::createScene()
{
	// 'scene' is an autorelease object
	auto OpeingScreenScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = OpeningScreen::create();

	// add layer as a child to scene
	OpeingScreenScene->addChild(layer);

	// return the scene
	return OpeingScreenScene;
}

bool OpeningScreen::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	for (int i = 0;i < 25;i++) {
		CollisionGridArea[i] = 0;
	}


	//adds label to the top of the screen to mark screen currently on,
	//remove later if decided they are not needed
	auto label = Label::createWithTTF("OpeningScreen", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	//adds the background used on all the scenes
	//backgrounds can be set differently on all scenes, change as needed
	auto sprite = Sprite::create("Background.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	//Adds an attack button to signal the end of the turn, currently not working
	//auto Attack = MenuItemImage::create("ArrowSelection.png", "ArrowSelection.png", CC_CALLBACK_1(OpeningScreen::PlayerAttack, this, sprite3));
	//Attack->setPosition(Vec2(origin.x + visibleSize.width - Attack->getContentSize().width, 360));
	//auto menuAttack = Menu::create(Attack, NULL);
	//menuAttack->setPosition(Vec2::ZERO);
	//this->addChild(menuAttack, 1);

	//auto Attack = Sprite::create("ArrowSelection.png");
	//Attack->setPosition(origin + Vec2(origin.x + visibleSize.width - Attack->getContentSize().width, 360));
	//auto containerForAttack = Node::create();
	//containerForAttack->addChild(Attack);
	//addChild(containerForAttack, 10);

	//////////////////////////////////
	//creates a simple grid to so where sprites need to be placed
	//needs to be decided how grid is placed and called
	//auto Grid = Sprite::create("testGrid.png");
	//Grid->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//this->addChild(Grid, 0);
	/////////////////////////////////////////////

	//////////////////////////////
	//auto TestArea = Sprite::create("AreaCollision.png");
	//TestArea->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//TestArea->setOpacity(0);
	//this->addChild(TestArea, 1);
	//////////////////////////////
	
	auto Grid = Sprite::create("GridTemplate2.png");
	Grid->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	Grid->setScale(1.5);
    this->addChild(Grid, 0);

	auto TestArea = Sprite::create("CollisionSquare.png");
	TestArea->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	TestArea->setOpacity(0);
	this->addChild(TestArea, 1);

	auto TowerArea = Sprite::create("testTowerArea.png");
	TowerArea->setPosition(Vec2(175,468));
	TowerArea->setOpacity(0);
	this->addChild(TowerArea, 1);
	
	//gap = Grid->getContentSize().width;
	//testGap = gap;
	//for (int j = 0; j < 2;j++) {
		
	//	TestArea->setPosition(Vec2((visibleSize.width / 2 + origin.x)+testGap, visibleSize.height / 2 + origin.y));
	//	TestArea->setOpacity(0);
	//	this->addChild(TestArea, 1);
	//	testGap = testGap + gap;
	//}

	//auto Grid2 = Sprite::create("GridSquare.png");
	//Grid2->setPosition(Vec2(((visibleSize.width / 2) + origin.x) + Grid->getContentSize().width, visibleSize.height / 2 + origin.y));
	//this->addChild(Grid2, 0);

	//creates a node to contain the sprites
	//might need to be changed later depending if problems occur with calling the cards
	auto containerForSprite1 = Node::create();
	
	//creates the first, second and third sprites and adds it to the container
	//sprites have to be hard coded in, try to find a shorcut way of doing it
	auto sprite1 = Sprite::create("SampleCard.png");
	sprite1->setPosition(origin + Vec2((visibleSize.width / 2)+100, (visibleSize.height / 2)-200));
	containerForSprite1->addChild(sprite1);
	addChild(containerForSprite1, 10);
	sprite1->setTag(C);

	auto sprite2 = Sprite::create("SampleCard.png");
	sprite2->setPosition(origin + Vec2(visibleSize.width / 2, (visibleSize.height / 2)-200));
	sprite2->setTag(T);
	addChild(sprite2, 20);

	auto sprite3 = Sprite::create("SampleCard.png");
	sprite3->setPosition(origin + Vec2((visibleSize.width / 2)-100, (visibleSize.height / 2)-200));
	addChild(sprite3, 20);
	sprite3->setTag(2);

	//Adds an attack button to signal the end of the turn, currently not working
	auto Attack = MenuItemImage::create("ArrowSelection.png", "ArrowSelection.png", CC_CALLBACK_1(OpeningScreen::PlayerAttack, this));
	Attack->setPosition(Vec2(origin.x + visibleSize.width - Attack->getContentSize().width, 360));
	auto menuAttack = Menu::create(Attack, NULL);
	menuAttack->setPosition(Vec2::ZERO);
	this->addChild(menuAttack, 1);


	//starts calling the listener events
	//generally need onTouchBegan and ontouchEnded, onTouchMoved is optional
	//but recommended due to seeing sprite movement
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	//gets the target currently moved, sets the original postion
	//sets the Opacity to 180
	listener1->onTouchBegan = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->getTag();
		//add in code so it doesn't touch anything within the grid
		//if (target->getPosition().y > 300 && target->getPosition().y < 600 && target->getPosition().x > 200 && target->getPosition().x < 700) {
		//
		//}
		//else 
		//{
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		OriginalX = target->getPosition().x;
		OriginalY = target->getPosition().y;
		
		log("Coordinates began... x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);


		if (rect.containsPoint(locationInNode))
		{
			log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			target->setOpacity(180);
			return true;
		}
		return false;
	   // }
	};

	//When the sprite is being moved it changes the texture to another texture
	//texture changes to a smaller sprite to be place on the grid
	listener1->onTouchMoved = [TestArea, TowerArea](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
		for (int i = 0; i < 25;i++) 
		{
		if (CollisionGridArea[i] == 0) 
		{
			TestArea->setOpacity(200);
			TowerArea->setOpacity(200);
		}
	    }
		//if (target->getTag() == C || target->getTag() == 2) 
		//{
		//	target->setTexture("testEnemy.png");
		//	if (target->getTag() == 2) 
		//	{
		//		TestArea->setOpacity(200);
		//	}
		//}
		target->setScale(2.0); 
		
	};

	//if the object is not within the set postion returns to the original postion,
	//also set the texture back to the original texture
	//if object is in the set postion the object is then placed
	listener1->onTouchEnded = [=](Touch* touch, Event* event) {
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		TestArea->setOpacity(0);
		TowerArea->setOpacity(0);
		if (target->getPosition().y > 300 && target->getPosition().y < 600 && target->getPosition().x > 200 && target->getPosition().x < 700) {
			log("sprite onTouchesEnded.. ");
			target->setOpacity(255);
			

			if (target == sprite2)
			{
				containerForSprite1->setLocalZOrder(100);
			}
			else if (target == sprite1)
			{
				containerForSprite1->setLocalZOrder(0);
			}
		}
		else
		{
			//target->setPosition(origin + Vec2((visibleSize.width / 2) + 100, (visibleSize.height / 2) - 200));
			target->setPosition(Vec2(OriginalX, OriginalY));
			target->setTexture("SampleCard.png");
			target->setScale(1.0);
			target->setOpacity(255);
			if (target == sprite2)
			{
				containerForSprite1->setLocalZOrder(100);
			}
			else if (target == sprite1)
			{
				containerForSprite1->setLocalZOrder(0);
			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);
	
	/*
	//Listener2 not working with other listerner crashes the program

	auto moveBy = MoveBy::create(2, Vec2(50, 0));
	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->setSwallowTouches(true);

	//gets the target currently moved, sets the original postion
	//sets the Opacity to 180
	listener2->onTouchBegan = [](Touch* touch, Event* event) {
		CCLOG("Listener2 on touch began");
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
	    log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
		target->setOpacity(180);
		return true;
	    }
	    return false;
		
	
	};

	listener2->onTouchEnded = [=](Touch* touch, Event* event) {
		CCLOG("Listener2 on touch ended");
		sprite1->runAction(moveBy);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, Attack);
	*/

	return true;
}

//was used for the transition from the opening to the main menu
//Opening would be set as the root scene if that was the case
void OpeningScreen::GoToTitle()
{
	auto MainMenuScene = MainMenu::createScene();
	Director::getInstance()->pushScene(MainMenuScene);
}

//adds the method for when the player wants to attack the enemy
void OpeningScreen::PlayerAttack(cocos2d::Ref* pSender)
{
	CCLOG("Testing Attack");
	//auto moveBy = MoveBy::create(2, Vec2(20, 0));
	//t->runAction(moveBy);
	CCLOG("Moving");
}
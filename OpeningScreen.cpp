#include "OpeningScreen.h"
#include "MainMenu.h"

USING_NS_CC;

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

	auto label = Label::createWithTTF("OpeningScreen", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	auto sprite = Sprite::create("Background.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	auto containerForSprite1 = Node::create();
	auto sprite1 = Sprite::create("ArrowSelection.png");
	sprite1->setPosition(origin + Vec2((visibleSize.width / 2)+100, (visibleSize.height / 2)-200));
	containerForSprite1->addChild(sprite1);
	addChild(containerForSprite1, 10);

	auto sprite2 = Sprite::create("ArrowSelection2.png");
	sprite2->setPosition(origin + Vec2(visibleSize.width / 2, (visibleSize.height / 2)-200));
	addChild(sprite2, 20);

	auto sprite3 = Sprite::create("Quit.png");
	sprite3->setPosition(origin + Vec2((visibleSize.width / 2)-100, (visibleSize.height / 2)-200));
	addChild(sprite3, 20);

	// Make sprite1 touchable
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [](Touch* touch, Event* event) {
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

	listener1->onTouchMoved = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
	};

	listener1->onTouchEnded = [=](Touch* touch, Event* event) {
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
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
			target->setPosition(origin + Vec2((visibleSize.width / 2) + 100, (visibleSize.height / 2) - 200));
			target->setOpacity(255);
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);


	return true;
}

void OpeningScreen::GoToTitle()
{
	auto MainMenuScene = MainMenu::createScene();
	Director::getInstance()->pushScene(MainMenuScene);
}
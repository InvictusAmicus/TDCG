#include "MultiPlayer.h"
#include "GameOverScreen.h"
#include "GameWonScreen.h"
#include "SimpleAudioEngine.h"
#include "Soldier.h"
#include "Tower.h"
#include "Player.h"
#include "CollisionDetection.h"
#include "Options.h"
#include "AudioEngine.h"
#include <utility>
#include <iostream>
#include <tuple>

USING_NS_CC;

int mSinglePlayGameMusic;
float mOriginalXPos, mOriginalYPos;

std::vector<Soldier*> marmy;
std::vector<Soldier*> menemyArmy;
std::vector<Tower*> mtowers;
std::vector<Tower*> menemyTowers;
std::vector<Sprite*> mspriteAnimation;
std::vector<Action*> mremoveAction;
std::vector<Sprite*> mattackSprite;

//need to set soldier to sprite

CollisionDetection mbaseGrid;


enum
{
	MoveSprite = 1,
};

#define LabelEnemyLife 12320
#define ErrorFeedback 12330
#define LabelTagLife 12340
#define LabelTagResource 12350
#define LabelTagEnemyResource 12360
#define CardsInHand 12370
#define p1Tower00 12380
#define p1Tower01 12390
#define p1Tower02 12400
#define p1Tower03 12410
#define p1Tower10 12420
#define p1Tower11 12430
#define p1Tower12 12440
#define p1Tower13 12450
#define p1Tower20 12460
#define p1Tower20 12470
#define p1Tower21 12480
#define p1Tower22 12490
#define p1Tower23 12500
#define p1Tower30 12510
#define p1Tower31 12520
#define p1Tower32 12530
#define p1Tower33 12540

#define mhandSprite1 20000
#define mhandSprite2 20001
#define mhandSprite3 20002
#define mhandSprite4 20003
#define mhandSprite5 20004
#define mhandSprite6 20005

#define p2Tower00 22380
#define p2Tower01 22390
#define p2Tower02 22400
#define p2Tower03 22410
#define p2Tower10 22420
#define p2Tower11 22430
#define p2Tower12 22440
#define p2Tower13 22450
#define p2Tower20 22460
#define p2Tower20 22470
#define p2Tower21 22480
#define p2Tower22 22490
#define p2Tower23 22500
#define p2Tower30 22510
#define p2Tower31 22520
#define p2Tower32 22530
#define p2Tower33 22540

Scene* MultiPlayer::createScene()
{
	// 'scene' is an autorelease object
	auto MultiPlayerScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MultiPlayer::create();

	// add layer as a child to scene
	MultiPlayerScene->addChild(layer);

	// return the scene
	return MultiPlayerScene;
}

bool MultiPlayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	menemyArmy.clear();
	marmy.clear();
	mtowers.clear();
	menemyTowers.clear();
	mspriteAnimation.clear();
	mremoveAction.clear();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Options gameMusic;
	CCLOG("GAME MUTE %d", gameMusic.getMusicMute());
	if (gameMusic.getMusicMute() != 1)
	{
		int V = gameMusic.getmusicVolume();
		CCLOG("gameMusic.getmusicVolume() %d", V);
		CCLOG("GAME MUTE %d", gameMusic.getMusicMute());
		mSinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("GameMusic.mp3", true, gameMusic.getMusicFloatVolume(V), nullptr);
	}
	player1 = new Player();
	player2 = new Player();
//	p = player1;
	isPlayer1 = true;

	player1->setResource(200);
	player2->setResource(200);
	//baseGrid = new CollisionDetection();
	mbaseGrid.CreateGrids();
	CCLOG("Creating Grid");

	std::string StringLife = std::to_string(player1->getLife());
	std::string StringResource = std::to_string(player1->getResource());
	std::string StringEnemyLife = std::to_string(player2->getLife());
	std::string StringEnemyResource = std::to_string(player2->getResource());


	auto label = Label::createWithTTF("MultiPlayer Game", "fonts/Marker Felt.ttf", 20);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	auto LifeLabel = Label::createWithTTF("Player 1 Health", "fonts/Marker Felt.ttf", 20);
	LifeLabel->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width - 20,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(LifeLabel, 1);

	auto LifeLabelValue = Label::createWithTTF(StringLife, "fonts/Marker Felt.ttf", 20);
	LifeLabelValue->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 50,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(LifeLabelValue, 1, LabelTagLife);

	auto ResourceLabel = Label::createWithTTF("Resource", "fonts/Marker Felt.ttf", 20);
	ResourceLabel->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 130,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(ResourceLabel, 1);

	auto ResourceLabelValue = Label::createWithTTF(StringResource, "fonts/Marker Felt.ttf", 20);
	ResourceLabelValue->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 200,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(ResourceLabelValue, 1, LabelTagResource);

	auto FeedBackLabel = Label::createWithTTF("Player 1's Turn", "fonts/Marker Felt.ttf", 36);
	FeedBackLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - 100));
	FeedBackLabel->setColor(ccc3(0, 0, 0));
	this->addChild(FeedBackLabel, 1, ErrorFeedback);

	auto EnemyLifeLabel = Label::createWithTTF("Player 2 Health", "fonts/Marker Felt.ttf", 20);
	EnemyLifeLabel->setPosition(Vec2(origin.x + 650,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(EnemyLifeLabel, 1);

	auto EnemyLifeLabelValue = Label::createWithTTF(StringEnemyLife, "fonts/Marker Felt.ttf", 20);
	EnemyLifeLabelValue->setPosition(Vec2(origin.x + (EnemyLifeLabel->getContentSize().width + 620),
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(EnemyLifeLabelValue, 1, LabelEnemyLife);

	auto EnemyResourceLabel = Label::createWithTTF("Resource", "fonts/Marker Felt.ttf", 20);
	EnemyResourceLabel->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 700,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(EnemyResourceLabel, 1);

	auto EnemyResourceLabelValue = Label::createWithTTF(StringEnemyResource, "fonts/Marker Felt.ttf", 20);
	EnemyResourceLabelValue->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 770,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(EnemyResourceLabelValue, 1, LabelTagEnemyResource);

	auto BackgroundSprite = Sprite::create("Background.png");
	BackgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(BackgroundSprite, 0);

	auto EndTurn = MenuItemImage::create("EndTurn.png", "EndTurn.png", CC_CALLBACK_1(MultiPlayer::EndRoundTurn, this));
	EndTurn->setPosition(Vec2(origin.x + visibleSize.width - EndTurn->getContentSize().width, 70));
	auto menu = Menu::create(EndTurn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto Grid = Sprite::create("GridTemplate2.png");
	Grid->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	Grid->setScale(1.5);
	this->addChild(Grid, 0);

	/////////////////////////////////////////////////////////////////////////////////////
	////Tower Area

	//X-(175, 250, 326, 401)
	//Y-(468, 395, 321, 246)

	auto TowerArea00 = Sprite::create("testTowerArea.png");
	TowerArea00->setPosition(Vec2(175, 468));
	TowerArea00->setOpacity(0);
	this->addChild(TowerArea00, 1, p1Tower00);

	auto TowerArea01 = Sprite::create("testTowerArea.png");
	TowerArea01->setPosition(Vec2(175, 395));
	TowerArea01->setOpacity(0);
	this->addChild(TowerArea01, 1, p1Tower01);

	auto TowerArea02 = Sprite::create("testTowerArea.png");
	TowerArea02->setPosition(Vec2(175, 321));
	TowerArea02->setOpacity(0);
	this->addChild(TowerArea02, 1, p1Tower02);

	auto TowerArea03 = Sprite::create("testTowerArea.png");
	TowerArea03->setPosition(Vec2(175, 246));
	TowerArea03->setOpacity(0);
	this->addChild(TowerArea03, 1, p1Tower03);

	auto TowerArea10 = Sprite::create("testTowerArea.png");
	TowerArea10->setPosition(Vec2(250, 468));
	TowerArea10->setOpacity(0);
	this->addChild(TowerArea10, 1, p1Tower10);

	auto TowerArea11 = Sprite::create("testTowerArea.png");
	TowerArea11->setPosition(Vec2(250, 395));
	TowerArea11->setOpacity(0);
	this->addChild(TowerArea11, 1, p1Tower11);

	auto TowerArea12 = Sprite::create("testTowerArea.png");
	TowerArea12->setPosition(Vec2(250, 321));
	TowerArea12->setOpacity(0);
	this->addChild(TowerArea12, 1, p1Tower12);

	auto TowerArea13 = Sprite::create("testTowerArea.png");
	TowerArea13->setPosition(Vec2(250, 246));
	TowerArea13->setOpacity(0);
	this->addChild(TowerArea13, 1, p1Tower13);

	auto TowerArea20 = Sprite::create("testTowerArea.png");
	TowerArea20->setPosition(Vec2(326, 468));
	TowerArea20->setOpacity(0);
	this->addChild(TowerArea20, 1, p1Tower20);

	auto TowerArea21 = Sprite::create("testTowerArea.png");
	TowerArea21->setPosition(Vec2(326, 395));
	TowerArea21->setOpacity(0);
	this->addChild(TowerArea21, 1, p1Tower21);

	auto TowerArea22 = Sprite::create("testTowerArea.png");
	TowerArea22->setPosition(Vec2(326, 321));
	TowerArea22->setOpacity(0);
	this->addChild(TowerArea22, 1, p1Tower22);

	auto TowerArea23 = Sprite::create("testTowerArea.png");
	TowerArea23->setPosition(Vec2(326, 246));
	TowerArea23->setOpacity(0);
	this->addChild(TowerArea23, 1, p1Tower23);

	auto TowerArea30 = Sprite::create("testTowerArea.png");
	TowerArea30->setPosition(Vec2(401, 468));
	TowerArea30->setOpacity(0);
	this->addChild(TowerArea30, 1, p1Tower30);

	auto TowerArea31 = Sprite::create("testTowerArea.png");
	TowerArea31->setPosition(Vec2(401, 395));
	TowerArea31->setOpacity(0);
	this->addChild(TowerArea31, 1, p1Tower31);

	auto TowerArea32 = Sprite::create("testTowerArea.png");
	TowerArea32->setPosition(Vec2(401, 321));
	TowerArea32->setOpacity(0);
	this->addChild(TowerArea32, 1, p1Tower32);

	auto TowerArea33 = Sprite::create("testTowerArea.png");
	TowerArea33->setPosition(Vec2(401, 246));
	TowerArea33->setOpacity(0);
	this->addChild(TowerArea33, 1, p1Tower33);

	auto p2TowerArea00 = Sprite::create("testTowerArea.png");
	p2TowerArea00->setPosition(Vec2(557, 468));
	p2TowerArea00->setOpacity(0);
	this->addChild(p2TowerArea00, 1, p2Tower00);

	auto p2TowerArea01 = Sprite::create("testTowerArea.png");
	p2TowerArea01->setPosition(Vec2(557, 395));
	p2TowerArea01->setOpacity(0);
	this->addChild(p2TowerArea01, 1, p2Tower01);

	auto p2TowerArea02 = Sprite::create("testTowerArea.png");
	p2TowerArea02->setPosition(Vec2(557, 321));
	p2TowerArea02->setOpacity(0);
	this->addChild(p2TowerArea02, 1, p2Tower02);

	auto p2TowerArea03 = Sprite::create("testTowerArea.png");
	p2TowerArea03->setPosition(Vec2(557, 249));
	p2TowerArea03->setOpacity(0);
	this->addChild(p2TowerArea03, 1, p2Tower03);

	auto p2TowerArea10 = Sprite::create("testTowerArea.png");
	p2TowerArea10->setPosition(Vec2(634, 468));
	p2TowerArea10->setOpacity(0);
	this->addChild(p2TowerArea10, 1, p2Tower10);

	auto p2TowerArea11 = Sprite::create("testTowerArea.png");
	p2TowerArea11->setPosition(Vec2(634, 395));
	p2TowerArea11->setOpacity(0);
	this->addChild(p2TowerArea11, 1, p2Tower11);

	auto p2TowerArea12 = Sprite::create("testTowerArea.png");
	p2TowerArea12->setPosition(Vec2(634, 321));
	p2TowerArea12->setOpacity(0);
	this->addChild(p2TowerArea12, 1, p2Tower12);

	auto p2TowerArea13 = Sprite::create("testTowerArea.png");
	p2TowerArea13->setPosition(Vec2(634, 249));
	p2TowerArea13->setOpacity(0);
	this->addChild(p2TowerArea13, 1, p2Tower13);

	auto p2TowerArea20 = Sprite::create("testTowerArea.png");
	p2TowerArea20->setPosition(Vec2(711, 468));
	p2TowerArea20->setOpacity(0);
	this->addChild(p2TowerArea20, 1, p2Tower20);

	auto p2TowerArea21 = Sprite::create("testTowerArea.png");
	p2TowerArea21->setPosition(Vec2(711, 395));
	p2TowerArea21->setOpacity(0);
	this->addChild(p2TowerArea21, 1, p2Tower21);

	auto p2TowerArea22 = Sprite::create("testTowerArea.png");
	p2TowerArea22->setPosition(Vec2(711, 321));
	p2TowerArea22->setOpacity(0);
	this->addChild(p2TowerArea22, 1, p2Tower22);

	auto p2TowerArea23 = Sprite::create("testTowerArea.png");
	p2TowerArea23->setPosition(Vec2(711, 249));
	p2TowerArea23->setOpacity(0);
	this->addChild(p2TowerArea23, 1, p2Tower23);

	auto p2TowerArea30 = Sprite::create("testTowerArea.png");
	p2TowerArea30->setPosition(Vec2(787, 468));
	p2TowerArea30->setOpacity(0);
	this->addChild(p2TowerArea30, 1, p2Tower30);

	auto p2TowerArea31 = Sprite::create("testTowerArea.png");
	p2TowerArea31->setPosition(Vec2(787, 395));
	p2TowerArea31->setOpacity(0);
	this->addChild(p2TowerArea31, 1, p2Tower31);

	auto p2TowerArea32 = Sprite::create("testTowerArea.png");
	p2TowerArea32->setPosition(Vec2(787, 321));
	p2TowerArea32->setOpacity(0);
	this->addChild(p2TowerArea32, 1, p2Tower32);

	auto p2TowerArea33 = Sprite::create("testTowerArea.png");
	p2TowerArea33->setPosition(Vec2(787, 249));
	p2TowerArea33->setOpacity(0);
	this->addChild(p2TowerArea33, 1, p2Tower33);

	this->schedule(schedule_selector(MultiPlayer::SpriteRemove), 1.0f);
	this->scheduleUpdate();

	displayHand(player1);
	return true;
}

void MultiPlayer::returnToTitle(cocos2d::Ref* pSender)
{
	Director::getInstance()->popToRootScene();
}

void MultiPlayer::LastPage(cocos2d::Ref* pSender)
{
	auto GameOverScene = GameOverScreen::createScene();
	Director::getInstance()->pushScene(GameOverScene);
}

void MultiPlayer::GameState()
{
	if (player1->getLife() <= 0)
	{
		MultiPlayer::WonGame();
	}
	else if (player2->getLife() <= 0)
	{
		MultiPlayer::LostGame();
	}
}

void MultiPlayer::WonGame()
{
	player1->reset();
	player2->reset();
	//	delete baseGrid;
	mspriteAnimation.clear();
	mremoveAction.clear();

	cocos2d::experimental::AudioEngine::stopAll();

	auto GameWonScene = GameWonScreen::createScene();
	Director::getInstance()->pushScene(GameWonScene);
}

void MultiPlayer::LostGame()
{
	player1->reset();
	player2->reset();
	//	delete baseGrid;
	mspriteAnimation.clear();
	mremoveAction.clear();

	cocos2d::experimental::AudioEngine::stopAll();

	auto GameOverScene = GameOverScreen::createScene();
	Director::getInstance()->pushScene(GameOverScene);
}

void MultiPlayer::EndRoundTurn(cocos2d::Ref* pSender)
{
	int r, t;
	bool hasAttacked = false;
	CollisionDetection moveForward;
	if (isPlayer1)
	{
		for (int i = 0; (unsigned)i < marmy.size(); i++)
		{
			r = marmy.at(i)->getPositionX();
			t = marmy.at(i)->getPositionY();

			if ((marmy.at(i)->getPositionX()) == 9)
			{
				player2->setLife(40);
				GameState();

				CCLOG("CHECKING AUDIO");
				Options EffectsMusic;
				if (EffectsMusic.getEffectsMute() != 1) {
					int V = EffectsMusic.EffectsVolume();
					CCLOG("gameMusic.getmusicVolume() %d", V);
					mSinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("WallAttack.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
				}

				std::string StringEnemyLife = std::to_string(player2->getLife());
				CCLabelBMFont* ChangeEnemyLife = (CCLabelBMFont*)getChildByTag(LabelEnemyLife);
				ChangeEnemyLife->setString(StringEnemyLife);
				moveForward.removeObject(marmy.at(i)->getPositionX(), marmy.at(i)->getPositionY());
				marmy.at(i)->getSprite()->removeFromParentAndCleanup(true);
				marmy.erase(marmy.begin() + i);
				hasAttacked = true;
				i--;
			}
			if (!hasAttacked)
			{
				if (marmy.at(i) != NULL)
				{
					if (moveForward.playerCollisionDetect(marmy.at(i)->getPositionX(),
						marmy.at(i)->getPositionY(), 'P') == 0)
					{
						if (marmy.at(i)->getSprite()->getPositionX() + 75 < 825)
						{
							auto moveBy = MoveBy::create(1, Vec2(75, 0));
							marmy.at(i)->getSprite()->runAction(moveBy);
							marmy.at(i)->setPositionX(marmy.at(i)->getPositionX() + 1);
						}
					}
					else if (moveForward.playerCollisionDetect(marmy.at(i)->getPositionX(),
						marmy.at(i)->getPositionY(), 'P') == 1)
					{
						CCLOG("CAN'T MOVE FORWARD Enemy");
						CCLOG("Current i %d :else if 1:", i);
						//call attack
						//deal damage to enemy = to attack

					}
					else if (moveForward.playerCollisionDetect(marmy.at(i)->getPositionX(),
						marmy.at(i)->getPositionY(), 'P') == 2)
					{
						CCLOG("CAN'T MOVE FORWARD Player");
						CCLOG("Current i %d :else if 2:", i);
						//Player in front
					}
				}
				CCLOG("Current i %d :End of for:  Value: %d %d", i, r, t);
			}
			//moveForward.PlayerTowerAttack();
			//moveForward.EnemyTowerAttack();
			//holding the button keeps calling the method
		}
		hasAttacked = false;
	}
	if (!isPlayer1)
	{
		for (int x = 0; (unsigned)x < menemyArmy.size(); x++)
		{
			if (x < 0)
			{
				x = 0;
			}
			int place = menemyArmy.at(x)->getPositionX();
			if ((menemyArmy.at(x)->getPositionX()) == 0)
			{
				player1->setLife(40);
				GameState();

				CCLOG("CHECKING AUDIO");
				Options EffectsMusic;
				if (EffectsMusic.getEffectsMute() != 1) {
					int V = EffectsMusic.EffectsVolume();
					CCLOG("gameMusic.getmusicVolume() %d", V);
					mSinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("WallAttack.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
				}

				moveForward.removeObject(menemyArmy.at(x)->getPositionX(), menemyArmy.at(x)->getPositionY());
				std::string StringLife = std::to_string(player1->getLife());
				CCLabelBMFont* ChangePlayerLife = (CCLabelBMFont*)getChildByTag(LabelTagLife);
				ChangePlayerLife->setString(StringLife);
				menemyArmy.at(x)->getSprite()->removeFromParentAndCleanup(true);
				//			this->removeChild(enemyArmy.at(x)->getSprite());
				menemyArmy.erase(menemyArmy.begin() + x);
				x--;
				hasAttacked = true;
			}

			if (!hasAttacked)
			{
				if (menemyArmy.at(x) != NULL)
				{
					if (moveForward.enemyCollisionDetect(menemyArmy.at(x)->getPositionX(), menemyArmy.at(x)->getPositionY(), 'E') == 0)
					{
						if (menemyArmy.at(x)->getSprite()->getPositionX() - 75 > 75)
						{
							auto moveBy = MoveBy::create(1, Vec2(-75, 0));
							menemyArmy.at(x)->getSprite()->runAction(moveBy);
							//enemyArmy.at(x)->getSprite()->setPositionX(enemyArmy.at(x)->getSprite()->getPositionX() - 75);
							menemyArmy.at(x)->setPositionX(menemyArmy.at(x)->getPositionX() - 1);
						}
					}
					else if (moveForward.enemyCollisionDetect(menemyArmy.at(x)->getPositionX(), menemyArmy.at(x)->getPositionY(), 'E') == 1)
					{
						//enemyArmy.at(x);
						//call attack
						//deal damage to enemy = to attack
						for (int y = 0; y < marmy.size(); y++)
						{
							if (menemyArmy.size() > 0) {
								if (x < 0)
								{
									x = 0;
								}
								CCLOG("X = %d", x);
								CCLOG("army.at(y)->getPositionX() %d", marmy.at(y)->getPositionX());
								CCLOG("enemyArmy.at(x)->getPositionX() - 1, %d", menemyArmy.at(x)->getPositionX() - 1);
								CCLOG("army.at(y)->getPositionY(), %d", marmy.at(y)->getPositionY());
								CCLOG("enemyArmy.at(x)->getPositionY(), %d", menemyArmy.at(x)->getPositionY());
								if (marmy.at(y)->getPositionX() == menemyArmy.at(x)->getPositionX() - 1
									&& marmy.at(y)->getPositionY() == menemyArmy.at(x)->getPositionY()) // x = -1
								{
									CCLOG("CHECKING AUDIO");
									Options EffectsMusic;
									if (EffectsMusic.getEffectsMute() != 1) {
										int V = EffectsMusic.EffectsVolume();
										CCLOG("gameMusic.getmusicVolume() %d", V);
										mSinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("SwordClash.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
									}
									////////////////////////////////////////////////////////
									//Creates a sprite in front of a player sprite which fades in and out 
									/*
									auto PlayerSwordSlash = Sprite::create("PlayerSwordAttack.png");
									PlayerSwordSlash->setPosition(Vec2(marmy.at(y)->getSprite()->getPositionX()+20, army.at(y)->getSprite()->getPositionY()));
									PlayerSwordSlash->setOpacity(0);
									this->addChild(PlayerSwordSlash, 1);

									auto EnemySwordSlash = Sprite::create("EnemySoldierAttack.png");
									EnemySwordSlash->setPosition(Vec2(marmy.at(y)->getSprite()->getPositionX()+60, army.at(y)->getSprite()->getPositionY()));
									EnemySwordSlash->setOpacity(0);
									this->addChild(EnemySwordSlash, 1);

									//running the animation actions
									auto fadeIn = FadeIn::create(0.5f);
									auto fadeOut = FadeOut::create(0.5f);

									//DelayTime *delayAction = DelayTime::create(1.0);

									//auto PlayerAttackSeq = Sequence::create(delayAction, fadeIn, fadeOut, nullptr);

									//auto EnemyAttackSeq = Sequence::create(delayAction, fadeIn, fadeOut, nullptr);
									//PlayerSwordSlash->runAction(PlayerAttackSeq);
									//EnemySwordSlash->runAction(EnemyAttackSeq);
									*/
									//////////////////////////////////////////////////
									marmy.at(y)->setHealth(menemyArmy.at(x)->getAttack());
									menemyArmy.at(x)->setHealth(marmy.at(y)->getAttack());
									if (marmy.at(y)->getHealth() <= 0)
									{
										moveForward.removeObject(marmy.at(y)->getPositionX(), marmy.at(y)->getPositionY());
										marmy.at(y)->activateAbility(player1);
										CCLabelBMFont* ChangeLife = (CCLabelBMFont*)getChildByTag(LabelTagLife);
										std::string StringLife = std::to_string(player1->getLife());
										ChangeLife->setString(StringLife);
										marmy.at(y)->getSprite()->removeFromParentAndCleanup(true);
										marmy.erase(marmy.begin() + y);
										y--;
										player2->setResource(50);
									}
									if (menemyArmy.at(x)->getHealth() <= 0)
									{
										moveForward.removeObject(menemyArmy.at(x)->getPositionX(), menemyArmy.at(x)->getPositionY());
										menemyArmy.at(x)->getSprite()->removeFromParentAndCleanup(true);
										menemyArmy.erase(menemyArmy.begin() + x);
										x--;
										player1->setResource(50);
									}
								}
							}
						}
					}
					else if (moveForward.enemyCollisionDetect(menemyArmy.at(x)->getPositionX(), menemyArmy.at(x)->getPositionY(), 'E') == 2)
					{
						//Player in front
					}
				}
			}
			//x++;
			hasAttacked = false;
		}
	}
	//soldier movement above
	//tower movement below
	bool hasShot = false;

	CCLOG("before TOWER attack statement");
	if (isPlayer1)
	{
		for (int o = 0; o < menemyTowers.size(); o++)
		{
			CCLOG("TOWER attack statement");
			CCLOG("MOVE, r = %d, t = %d", menemyTowers.at(o)->getPositionX(), menemyTowers.at(o)->getPositionY());

			if (moveForward.enemyTowerAttacks(menemyTowers.at(o)->getPositionX(), menemyTowers.at(o)->getPositionY()) == 0)
			{
				//template code for towers shooting 
				//CCLOG("enemy if Zero");
				//animation for shooting
				for (int z = 0; z < marmy.size(); z++)
				{
					//CCLOG("Start of Zero");
					//CCLOG("army x: %d", army.at(p)->getPositionX());
					//CCLOG("tower x: %d", enemyTowers.at(o)->getPositionX() + 5);
					//CCLOG("army y: %d", army.at(p)->getPositionY());
					//CCLOG("tower y: %d", enemyTowers.at(o)->getPositionY());
					if (marmy.at(z)->getPositionX() == menemyTowers.at(o)->getPositionX() + 5
						&& marmy.at(z)->getPositionY() == menemyTowers.at(o)->getPositionY())
					{

						CCLOG("CHECKING AUDIO");
						Options EffectsMusic;
						if (EffectsMusic.getEffectsMute() != 1) {
							int V = EffectsMusic.EffectsVolume();
							CCLOG("gameMusic.getmusicVolume() %d", V);
							mSinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
						}

						//0-0
						//auto Bullet = Sprite::create("TowerBullet.png");
						//Bullet->setPosition(Vec2(100, 500));
						//this->addChild(Bullet, 1);

						auto Bullet = Sprite::create("TowerBullet.png");
						mspriteAnimation.push_back(Bullet);
						int BulletX = moveForward.enemyTowerBulletX(menemyTowers.at(o)->getPositionX());
						int BulletY = moveForward.TowerBulletY(menemyTowers.at(o)->getPositionY());
						Bullet->setPosition(Vec2(BulletX, BulletY));
						this->addChild(Bullet, 1);
						auto moveTo = MoveTo::create(2.0, Vec2(BulletX - 40, BulletY + 35));
						auto fade = FadeOut::create(0.1f);
						auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
						mremoveAction.push_back(runAction(BulletAttack));
						//Bullet->runAction(moveTo);
						Bullet->runAction(mremoveAction.back());


						//CCLOG("1 if");
						hasShot = true;
						marmy.at(z)->setHealth(menemyTowers.at(o)->getDamage());
						if (marmy.at(z)->getHealth() <= 0)
						{
							//CCLOG("2 if");
							moveForward.removeObject(marmy.at(z)->getPositionX(), marmy.at(z)->getPositionY());
							marmy.at(z)->activateAbility(player1);
							CCLabelBMFont* ChangeLife = (CCLabelBMFont*)getChildByTag(LabelTagLife);
							std::string StringLife = std::to_string(player1->getLife());
							ChangeLife->setString(StringLife);

							marmy.at(z)->getSprite()->removeFromParentAndCleanup(true);
							marmy.erase(marmy.begin() + z);
							player2->setResource(50);
							z--;
							CCLOG("PLAYER SHOT");
						}
					}
				}
			}
			//CCLOG("before ONE");
			if (moveForward.enemyTowerAttacks(menemyTowers.at(o)->getPositionX(), menemyTowers.at(o)->getPositionY()) == 1)
			{
				//template code for towers shooting 

				//animation for shooting

				//CCLOG("enemy Start of ONE");
				for (int z = 0; z < marmy.size(); z++)
				{
					//CCLOG("enemy for ONE");
					//CCLOG("army x: %d", army.at(p)->getPositionX());
					//CCLOG("tower x: %d", enemyTowers.at(o)->getPositionX() + 5);
					//CCLOG("army y: %d", army.at(p)->getPositionY());
					//CCLOG("tower y: %d", enemyTowers.at(o)->getPositionY());

					if (marmy.at(z)->getPositionX() == menemyTowers.at(o)->getPositionX() + 5
						&& marmy.at(z)->getPositionY() == menemyTowers.at(o)->getPositionY() + 1)
					{
						CCLOG("CHECKING AUDIO");
						Options EffectsMusic;
						if (EffectsMusic.getEffectsMute() != 1) {
							int V = EffectsMusic.EffectsVolume();
							CCLOG("gameMusic.getmusicVolume() %d", V);
							mSinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
						}

						//0-1
						//auto Bullet = Sprite::create("TowerBullet.png");
						//Bullet->setPosition(Vec2(100, 500));
						//this->addChild(Bullet, 1);
						auto Bullet = Sprite::create("TowerBullet.png");
						mspriteAnimation.push_back(Bullet);
						int BulletX = moveForward.enemyTowerBulletX(menemyTowers.at(o)->getPositionX());
						int BulletY = moveForward.TowerBulletY(menemyTowers.at(o)->getPositionY());
						Bullet->setPosition(Vec2(BulletX, BulletY));
						this->addChild(Bullet, 1);
						auto moveTo = MoveTo::create(2.0, Vec2(BulletX - 40, BulletY - 35));
						auto fade = FadeOut::create(0.1f);
						auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
						mremoveAction.push_back(runAction(BulletAttack));
						//Bullet->runAction(moveTo);
						Bullet->runAction(mremoveAction.back());


						//CCLOG("1 if");
						hasShot = true;
						//army.at(p)->setHealth(enemyTowers.at(o)->getDamage());
						//CCLOG("HEALTH, %d", army.at(p)->getHealth());
						//CCLOG("Damage, %d", enemyTowers.at(o)->getDamage());
						marmy.at(z)->setHealth(menemyTowers.at(o)->getDamage());
						if (marmy.at(z)->getHealth() <= 0)
						{
							//CCLOG("2 if");
							moveForward.removeObject(marmy.at(z)->getPositionX(), marmy.at(z)->getPositionY());
							marmy.at(z)->activateAbility(player1);
							CCLabelBMFont* ChangeLife = (CCLabelBMFont*)getChildByTag(LabelTagLife);
							std::string StringLife = std::to_string(player1->getLife());
							ChangeLife->setString(StringLife);
							marmy.at(z)->getSprite()->removeFromParentAndCleanup(true);
							marmy.erase(marmy.begin() + z);
							player2->setResource(50);
							z--;
							CCLOG("PLAYER SHOT");
						}
					}
				}
			}

			if (moveForward.enemyTowerAttacks(menemyTowers.at(o)->getPositionX(), menemyTowers.at(o)->getPositionY()) == 2)
			{//template code for towers shooting 
			 //CCLOG("enemy Start of Two");
			 //animation for shooting
				for (int z = 0; z < marmy.size(); z++)
				{
					//CCLOG("enemy for TWO");
					//CCLOG("army x: %d", army.at(p)->getPositionX());
					//CCLOG("tower x: %d", enemyTowers.at(o)->getPositionX() + 6);
					//CCLOG("army y: %d", army.at(p)->getPositionY());
					//CCLOG("tower y: %d", enemyTowers.at(o)->getPositionY());
					if (marmy.at(z)->getPositionX() == menemyTowers.at(o)->getPositionX() + 6
						&& marmy.at(z)->getPositionY() == menemyTowers.at(o)->getPositionY())
					{
						CCLOG("CHECKING AUDIO");
						Options EffectsMusic;
						if (EffectsMusic.getEffectsMute() != 1) {
							int V = EffectsMusic.EffectsVolume();
							CCLOG("gameMusic.getmusicVolume() %d", V);
							mSinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
						}

						//1-0
						//auto Bullet = Sprite::create("TowerBullet.png");
						//Bullet->setPosition(Vec2(100, 500));
						//this->addChild(Bullet, 1);
						auto Bullet = Sprite::create("TowerBullet.png");
						mspriteAnimation.push_back(Bullet);
						int BulletX = moveForward.enemyTowerBulletX(menemyTowers.at(o)->getPositionX());
						int BulletY = moveForward.TowerBulletY(menemyTowers.at(o)->getPositionY());
						Bullet->setPosition(Vec2(BulletX, BulletY));
						this->addChild(Bullet, 1);
						auto moveTo = MoveTo::create(2.0, Vec2(BulletX + 35, BulletY + 35));
						auto fade = FadeOut::create(0.1f);
						auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
						mremoveAction.push_back(runAction(BulletAttack));
						//Bullet->runAction(moveTo);
						Bullet->runAction(mremoveAction.back());


						hasShot = true;
						marmy.at(z)->setHealth(menemyTowers.at(o)->getDamage());
						if (marmy.at(z)->getHealth() <= 0)
						{
							moveForward.removeObject(marmy.at(z)->getPositionX(), marmy.at(z)->getPositionY());
							marmy.at(z)->activateAbility(player1);
							CCLabelBMFont* ChangeLife = (CCLabelBMFont*)getChildByTag(LabelTagLife);
							std::string StringLife = std::to_string(player1->getLife());
							ChangeLife->setString(StringLife);
							marmy.at(z)->getSprite()->removeFromParentAndCleanup(true);
							marmy.erase(marmy.begin() + z);
							player2->setResource(50);
							z--;
							CCLOG("PLAYER SHOT");
						}
					}
				}
			}

			if (moveForward.enemyTowerAttacks(menemyTowers.at(o)->getPositionX(), menemyTowers.at(o)->getPositionY()) == 3)
			{
				//template code for towers shooting 
				//CCLOG("enemy Start of three");
				//animation for shooting
				for (int z = 0; z < marmy.size(); z++)
				{
					if (marmy.at(z)->getPositionX() == menemyTowers.at(o)->getPositionX() + 6
						&& marmy.at(z)->getPositionY() == menemyTowers.at(o)->getPositionY() + 1)
					{
						CCLOG("CHECKING AUDIO");
						Options EffectsMusic;
						if (EffectsMusic.getEffectsMute() != 1) {
							int V = EffectsMusic.EffectsVolume();
							CCLOG("gameMusic.getmusicVolume() %d", V);
							mSinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
						}

						//1-1
						//auto Bullet = Sprite::create("TowerBullet.png");
						//Bullet->setPosition(Vec2(100, 500));
						//this->addChild(Bullet, 1);
						auto Bullet = Sprite::create("TowerBullet.png");
						mspriteAnimation.push_back(Bullet);
						int BulletX = moveForward.enemyTowerBulletX(menemyTowers.at(o)->getPositionX());
						int BulletY = moveForward.TowerBulletY(menemyTowers.at(o)->getPositionY());
						Bullet->setPosition(Vec2(BulletX, BulletY));
						this->addChild(Bullet, 1);
						auto moveTo = MoveTo::create(2.0, Vec2(BulletX + 35, BulletY - 35));
						auto fade = FadeOut::create(0.1f);
						auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
						mremoveAction.push_back(runAction(BulletAttack));
						//Bullet->runAction(moveTo);
						Bullet->runAction(mremoveAction.back());

						hasShot = true;
						marmy.at(z)->setHealth(menemyTowers.at(o)->getDamage());
						if (marmy.at(z)->getHealth() <= 0)
						{
							moveForward.removeObject(marmy.at(z)->getPositionX(), marmy.at(z)->getPositionY());
							marmy.at(z)->getSprite()->removeFromParentAndCleanup(true);
							marmy.erase(marmy.begin() + z);
							player2->setResource(50);
							z--;
							CCLOG("PLAYER SHOT");
						}
					}
				}

			}
			hasShot = false;
		}
	}
	if (!isPlayer1)
	{
		for (int q = 0; q < mtowers.size(); q++)
		{
			CCLOG("TOWER attack statement");
			CCLOG("MOVE, r = %d, t = %d", mtowers.at(q)->getPositionX(), mtowers.at(q)->getPositionY());

			if (moveForward.towerAttacks(mtowers.at(q)->getPositionX(), mtowers.at(q)->getPositionY()) == 0)
			{
				//template code for towers shooting 
				//CCLOG("player if Zero");
				//animation for shooting
				for (int r = 0; r < menemyArmy.size(); r++)
				{
					//CCLOG("player Start of Zero");
					//CCLOG("army x: %d", army.at(p)->getPositionX());
					//CCLOG("tower x: %d", enemyTowers.at(o)->getPositionX() + 5);
					//CCLOG("army y: %d", army.at(p)->getPositionY());
					//CCLOG("tower y: %d", enemyTowers.at(o)->getPositionY());
					if (menemyArmy.at(r)->getPositionX() == mtowers.at(q)->getPositionX()
						&& menemyArmy.at(r)->getPositionY() == mtowers.at(q)->getPositionY())
					{
						CCLOG("CHECKING AUDIO");
						Options EffectsMusic;
						if (EffectsMusic.getEffectsMute() != 1) {
							int V = EffectsMusic.EffectsVolume();
							CCLOG("gameMusic.getmusicVolume() %d", V);
							mSinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
						}

						//CCLOG("1 if");
						hasShot = true;

						if (hasShot == true)
						{
							//0-0
							auto Bullet = Sprite::create("TowerBullet.png");
							mspriteAnimation.push_back(Bullet);
							int BulletX = moveForward.playerTowerBulletX(mtowers.at(q)->getPositionX());
							int BulletY = moveForward.TowerBulletY(mtowers.at(q)->getPositionY());
							Bullet->setPosition(Vec2(BulletX, BulletY));
							this->addChild(Bullet, 1);
							auto moveTo = MoveTo::create(2.0, Vec2(BulletX - 40, BulletY + 35));
							auto fade = FadeOut::create(0.1f);
							auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
							mremoveAction.push_back(runAction(BulletAttack));
							//Bullet->runAction(moveTo);
							Bullet->runAction(mremoveAction.back());
						}


						menemyArmy.at(r)->setHealth(mtowers.at(q)->getDamage());
						if (menemyArmy.at(r)->getHealth() <= 0)
						{
							//CCLOG("2 if");
							moveForward.removeObject(menemyArmy.at(r)->getPositionX(), menemyArmy.at(r)->getPositionY());
							menemyArmy.at(r)->getSprite()->removeFromParentAndCleanup(true);
							menemyArmy.erase(menemyArmy.begin() + r);
							player1->setResource(50);
							r--;
							CCLOG("PLAYER SHOT");
						}
					}
				}
			}
			//CCLOG("player before ONE");
			if (moveForward.towerAttacks(mtowers.at(q)->getPositionX(), mtowers.at(q)->getPositionY()) == 1)
			{
				for (int r = 0; r < menemyArmy.size(); r++)
				{
					//CCLOG("player Start of One");
					//CCLOG("army x: %d", army.at(p)->getPositionX());
					//CCLOG("tower x: %d", enemyTowers.at(o)->getPositionX() + 5);
					//CCLOG("army y: %d", army.at(p)->getPositionY());
					//CCLOG("tower y: %d", enemyTowers.at(o)->getPositionY());
					if (menemyArmy.at(r)->getPositionX() == mtowers.at(q)->getPositionX()
						&& menemyArmy.at(r)->getPositionY() == mtowers.at(q)->getPositionY() + 1)
					{
						CCLOG("CHECKING AUDIO");
						Options EffectsMusic;
						if (EffectsMusic.getEffectsMute() != 1) {
							int V = EffectsMusic.EffectsVolume();
							CCLOG("gameMusic.getmusicVolume() %d", V);
							mSinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
						}

						//CCLOG("1 if");
						hasShot = true;

						if (hasShot == true)
						{
							//0-1
							auto Bullet = Sprite::create("TowerBullet.png");
							mspriteAnimation.push_back(Bullet);
							int BulletX = moveForward.playerTowerBulletX(mtowers.at(q)->getPositionX());
							int BulletY = moveForward.TowerBulletY(mtowers.at(q)->getPositionY());
							Bullet->setPosition(Vec2(BulletX, BulletY));
							this->addChild(Bullet, 1);
							auto moveTo = MoveTo::create(2.0, Vec2(BulletX - 40, BulletY - 35));
							auto fade = FadeOut::create(0.1f);
							auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
							mremoveAction.push_back(runAction(BulletAttack));
							//Bullet->runAction(moveTo);
							Bullet->runAction(mremoveAction.back());
						}


						menemyArmy.at(r)->setHealth(mtowers.at(q)->getDamage());
						if (menemyArmy.at(r)->getHealth() <= 0)
						{
							//CCLOG("2 if");
							moveForward.removeObject(menemyArmy.at(r)->getPositionX(), menemyArmy.at(r)->getPositionY());
							menemyArmy.at(r)->getSprite()->removeFromParentAndCleanup(true);
							menemyArmy.erase(menemyArmy.begin() + r);
							player1->setResource(50);
							r--;
							CCLOG("PLAYER SHOT");
						}
					}
				}
			}

			if (moveForward.towerAttacks(mtowers.at(q)->getPositionX(), mtowers.at(q)->getPositionY()) == 2)
			{//template code for towers shooting 
			 //CCLOG("player Start of Two");
			 //animation for shooting
				for (int r = 0; r < menemyArmy.size(); r++)
				{
					//CCLOG("Player Start of Two");
					//CCLOG("army x: %d", army.at(p)->getPositionX());
					//CCLOG("tower x: %d", enemyTowers.at(o)->getPositionX() + 5);
					//CCLOG("army y: %d", army.at(p)->getPositionY());
					//CCLOG("tower y: %d", enemyTowers.at(o)->getPositionY());
					if (menemyArmy.at(r)->getPositionX() == mtowers.at(q)->getPositionX() + 1
						&& menemyArmy.at(r)->getPositionY() == mtowers.at(q)->getPositionY())
					{
						CCLOG("CHECKING AUDIO");
						Options EffectsMusic;
						if (EffectsMusic.getEffectsMute() != 1) {
							int V = EffectsMusic.EffectsVolume();
							CCLOG("gameMusic.getmusicVolume() %d", V);
							mSinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
						}

						//CCLOG("1 if");
						hasShot = true;

						if (hasShot == true)
						{
							//1-0
							auto Bullet = Sprite::create("TowerBullet.png");
							mspriteAnimation.push_back(Bullet);
							int BulletX = moveForward.playerTowerBulletX(mtowers.at(q)->getPositionX());
							int BulletY = moveForward.TowerBulletY(mtowers.at(q)->getPositionY());
							Bullet->setPosition(Vec2(BulletX, BulletY));
							this->addChild(Bullet, 1);
							auto moveTo = MoveTo::create(2.0, Vec2(BulletX + 35, BulletY + 35));
							auto fade = FadeOut::create(0.1f);
							auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
							mremoveAction.push_back(runAction(BulletAttack));
							//Bullet->runAction(moveTo);
							Bullet->runAction(mremoveAction.back());
						}

						menemyArmy.at(r)->setHealth(mtowers.at(q)->getDamage());
						if (menemyArmy.at(r)->getHealth() <= 0)
						{
							//CCLOG("2 if");
							moveForward.removeObject(menemyArmy.at(r)->getPositionX(), menemyArmy.at(r)->getPositionY());
							menemyArmy.at(r)->getSprite()->removeFromParentAndCleanup(true);
							menemyArmy.erase(menemyArmy.begin() + r);
							player1->setResource(50);
							r--;
							CCLOG("PLAYER SHOT");
						}
					}
				}
			}

			if (moveForward.towerAttacks(mtowers.at(q)->getPositionX(), mtowers.at(q)->getPositionY()) == 3)
			{
				//template code for towers shooting 
				//CCLOG("player Start of three");
				//animation for shooting
				for (int r = 0; r < menemyArmy.size(); r++)
				{
					//CCLOG("player Start of three");
					//CCLOG("army x: %d", army.at(p)->getPositionX());
					//CCLOG("tower x: %d", enemyTowers.at(o)->getPositionX() + 5);
					//CCLOG("army y: %d", army.at(p)->getPositionY());
					//CCLOG("tower y: %d", enemyTowers.at(o)->getPositionY());
					if (menemyArmy.at(r)->getPositionX() == mtowers.at(q)->getPositionX() + 1
						&& menemyArmy.at(r)->getPositionY() == mtowers.at(q)->getPositionY() + 1)
					{
						CCLOG("CHECKING AUDIO");
						Options EffectsMusic;
						if (EffectsMusic.getEffectsMute() != 1) {
							int V = EffectsMusic.EffectsVolume();
							CCLOG("gameMusic.getmusicVolume() %d", V);
							mSinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
						}

						//CCLOG("1 if");
						hasShot = true;

						if (hasShot == true)
						{
							//1-1
							auto Bullet = Sprite::create("TowerBullet.png");
							mspriteAnimation.push_back(Bullet);
							int BulletX = moveForward.playerTowerBulletX(mtowers.at(q)->getPositionX());
							int BulletY = moveForward.TowerBulletY(mtowers.at(q)->getPositionY());
							Bullet->setPosition(Vec2(BulletX, BulletY));
							this->addChild(Bullet, 1);
							auto moveTo = MoveTo::create(2.0, Vec2(BulletX + 35, BulletY - 35));
							auto fade = FadeOut::create(0.1f);
							auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
							mremoveAction.push_back(runAction(BulletAttack));
							//Bullet->runAction(moveTo);
							Bullet->runAction(mremoveAction.back());
						}

						menemyArmy.at(r)->setHealth(mtowers.at(q)->getDamage());
						if (menemyArmy.at(r)->getHealth() <= 0)
						{
							//CCLOG("2 if");
							moveForward.removeObject(menemyArmy.at(r)->getPositionX(), menemyArmy.at(r)->getPositionY());
							menemyArmy.at(r)->getSprite()->removeFromParentAndCleanup(true);
							menemyArmy.erase(menemyArmy.begin() + r);
							player1->setResource(50);
							r--;
							CCLOG("PLAYER SHOT");
						}
					}
				}

			}
			hasShot = false;
		}
	}
	startTurn();

	CCLOG("Test For End Turn");
//	enemyAI();

}

void MultiPlayer::startTurn()
{
	/*
	for (int q = 0; q < removeAction.size(); q++)
	{
	if (removeAction.at(q)->isDone())
	{
	spriteAnimation.at(q)->removeFromParentAndCleanup(true);
	spriteAnimation.erase(spriteAnimation.begin()+q);
	removeAction.erase(removeAction.begin() + q);
	}
	}
	*/
	if (isPlayer1)
	{
		player2->setResource(100);
		isPlayer1 = false;

		std::string s = std::to_string(player2->getResource());
		CCLabelBMFont* ChangeResource = (CCLabelBMFont*)getChildByTag(LabelTagEnemyResource);
		ChangeResource->setString(s);

		std::string t = "Player 2's Turn";
		CCLabelBMFont* turn = (CCLabelBMFont*)getChildByTag(ErrorFeedback);
		turn->setString(t);
		
		player2->drawCard();
		displayHand(player2);
	}
	else
	{
		player1->setResource(100);
		isPlayer1 = true;
		std::string s = std::to_string(player1->getResource());
		
		std::string t = "Player 1's Turn";
		CCLabelBMFont* ChangeResource = (CCLabelBMFont*)getChildByTag(ErrorFeedback);
		ChangeResource->setString(t);
		
		CCLabelBMFont* turn = (CCLabelBMFont*)getChildByTag(LabelTagResource);
		turn->setString(s);
		player1->drawCard();
		displayHand(player1);
	}
}

void MultiPlayer::SpriteRemove(float ct)
{
	if (mremoveAction.size() != 0)
	{
		for (int q = 0; q < mremoveAction.size(); q++)
		{
			if (mremoveAction.at(q)->isDone())
			{
				mspriteAnimation.at(q)->removeFromParentAndCleanup(true);
				mspriteAnimation.erase(mspriteAnimation.begin() + q);
				mremoveAction.erase(mremoveAction.begin() + q);
			}
		}
	}
}

void MultiPlayer::displayHand(Player* p)
{
	CCLOG("DECK SIZE %d", p->getDeckSize());
	for (int i = 0; i < 6; i++)
	{
		CCLOG("Card No: %d", i);
		if (getChildByTag(mhandSprite1 + i) != NULL)
		{
			getChildByTag(mhandSprite1 + i)->removeFromParentAndCleanup(true);
		}
	}

	int i;
	for (i = 0; (unsigned)i < p->getHandSize(); i++)
	{
		//sprite = p->getCardInHand(i)->getSprite();
		//sprite->setPosition(Vec2(100 + (i * 100), 50));
		auto sprite = cocos2d::Sprite::create(p->getCardInHand(i)->getSpriteName());
		//sprite->setPosition(Vec2(100 + (i * 100), 50));
		this->addChild(sprite, 1, mhandSprite1 + i);

		//		if (getChildByTag(handSprite1 + i) != NULL)
		//		{
		this->getChildByTag(mhandSprite1 + i)->setPosition(Vec2(100 + (i * 100), 80));
		CCLOG("TAG %d", (mhandSprite1 + i));
		//		}
	}

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [=](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		
		if (target->getPosition().x >100 && target->getPosition().x <859 && target->getPosition().y > 178 && target->getPosition().y <544)
		{
			return false;
		}
		else
		{
			Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());

			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);
			mOriginalXPos = target->getPosition().x;
			mOriginalYPos = target->getPosition().y;

			if (rect.containsPoint(locationInNode))
			{
				target->setOpacity(180);
				target->setPositionX(touch->getStartLocation().x);
				target->setPositionY(touch->getStartLocation().y);

				return true;
			}
			return false;
		}
	};

	listener1->onTouchMoved = [=](Touch* touch, Event* event)
	{
		CollisionDetection CheckT;
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
		int tag = target->getTag();
		char type;
		if (tag == 20000)
		{
			type = p->getCardInHand(0)->getType();
		}
		else if (tag == 20001)
		{
			type = p->getCardInHand(1)->getType();
		}
		else if (tag == 20002)
		{
			type = p->getCardInHand(2)->getType();
		}
		else if (tag == 20003)
		{
			type = p->getCardInHand(3)->getType();
		}
		else if (tag == 20004)
		{
			type = p->getCardInHand(4)->getType();
		}
		else if (tag == 20005)
		{
			type = p->getCardInHand(5)->getType();
		}
		if (type == 's')
		{
			target->setTexture("testEnemy.png");
		}
		else if (type == 't')
		{
			target->setTexture("SampleTower.png");
			
			if (isPlayer1)
			{
				if (CheckT.CheckTower(0, 0) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid00 = (Sprite*)getChildByTag(p1Tower00);
					TowerGrid00->setOpacity(200);
				}
				if (CheckT.CheckTower(0, 1) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid01 = (Sprite*)getChildByTag(p1Tower01);
					TowerGrid01->setOpacity(200);
				}
				if (CheckT.CheckTower(0, 2) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid02 = (Sprite*)getChildByTag(p1Tower02);
					TowerGrid02->setOpacity(200);
				}
				if (CheckT.CheckTower(0, 3) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid03 = (Sprite*)getChildByTag(p1Tower03);
					TowerGrid03->setOpacity(200);
				}
				if (CheckT.CheckTower(1, 0) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid10 = (Sprite*)getChildByTag(p1Tower10);
					TowerGrid10->setOpacity(200);
				}
				if (CheckT.CheckTower(1, 1) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid11 = (Sprite*)getChildByTag(p1Tower11);
					TowerGrid11->setOpacity(200);
				}
				if (CheckT.CheckTower(1, 2) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid12 = (Sprite*)getChildByTag(p1Tower12);
					TowerGrid12->setOpacity(200);
				}
				if (CheckT.CheckTower(1, 3) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid13 = (Sprite*)getChildByTag(p1Tower13);
					TowerGrid13->setOpacity(200);
				}
				if (CheckT.CheckTower(2, 0) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid20 = (Sprite*)getChildByTag(p1Tower20);
					TowerGrid20->setOpacity(200);
				}
				if (CheckT.CheckTower(2, 1) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid21 = (Sprite*)getChildByTag(p1Tower21);
					TowerGrid21->setOpacity(200);
				}
				if (CheckT.CheckTower(2, 2) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid22 = (Sprite*)getChildByTag(p1Tower22);
					TowerGrid22->setOpacity(200);
				}
				if (CheckT.CheckTower(2, 3) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid23 = (Sprite*)getChildByTag(p1Tower23);
					TowerGrid23->setOpacity(200);
				}
				if (CheckT.CheckTower(3, 0) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid30 = (Sprite*)getChildByTag(p1Tower30);
					TowerGrid30->setOpacity(200);
				}
				if (CheckT.CheckTower(3, 1) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid31 = (Sprite*)getChildByTag(p1Tower31);
					TowerGrid31->setOpacity(200);
				}
				if (CheckT.CheckTower(3, 2) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid32 = (Sprite*)getChildByTag(p1Tower32);
					TowerGrid32->setOpacity(200);
				}
				if (CheckT.CheckTower(3, 3) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid33 = (Sprite*)getChildByTag(p1Tower33);
					TowerGrid33->setOpacity(200);
				}
			}
			else
			{
				if (CheckT.CheckEnemyTower(0, 0) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid00 = (Sprite*)getChildByTag(p2Tower00);
					TowerGrid00->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(0, 1) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid01 = (Sprite*)getChildByTag(p2Tower01);
					TowerGrid01->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(0, 2) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid02 = (Sprite*)getChildByTag(p2Tower02);
					TowerGrid02->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(0, 3) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid03 = (Sprite*)getChildByTag(p2Tower03);
					TowerGrid03->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(1, 0) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid10 = (Sprite*)getChildByTag(p2Tower10);
					TowerGrid10->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(1, 1) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid11 = (Sprite*)getChildByTag(p2Tower11);
					TowerGrid11->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(1, 2) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid12 = (Sprite*)getChildByTag(p2Tower12);
					TowerGrid12->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(1, 3) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid13 = (Sprite*)getChildByTag(p2Tower13);
					TowerGrid13->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(2, 0) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid20 = (Sprite*)getChildByTag(p2Tower20);
					TowerGrid20->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(2, 1) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid21 = (Sprite*)getChildByTag(p2Tower21);
					TowerGrid21->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(2, 2) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid22 = (Sprite*)getChildByTag(p2Tower22);
					TowerGrid22->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(2, 3) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid23 = (Sprite*)getChildByTag(p2Tower23);
					TowerGrid23->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(3, 0) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid30 = (Sprite*)getChildByTag(p2Tower30);
					TowerGrid30->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(3, 1) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid31 = (Sprite*)getChildByTag(p2Tower31);
					TowerGrid31->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(3, 2) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid32 = (Sprite*)getChildByTag(p2Tower32);
					TowerGrid32->setOpacity(200);
				}
				if (CheckT.CheckEnemyTower(3, 3) == 0)
				{
					CCLOG("Test Sprite Opacity");
					Sprite* TowerGrid33 = (Sprite*)getChildByTag(p2Tower33);
					TowerGrid33->setOpacity(200);
				}
			}
		}

		target->setScale(2.0);
	};

	listener1->onTouchEnded = [=](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		CollisionDetection RegObjects;
		int tag = target->getTag();
		char type;
		int cost;
		std::string spriteName;
		if (tag == 20000)
		{
			type = p->getCardInHand(0)->getType();
			cost = p->getCardInHand(0)->getCost();
			spriteName = p->getCardInHand(0)->getSpriteName();
		}
		else if (tag == 20001)
		{
			type = p->getCardInHand(1)->getType();
			cost = p->getCardInHand(1)->getCost();
			spriteName = p->getCardInHand(1)->getSpriteName();
		}
		else if (tag == 20002)
		{
			type = p->getCardInHand(2)->getType();
			cost = p->getCardInHand(2)->getCost();
			spriteName = p->getCardInHand(2)->getSpriteName();
		}
		else if (tag == 20003)
		{
			type = p->getCardInHand(3)->getType();
			cost = p->getCardInHand(3)->getCost();
			spriteName = p->getCardInHand(3)->getSpriteName();
		}
		else if (tag == 20004)
		{
			type = p->getCardInHand(4)->getType();
			cost = p->getCardInHand(4)->getCost();
			spriteName = p->getCardInHand(4)->getSpriteName();
		}
		else if (tag == 20005)
		{
			type = p->getCardInHand(5)->getType();
			cost = p->getCardInHand(5)->getCost();
			spriteName = p->getCardInHand(5)->getSpriteName();
		}
		CCLabelBMFont* ChangeText = (CCLabelBMFont*)getChildByTag(ErrorFeedback);

		if(isPlayer1)
		{
			if (target->getPosition().x >100 && target->getPosition().x <478 && target->getPosition().y > 178 && target->getPosition().y <544)
			{
				//	log("sprite onTouchesEnded.. ");
				target->setOpacity(255);
				//Dragging the Tower sprites to the relevent postion
				if (type == 't')
				{
					if (p->getResource() >= cost)
					{
						//Col - 0  Grid postion 0-0
						if (target->getPosition().x > 136 && target->getPosition().x < 213 && target->getPosition().y > 413 && target->getPosition().y < 508)
						{
							if (RegObjects.registerTower(0, 0, 'T') == 0)
							{
								target->setPosition(176, 478);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(0);
								mtowers.at(mtowers.size() - 1)->setPositionY(0);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(176, 478));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 0  Grid postion 0-1
						else if (target->getPosition().x > 136 && target->getPosition().x < 213 && target->getPosition().y > 359 && target->getPosition().y < 431)
						{
							if (RegObjects.registerTower(0, 1, 'T') == 0)
							{
								target->setPosition(174, 402);
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(0);
								mtowers.at(mtowers.size() - 1)->setPositionY(1);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(174, 402));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 0  Grid postion 0-2
						else if (target->getPosition().x > 136 && target->getPosition().x < 213 && target->getPosition().y > 286 && target->getPosition().y < 359)
						{
							if (RegObjects.registerTower(0, 2, 'T') == 0)
							{
								target->setPosition(174, 330);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(0);
								mtowers.at(mtowers.size() - 1)->setPositionY(2);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(174, 330));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 0  Grid postion 0-3
						else if (target->getPosition().x > 136 && target->getPosition().x < 213 && target->getPosition().y > 205 && target->getPosition().y < 286)
						{
							if (RegObjects.registerTower(0, 3, 'T') == 0)
							{
								target->setPosition(174, 256);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(0);
								mtowers.at(mtowers.size() - 1)->setPositionY(3);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(174, 256));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 1  Grid postion 1-0
						else if (target->getPosition().x > 213 && target->getPosition().x < 288 && target->getPosition().y > 413 && target->getPosition().y < 508)
						{
							if (RegObjects.registerTower(1, 0, 'T') == 0)
							{
								target->setPosition(250, 478);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(1);
								mtowers.at(mtowers.size() - 1)->setPositionY(0);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(250, 478));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
							}
						}
						//Col - 1  Grid postion 1-1
						else if (target->getPosition().x >= 213 && target->getPosition().x < 288 && target->getPosition().y > 359 && target->getPosition().y < 413)
						{
							if (RegObjects.registerTower(1, 1, 'T') == 0)
							{
								target->setPosition(250, 402);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(1);
								mtowers.at(mtowers.size() - 1)->setPositionY(1);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(250, 402));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 1  Grid postion 1-2
						else if (target->getPosition().x >= 213 && target->getPosition().x < 288 && target->getPosition().y > 286 && target->getPosition().y < 359)
						{
							if (RegObjects.registerTower(1, 2, 'T') == 0)
							{
								target->setPosition(250, 330);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(1);
								mtowers.at(mtowers.size() - 1)->setPositionY(2);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(250, 330));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 1  Grid postion 1-3
						else if (target->getPosition().x >= 213 && target->getPosition().x < 288 && target->getPosition().y > 205 && target->getPosition().y < 286)
						{
							if (RegObjects.registerTower(1, 3, 'T') == 0)
							{
								target->setPosition(250, 258);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(1);
								mtowers.at(mtowers.size() - 1)->setPositionY(3);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(250, 258));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 2  Grid postion 2-0
						else if (target->getPosition().x > 288 && target->getPosition().x < 365 && target->getPosition().y > 413 && target->getPosition().y < 508)
						{
							if (RegObjects.registerTower(2, 0, 'T') == 0)
							{
								target->setPosition(325, 478);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(2);
								mtowers.at(mtowers.size() - 1)->setPositionY(0);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(325, 478));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 2  Grid postion 2-1
						else if (target->getPosition().x > 288 && target->getPosition().x < 365 && target->getPosition().y > 359 && target->getPosition().y < 413)
						{
							if (RegObjects.registerTower(2, 1, 'T') == 0)
							{
								target->setPosition(325, 402);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(2);
								mtowers.at(mtowers.size() - 1)->setPositionY(1);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(325, 402));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 2  Grid postion 2-2
						else if (target->getPosition().x > 288 && target->getPosition().x < 365 && target->getPosition().y > 286 && target->getPosition().y < 359)
						{
							if (RegObjects.registerTower(2, 2, 'T') == 0)
							{
								target->setPosition(325, 330);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(2);
								mtowers.at(mtowers.size() - 1)->setPositionY(2);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(325, 330));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 2  Grid postion 2-3
						else if (target->getPosition().x > 288 && target->getPosition().x < 365 && target->getPosition().y > 205 && target->getPosition().y < 286)
						{
							if (RegObjects.registerTower(2, 3, 'T') == 0)
							{
								target->setPosition(325, 258);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(2);
								mtowers.at(mtowers.size() - 1)->setPositionY(3);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(325, 258));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 3  Grid postion 3-0
						else if (target->getPosition().x > 365 && target->getPosition().x < 505 && target->getPosition().y > 413 && target->getPosition().y < 508)
						{
							if (RegObjects.registerTower(3, 0, 'T') == 0)
							{
								target->setPosition(401, 478);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(3);
								mtowers.at(mtowers.size() - 1)->setPositionY(0);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(401, 478));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 3  Grid postion 3-1
						else if (target->getPosition().x > 365 && target->getPosition().x < 505 && target->getPosition().y > 359 && target->getPosition().y < 413)
						{
							if (RegObjects.registerTower(3, 1, 'T') == 0)
							{
								target->setPosition(401, 402);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(3);
								mtowers.at(mtowers.size() - 1)->setPositionY(1);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(401, 402));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 3  Grid postion 3-2
						else if (target->getPosition().x > 365 && target->getPosition().x < 505 && target->getPosition().y > 286 && target->getPosition().y < 359)
						{
							if (RegObjects.registerTower(3, 2, 'T') == 0)
							{
								target->setPosition(401, 330);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(3);
								mtowers.at(mtowers.size() - 1)->setPositionY(2);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(401, 330));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 3  Grid postion 3-3
						else if (target->getPosition().x > 365 && target->getPosition().x < 505 && target->getPosition().y > 205 && target->getPosition().y < 286)
						{
							if (RegObjects.registerTower(3, 3, 'T') == 0)
							{
								target->setPosition(401, 258);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								mtowers.push_back(new Tower("SampleTower.png"));
								mtowers.at(mtowers.size() - 1)->setPositionX(3);
								mtowers.at(mtowers.size() - 1)->setPositionY(3);
								mtowers.at(mtowers.size() - 1)->getSprite()->setPosition(Vec2(401, 258));
								mtowers.at(mtowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((mtowers.at(mtowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						else
						{
							target->setTexture("SampleCard.png");
							target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
						}
					}
					else
					{
						ChangeText->setString("Not enough resources");
						CCLOG("No Resource available");
						target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
						target->setTexture(spriteName);
						target->setScale(1.0);
					}

				}

				//Dragging the Soldier sprites to the relevent postion
				//code needs to be added
				if (type == 's')
				{
					if (p->getResource() >= cost)
					{
						//Col - 0  Grid postion 0-0
						if (target->getPosition().x > 98 && target->getPosition().x < 174 && target->getPosition().y > 472 && target->getPosition().y < 545)
						{
							if (RegObjects.registerObject(0, 0, 'P') == 0)
							{
								target->setPosition(137, 504);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(0);
								marmy.at(marmy.size() - 1)->setPositionY(0);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(137, 504));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 0  Grid postion 0-1
						else if (target->getPosition().x > 98 && target->getPosition().x < 174 && target->getPosition().y > 395 && target->getPosition().y <= 472)
						{
							if (RegObjects.registerObject(0, 1, 'P') == 0)
							{
								target->setPosition(137, 431);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(0);
								marmy.at(marmy.size() - 1)->setPositionY(1);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(137, 431));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 0  Grid postion 0-2
						else if (target->getPosition().x > 98 && target->getPosition().x < 174 && target->getPosition().y > 324 && target->getPosition().y <= 395)
						{
							if (RegObjects.registerObject(0, 2, 'P') == 0)
							{
								target->setPosition(137, 358);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(0);
								marmy.at(marmy.size() - 1)->setPositionY(2);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(137, 358));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());

							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 0  Grid postion 0-3
						else if (target->getPosition().x > 98 && target->getPosition().x < 174 && target->getPosition().y > 250 && target->getPosition().y <= 324)
						{
							if (RegObjects.registerObject(0, 3, 'P') == 0)
							{
								target->setPosition(137, 285);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(0);
								marmy.at(marmy.size() - 1)->setPositionY(3);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(137, 285));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());

							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 0  Grid postion 0-4
						else if (target->getPosition().x > 98 && target->getPosition().x < 174 && target->getPosition().y > 178 && target->getPosition().y <= 250)
						{
							if (RegObjects.registerObject(0, 4, 'P') == 0)
							{
								target->setPosition(137, 211);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(0);
								marmy.at(marmy.size() - 1)->setPositionY(4);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(137, 211));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());

							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 1  Grid postion 1-0
						else if (target->getPosition().x >= 174 && target->getPosition().x < 250 && target->getPosition().y > 472 && target->getPosition().y < 545)
						{
							if (RegObjects.registerObject(1, 0, 'P') == 0)
							{
								target->setPosition(214, 504);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(1);
								marmy.at(marmy.size() - 1)->setPositionY(0);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(214, 504));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());

							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 1  Grid postion 1-1
						else if (target->getPosition().x >= 174 && target->getPosition().x < 250 && target->getPosition().y > 395 && target->getPosition().y <= 472)
						{
							if (RegObjects.registerObject(1, 1, 'P') == 0)
							{
								target->setPosition(214, 431);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(1);
								marmy.at(marmy.size() - 1)->setPositionY(1);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(214, 431));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 1  Grid postion 1-2
						else if (target->getPosition().x >= 174 && target->getPosition().x < 250 && target->getPosition().y > 324 && target->getPosition().y <= 395)
						{
							if (RegObjects.registerObject(1, 2, 'P') == 0)
							{
								target->setPosition(214, 358);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(1);
								marmy.at(marmy.size() - 1)->setPositionY(2);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(214, 358));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 1  Grid postion 1-3
						else if (target->getPosition().x >= 174 && target->getPosition().x < 250 && target->getPosition().y > 250 && target->getPosition().y <= 324)
						{
							if (RegObjects.registerObject(1, 3, 'P') == 0)
							{
								target->setPosition(214, 285);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(1);
								marmy.at(marmy.size() - 1)->setPositionY(3);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(214, 285));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 1  Grid postion 1-4
						else if (target->getPosition().x >= 174 && target->getPosition().x < 250 && target->getPosition().y > 178 && target->getPosition().y <= 250)
						{
							if (RegObjects.registerObject(1, 4, 'P') == 0)
							{
								target->setPosition(214, 211);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(1);
								marmy.at(marmy.size() - 1)->setPositionY(4);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(214, 211));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 2  Grid postion 2-0
						else if (target->getPosition().x >= 250 && target->getPosition().x < 325 && target->getPosition().y > 472 && target->getPosition().y < 545)
						{
							if (RegObjects.registerObject(2, 0, 'P') == 0)
							{
								target->setPosition(288, 504);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(2);
								marmy.at(marmy.size() - 1)->setPositionY(0);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(288, 504));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 2  Grid postion 2-1
						else if (target->getPosition().x >= 250 && target->getPosition().x < 325 && target->getPosition().y > 395 && target->getPosition().y <= 472)
						{
							if (RegObjects.registerObject(2, 1, 'P') == 0)
							{
								target->setPosition(288, 431);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(2);
								marmy.at(marmy.size() - 1)->setPositionY(1);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(288, 431));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 2  Grid postion 2-2
						else if (target->getPosition().x >= 250 && target->getPosition().x < 325 && target->getPosition().y > 324 && target->getPosition().y <= 395)
						{
							if (RegObjects.registerObject(2, 2, 'P') == 0)
							{
								target->setPosition(288, 358);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(2);
								marmy.at(marmy.size() - 1)->setPositionY(2);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(288, 358));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 2  Grid postion 2-3
						else if (target->getPosition().x >= 250 && target->getPosition().x < 325 && target->getPosition().y > 250 && target->getPosition().y <= 324)
						{
							if (RegObjects.registerObject(2, 3, 'P') == 0)
							{
								target->setPosition(288, 285);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(2);
								marmy.at(marmy.size() - 1)->setPositionY(3);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(288, 285));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 2  Grid postion 2-4
						else if (target->getPosition().x >= 250 && target->getPosition().x < 325 && target->getPosition().y > 178 && target->getPosition().y <= 250)
						{
							if (RegObjects.registerObject(2, 4, 'P') == 0)
							{
								target->setPosition(288, 211);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(2);
								marmy.at(marmy.size() - 1)->setPositionY(4);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(288, 211));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 3  Grid postion 3-0
						else if (target->getPosition().x >= 325 && target->getPosition().x < 401 && target->getPosition().y > 472 && target->getPosition().y < 545)
						{
							if (RegObjects.registerObject(3, 0, 'P') == 0)
							{
								target->setPosition(364, 504);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(3);
								marmy.at(marmy.size() - 1)->setPositionY(0);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(364, 504));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 3  Grid postion 3-1
						else if (target->getPosition().x >= 325 && target->getPosition().x < 401 && target->getPosition().y > 395 && target->getPosition().y <= 472)
						{
							if (RegObjects.registerObject(3, 1, 'P') == 0)
							{
								target->setPosition(364, 431);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(3);
								marmy.at(marmy.size() - 1)->setPositionY(1);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(364, 431));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 3  Grid postion 3-2
						else if (target->getPosition().x >= 325 && target->getPosition().x < 401 && target->getPosition().y > 324 && target->getPosition().y <= 395)
						{
							if (RegObjects.registerObject(3, 2, 'P') == 0)
							{
								target->setPosition(364, 358);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(3);
								marmy.at(marmy.size() - 1)->setPositionY(2);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(364, 358));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 3  Grid postion 3-3
						else if (target->getPosition().x >= 325 && target->getPosition().x < 401 && target->getPosition().y > 250 && target->getPosition().y <= 324)
						{
							if (RegObjects.registerObject(3, 3, 'P') == 0)
							{
								target->setPosition(364, 285);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(3);
								marmy.at(marmy.size() - 1)->setPositionY(3);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(364, 285));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 3  Grid postion 3-4
						else if (target->getPosition().x >= 325 && target->getPosition().x < 401 && target->getPosition().y > 178 && target->getPosition().y <= 250)
						{
							if (RegObjects.registerObject(3, 4, 'P') == 0)
							{
								target->setPosition(364, 211);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(3);
								marmy.at(marmy.size() - 1)->setPositionY(4);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(364, 211));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 4  Grid postion 4-0
						else if (target->getPosition().x >= 401 && target->getPosition().x < 478 && target->getPosition().y > 472 && target->getPosition().y < 545)
						{
							if (RegObjects.registerObject(4, 0, 'P') == 0)
							{
								target->setPosition(441, 504);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(4);
								marmy.at(marmy.size() - 1)->setPositionY(0);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(441, 504));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 4  Grid postion 4-1
						else if (target->getPosition().x >= 401 && target->getPosition().x < 478 && target->getPosition().y > 395 && target->getPosition().y <= 472)
						{
							if (RegObjects.registerObject(4, 1, 'P') == 0)
							{
								target->setPosition(441, 431);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(4);
								marmy.at(marmy.size() - 1)->setPositionY(1);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(441, 431));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 4  Grid postion 4-2
						else if (target->getPosition().x >= 401 && target->getPosition().x < 478 && target->getPosition().y > 324 && target->getPosition().y <= 395)
						{
							if (RegObjects.registerObject(4, 2, 'P') == 0)
							{
								target->setPosition(441, 358);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(4);
								marmy.at(marmy.size() - 1)->setPositionY(2);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(441, 358));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 4  Grid postion 4-3
						else if (target->getPosition().x >= 401 && target->getPosition().x < 478 && target->getPosition().y > 250 && target->getPosition().y <= 324)
						{
							if (RegObjects.registerObject(4, 3, 'P') == 0)
							{
								target->setPosition(441, 285);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(4);
								marmy.at(marmy.size() - 1)->setPositionY(3);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(441, 285));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 4  Grid postion 4-4
						else if (target->getPosition().x >= 401 && target->getPosition().x < 478 && target->getPosition().y > 178 && target->getPosition().y <= 250)
						{
							if (RegObjects.registerObject(4, 4, 'P') == 0)
							{
								target->setPosition(441, 211);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(4);
								marmy.at(marmy.size() - 1)->setPositionY(4);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(441, 211));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
					}
					else
					{
						ChangeText->setString("Not enough resources");
						CCLOG("No Resource available");
						target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
						target->setTexture(spriteName);
						target->setScale(1.0);
					}
				}
			}
			else
			{
				//target->setPosition(origin + Vec2((visibleSize.width / 2) + 100, (visibleSize.height / 2) - 200));
				target->setPosition(Vec2(mOriginalXPos,mOriginalYPos));
				target->setTexture(spriteName);
				//target->setTexture(spriteTemplate->getTexture());
				target->setScale(1.0);
				target->setOpacity(255);
			}
		}
		else //player 2
		{
			if (target->getPosition().x >480 && target->getPosition().x <850 && target->getPosition().y > 178 && target->getPosition().y <544)
			{
				//	log("sprite onTouchesEnded.. ");
				target->setOpacity(255);
				//Dragging the Tower sprites to the relevent postion
				if (type == 't')
				{
					if (p->getResource() >= cost)
					{
						//Col - 0  Grid postion 0-0
						if (target->getPosition().x > 522 && target->getPosition().x < 592 && target->getPosition().y > 443 && target->getPosition().y < 513)
						{
							if (RegObjects.registerEnemyTower(0, 0, 'T') == 0)
							{
								target->setPosition(557, 478);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(0);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(0);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(557, 478));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 0  Grid postion 0-1
						else if (target->getPosition().x > 522 && target->getPosition().x < 592 && target->getPosition().y > 367 && target->getPosition().y < 437)
						{
							if (RegObjects.registerEnemyTower(0, 1, 'T') == 0)
							{
								target->setPosition(557, 402);
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(0);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(1);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(557, 402));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 0  Grid postion 0-2
						else if (target->getPosition().x > 522 && target->getPosition().x < 592 && target->getPosition().y > 295 && target->getPosition().y < 365)
						{
							if (RegObjects.registerEnemyTower(0, 2, 'T') == 0)
							{
								target->setPosition(557, 330);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(0);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(2);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(557, 330));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 0  Grid postion 0-3
						else if (target->getPosition().x > 522 && target->getPosition().x < 592 && target->getPosition().y > 221 && target->getPosition().y < 291)
						{
							if (RegObjects.registerEnemyTower(0, 3, 'T') == 0)
							{
								target->setPosition(557, 256);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(0);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(3);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(557, 256));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 1  Grid postion 1-0
						else if (target->getPosition().x > 599 && target->getPosition().x < 669 && target->getPosition().y > 443 && target->getPosition().y < 513)
						{
							if (RegObjects.registerEnemyTower(1, 0, 'T') == 0)
							{
								target->setPosition(634, 478);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(1);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(0);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(634, 478));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
							}
						}
						//Col - 1  Grid postion 1-1
						else if (target->getPosition().x >= 599 && target->getPosition().x < 669 && target->getPosition().y > 367 && target->getPosition().y < 437)
						{
							if (RegObjects.registerEnemyTower(1, 1, 'T') == 0)
							{
								target->setPosition(634, 402);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(1);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(1);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(634, 402));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 1  Grid postion 1-2
						else if (target->getPosition().x >= 599 && target->getPosition().x < 669 && target->getPosition().y > 295 && target->getPosition().y < 365)
						{
							if (RegObjects.registerEnemyTower(1, 2, 'T') == 0)
							{
								target->setPosition(634, 330);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(1);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(2);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(634, 330));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 1  Grid postion 1-3
						else if (target->getPosition().x >= 599 && target->getPosition().x < 669 && target->getPosition().y > 223 && target->getPosition().y < 293)
						{
							if (RegObjects.registerEnemyTower(1, 3, 'T') == 0)
							{
								target->setPosition(634, 258);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(1);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(3);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(634, 258));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 2  Grid postion 2-0
						else if (target->getPosition().x > 676 && target->getPosition().x < 746 && target->getPosition().y > 443 && target->getPosition().y < 513)
						{
							if (RegObjects.registerEnemyTower(2, 0, 'T') == 0)
							{
								target->setPosition(711, 478);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(2);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(0);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(711, 478));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 2  Grid postion 2-1
						else if (target->getPosition().x > 676 && target->getPosition().x < 746 && target->getPosition().y > 367 && target->getPosition().y < 437)
						{
							if (RegObjects.registerEnemyTower(2, 1, 'T') == 0)
							{
								target->setPosition(711, 402);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(2);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(1);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(711, 402));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 2  Grid postion 2-2
						else if (target->getPosition().x > 676 && target->getPosition().x < 746 && target->getPosition().y > 295 && target->getPosition().y < 365)
						{
							if (RegObjects.registerEnemyTower(2, 2, 'T') == 0)
							{
								target->setPosition(711, 330);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(2);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(2);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(711, 330));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 2  Grid postion 2-3
						else if (target->getPosition().x > 676 && target->getPosition().x < 746 && target->getPosition().y > 223 && target->getPosition().y < 293)
						{
							if (RegObjects.registerEnemyTower(2, 3, 'T') == 0)
							{
								target->setPosition(711, 258);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(2);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(3);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(711, 258));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 3  Grid postion 3-0
						else if (target->getPosition().x > 752 && target->getPosition().x < 822 && target->getPosition().y > 443 && target->getPosition().y < 513)
						{
							if (RegObjects.registerEnemyTower(3, 0, 'T') == 0)
							{
								target->setPosition(787, 478);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(3);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(0);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(787, 478));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 3  Grid postion 3-1
						else if (target->getPosition().x > 752 && target->getPosition().x < 822 && target->getPosition().y > 367 && target->getPosition().y < 437)
						{
							if (RegObjects.registerEnemyTower(3, 1, 'T') == 0)
							{
								target->setPosition(787, 402);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(3);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(1);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(787, 402));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 3  Grid postion 3-2
						else if (target->getPosition().x > 752 && target->getPosition().x < 822 && target->getPosition().y > 295 && target->getPosition().y < 365)
						{
							if (RegObjects.registerEnemyTower(3, 2, 'T') == 0)
							{
								target->setPosition(787, 330);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(3);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(2);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(787, 330));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						//Col - 3  Grid postion 3-3
						else if (target->getPosition().x > 752 && target->getPosition().x < 822 && target->getPosition().y > 223 && target->getPosition().y < 293)
						{
							if (RegObjects.registerEnemyTower(3, 3, 'T') == 0)
							{
								target->setPosition(787, 258);
								p->setResource(-cost);
								ChangeText->setString("Tower Placed");
								p->removeFromHand(target->getTag());
								menemyTowers.push_back(new Tower("SampleTower.png"));
								menemyTowers.at(menemyTowers.size() - 1)->setPositionX(3);
								menemyTowers.at(menemyTowers.size() - 1)->setPositionY(3);
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setPosition(Vec2(787, 258));
								menemyTowers.at(menemyTowers.size() - 1)->getSprite()->setScale(2.0);
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((menemyTowers.at(menemyTowers.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
							}
						}
						else
						{
							target->setTexture("SampleCard.png");
							target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
						}
					}
					else
					{
						ChangeText->setString("Not enough resources");
						CCLOG("No Resource available");
						target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
						target->setTexture(spriteName);
						target->setScale(1.0);
					}

				}

				//Dragging the Soldier sprites to the relevent postion
				//code needs to be added
				if (type == 's')
				{
					if (p->getResource() >= cost)
					{
						//Col - 0  Grid postion 0-0
						if (target->getPosition().x > 98 && target->getPosition().x < 174 && target->getPosition().y > 472 && target->getPosition().y < 545)
						{
							if (RegObjects.registerObject(0, 0, 'P') == 0)
							{
								target->setPosition(137, 504);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(0);
								marmy.at(marmy.size() - 1)->setPositionY(0);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(137, 504));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 0  Grid postion 0-1
						else if (target->getPosition().x > 98 && target->getPosition().x < 174 && target->getPosition().y > 395 && target->getPosition().y <= 472)
						{
							if (RegObjects.registerObject(0, 1, 'P') == 0)
							{
								target->setPosition(137, 431);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(0);
								marmy.at(marmy.size() - 1)->setPositionY(1);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(137, 431));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 0  Grid postion 0-2
						else if (target->getPosition().x > 98 && target->getPosition().x < 174 && target->getPosition().y > 324 && target->getPosition().y <= 395)
						{
							if (RegObjects.registerObject(0, 2, 'P') == 0)
							{
								target->setPosition(137, 358);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(0);
								marmy.at(marmy.size() - 1)->setPositionY(2);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(137, 358));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());

							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 0  Grid postion 0-3
						else if (target->getPosition().x > 98 && target->getPosition().x < 174 && target->getPosition().y > 250 && target->getPosition().y <= 324)
						{
							if (RegObjects.registerObject(0, 3, 'P') == 0)
							{
								target->setPosition(137, 285);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(0);
								marmy.at(marmy.size() - 1)->setPositionY(3);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(137, 285));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());

							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 0  Grid postion 0-4
						else if (target->getPosition().x > 98 && target->getPosition().x < 174 && target->getPosition().y > 178 && target->getPosition().y <= 250)
						{
							if (RegObjects.registerObject(0, 4, 'P') == 0)
							{
								target->setPosition(137, 211);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(0);
								marmy.at(marmy.size() - 1)->setPositionY(4);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(137, 211));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());

							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 1  Grid postion 1-0
						else if (target->getPosition().x >= 174 && target->getPosition().x < 250 && target->getPosition().y > 472 && target->getPosition().y < 545)
						{
							if (RegObjects.registerObject(1, 0, 'P') == 0)
							{
								target->setPosition(214, 504);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(1);
								marmy.at(marmy.size() - 1)->setPositionY(0);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(214, 504));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());

							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 1  Grid postion 1-1
						else if (target->getPosition().x >= 174 && target->getPosition().x < 250 && target->getPosition().y > 395 && target->getPosition().y <= 472)
						{
							if (RegObjects.registerObject(1, 1, 'P') == 0)
							{
								target->setPosition(214, 431);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(1);
								marmy.at(marmy.size() - 1)->setPositionY(1);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(214, 431));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 1  Grid postion 1-2
						else if (target->getPosition().x >= 174 && target->getPosition().x < 250 && target->getPosition().y > 324 && target->getPosition().y <= 395)
						{
							if (RegObjects.registerObject(1, 2, 'P') == 0)
							{
								target->setPosition(214, 358);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(1);
								marmy.at(marmy.size() - 1)->setPositionY(2);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(214, 358));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 1  Grid postion 1-3
						else if (target->getPosition().x >= 174 && target->getPosition().x < 250 && target->getPosition().y > 250 && target->getPosition().y <= 324)
						{
							if (RegObjects.registerObject(1, 3, 'P') == 0)
							{
								target->setPosition(214, 285);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(1);
								marmy.at(marmy.size() - 1)->setPositionY(3);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(214, 285));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 1  Grid postion 1-4
						else if (target->getPosition().x >= 174 && target->getPosition().x < 250 && target->getPosition().y > 178 && target->getPosition().y <= 250)
						{
							if (RegObjects.registerObject(1, 4, 'P') == 0)
							{
								target->setPosition(214, 211);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(1);
								marmy.at(marmy.size() - 1)->setPositionY(4);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(214, 211));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 2  Grid postion 2-0
						else if (target->getPosition().x >= 250 && target->getPosition().x < 325 && target->getPosition().y > 472 && target->getPosition().y < 545)
						{
							if (RegObjects.registerObject(2, 0, 'P') == 0)
							{
								target->setPosition(288, 504);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(2);
								marmy.at(marmy.size() - 1)->setPositionY(0);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(288, 504));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 2  Grid postion 2-1
						else if (target->getPosition().x >= 250 && target->getPosition().x < 325 && target->getPosition().y > 395 && target->getPosition().y <= 472)
						{
							if (RegObjects.registerObject(2, 1, 'P') == 0)
							{
								target->setPosition(288, 431);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(2);
								marmy.at(marmy.size() - 1)->setPositionY(1);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(288, 431));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 2  Grid postion 2-2
						else if (target->getPosition().x >= 250 && target->getPosition().x < 325 && target->getPosition().y > 324 && target->getPosition().y <= 395)
						{
							if (RegObjects.registerObject(2, 2, 'P') == 0)
							{
								target->setPosition(288, 358);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(2);
								marmy.at(marmy.size() - 1)->setPositionY(2);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(288, 358));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 2  Grid postion 2-3
						else if (target->getPosition().x >= 250 && target->getPosition().x < 325 && target->getPosition().y > 250 && target->getPosition().y <= 324)
						{
							if (RegObjects.registerObject(2, 3, 'P') == 0)
							{
								target->setPosition(288, 285);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(2);
								marmy.at(marmy.size() - 1)->setPositionY(3);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(288, 285));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 2  Grid postion 2-4
						else if (target->getPosition().x >= 250 && target->getPosition().x < 325 && target->getPosition().y > 178 && target->getPosition().y <= 250)
						{
							if (RegObjects.registerObject(2, 4, 'P') == 0)
							{
								target->setPosition(288, 211);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(2);
								marmy.at(marmy.size() - 1)->setPositionY(4);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(288, 211));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 3  Grid postion 3-0
						else if (target->getPosition().x >= 325 && target->getPosition().x < 401 && target->getPosition().y > 472 && target->getPosition().y < 545)
						{
							if (RegObjects.registerObject(3, 0, 'P') == 0)
							{
								target->setPosition(364, 504);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(3);
								marmy.at(marmy.size() - 1)->setPositionY(0);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(364, 504));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 3  Grid postion 3-1
						else if (target->getPosition().x >= 325 && target->getPosition().x < 401 && target->getPosition().y > 395 && target->getPosition().y <= 472)
						{
							if (RegObjects.registerObject(3, 1, 'P') == 0)
							{
								target->setPosition(364, 431);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(3);
								marmy.at(marmy.size() - 1)->setPositionY(1);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(364, 431));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 3  Grid postion 3-2
						else if (target->getPosition().x >= 325 && target->getPosition().x < 401 && target->getPosition().y > 324 && target->getPosition().y <= 395)
						{
							if (RegObjects.registerObject(3, 2, 'P') == 0)
							{
								target->setPosition(364, 358);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(3);
								marmy.at(marmy.size() - 1)->setPositionY(2);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(364, 358));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 3  Grid postion 3-3
						else if (target->getPosition().x >= 325 && target->getPosition().x < 401 && target->getPosition().y > 250 && target->getPosition().y <= 324)
						{
							if (RegObjects.registerObject(3, 3, 'P') == 0)
							{
								target->setPosition(364, 285);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(3);
								marmy.at(marmy.size() - 1)->setPositionY(3);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(364, 285));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 3  Grid postion 3-4
						else if (target->getPosition().x >= 325 && target->getPosition().x < 401 && target->getPosition().y > 178 && target->getPosition().y <= 250)
						{
							if (RegObjects.registerObject(3, 4, 'P') == 0)
							{
								target->setPosition(364, 211);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(3);
								marmy.at(marmy.size() - 1)->setPositionY(4);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(364, 211));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 4  Grid postion 4-0
						else if (target->getPosition().x >= 401 && target->getPosition().x < 478 && target->getPosition().y > 472 && target->getPosition().y < 545)
						{
							if (RegObjects.registerObject(4, 0, 'P') == 0)
							{
								target->setPosition(441, 504);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(4);
								marmy.at(marmy.size() - 1)->setPositionY(0);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(441, 504));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 4  Grid postion 4-1
						else if (target->getPosition().x >= 401 && target->getPosition().x < 478 && target->getPosition().y > 395 && target->getPosition().y <= 472)
						{
							if (RegObjects.registerObject(4, 1, 'P') == 0)
							{
								target->setPosition(441, 431);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(4);
								marmy.at(marmy.size() - 1)->setPositionY(1);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(441, 431));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 4  Grid postion 4-2
						else if (target->getPosition().x >= 401 && target->getPosition().x < 478 && target->getPosition().y > 324 && target->getPosition().y <= 395)
						{
							if (RegObjects.registerObject(4, 2, 'P') == 0)
							{
								target->setPosition(441, 358);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(4);
								marmy.at(marmy.size() - 1)->setPositionY(2);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(441, 358));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 4  Grid postion 4-3
						else if (target->getPosition().x >= 401 && target->getPosition().x < 478 && target->getPosition().y > 250 && target->getPosition().y <= 324)
						{
							if (RegObjects.registerObject(4, 3, 'P') == 0)
							{
								target->setPosition(441, 285);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(4);
								marmy.at(marmy.size() - 1)->setPositionY(3);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(441, 285));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
						//Col - 4  Grid postion 4-4
						else if (target->getPosition().x >= 401 && target->getPosition().x < 478 && target->getPosition().y > 178 && target->getPosition().y <= 250)
						{
							if (RegObjects.registerObject(4, 4, 'P') == 0)
							{
								target->setPosition(441, 211);
								p->setResource(-cost);
								ChangeText->setString("Soldier Placed");
								marmy.push_back(new Soldier(spriteName));
								marmy.at(marmy.size() - 1)->getSprite()->setTexture("testEnemy.png");
								marmy.at(marmy.size() - 1)->setPositionX(4);
								marmy.at(marmy.size() - 1)->setPositionY(4);
								marmy.at(marmy.size() - 1)->getSprite()->setPosition(Vec2(441, 211));
								marmy.at(marmy.size() - 1)->getSprite()->setScale(2.0);
								p->removeFromHand(target->getTag());
								target->removeFromParentAndCleanup(true);
								displayHand(p);
								this->addChild((marmy.at(marmy.size() - 1))->getSprite());
							}
							else
							{
								CCLOG("Can't place here");
								ChangeText->setString("Can't place here");
								target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
								target->setTexture(spriteName);
								target->setScale(1.0);
							}
						}
					}
					else
					{
						ChangeText->setString("Not enough resources");
						CCLOG("No Resource available");
						target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
						target->setTexture(spriteName);
						target->setScale(1.0);
					}
				}
			}
			else
			{
				//target->setPosition(origin + Vec2((visibleSize.width / 2) + 100, (visibleSize.height / 2) - 200));
				target->setPosition(Vec2(mOriginalXPos, mOriginalYPos));
				target->setTexture(spriteName);
				//target->setTexture(spriteTemplate->getTexture());
				target->setScale(1.0);
				target->setOpacity(255);
			}
		}//end of Player 2

		CCLabelBMFont* ChangeResource = (CCLabelBMFont*)getChildByTag(LabelTagResource);
		std::string StringResource = std::to_string(p->getResource());
		ChangeResource->setString(StringResource);
		if (isPlayer1)
		{
			Sprite* towerG_00 = (Sprite*)getChildByTag(p1Tower00);
			towerG_00->setOpacity(0);
			Sprite* towerG_01 = (Sprite*)getChildByTag(p1Tower01);
			towerG_01->setOpacity(0);
			Sprite* towerG_02 = (Sprite*)getChildByTag(p1Tower02);
			towerG_02->setOpacity(0);
			Sprite* towerG_03 = (Sprite*)getChildByTag(p1Tower03);
			towerG_03->setOpacity(0);
			Sprite* towerG_10 = (Sprite*)getChildByTag(p1Tower10);
			towerG_10->setOpacity(0);
			Sprite* towerG_11 = (Sprite*)getChildByTag(p1Tower11);
			towerG_11->setOpacity(0);
			Sprite* towerG_12 = (Sprite*)getChildByTag(p1Tower12);
			towerG_12->setOpacity(0);
			Sprite* towerG_13 = (Sprite*)getChildByTag(p1Tower13);
			towerG_13->setOpacity(0);
			Sprite* towerG_20 = (Sprite*)getChildByTag(p1Tower20);
			towerG_20->setOpacity(0);
			Sprite* towerG_21 = (Sprite*)getChildByTag(p1Tower21);
			towerG_21->setOpacity(0);
			Sprite* towerG_22 = (Sprite*)getChildByTag(p1Tower22);
			towerG_22->setOpacity(0);
			Sprite* towerG_23 = (Sprite*)getChildByTag(p1Tower23);
			towerG_23->setOpacity(0);
			Sprite* towerG_30 = (Sprite*)getChildByTag(p1Tower30);
			towerG_30->setOpacity(0);
			Sprite* towerG_31 = (Sprite*)getChildByTag(p1Tower31);
			towerG_31->setOpacity(0);
			Sprite* towerG_32 = (Sprite*)getChildByTag(p1Tower32);
			towerG_32->setOpacity(0);
			Sprite* towerG_33 = (Sprite*)getChildByTag(p1Tower33);
			towerG_33->setOpacity(0);
		}
		else
		{
			Sprite* towerG_00 = (Sprite*)getChildByTag(p2Tower00);
			towerG_00->setOpacity(0);
			Sprite* towerG_01 = (Sprite*)getChildByTag(p2Tower01);
			towerG_01->setOpacity(0);
			Sprite* towerG_02 = (Sprite*)getChildByTag(p2Tower02);
			towerG_02->setOpacity(0);
			Sprite* towerG_03 = (Sprite*)getChildByTag(p2Tower03);
			towerG_03->setOpacity(0);
			Sprite* towerG_10 = (Sprite*)getChildByTag(p2Tower10);
			towerG_10->setOpacity(0);
			Sprite* towerG_11 = (Sprite*)getChildByTag(p2Tower11);
			towerG_11->setOpacity(0);
			Sprite* towerG_12 = (Sprite*)getChildByTag(p2Tower12);
			towerG_12->setOpacity(0);
			Sprite* towerG_13 = (Sprite*)getChildByTag(p2Tower13);
			towerG_13->setOpacity(0);
			Sprite* towerG_20 = (Sprite*)getChildByTag(p2Tower20);
			towerG_20->setOpacity(0);
			Sprite* towerG_21 = (Sprite*)getChildByTag(p2Tower21);
			towerG_21->setOpacity(0);
			Sprite* towerG_22 = (Sprite*)getChildByTag(p2Tower22);
			towerG_22->setOpacity(0);
			Sprite* towerG_23 = (Sprite*)getChildByTag(p2Tower23);
			towerG_23->setOpacity(0);
			Sprite* towerG_30 = (Sprite*)getChildByTag(p2Tower30);
			towerG_30->setOpacity(0);
			Sprite* towerG_31 = (Sprite*)getChildByTag(p2Tower31);
			towerG_31->setOpacity(0);
			Sprite* towerG_32 = (Sprite*)getChildByTag(p2Tower32);
			towerG_32->setOpacity(0);
			Sprite* towerG_33 = (Sprite*)getChildByTag(p2Tower33);
			towerG_33->setOpacity(0);
		}
	};
	if (p->getHandSize() > 0)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->getChildByTag(mhandSprite1));
	}
	for (int j = 0; j < p->getHandSize(); j ++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->getChildByTag(mhandSprite1 + j));
	}
}
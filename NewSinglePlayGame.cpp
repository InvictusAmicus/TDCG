//Worked on by Ciaran Clerkin K00191500 and Declan Cordial K00184439

#include "NewSinglePlayGame.h"
#include "GameOverScreen.h"
#include "GameWonScreen.h"
#include "SimpleAudioEngine.h"
#include "Soldier.h"
#include "Tower.h"
#include "Player.h"
#include "CollisionDetection.h"
#include "EnemyAI.h"
#include "Options.h"
#include "AudioEngine.h"
#include <utility>
#include <iostream>
#include <tuple>

USING_NS_CC;

enum
{
	MoveSprite = 1,
};

int Enemylife;
int EnemyResource;
int TowerGridLoop;
int enemyTurn = 0;
int SinglePlayGameMusic;
float OriginalXPos, OriginalYPos;
int score;
bool CoverTest;
int RunningAction;

std::vector<Soldier*> army;
std::vector<Soldier*> enemyArmy;
std::vector<Tower*> towers;
std::vector<Tower*> enemyTowers;
std::vector<Sprite*> spriteAnimation;
std::vector<Action*> removeAction;
std::vector<Action*> SoldierMovement;
std::vector<Sprite*> attackSprite;

//need to set soldier to sprite

CollisionDetection baseGrid;
CollisionDetection moveForward;

#define CoverImage 1230
#define LabelEnemyLife 1232
#define ErrorFeedback 1233
#define LabelTagLife 1234
#define LabelTagResource 1235
#define CardsInHand 1237
#define Tower00 1238
#define Tower01 1239
#define Tower02 1240
#define Tower03 1241
#define Tower10 1242
#define Tower11 1243
#define Tower12 1244
#define Tower13 1245
#define Tower20 1246
#define Tower20 1247
#define Tower21 1248
#define Tower22 1249
#define Tower23 1250
#define Tower30 1251
#define Tower31 1252
#define Tower32 1253
#define Tower33 1254

#define handSprite1 2000
#define handSprite2 2001
#define handSprite3 2002
#define handSprite4 2003
#define handSprite5 2004
#define handSprite6 2005

Scene* NewSinglePlayGame::createScene()
{
	// 'scene' is an autorelease object
	auto NewGameScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = NewSinglePlayGame::create();

	// add layer as a child to scene
	NewGameScene->addChild(layer);

	// return the scene
	return NewGameScene;
}

bool NewSinglePlayGame::init()
{

	if (!Layer::init())
	{
		return false;
	}

	enemyArmy.clear();
	army.clear();
	towers.clear();
	enemyTowers.clear();
	spriteAnimation.clear();
	removeAction.clear();
	SoldierMovement.clear();

	CoverTest = false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Options gameMusic;
	CCLOG("GAME MUTE %d", gameMusic.getMusicMute());
	if (gameMusic.getMusicMute() != 1) {
		int V = gameMusic.getmusicVolume();
		CCLOG("gameMusic.getmusicVolume() %d", V);
		CCLOG("GAME MUTE %d", gameMusic.getMusicMute());
		SinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("GameMusic.mp3", true, gameMusic.getMusicFloatVolume(V), nullptr);
	}
	p = new Player();

	enemyTurn = 0;
	Enemylife = 100;
	p->setResource(200);
	EnemyResource = 200;
    //baseGrid = new CollisionDetection();
	baseGrid.CreateGrids();
	CCLOG("Creating Grid");

	std::string StringLife = std::to_string(p->getLife());
	std::string StringResource = std::to_string(p->getResource());
	std::string StringEnemyLife = std::to_string(Enemylife);

	auto label = Label::createWithTTF("Single Player Game", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	auto LifeLabel = Label::createWithTTF("Health", "fonts/Marker Felt.ttf", 24);
	LifeLabel->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 10,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(LifeLabel, 1);

	auto LifeLabelValue = Label::createWithTTF(StringLife, "fonts/Marker Felt.ttf", 24);
	LifeLabelValue->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 70,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(LifeLabelValue, 1, LabelTagLife);

	auto ResourceLabel = Label::createWithTTF("Resource", "fonts/Marker Felt.ttf", 24);
	ResourceLabel->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 150,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(ResourceLabel, 1);

	auto ResourceLabelValue = Label::createWithTTF(StringResource, "fonts/Marker Felt.ttf", 24);
	ResourceLabelValue->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 220,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(ResourceLabelValue, 1, LabelTagResource);

	auto FeedBackLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 36);
	FeedBackLabel->setPosition(Vec2(origin.x + LifeLabel->getContentSize().width + 100,
		origin.y + visibleSize.height - 100));
	FeedBackLabel->setColor(ccc3(0, 0, 0));
	this->addChild(FeedBackLabel, 1, ErrorFeedback);

	auto EnemyLifeLabel = Label::createWithTTF("Enemy Health", "fonts/Marker Felt.ttf", 24);
	EnemyLifeLabel->setPosition(Vec2(origin.x + 700,
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(EnemyLifeLabel, 1);

	auto EnemyLifeLabelValue = Label::createWithTTF(StringEnemyLife, "fonts/Marker Felt.ttf", 24);
	EnemyLifeLabelValue->setPosition(Vec2(origin.x + (EnemyLifeLabel->getContentSize().width + 700),
		origin.y + visibleSize.height - LifeLabel->getContentSize().height));
	this->addChild(EnemyLifeLabelValue, 1, LabelEnemyLife);

	auto BackgroundSprite = Sprite::create("Background.png");
	BackgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, (visibleSize.height / 2 + origin.y)-1));
	this->addChild(BackgroundSprite, 0);

	//auto Cover = Sprite::create("backgroungCoverEndTurn.png");
	//Cover->setPosition(Vec2(origin.x + visibleSize.width - Cover->getContentSize().width, 70));
	//this->addChild(Cover, 2, CoverImage);

	EndTurn = MenuItemImage::create("EndTurn.png", "EndTurn.png", CC_CALLBACK_1(NewSinglePlayGame::EndRoundTurn, this));
	EndTurn->setPosition(Vec2(origin.x + visibleSize.width - EndTurn->getContentSize().width, 70));
	auto menu = Menu::create(EndTurn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1, CoverImage);
	EndTurn->setEnabled(true);

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
	this->addChild(TowerArea00, 1, Tower00);

	auto TowerArea01 = Sprite::create("testTowerArea.png");
	TowerArea01->setPosition(Vec2(175, 395));
	TowerArea01->setOpacity(0);
	this->addChild(TowerArea01, 1, Tower01);

	auto TowerArea02 = Sprite::create("testTowerArea.png");
	TowerArea02->setPosition(Vec2(175, 321));
	TowerArea02->setOpacity(0);
	this->addChild(TowerArea02, 1, Tower02);

	auto TowerArea03 = Sprite::create("testTowerArea.png");
	TowerArea03->setPosition(Vec2(175, 246));
	TowerArea03->setOpacity(0);
	this->addChild(TowerArea03, 1, Tower03);
	
	auto TowerArea10 = Sprite::create("testTowerArea.png");
	TowerArea10->setPosition(Vec2(250, 468));
	TowerArea10->setOpacity(0);
	this->addChild(TowerArea10, 1, Tower10);

	auto TowerArea11 = Sprite::create("testTowerArea.png");
	TowerArea11->setPosition(Vec2(250, 395));
	TowerArea11->setOpacity(0);
	this->addChild(TowerArea11, 1, Tower11);

	auto TowerArea12 = Sprite::create("testTowerArea.png");
	TowerArea12->setPosition(Vec2(250, 321));
	TowerArea12->setOpacity(0);
	this->addChild(TowerArea12, 1, Tower12);

	auto TowerArea13 = Sprite::create("testTowerArea.png");
	TowerArea13->setPosition(Vec2(250, 246));
	TowerArea13->setOpacity(0);
	this->addChild(TowerArea13, 1, Tower13);

	auto TowerArea20 = Sprite::create("testTowerArea.png");
	TowerArea20->setPosition(Vec2(326, 468));
	TowerArea20->setOpacity(0);
	this->addChild(TowerArea20, 1, Tower20);

	auto TowerArea21 = Sprite::create("testTowerArea.png");
	TowerArea21->setPosition(Vec2(326, 395));
	TowerArea21->setOpacity(0);
	this->addChild(TowerArea21, 1, Tower21);

	auto TowerArea22 = Sprite::create("testTowerArea.png");
	TowerArea22->setPosition(Vec2(326, 321));
	TowerArea22->setOpacity(0);
	this->addChild(TowerArea22, 1, Tower22);

	auto TowerArea23 = Sprite::create("testTowerArea.png");
	TowerArea23->setPosition(Vec2(326, 246));
	TowerArea23->setOpacity(0);
	this->addChild(TowerArea23, 1, Tower23);

	auto TowerArea30 = Sprite::create("testTowerArea.png");
	TowerArea30->setPosition(Vec2(401, 468));
	TowerArea30->setOpacity(0);
	this->addChild(TowerArea30, 1, Tower30);

	auto TowerArea31 = Sprite::create("testTowerArea.png");
	TowerArea31->setPosition(Vec2(401, 395));
	TowerArea31->setOpacity(0);
	this->addChild(TowerArea31, 1, Tower31);

	auto TowerArea32 = Sprite::create("testTowerArea.png");
	TowerArea32->setPosition(Vec2(401, 321));
	TowerArea32->setOpacity(0);
	this->addChild(TowerArea32, 1, Tower32);

	auto TowerArea33 = Sprite::create("testTowerArea.png");
	TowerArea33->setPosition(Vec2(401, 246));
	TowerArea33->setOpacity(0);
	this->addChild(TowerArea33, 1, Tower33);

	this->schedule(schedule_selector(NewSinglePlayGame::SpriteRemove), 1.0f);
	this->scheduleUpdate();

	displayHand(p);
	displayHand(p);
	return true;
}

void NewSinglePlayGame::GameState()
{
	if (p->getLife() <= 0)
	{
		NewSinglePlayGame::LostGame();
	}
	else if (Enemylife <= 0)
	{
		NewSinglePlayGame::WonGame();
	}
}

void NewSinglePlayGame::WonGame()
{
	score = p->getLife() * (p->getResource()/100);
	p->reset();
//	delete baseGrid;
	spriteAnimation.clear();
	removeAction.clear();
	
	cocos2d::experimental::AudioEngine::stopAll();

	auto GameWonScene = GameWonScreen::createScene(score);
	Director::getInstance()->pushScene(GameWonScene);
}

void NewSinglePlayGame::LostGame()
{
	p->reset();
//	delete baseGrid;
	spriteAnimation.clear();
	removeAction.clear();

	cocos2d::experimental::AudioEngine::stopAll();

	auto GameOverScene = GameOverScreen::createScene();
	Director::getInstance()->pushScene(GameOverScene);
}

void NewSinglePlayGame::EndRoundTurn(cocos2d::Ref* pSender)
{
	EndTurn->setEnabled(false);
	this->schedule(schedule_selector(NewSinglePlayGame::MenuDisable), 2.0);
	//std::string StringFeedBack = "Wait";
	//CCLabelBMFont* ChangeFeedback = (CCLabelBMFont*)getChildByTag(ErrorFeedback);
	//ChangeFeedback->setString(StringFeedBack);
	
	int r, t;
	bool hasAttacked = false;

	for (int i = 0; (unsigned)i < army.size(); i++)
	{
		r = army.at(i)->getPositionX();
		t = army.at(i)->getPositionY();

		if ((army.at(i)->getPositionX()) == 9)
		{
			Enemylife = Enemylife - 40;
			GameState();

			CCLOG("CHECKING AUDIO");
			Options EffectsMusic;
			if (EffectsMusic.getEffectsMute() != 1) {
				int V = EffectsMusic.EffectsVolume();
				CCLOG("gameMusic.getmusicVolume() %d", V);
				SinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("WallAttack.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
			}

			std::string StringEnemyLife = std::to_string(Enemylife);
			CCLabelBMFont* ChangeEnemyLife = (CCLabelBMFont*)getChildByTag(LabelEnemyLife);
			ChangeEnemyLife->setString(StringEnemyLife);
			moveForward.removeObject(army.at(i)->getPositionX(), army.at(i)->getPositionY());
			army.at(i)->getSprite()->removeFromParentAndCleanup(true);
			army.erase(army.begin() + i);
			hasAttacked = true;
			i--;
		}
		if (!hasAttacked)
		{
			if (army.at(i) != NULL)
			{
				if (moveForward.playerCollisionDetect(army.at(i)->getPositionX(),
					army.at(i)->getPositionY(), 'P') == 0)
				{
					if (army.at(i)->getSprite()->getPositionX() + 75 < 825)
					{
						//auto moveBy = MoveBy::create(1, Vec2(75, 0));
						//army.at(i)->getSprite()->runAction(moveBy);
						army.at(i)->setPositionX(army.at(i)->getPositionX() + 1);
						army.at(i)->isMoving(true);

					}
				}
				else if (moveForward.playerCollisionDetect(army.at(i)->getPositionX(),
					army.at(i)->getPositionY(), 'P') == 1)
				{
					CCLOG("CAN'T MOVE FORWARD Enemy");
					CCLOG("Current i %d :else if 1:", i);
					//call attack
					//deal damage to enemy = to attack
					
				}
				else if (moveForward.playerCollisionDetect(army.at(i)->getPositionX(),
					army.at(i)->getPositionY(), 'P') == 2)
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

	for (int x = 0; (unsigned)x < enemyArmy.size(); x++)
	{
		if (x < 0)
		{
			x = 0;
		}
		int place = enemyArmy.at(x)->getPositionX();
		if ((enemyArmy.at(x)->getPositionX()) == 0)
		{
			p->setLife(40);
			GameState();

			CCLOG("CHECKING AUDIO");
			Options EffectsMusic;
			if (EffectsMusic.getEffectsMute() != 1) {
				int V = EffectsMusic.EffectsVolume();
				CCLOG("gameMusic.getmusicVolume() %d", V);
				SinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("WallAttack.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
			}

			moveForward.removeObject(enemyArmy.at(x)->getPositionX(), enemyArmy.at(x)->getPositionY());
			std::string StringLife = std::to_string(p->getLife());
			CCLabelBMFont* ChangePlayerLife = (CCLabelBMFont*)getChildByTag(LabelTagLife);
			ChangePlayerLife->setString(StringLife);
			enemyArmy.at(x)->getSprite()->removeFromParentAndCleanup(true);
			//			this->removeChild(enemyArmy.at(x)->getSprite());
			enemyArmy.erase(enemyArmy.begin() + x);
			x--;
			hasAttacked = true;
		}

		if (!hasAttacked)
		{
			if (enemyArmy.at(x) != NULL)
			{
				if (moveForward.enemyCollisionDetect(enemyArmy.at(x)->getPositionX(), enemyArmy.at(x)->getPositionY(), 'E') == 0)
				{
					if (enemyArmy.at(x)->getSprite()->getPositionX() - 75 > 75)
					{
						enemyArmy.at(x)->setPositionX(enemyArmy.at(x)->getPositionX() - 1);
						enemyArmy.at(x)->isMoving(true);
					}
				}
				else if (moveForward.enemyCollisionDetect(enemyArmy.at(x)->getPositionX(), enemyArmy.at(x)->getPositionY(), 'E') == 1)
				{
					for (int y = 0; y < army.size(); y++)
					{
						if (enemyArmy.size() > 0)
						{
							if (x < 0)
							{
								x = 0;
							}
							if (army.at(y)->getPositionX() == enemyArmy.at(x)->getPositionX() - 1
							&& army.at(y)->getPositionY() == enemyArmy.at(x)->getPositionY()) // x = -1
							{
								army.at(y)->isAttacking(true);
								enemyArmy.at(x)->isAttacking(true);
								army.at(y)->setHealth(enemyArmy.at(x)->getAttack());
								enemyArmy.at(x)->setHealth(army.at(y)->getAttack());
							}
						}
					}
				}
				else if (moveForward.enemyCollisionDetect(enemyArmy.at(x)->getPositionX(), enemyArmy.at(x)->getPositionY(), 'E') == 2)
				{
					//Player in front
				}
			}
		}
		//x++;
		hasAttacked = false;
	}

	//soldier movement above
	//tower movement below
	bool hasShot = false;

	CCLOG("before TOWER attack statement");
	for (int o = 0; o < enemyTowers.size(); o++)
	{
		CCLOG("TOWER attack statement");
		CCLOG("MOVE, r = %d, t = %d", enemyTowers.at(o)->getPositionX(), enemyTowers.at(o)->getPositionY());
		
		if (moveForward.enemyTowerAttacks(enemyTowers.at(o)->getPositionX(), enemyTowers.at(o)->getPositionY()) == 0)
		{	
			//animation for shooting
			for (int z = 0; z < army.size(); z++)
			{
				if (army.at(z)->getPositionX() == enemyTowers.at(o)->getPositionX() + 5
					&& army.at(z)->getPositionY() == enemyTowers.at(o)->getPositionY())
				{
					CCLOG("CHECKING AUDIO");
					Options EffectsMusic;
					if (EffectsMusic.getEffectsMute() != 1) {
						int V = EffectsMusic.EffectsVolume();
						CCLOG("gameMusic.getmusicVolume() %d", V);
						SinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
					}

					//0-0
					auto Bullet = Sprite::create("TowerBullet.png");
					spriteAnimation.push_back(Bullet);
					int BulletX = moveForward.enemyTowerBulletX(enemyTowers.at(o)->getPositionX());
					int BulletY = moveForward.TowerBulletY(enemyTowers.at(o)->getPositionY());
					Bullet->setPosition(Vec2(BulletX, BulletY));
					this->addChild(Bullet, 1);
					auto moveTo = MoveTo::create(3.0, Vec2(BulletX - 40, BulletY + 35));
					auto fade = FadeOut::create(0.1f);
					auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
					removeAction.push_back(runAction(BulletAttack));
					//Bullet->runAction(moveTo);
					Bullet->runAction(removeAction.back());
					

					//CCLOG("1 if");
					hasShot = true;
					army.at(z)->setHealth(enemyTowers.at(o)->getDamage());
				}
			}
		}
		//CCLOG("before ONE");
		if(moveForward.enemyTowerAttacks(enemyTowers.at(o)->getPositionX(), enemyTowers.at(o)->getPositionY()) == 1)
		{
			//animation for shooting
			for (int z = 0; z < army.size(); z++)
			{
				if (army.at(z)->getPositionX() == enemyTowers.at(o)->getPositionX() + 5
					&& army.at(z)->getPositionY() == enemyTowers.at(o)->getPositionY()+1)
				{
					CCLOG("CHECKING AUDIO");
					Options EffectsMusic;
					if (EffectsMusic.getEffectsMute() != 1) {
						int V = EffectsMusic.EffectsVolume();
						CCLOG("gameMusic.getmusicVolume() %d", V);
						SinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
					}

					//0-1
					auto Bullet = Sprite::create("TowerBullet.png");
					spriteAnimation.push_back(Bullet);
					int BulletX = moveForward.enemyTowerBulletX(enemyTowers.at(o)->getPositionX());
					int BulletY = moveForward.TowerBulletY(enemyTowers.at(o)->getPositionY());
					Bullet->setPosition(Vec2(BulletX, BulletY));
					this->addChild(Bullet, 1);
					auto moveTo = MoveTo::create(3.0, Vec2(BulletX - 40, BulletY - 35));
					auto fade = FadeOut::create(0.1f);
					auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
					removeAction.push_back(runAction(BulletAttack));
					//Bullet->runAction(moveTo);
					Bullet->runAction(removeAction.back());

					//CCLOG("1 if");
					hasShot = true;
					army.at(z)->setHealth(enemyTowers.at(o)->getDamage());
				}
			}
		}

		if (moveForward.enemyTowerAttacks(enemyTowers.at(o)->getPositionX(), enemyTowers.at(o)->getPositionY()) == 2)
		{
			//animation for shooting
			for (int z = 0; z < army.size(); z++)
			{
				if (army.at(z)->getPositionX() == enemyTowers.at(o)->getPositionX() + 6
					&& army.at(z)->getPositionY() == enemyTowers.at(o)->getPositionY())
				{
					CCLOG("CHECKING AUDIO");
					Options EffectsMusic;
					if (EffectsMusic.getEffectsMute() != 1) {
						int V = EffectsMusic.EffectsVolume();
						CCLOG("gameMusic.getmusicVolume() %d", V);
						SinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
					}

					//1-0
					auto Bullet = Sprite::create("TowerBullet.png");
					spriteAnimation.push_back(Bullet);
					int BulletX = moveForward.enemyTowerBulletX(enemyTowers.at(o)->getPositionX());
					int BulletY = moveForward.TowerBulletY(enemyTowers.at(o)->getPositionY());
					Bullet->setPosition(Vec2(BulletX, BulletY));
					this->addChild(Bullet, 1);
					auto moveTo = MoveTo::create(3.0, Vec2(BulletX + 35, BulletY + 35));
					auto fade = FadeOut::create(0.1f);
					auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
					removeAction.push_back(runAction(BulletAttack));
					//Bullet->runAction(moveTo);
					Bullet->runAction(removeAction.back());


					hasShot = true;
					army.at(z)->setHealth(enemyTowers.at(o)->getDamage());
				}
			}
		}
		
		if (moveForward.enemyTowerAttacks(enemyTowers.at(o)->getPositionX(), enemyTowers.at(o)->getPositionY()) == 3)
		{
			//animation for shooting
			for (int z = 0; z < army.size(); z++)
			{
				if (army.at(z)->getPositionX() == enemyTowers.at(o)->getPositionX() + 6
					&& army.at(z)->getPositionY() == enemyTowers.at(o)->getPositionY() + 1)
				{
					CCLOG("CHECKING AUDIO");
					Options EffectsMusic;
					if (EffectsMusic.getEffectsMute() != 1) {
						int V = EffectsMusic.EffectsVolume();
						CCLOG("gameMusic.getmusicVolume() %d", V);
						SinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
					}

					//1-1
					auto Bullet = Sprite::create("TowerBullet.png");
					spriteAnimation.push_back(Bullet);
					int BulletX = moveForward.enemyTowerBulletX(enemyTowers.at(o)->getPositionX());
					int BulletY = moveForward.TowerBulletY(enemyTowers.at(o)->getPositionY());
					Bullet->setPosition(Vec2(BulletX, BulletY));
					this->addChild(Bullet, 1);
					auto moveTo = MoveTo::create(3.0, Vec2(BulletX + 35, BulletY - 35));
					auto fade = FadeOut::create(0.1f);
					auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
					removeAction.push_back(runAction(BulletAttack));
					//Bullet->runAction(moveTo);
					Bullet->runAction(removeAction.back());

					hasShot = true;
				}
			}

		}
		hasShot = false;
	}
	for (int q = 0; q < towers.size(); q++)
	{
		CCLOG("TOWER attack statement");
		CCLOG("MOVE, r = %d, t = %d", towers.at(q)->getPositionX(), towers.at(q)->getPositionY());

		CCLOG("BEFORE TOWER IF");
		if (moveForward.towerAttacks(towers.at(q)->getPositionX(), towers.at(q)->getPositionY()) == 0)
		{
			//animation for shooting
			CCLOG("AFTER IF BEFORE FOR");
			for (int r = 0; r < enemyArmy.size(); r++)
			{
				CCLOG("BEFORE TOWER IF");
				if (enemyArmy.at(r)->getPositionX() == towers.at(q)->getPositionX()
					&& enemyArmy.at(r)->getPositionY() == towers.at(q)->getPositionY())
				{
					CCLOG("CHECKING AUDIO");
					Options EffectsMusic;
					if (EffectsMusic.getEffectsMute() != 1) {
						int V = EffectsMusic.EffectsVolume();
						CCLOG("gameMusic.getmusicVolume() %d", V);
						SinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
					}

					//CCLOG("1 if");
					hasShot = true;
					
					if (hasShot == true)
					{
						//0-0
						auto Bullet = Sprite::create("TowerBullet.png");
						spriteAnimation.push_back(Bullet);
						int BulletX = moveForward.playerTowerBulletX(towers.at(q)->getPositionX());
						int BulletY = moveForward.TowerBulletY(towers.at(q)->getPositionY());
						Bullet->setPosition(Vec2(BulletX, BulletY));
						this->addChild(Bullet, 1);
						auto moveTo = MoveTo::create(3.0, Vec2(BulletX-40, BulletY+35));
						auto fade = FadeOut::create(0.1f);
						auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
						removeAction.push_back(runAction(BulletAttack));
						//Bullet->runAction(moveTo);
						Bullet->runAction(removeAction.back());
						CCLOG("RUNNING ACTION");
					}
					enemyArmy.at(r)->setHealth(towers.at(q)->getDamage());
				}
			}
		}
		//CCLOG("player before ONE");
		if (moveForward.towerAttacks(towers.at(q)->getPositionX(), towers.at(q)->getPositionY()) == 1)
		{
			for (int r = 0; r < enemyArmy.size(); r++)
			{
				if (enemyArmy.at(r)->getPositionX() == towers.at(q)->getPositionX()
					&& enemyArmy.at(r)->getPositionY() == towers.at(q)->getPositionY() + 1)
				{
					CCLOG("CHECKING AUDIO");
					Options EffectsMusic;
					if (EffectsMusic.getEffectsMute() != 1) {
						int V = EffectsMusic.EffectsVolume();
						CCLOG("gameMusic.getmusicVolume() %d", V);
						SinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
					}

					//CCLOG("1 if");
					hasShot = true;
					
					if (hasShot == true)
					{
						//0-1
						auto Bullet = Sprite::create("TowerBullet.png");
						spriteAnimation.push_back(Bullet);
						int BulletX = moveForward.playerTowerBulletX(towers.at(q)->getPositionX());
						int BulletY = moveForward.TowerBulletY(towers.at(q)->getPositionY());
						Bullet->setPosition(Vec2(BulletX, BulletY));
						this->addChild(Bullet, 1);
						auto moveTo = MoveTo::create(3.0, Vec2(BulletX - 40, BulletY - 35));
						auto fade = FadeOut::create(0.1f);
						auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
						removeAction.push_back(runAction(BulletAttack));
						//Bullet->runAction(moveTo);
						Bullet->runAction(removeAction.back());
						CCLOG("RUNNING ACTION");
					}
					enemyArmy.at(r)->setHealth(towers.at(q)->getDamage());
				}
			}
		
		}

		if (moveForward.towerAttacks(towers.at(q)->getPositionX(), towers.at(q)->getPositionY()) == 2)
		{
		 //animation for shooting
			for (int r = 0; r < enemyArmy.size(); r++)
			{
				if (enemyArmy.at(r)->getPositionX() == towers.at(q)->getPositionX() + 1
					&& enemyArmy.at(r)->getPositionY() == towers.at(q)->getPositionY())
				{
					CCLOG("CHECKING AUDIO");
					Options EffectsMusic;
					if (EffectsMusic.getEffectsMute() != 1) {
						int V = EffectsMusic.EffectsVolume();
						CCLOG("gameMusic.getmusicVolume() %d", V);
						SinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
					}

					//CCLOG("1 if");
					hasShot = true;
					
					if (hasShot == true)
					{
						//1-0
						auto Bullet = Sprite::create("TowerBullet.png");
						spriteAnimation.push_back(Bullet);
						int BulletX = moveForward.playerTowerBulletX(towers.at(q)->getPositionX());
						int BulletY = moveForward.TowerBulletY(towers.at(q)->getPositionY());
						Bullet->setPosition(Vec2(BulletX, BulletY));
						this->addChild(Bullet, 1);
						auto moveTo = MoveTo::create(3.0, Vec2(BulletX + 35, BulletY + 35));
						auto fade = FadeOut::create(0.1f);
						auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
						removeAction.push_back(runAction(BulletAttack));
						//Bullet->runAction(moveTo);
						Bullet->runAction(removeAction.back());
						CCLOG("RUNNING ACTION");
					}
					enemyArmy.at(r)->setHealth(towers.at(q)->getDamage());
				}
			}
		}

		if (moveForward.towerAttacks(towers.at(q)->getPositionX(), towers.at(q)->getPositionY()) == 3)
		{
			//animation for shooting
			for (int r = 0; r < enemyArmy.size(); r++)
			{
				if (enemyArmy.at(r)->getPositionX() == towers.at(q)->getPositionX() + 1
					&& enemyArmy.at(r)->getPositionY() == towers.at(q)->getPositionY() + 1)
				{
					CCLOG("CHECKING AUDIO");
					Options EffectsMusic;
					if (EffectsMusic.getEffectsMute() != 1) {
						int V = EffectsMusic.EffectsVolume();
						CCLOG("gameMusic.getmusicVolume() %d", V);
						SinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("TowerShot.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
					}

					//CCLOG("1 if");
					hasShot = true;
					
					if (hasShot==true) 
					{
					    //1-1
						
					    auto Bullet = Sprite::create("TowerBullet.png");
						spriteAnimation.push_back(Bullet);
						int BulletX = moveForward.playerTowerBulletX(towers.at(q)->getPositionX());
						int BulletY = moveForward.TowerBulletY(towers.at(q)->getPositionY());
					    Bullet->setPosition(Vec2(BulletX, BulletY));
					    this->addChild(Bullet, 1);
						auto moveTo = MoveTo::create(3.0, Vec2(BulletX + 35, BulletY - 35));
						auto fade = FadeOut::create(0.1f);
						auto BulletAttack = Sequence::create(moveTo, fade, nullptr);
						removeAction.push_back(runAction(BulletAttack));
						//Bullet->runAction(moveTo);
						Bullet->runAction(removeAction.back());
						CCLOG("RUNNING ACTION");
					}
					enemyArmy.at(r)->setHealth(towers.at(q)->getDamage());
				}
			}
			
		}
		hasShot = false;
	}

	CCLOG("Test For End Turn");
	enemyAI();

}

void NewSinglePlayGame::enemyAI()
{
	
	std::string StringEnemyLife = std::to_string(Enemylife);
	CCLabelBMFont* ChangeEnemyLife = (CCLabelBMFont*)getChildByTag(LabelEnemyLife);
	ChangeEnemyLife->setString(StringEnemyLife);

	//Can be used to check for collisions and win/lose conditions
	CollisionDetection RegEnemy;
	EnemyAI CreateEnemy;
	
	//Creates an enemy tower and adds it to the field
	int CreateLoop = 0;
	while(CreateLoop!=10000){
	    std::tuple<int, int, int, int, int> CreateEnemyObjects= CreateEnemy.checkVariables(p->getResource(), EnemyResource);
	    if (std::get<0>(CreateEnemyObjects) == 0)
	    {
			CCLOG("1-1 %d", std::get<0>(CreateEnemyObjects));
			CCLOG("2-2 %d", std::get<1>(CreateEnemyObjects));
			CCLOG("3-3 %d", std::get<2>(CreateEnemyObjects));
			CCLOG("4-4 %d", std::get<3>(CreateEnemyObjects));
			CCLOG("5-5 %d", std::get<4>(CreateEnemyObjects));
		    Tower* t1 = new Tower("SampleTower2.png");
			t1->setPositionX(std::get<3>(CreateEnemyObjects));
			t1->setPositionY(std::get<4>(CreateEnemyObjects));
			(RegEnemy.registerEnemyTower(std::get<3>(CreateEnemyObjects), std::get<4>(CreateEnemyObjects), 'T'));
		    t1->getSprite()->setPosition(Vec2(std::get<1>(CreateEnemyObjects), std::get<2>(CreateEnemyObjects)));
		    t1->getSprite()->setScale(2.0);
		    this->addChild(t1->getSprite(), 1);
		   
		    enemyTowers.push_back(t1);
		    EnemyResource = EnemyResource - 200;
	    }
	    else if (std::get<0>(CreateEnemyObjects) == 1) 
	    {
			if(RegEnemy.registerObject(std::get<3>(CreateEnemyObjects), std::get<4>(CreateEnemyObjects), 'E')==0)
			{
		        Soldier* s1 = new Soldier("testEnemy2.png");
			    (RegEnemy.registerObject(std::get<3>(CreateEnemyObjects), std::get<4>(CreateEnemyObjects), 'E') == 0);
			    s1->setPositionX(std::get<3>(CreateEnemyObjects));
			    s1->setPositionY(std::get<4>(CreateEnemyObjects));
			    s1->getSprite()->setPosition(Vec2(std::get<1>(CreateEnemyObjects), std::get<2>(CreateEnemyObjects)));
			    s1->getSprite()->setScale(2.0);
			    this->addChild(s1->getSprite(), 1);
			    enemyArmy.push_back(s1);
			    EnemyResource = EnemyResource - 100;
			}
			
			else 
			{
				std::get<0>(CreateEnemyObjects) = 10000;
			}
	    }
		
	CreateLoop = std::get<0>(CreateEnemyObjects);
    CCLOG("CREATELOOP %d", CreateLoop);
	}

	enemyTurn++;
	startTurn();
}

void NewSinglePlayGame::startTurn()
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
	EnemyAI t;
	//t.test();
	t.checkVariables(p->getResource(), EnemyResource);
	p->setResource(100);
	EnemyResource += 100;
	
	std::string s = std::to_string(p->getResource());
	CCLabelBMFont* ChangeResource = (CCLabelBMFont*)getChildByTag(LabelTagResource);
	ChangeResource->setString(s);
    
	p->drawCard();
	displayHand(p);
}

void NewSinglePlayGame::displayHand(Player* p)
{
	CCLOG("DECK SIZE %d", p->getDeckSize());
	for (int i = 0; i < 6; i++)
	{
		CCLOG("Card No: %d", i);
		if (getChildByTag(handSprite1 + i) != NULL)
		{
			getChildByTag(handSprite1 + i)->removeFromParentAndCleanup(true);
		}
	}
	//this->removeChildByTag(handSprite1);
	//this->removeChildByTag(handSprite2);
	//this->removeChildByTag(handSprite3);
	//this->removeChildByTag(handSprite4);
	//this->removeChildByTag(handSprite5);
	//this->removeChildByTag(handSprite6);

	//auto sprite = cocos2d::Sprite::create("HelloWorld.png");
	int i;
	for (i = 0; (unsigned)i < p->getHandSize(); i++)
	{
		//sprite = p->getCardInHand(i)->getSprite();
		//sprite->setPosition(Vec2(100 + (i * 100), 50));
		auto sprite = cocos2d::Sprite::create(p->getCardInHand(i)->getSpriteName());
		//sprite->setPosition(Vec2(100 + (i * 100), 50));
		this->addChild(sprite, 1, handSprite1 + i);
	
//		if (getChildByTag(handSprite1 + i) != NULL)
//		{
			this->getChildByTag(handSprite1 + i)->setPosition(Vec2(100 + (i * 100), 80));
			CCLOG("TAG %d", (handSprite1+i));
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
			OriginalXPos = target->getPosition().x;
			OriginalYPos = target->getPosition().y;
			
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
		if (tag == 2000)
		{
			type = p->getCardInHand(0)->getType();
		}
		else if (tag == 2001)
		{
			type = p->getCardInHand(1)->getType();
		}
		else if (tag == 2002)
		{
			type = p->getCardInHand(2)->getType();
		}
		else if (tag == 2003)
		{
			type = p->getCardInHand(3)->getType();
		}
		else if (tag == 2004)
		{
			type = p->getCardInHand(4)->getType();
		}
		else if (tag == 2005)
		{
			type = p->getCardInHand(5)->getType();
		}
		if (type == 's')
//		if(target->getTag())
		{
			target->setTexture("testEnemy.png");
		}
		else if (type == 't')
		{
			target->setTexture("SampleTower.png");
			if (CheckT.CheckTower(0, 0) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid00 = (Sprite*)getChildByTag(Tower00);
				TowerGrid00->setOpacity(200);
			}
			if (CheckT.CheckTower(0, 1) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid01 = (Sprite*)getChildByTag(Tower01);
				TowerGrid01->setOpacity(200);
			}
			if (CheckT.CheckTower(0, 2) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid02 = (Sprite*)getChildByTag(Tower02);
				TowerGrid02->setOpacity(200);
			}
			if (CheckT.CheckTower(0, 3) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid03 = (Sprite*)getChildByTag(Tower03);
				TowerGrid03->setOpacity(200);
			}
			if (CheckT.CheckTower(1, 0) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid10 = (Sprite*)getChildByTag(Tower10);
				TowerGrid10->setOpacity(200);
			}
			if (CheckT.CheckTower(1, 1) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid11 = (Sprite*)getChildByTag(Tower11);
				TowerGrid11->setOpacity(200);
			}
			if (CheckT.CheckTower(1, 2) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid12 = (Sprite*)getChildByTag(Tower12);
				TowerGrid12->setOpacity(200);
			}
			if (CheckT.CheckTower(1, 3) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid13 = (Sprite*)getChildByTag(Tower13);
				TowerGrid13->setOpacity(200);
			}
			if (CheckT.CheckTower(2, 0) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid20 = (Sprite*)getChildByTag(Tower20);
				TowerGrid20->setOpacity(200);
			}
			if (CheckT.CheckTower(2, 1) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid21 = (Sprite*)getChildByTag(Tower21);
				TowerGrid21->setOpacity(200);
			}
			if (CheckT.CheckTower(2, 2) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid22 = (Sprite*)getChildByTag(Tower22);
				TowerGrid22->setOpacity(200);
			}
			if (CheckT.CheckTower(2, 3) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid23 = (Sprite*)getChildByTag(Tower23);
				TowerGrid23->setOpacity(200);
			}
			if (CheckT.CheckTower(3, 0) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid30 = (Sprite*)getChildByTag(Tower30);
				TowerGrid30->setOpacity(200);
			}
			if (CheckT.CheckTower(3, 1) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid31 = (Sprite*)getChildByTag(Tower31);
				TowerGrid31->setOpacity(200);
			}
			if (CheckT.CheckTower(3, 2) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid32 = (Sprite*)getChildByTag(Tower32);
				TowerGrid32->setOpacity(200);
			}
			if (CheckT.CheckTower(3, 3) == 0)
			{
				CCLOG("Test Sprite Opacity");
				Sprite* TowerGrid33 = (Sprite*)getChildByTag(Tower33);
				TowerGrid33->setOpacity(200);
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
		if (tag == 2000)
		{
			type = p->getCardInHand(0)->getType();
			cost = p->getCardInHand(0)->getCost();
			spriteName = p->getCardInHand(0)->getSpriteName();
		}
		else if (tag == 2001)
		{
			type = p->getCardInHand(1)->getType();
			cost = p->getCardInHand(1)->getCost();
			spriteName = p->getCardInHand(1)->getSpriteName();
		}
		else if (tag == 2002)
		{
			type = p->getCardInHand(2)->getType();
			cost = p->getCardInHand(2)->getCost();
			spriteName = p->getCardInHand(2)->getSpriteName();
		}
		else if (tag == 2003)
		{
			type = p->getCardInHand(3)->getType();
			cost = p->getCardInHand(3)->getCost();
			spriteName = p->getCardInHand(3)->getSpriteName();
		}
		else if (tag == 2004)
		{
			type = p->getCardInHand(4)->getType();
			cost = p->getCardInHand(4)->getCost();
			spriteName = p->getCardInHand(4)->getSpriteName();
		}
		else if (tag == 2005)
		{
			type = p->getCardInHand(5)->getType();
			cost = p->getCardInHand(5)->getCost();
			spriteName = p->getCardInHand(5)->getSpriteName();
		}
		CCLabelBMFont* ChangeText = (CCLabelBMFont*)getChildByTag(ErrorFeedback);

		//Scale of images when they return to the hand need fixed
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(0);
							towers.at(towers.size() - 1)->setPositionY(0);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(176, 478));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
							target->setTexture(spriteName);
						}
					}
					//Col - 0  Grid postion 0-1
					else if (target->getPosition().x > 136 && target->getPosition().x < 213 && target->getPosition().y > 359 && target->getPosition().y < 431)
					{
						if (RegObjects.registerTower(0, 1, 'T') == 0)
						{
							target->setPosition(174, 402);
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(0);
							towers.at(towers.size() - 1)->setPositionY(1);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(174, 402));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							p->setResource(-cost);
							ChangeText->setString("Tower Placed");
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(0);
							towers.at(towers.size() - 1)->setPositionY(2);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(174, 330));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(0);
							towers.at(towers.size() - 1)->setPositionY(3);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(174, 256));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(1);
							towers.at(towers.size() - 1)->setPositionY(0);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(250, 478));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(1);
							towers.at(towers.size() - 1)->setPositionY(1);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(250, 402));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(1);
							towers.at(towers.size() - 1)->setPositionY(2);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(250, 330));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(1);
							towers.at(towers.size() - 1)->setPositionY(3);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(250, 258));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(2);
							towers.at(towers.size() - 1)->setPositionY(0);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(325, 478));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(2);
							towers.at(towers.size() - 1)->setPositionY(1);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(325, 402));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(2);
							towers.at(towers.size() - 1)->setPositionY(2);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(325, 330));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(2);
							towers.at(towers.size() - 1)->setPositionY(3);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(325, 258));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(3);
							towers.at(towers.size() - 1)->setPositionY(0);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(401, 478));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(3);
							towers.at(towers.size() - 1)->setPositionY(1);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(401, 402));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(3);
							towers.at(towers.size() - 1)->setPositionY(2);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(401, 330));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							towers.push_back(new Tower("SampleTower.png"));
							towers.at(towers.size() - 1)->setPositionX(3);
							towers.at(towers.size() - 1)->setPositionY(3);
							towers.at(towers.size() - 1)->getSprite()->setPosition(Vec2(401, 258));
							towers.at(towers.size() - 1)->getSprite()->setScale(2.0);
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((towers.at(towers.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
							target->setTexture(spriteName);
						}
					}
					else
					{
						target->setTexture("SampleCard.png");
						target->setPosition(Vec2(OriginalXPos, OriginalYPos));
					}
				}
				else
				{
					ChangeText->setString("Not enough resources");
					CCLOG("No Resource available");
					target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(0);
							army.at(army.size() - 1)->setPositionY(0);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(137, 504));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(0);
							army.at(army.size() - 1)->setPositionY(1);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(137, 431));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(0);
							army.at(army.size() - 1)->setPositionY(2);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(137, 358));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());

						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");							army.at(army.size() - 1)->setPositionX(0);
							army.at(army.size() - 1)->setPositionY(3);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(137, 285));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());

						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(0);
							army.at(army.size() - 1)->setPositionY(4);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(137, 211));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());

						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(1);
							army.at(army.size() - 1)->setPositionY(0);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(214, 504));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());

						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(1);
							army.at(army.size() - 1)->setPositionY(1);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(214, 431));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(1);
							army.at(army.size() - 1)->setPositionY(2);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(214, 358));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(1);
							army.at(army.size() - 1)->setPositionY(3);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(214, 285));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(1);
							army.at(army.size() - 1)->setPositionY(4);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(214, 211));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(2);
							army.at(army.size() - 1)->setPositionY(0);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(288, 504));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(2);
							army.at(army.size() - 1)->setPositionY(1);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(288, 431));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(2);
							army.at(army.size() - 1)->setPositionY(2);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(288, 358));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(2);
							army.at(army.size() - 1)->setPositionY(3);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(288, 285));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(2);
							army.at(army.size() - 1)->setPositionY(4);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(288, 211));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(3);
							army.at(army.size() - 1)->setPositionY(0);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(364, 504));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(3);
							army.at(army.size() - 1)->setPositionY(1);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(364, 431));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(3);
							army.at(army.size() - 1)->setPositionY(2);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(364, 358));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(3);
							army.at(army.size() - 1)->setPositionY(3);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(364, 285));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(3);
							army.at(army.size() - 1)->setPositionY(4);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(364, 211));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(4);
							army.at(army.size() - 1)->setPositionY(0);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(441, 504));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(4);
							army.at(army.size() - 1)->setPositionY(1);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(441, 431));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(4);
							army.at(army.size() - 1)->setPositionY(2);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(441, 358));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(4);
							army.at(army.size() - 1)->setPositionY(3);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(441, 285));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
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
							army.push_back(new Soldier(spriteName));
							army.at(army.size() - 1)->getSprite()->setTexture("testEnemy.png");
							army.at(army.size() - 1)->setPositionX(4);
							army.at(army.size() - 1)->setPositionY(4);
							army.at(army.size() - 1)->getSprite()->setPosition(Vec2(441, 211));
							army.at(army.size() - 1)->getSprite()->setScale(2.0);
							p->removeFromHand(target->getTag());
							target->removeFromParentAndCleanup(true);
							displayHand(p);
							this->addChild((army.at(army.size() - 1))->getSprite());
						}
						else
						{
							CCLOG("Can't place here");
							ChangeText->setString("Can't place here");
							target->setPosition(Vec2(OriginalXPos, OriginalYPos));
							target->setTexture(spriteName);
							target->setScale(1.0);
						}
					}
				}
				else
				{
					ChangeText->setString("Not enough resources");
					CCLOG("No Resource available");
					target->setPosition(Vec2(OriginalXPos, OriginalYPos));
					target->setTexture(spriteName);
					target->setScale(1.0);
				}
			}
		}
		else
		{
			//target->setPosition(origin + Vec2((visibleSize.width / 2) + 100, (visibleSize.height / 2) - 200));
			target->setPosition(Vec2(OriginalXPos, OriginalYPos));
			target->setTexture(spriteName);
			//target->setTexture(spriteTemplate->getTexture());
			target->setScale(1.0);
			target->setOpacity(255);
		}
		CCLabelBMFont* ChangeResource = (CCLabelBMFont*)getChildByTag(LabelTagResource);
		std::string StringResource = std::to_string(p->getResource());
		ChangeResource->setString(StringResource);

		Sprite* towerG_00 = (Sprite*)getChildByTag(Tower00);
		towerG_00->setOpacity(0);
		Sprite* towerG_01 = (Sprite*)getChildByTag(Tower01);
		towerG_01->setOpacity(0);
		Sprite* towerG_02 = (Sprite*)getChildByTag(Tower02);
		towerG_02->setOpacity(0);
		Sprite* towerG_03 = (Sprite*)getChildByTag(Tower03);
		towerG_03->setOpacity(0);
		Sprite* towerG_10 = (Sprite*)getChildByTag(Tower10);
		towerG_10->setOpacity(0);
		Sprite* towerG_11 = (Sprite*)getChildByTag(Tower11);
		towerG_11->setOpacity(0);
		Sprite* towerG_12 = (Sprite*)getChildByTag(Tower12);
		towerG_12->setOpacity(0);
		Sprite* towerG_13 = (Sprite*)getChildByTag(Tower13);
		towerG_13->setOpacity(0);
		Sprite* towerG_20 = (Sprite*)getChildByTag(Tower20);
		towerG_20->setOpacity(0);
		Sprite* towerG_21 = (Sprite*)getChildByTag(Tower21);
		towerG_21->setOpacity(0);
		Sprite* towerG_22 = (Sprite*)getChildByTag(Tower22);
		towerG_22->setOpacity(0);
		Sprite* towerG_23 = (Sprite*)getChildByTag(Tower23);
		towerG_23->setOpacity(0);
		Sprite* towerG_30 = (Sprite*)getChildByTag(Tower30);
		towerG_30->setOpacity(0);
		Sprite* towerG_31 = (Sprite*)getChildByTag(Tower31);
		towerG_31->setOpacity(0);
		Sprite* towerG_32 = (Sprite*)getChildByTag(Tower32);
		towerG_32->setOpacity(0);
		Sprite* towerG_33 = (Sprite*)getChildByTag(Tower33);
		towerG_33->setOpacity(0);
	};
	if (p->getHandSize() > 0)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->getChildByTag(handSprite1));
	}
	for (int j = 0; j < p->getHandSize(); j++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this->getChildByTag(handSprite1 + j));
	}
}

int NewSinglePlayGame::getScore()
{
	CCLOG("Score: getScore: %d", score);
	return score;
}

void NewSinglePlayGame::SpriteRemove(float ct)
{
	/*
	if (numberOfRunningActions() != 0)
	{
		if (CoverTest == false) {
			CCLOG("RAN");
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Vec2 origin = Director::getInstance()->getVisibleOrigin();
			auto Cover = Sprite::create("backgroungCoverEndTurn.png");
			Cover->setPosition(Vec2(origin.x + visibleSize.width - Cover->getContentSize().width, 70));
			this->addChild(Cover, 2, CoverImage);
			CoverTest = true;
		}
	}
	if (numberOfRunningActions() == 0)
	{
		if (CoverTest == true)
		{
			//removeAllChildrenWithCleanup(getChildByTag(CoverImage));
		}
		CoverTest == false;
	}
	*/

	for (int c = 0; c < army.size(); c++) 
	{
		if (army.at(c)->getMoving() == true) 
		{
			auto moveBy = MoveBy::create(1, Vec2(75, 0));
			//army.at(c)->getSprite()->runAction(moveBy);
            SoldierMovement.push_back(runAction(moveBy));
			army.at(c)->getSprite()->runAction(SoldierMovement.back());
			//army.at(c)->setPositionX(army.at(c)->getPositionX() + 1);
			army.at(c)->isMoving(false);
		}
	}
	
	for (int b = 0; b < enemyArmy.size(); b++)
	{
		if (enemyArmy.at(b)->getMoving() == true) 
		{
			auto moveBy = MoveBy::create(1, Vec2(-75, 0));
			SoldierMovement.push_back(runAction(moveBy));
			enemyArmy.at(b)->getSprite()->runAction(SoldierMovement.back());
			//enemyArmy.at(b)->getSprite()->runAction(moveBy);
			//enemyArmy.at(b)->setPositionX(enemyArmy.at(b)->getPositionX() - 1);
			enemyArmy.at(b)->isMoving(false);
		}
	}
	if (SoldierMovement.size()!=0) 
	{
		for (int q = 0; q < SoldierMovement.size(); q++)
		{
			if (SoldierMovement.at(q)->isDone())
			{
				SoldierMovement.erase(SoldierMovement.begin() + q);
			}
		}
	}
	
	if (SoldierMovement.size()==0) {
		for (int r = 0; r < army.size(); r++)
		{
			if (army.at(r)->getAttacking() == true)
			{
				CCLOG("CHECKING AUDIO");
				Options EffectsMusic;
				if (EffectsMusic.getEffectsMute() != 1) {
					int V = EffectsMusic.EffectsVolume();
					CCLOG("gameMusic.getmusicVolume() %d", V);
					SinglePlayGameMusic = cocos2d::experimental::AudioEngine::play2d("SwordClash.mp3", false, EffectsMusic.getMusicFloatVolume(V), nullptr);
				}
				auto PlayerSwordSlash = Sprite::create("PlayerSwordAttack.png");
				PlayerSwordSlash->setPosition(Vec2(army.at(r)->getSprite()->getPositionX() + 20, army.at(r)->getSprite()->getPositionY()));
				PlayerSwordSlash->setOpacity(0);
				this->addChild(PlayerSwordSlash, 1);
				auto fadeIn = FadeIn::create(0.5f);
				auto fadeOut = FadeOut::create(0.5f);
				auto PlayerAttackSeq = Sequence::create(fadeIn, fadeOut, nullptr);
				PlayerSwordSlash->runAction(PlayerAttackSeq);
				army.at(r)->isAttacking(false);
			}
		}
		for (int r = 0; r < enemyArmy.size(); r++)
		{
			if (enemyArmy.at(r)->getAttacking() == true)
			{
				auto EnemySwordSlash = Sprite::create("EnemySoldierAttack.png");
				EnemySwordSlash->setPosition(Vec2(enemyArmy.at(r)->getSprite()->getPositionX() - 20, enemyArmy.at(r)->getSprite()->getPositionY()));
				EnemySwordSlash->setOpacity(0);
				this->addChild(EnemySwordSlash, 1);
				auto fadeIn = FadeIn::create(0.5f);
				auto fadeOut = FadeOut::create(0.5f);
				auto EnemyAttackSeq = Sequence::create(fadeIn, fadeOut, nullptr);
				EnemySwordSlash->runAction(EnemyAttackSeq);
				enemyArmy.at(r)->isAttacking(false);
			}
		}

		if (removeAction.size() != 0)
		{
			for (int q = 0; q < removeAction.size(); q++)
			{
				if (removeAction.at(q)->isDone())
				{
					spriteAnimation.at(q)->removeFromParentAndCleanup(true);
					spriteAnimation.erase(spriteAnimation.begin() + q);
					removeAction.erase(removeAction.begin() + q);
				}
			}
		}

		if (removeAction.size() == 0)
		{
			for (int x = 0; x < enemyArmy.size(); x++)
			{
				if (enemyArmy.at(x)->getHealth() <= 0)
				{
					moveForward.removeObject(enemyArmy.at(x)->getPositionX(), enemyArmy.at(x)->getPositionY());
					enemyArmy.at(x)->getSprite()->removeFromParentAndCleanup(true);
					enemyArmy.erase(enemyArmy.begin() + x);
					x--;
					p->setResource(50);
				}
			}
			for (int y = 0; y < army.size(); y++)
			{
				if (army.at(y)->getHealth() <= 0)
				{
					moveForward.removeObject(army.at(y)->getPositionX(), army.at(y)->getPositionY());
					army.at(y)->activateAbility(p);
					CCLabelBMFont* ChangeLife = (CCLabelBMFont*)getChildByTag(LabelTagLife);
					std::string StringLife = std::to_string(p->getLife());
					ChangeLife->setString(StringLife);
					army.at(y)->getSprite()->removeFromParentAndCleanup(true);
					army.erase(army.begin() + y);
					y--;
					EnemyResource += 50;
				}
			}
		}
	}
}

void NewSinglePlayGame::MenuDisable(float ct) 
{
	EndTurn->setEnabled(true);
}
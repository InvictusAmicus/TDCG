#include "LeaderBoard.h"
#include "MultiPlayer.h"
#include <string>
#include <iostream>
#include <tuple>

USING_NS_CC;

Scene* LeaderBoard::createScene()
{
	// 'scene' is an autorelease object
	auto LeaderBoard = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LeaderBoard::create();

	// add layer as a child to scene
	LeaderBoard->addChild(layer);

	// return the scene
	return LeaderBoard;
}

bool LeaderBoard::init()
{
	
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	G1 = "";
	G2 = "";
	G3 = "";
	G4 = "";
	G5 = "";

	L1 = "";
	L2 = "";
	L3 = "";
	L4 = "";
	L5 = "";

	/*
	std::tuple<std::string, std::string, std::string, std::string, std::string, std::string, 
		std::string, std::string, std::string, std::string, > ScoreList;

	G1 = std::get<0>(ScoreList);
	G2 = std::get<1>(ScoreList);
	G3 = std::get<2>(ScoreList);
	G4 = std::get<3>(ScoreList);
	G5 = std::get<4>(ScoreList);

	L1 = std::get<5>(ScoreList);
	L2 = std::get<6>(ScoreList);
	L3 = std::get<7>(ScoreList);
	L4 = std::get<8>(ScoreList);
	L5 = std::get<9>(ScoreList);
	*/

	auto label = Label::createWithTTF("Leaderboards", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	auto Back = MenuItemImage::create("Back.png", "BackClicked.png", CC_CALLBACK_1(LeaderBoard::returnToTitle, this));
	Back->setPosition(Vec2(origin.x + visibleSize.width - Back->getContentSize().width, 70));
	auto menu = Menu::create(Back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//auto NextPage = MenuItemImage::create("ArrowSelection.png", "ArrowSelection.png", CC_CALLBACK_1(MultiPlayerSearch::Next, this));
	//NextPage->setPosition(Vec2(origin.x + visibleSize.width - NextPage->getContentSize().width, 360));
	//auto menu1 = Menu::create(NextPage, NULL);
	//menu1->setPosition(Vec2::ZERO);
	//this->addChild(menu1, 1);

	auto sprite = Sprite::create("Background.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	auto GlobalLeaderBoard = Label::createWithTTF("Global LeaderBoard", "fonts/Marker Felt.ttf", 32);
	GlobalLeaderBoard->setPosition(Vec2(origin.x + visibleSize.width / 2,
		(origin.y + visibleSize.height - GlobalLeaderBoard->getContentSize().height)-60));
	GlobalLeaderBoard->setColor(ccc3(0, 0, 0));
	this->addChild(GlobalLeaderBoard, 1);

	auto G_LeaderBoard1 = Label::createWithTTF("1. "+G1, "fonts/Marker Felt.ttf", 24);
	G_LeaderBoard1->setPosition(Vec2(origin.x + visibleSize.width / 2,
		(origin.y + visibleSize.height - G_LeaderBoard1->getContentSize().height) - 120));
	G_LeaderBoard1->setColor(ccc3(0, 0, 0));
	this->addChild(G_LeaderBoard1, 1);

	auto G_LeaderBoard2 = Label::createWithTTF("2. "+G2, "fonts/Marker Felt.ttf", 24);
	G_LeaderBoard2->setPosition(Vec2(origin.x + visibleSize.width / 2,
		(origin.y + visibleSize.height - G_LeaderBoard2->getContentSize().height) - 160));
	G_LeaderBoard2->setColor(ccc3(0, 0, 0));
	this->addChild(G_LeaderBoard2, 1);

	auto G_LeaderBoard3 = Label::createWithTTF("3. " + G3, "fonts/Marker Felt.ttf", 24);
	G_LeaderBoard3->setPosition(Vec2(origin.x + visibleSize.width / 2,
		(origin.y + visibleSize.height - G_LeaderBoard3->getContentSize().height) - 200));
	G_LeaderBoard3->setColor(ccc3(0, 0, 0));
	this->addChild(G_LeaderBoard3, 1);

	auto G_LeaderBoard4 = Label::createWithTTF("4. " + G4, "fonts/Marker Felt.ttf", 24);
	G_LeaderBoard4->setPosition(Vec2(origin.x + visibleSize.width / 2,
		(origin.y + visibleSize.height - G_LeaderBoard4->getContentSize().height) - 240));
	G_LeaderBoard4->setColor(ccc3(0, 0, 0));
	this->addChild(G_LeaderBoard4, 1);

	auto G_LeaderBoard5 = Label::createWithTTF("5. " + G5, "fonts/Marker Felt.ttf", 24);
	G_LeaderBoard5->setPosition(Vec2(origin.x + visibleSize.width / 2,
		(origin.y + visibleSize.height - G_LeaderBoard5->getContentSize().height) - 280));
	G_LeaderBoard5->setColor(ccc3(0, 0, 0));
	this->addChild(G_LeaderBoard5, 1);

	auto LocalLeaderBoard = Label::createWithTTF("Local LeaderBoard", "fonts/Marker Felt.ttf", 32);
	LocalLeaderBoard->setPosition(Vec2(origin.x + visibleSize.width / 2,
		(origin.y + visibleSize.height / 2) - LocalLeaderBoard->getContentSize().height ));
	LocalLeaderBoard->setColor(ccc3(0, 0, 0));
	this->addChild(LocalLeaderBoard, 1);

	auto L_LeaderBoard1 = Label::createWithTTF("1. "+L1, "fonts/Marker Felt.ttf", 24);
	L_LeaderBoard1->setPosition(Vec2(origin.x + visibleSize.width / 2,
		((origin.y + visibleSize.height / 2) - L_LeaderBoard1->getContentSize().height)-60));
	L_LeaderBoard1->setColor(ccc3(0, 0, 0));
	this->addChild(L_LeaderBoard1, 1);

	auto L_LeaderBoard2 = Label::createWithTTF("2. " + L2, "fonts/Marker Felt.ttf", 24);
	L_LeaderBoard2->setPosition(Vec2(origin.x + visibleSize.width / 2,
		((origin.y + visibleSize.height / 2) - L_LeaderBoard2->getContentSize().height)-100));
	L_LeaderBoard2->setColor(ccc3(0, 0, 0));
	this->addChild(L_LeaderBoard2, 1);

	auto L_LeaderBoard3 = Label::createWithTTF("3. " + L3, "fonts/Marker Felt.ttf", 24);
	L_LeaderBoard3->setPosition(Vec2(origin.x + visibleSize.width / 2,
		((origin.y + visibleSize.height / 2) - L_LeaderBoard3->getContentSize().height)-140));
	L_LeaderBoard3->setColor(ccc3(0, 0, 0));
	this->addChild(L_LeaderBoard3, 1);

	auto L_LeaderBoard4 = Label::createWithTTF("4. " + L4, "fonts/Marker Felt.ttf", 24);
	L_LeaderBoard4->setPosition(Vec2(origin.x + visibleSize.width / 2,
		((origin.y + visibleSize.height / 2) - L_LeaderBoard4->getContentSize().height)-180));
	L_LeaderBoard4->setColor(ccc3(0, 0, 0));
	this->addChild(L_LeaderBoard4, 1);

	auto L_LeaderBoard5 = Label::createWithTTF("5. " + L5, "fonts/Marker Felt.ttf", 24);
	L_LeaderBoard5->setPosition(Vec2(origin.x + visibleSize.width / 2,
		((origin.y + visibleSize.height / 2) - L_LeaderBoard5->getContentSize().height)-220));
	L_LeaderBoard5->setColor(ccc3(0, 0, 0));
	this->addChild(L_LeaderBoard5, 1);

	return true;
}

void LeaderBoard::returnToTitle(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}
void LeaderBoard::Next(cocos2d::Ref* pSender)
{
	auto NextScene = MultiPlayer::createScene();
	Director::getInstance()->pushScene(NextScene);
}
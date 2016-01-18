#include"Options.h"
#include"MainMenu.h"
#include"ui/CocosGUI.h"
#include"SimpleAudioEngine.h"
#include<fstream>
#include<iostream>

float musicVolumeControl;
float SoundEffectsVolumeControl;
int EffectsMute;
char testFile;
int testFileInt;


USING_NS_CC;
using namespace std;

Scene* Options::createScene()
{
	// 'scene' is an autorelease object
	auto OptionsScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Options::create();

	// add layer as a child to scene
	OptionsScene->addChild(layer);

	// return the scene
	return OptionsScene;
}

bool Options::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Options::SetMusicVolume(0.5);
	/*
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
		//ReadFile.get(testFile);
		for (int x = 0; !ReadFile.eof(); x++) 
		{
			if (x==0) 
			{
			    getline(ReadFile, text);
                //int testFileInt = atoi(text.c_str());
				std::string::size_type sz;     
				musicVolumeControl = std::stof(text, &sz);
				CCLOG("MVC %.2f", musicVolumeControl);
				x++;
			}
			if (x == 1)
			{
				getline(ReadFile, text);
				//int testFileInt = atoi(text.c_str());
				std::string::size_type sz;     
				SoundEffectsVolumeControl = std::stof(text, &sz);
				CCLOG("SEVC %.2f", SoundEffectsVolumeControl);
				x++;
			}
			if (x == 2)
			{
				getline(ReadFile, text);
				EffectsMute = atoi(text.c_str());
				CCLOG("EFFECTS MUTE %d", EffectsMute);
			}
			CCLOG("X == %d", x);

		}
	    
		ReadFile.close();
		
		CCLOG("SYSTEM FILE %d", testFileInt);
	}
	*/
	auto label = Label::createWithTTF("Options", "fonts/Marker Felt.ttf", 24);

	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	auto sprite = Sprite::create("Background.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	
	auto MusicCheckBox = cocos2d::ui::CheckBox::create("check_box_normal.png",
		"check_box_normal_press.png",
		"check_box_active.png",
		"check_box_normal_disable.png",
		"check_box_active_disable.png");
	MusicCheckBox->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - MusicCheckBox->getContentSize().height * 12));
	//checkBox->addEventListener(CC_CALLBACK_2(UICheckBoxTest::selectedEvent, this));
	MusicCheckBox->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("CHECKBOX");
			if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying() == true) {
				CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			}
			else {
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
					"background-music-aac.wav", true);
			}

			CCLOG("CHECKBOX PASSED POSTION");
			break;
		default:
			break;
		}
	
	});
	
	this->addChild(MusicCheckBox,1);

	auto MusicCheckBoxLabel = Label::createWithTTF("Mute Music", "fonts/Marker Felt.ttf", 24);
	MusicCheckBoxLabel->setColor(ccc3(0, 0, 0));
	MusicCheckBoxLabel->setPosition(Vec2((origin.x + visibleSize.width / 2) - 250,
		origin.y + visibleSize.height - MusicCheckBox->getContentSize().height * 12));
	this->addChild(MusicCheckBoxLabel, 1);

	auto SoundEffectCheckBox = cocos2d::ui::CheckBox::create("check_box_normal.png",
		"check_box_normal_press.png",
		"check_box_active.png",
		"check_box_normal_disable.png",
		"check_box_active_disable.png");
	SoundEffectCheckBox->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - SoundEffectCheckBox->getContentSize().height * 14));
	//checkBox->addEventListener(CC_CALLBACK_2(UICheckBoxTest::selectedEvent, this));
	SoundEffectCheckBox->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("Sound EFFECT CHECKBOX");
			//Needs the logic of the sound effect checkbox to be added here
			if (EffectsMute==0) 
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
				EffectsMute++;
			}
			else {
				CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
				EffectsMute = 0;
			}
			CCLOG(" SOUND EFFECT CHECKBOX PASSED POSTION");
			break;
		default:
			break;
		}

	});

	this->addChild(SoundEffectCheckBox, 1);

	auto SoundEffectCheckBoxLabel = Label::createWithTTF("Mute Sound Effect", "fonts/Marker Felt.ttf", 24);
	SoundEffectCheckBoxLabel->setColor(ccc3(0, 0, 0));
	SoundEffectCheckBoxLabel->setPosition(Vec2((origin.x + visibleSize.width / 2) - 250,
		origin.y + visibleSize.height - SoundEffectCheckBox->getContentSize().height * 14));
	this->addChild(SoundEffectCheckBoxLabel, 1);



	auto MusicSlider = cocos2d::ui::Slider::create();
	MusicSlider->loadBarTexture("sliderTrack.png");
	MusicSlider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	MusicSlider->loadProgressBarTexture("sliderProgress.png");
	MusicSlider->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - MusicSlider->getContentSize().height * 4));
	
	MusicSlider->setPercent(musicVolumeControl*100);
	musicVolumeControl = MusicSlider->getPercent();

	//MusicSlider->setPercent(100);
	//MusicSlider->getPercent();
	//musicVolumeControl = MusicSlider->getPercent();
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(MusicSlider->getPercent()/100);
	//MusicSlider->addEventListener(CC_CALLBACK_2(Options::MusicVolume, this));
	MusicSlider->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("Slider Moved");

			//MusicSlider->setPercent(MusicSlider->getPercent());
			Options::SetMusicVolume(MusicSlider->getPercent() / 100);
			CCLOG("PASSED POSTION");
			break;
		default:
			break;
		}
	});

	this->addChild(MusicSlider,1);
	
	CCLOG("BEFORE STRING");
	//std::string MusicString = std::to_string(MusicSlider->getPercent());
	std::string MusicString = std::to_string(musicVolumeControl);
	auto TestLabel = Label::createWithTTF(MusicString, "fonts/Marker Felt.ttf", 24);
	TestLabel->setColor(ccc3(0, 0, 0));
	TestLabel->setPosition(Vec2((origin.x + visibleSize.width / 2) - 250,
		origin.y + visibleSize.height - MusicSlider->getContentSize().height * 14));
	this->addChild(TestLabel, 1);



	auto MusicLabel = Label::createWithTTF("Music Volume", "fonts/Marker Felt.ttf", 24);
	MusicLabel->setColor(ccc3(0,0,0));
	MusicLabel->setPosition(Vec2((origin.x + visibleSize.width / 2) - 250,
		origin.y + visibleSize.height - MusicSlider->getContentSize().height * 4));
	this->addChild(MusicLabel, 1);
	
	
	auto SoundEffectSlider = cocos2d::ui::Slider::create();
	SoundEffectSlider->loadBarTexture("sliderTrack.png");
	SoundEffectSlider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	SoundEffectSlider->loadProgressBarTexture("sliderProgress.png");
	SoundEffectSlider->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - SoundEffectSlider->getContentSize().height * 6));

	//SoundEffectSlider->addEventListener(CC_CALLBACK_2(UISliderTest::sliderEvent, this));

	SoundEffectSlider->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("Sound Effect Slider Moved");

			//MusicSlider->setPercent(MusicSlider->getPercent());
			CCLOG("SOUND EFFECT PASSED POSTION");
			break;
		default:
			break;
		}
	});

	this->addChild(SoundEffectSlider,1);

	auto SoundEffectLabel = Label::createWithTTF("Sound Effect Volume", "fonts/Marker Felt.ttf", 24);
	SoundEffectLabel->setColor(ccc3(0, 0, 0));
	SoundEffectLabel->setPosition(Vec2((origin.x + visibleSize.width / 2) - 250,
		origin.y + visibleSize.height - SoundEffectSlider->getContentSize().height * 6));
	this->addChild(SoundEffectLabel, 1);

	auto BackToMain = MenuItemImage::create("Back.png", "BackClicked.png", CC_CALLBACK_1(Options::menuReturn, this));
	BackToMain->setPosition(Vec2(origin.x + visibleSize.width - BackToMain->getContentSize().width, 70));

	auto menuReturn = Menu::create(BackToMain, NULL);
	menuReturn->setPosition(Vec2::ZERO);
	this->addChild(menuReturn, 1);

	return true;

}

void Options::menuReturn(Ref* pSender)
{
	Director::getInstance()->popScene();
}

double Options::MusicVolume() {

	CCLOG("Music Volume Changed");
	return musicVolumeControl;

}

void Options::SetMusicVolume(float x) {
    musicVolumeControl = x;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(musicVolumeControl);

	//test to see if the slider works, needs the value system to be fixed

	//if (musicVolumeControl >= 1.0) {
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//}
	//else {
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	//}
	CCLOG("SET VOLUME %f", musicVolumeControl);
}
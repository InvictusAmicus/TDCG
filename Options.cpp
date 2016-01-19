/*
Sound effects need to be fix so that they turn off
Background music has to be fix so that it is muted when turning on if it is muted in system file
Slide has to change the value range from 1-100 to 0.0-1.0
*/

#include"Options.h"
#include"MainMenu.h"
#include"ui/CocosGUI.h"
#include"SimpleAudioEngine.h"
#include<fstream>
#include<iostream>
#include"AudioEngine.h"

int musicVolumeControl;
float SoundEffectsVolumeControl;
int EffectsMute;
int MusicMute;
char testFile;
int testFileInt;
float VolumeFloat;
int change;
int track = 0;

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
	//Options::SetMusicVolume(0.5);
	   // track = cocos2d::experimental::AudioEngine::play2d("Iris.mp3", true, 1.0f, nullptr);
	   // cocos2d::experimental::AudioEngine::setVolume(track, 1.0f);
	/////////////////////////////////////
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

		//
		//When compiled System_File being read from the debug win32, change values there
		//
		for (int x = 0; x<4; x++) 
		{
			if (x==0) 
			{
			    getline(ReadFile, text);
                int testFileInt = atoi(text.c_str());
				std::string::size_type sz;     
				musicVolumeControl = std::stof(text, &sz);
				CCLOG("MVC %.2f", musicVolumeControl);
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
				EffectsMute = atoi(text.c_str());
				CCLOG("EFFECTS MUTE %d", EffectsMute);
		    }
			if (x == 3)
			{
				getline(ReadFile, text);
				MusicMute = atoi(text.c_str());
				CCLOG("MUSIC MUTE %d", MusicMute);
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
	////////////////////////////////
	if (MusicMute == 1)
	{
		MusicCheckBox->setSelectedState(true);
	}
	else
	{
		MusicCheckBox->setSelectedState(false);
	}
	
	MusicCheckBox->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("CHECKBOX");
			//////////////////////////////////
			/*
			if(MusicMute==0){
				CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
				MusicCheckBox->setSelectedState(true);
				MusicMute++;
			}
			else {
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
					"background-music-aac.wav", true);
				MusicCheckBox->setSelectedState(false);
				MusicMute = 0;
			}
			Options::setMusicMute(MusicMute);
		*/
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
	//////////////////////////////////////////
	if (EffectsMute == 1) 
	{
	    SoundEffectCheckBox->setSelectedState(true);
	}
	else 
	{
		SoundEffectCheckBox->setSelectedState(false);
	}
	
	//checkBox->addEventListener(CC_CALLBACK_2(UICheckBoxTest::selectedEvent, this));
	SoundEffectCheckBox->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("Sound EFFECT CHECKBOX");
			//Needs the logic of the sound effect checkbox to be added here
			//////////////////////////////////////////////
			/*
			if (EffectsMute==0) 
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
				EffectsMute++;
				SoundEffectCheckBox->setSelectedState(true);
				CCLOG("First IF");
			}
			else {
				CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
				
				EffectsMute = 0;
				SoundEffectCheckBox->setSelectedState(false);
				CCLOG("Else STATEMENT");
			}
			Options::SetSoundEffectMute(EffectsMute);
			*/
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
	
	MusicSlider->setPercent(musicVolumeControl);
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
			CCLOG("SLIDER %d", MusicSlider->getPercent());
			change = MusicSlider->getPercent();
			VolumeFloat = change;
			
			CCLOG("SLIDER %.6f", VolumeFloat);
			//////////////////////////////
			//CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(VolumeFloat);
			/*
			if (MusicSlider == 0) {
				cocos2d::experimental::AudioEngine::setVolume(t, 0.0f);
			}
			else if (MusicSlider->getPercent()>0&& MusicSlider->getPercent()<10) {
				cocos2d::experimental::AudioEngine::setVolume(t, 0.1f);
			}
			else if (MusicSlider->getPercent()>=10 && MusicSlider->getPercent()<20) {
				cocos2d::experimental::AudioEngine::setVolume(t, 0.2f);
			}
			else if (MusicSlider->getPercent()>=20 && MusicSlider->getPercent()<30) {
				cocos2d::experimental::AudioEngine::setVolume(t, 0.3f);
			}
			else if (MusicSlider->getPercent()>=30 && MusicSlider->getPercent()<40) {
				cocos2d::experimental::AudioEngine::setVolume(t, 0.4f);
			}
			else if (MusicSlider->getPercent()>=40 && MusicSlider->getPercent()<50) {
				cocos2d::experimental::AudioEngine::setVolume(t, 0.5f);
			}
			else if (MusicSlider->getPercent() >= 50 && MusicSlider->getPercent()<60) {
				cocos2d::experimental::AudioEngine::setVolume(t, 0.6f);
			}
			else if (MusicSlider->getPercent() >= 60 && MusicSlider->getPercent()<70) {
				cocos2d::experimental::AudioEngine::setVolume(t, 0.7f);
			}
			else if (MusicSlider->getPercent() >= 70 && MusicSlider->getPercent()<80) {
				cocos2d::experimental::AudioEngine::setVolume(t, 0.8f);
			}
			else if (MusicSlider->getPercent() >= 80 && MusicSlider->getPercent()<90) {
				cocos2d::experimental::AudioEngine::setVolume(t, 0.9f);
			}
			else if (MusicSlider->getPercent() >= 90 && MusicSlider->getPercent()<100) {
				cocos2d::experimental::AudioEngine::setVolume(t, 1.0f);
			}
			else if (MusicSlider->getPercent() == 100) {}
			
			//cocos2d::experimental::AudioEngine::setVolume(t, VolumeFloat);
			Options::SetMusicVolume(change);
			*/
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
	SoundEffectSlider->setPercent(SoundEffectsVolumeControl * 100);

	SoundEffectSlider->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("Sound Effect Slider Moved");
			/////////////////////////////////////////
			//Options::SetSoundEffectVolume(SoundEffectSlider->getPercent());
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
	cocos2d::experimental::AudioEngine::stop(track);
	Director::getInstance()->popScene();
}

double Options::MusicVolume() {

	CCLOG("Music Volume Changed");
	return musicVolumeControl;

}

/*
void Options::SetMusicVolume(int x) {
	musicVolumeControl = x;
    int changedVolume = x;
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(changedVolume);

	//FileUtils::getInstance()->addSearchPath("SystemFile");
	if (musicVolumeControl == 0) {
		cocos2d::experimental::AudioEngine::setVolume(track, 0.0f);
	}
	else if (musicVolumeControl>0 && musicVolumeControl<10) {
		cocos2d::experimental::AudioEngine::setVolume(track, 0.1f);
	}
	else if (musicVolumeControl >= 10 && musicVolumeControl<20) {
		cocos2d::experimental::AudioEngine::setVolume(track, 0.2f);
	}
	else if (musicVolumeControl >= 20 && musicVolumeControl<30) {
		cocos2d::experimental::AudioEngine::setVolume(track, 0.3f);
	}
	else if (musicVolumeControl >= 30 && musicVolumeControl<40) {
		cocos2d::experimental::AudioEngine::setVolume(track, 0.4f);
	}
	else if (musicVolumeControl >= 40 && musicVolumeControl<50) {
		cocos2d::experimental::AudioEngine::setVolume(track, 0.5f);
	}
	else if (musicVolumeControl >= 50 && musicVolumeControl<60) {
		cocos2d::experimental::AudioEngine::setVolume(track, 0.6f);
	}
	else if (musicVolumeControl >= 60 && musicVolumeControl<70) {
		cocos2d::experimental::AudioEngine::setVolume(track, 0.7f);
	}
	else if (musicVolumeControl >= 70 && musicVolumeControl<80) {
		cocos2d::experimental::AudioEngine::setVolume(track, 0.8f);
	}
	else if (musicVolumeControl >= 80 && musicVolumeControl<90) {
		cocos2d::experimental::AudioEngine::setVolume(track, 0.9f);
	}
	else if (musicVolumeControl >= 90 && musicVolumeControl <=100) {
		cocos2d::experimental::AudioEngine::setVolume(track, 1.0f);
	}

	string DataFileName = "System_File.txt";
	std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(DataFileName.c_str());
	//CCLOG("%s", fullpath);
	//std::ofstream ReadFile(fullpath);
	std::ofstream ReadFile;
    ReadFile.open(fullpath);
	string text;
	if (!ReadFile)
	{
		CCLOG("SetMusicVolume FILE NOT FOUND");
	}
	else
	{
		CCLOG("CHANGING FILE CONTENTS");
		std::string MV = std::to_string(changedVolume);
		std::string SEV = std::to_string(SoundEffectsVolumeControl);
		std::string SEM = std::to_string(EffectsMute);
		std::string MM = std::to_string(MusicMute);
		
		ReadFile << MV << "\n";
		ReadFile << SEV << "\n";
		ReadFile << SEM << "\n";
		ReadFile << MM << "\n";
		ReadFile.close();
	}

	//test to see if the slider works, needs the value system to be fixed

	//if (musicVolumeControl >= 1.0) {
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//}
	//else {
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	//}
	CCLOG("SET VOLUME %d", changedVolume);
}


//Due to using AudioEngine to change the music volume no sound effects are stated
//each sound effect has to be stated and lowered using the if/if else statements as in the set music method
//track needs to be changed for the soundeffects being used
void Options::SetSoundEffectVolume(int x) {
	SoundEffectsVolumeControl = x;
	//float changedVolume = x;
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(changedVolume/100);

	int changedVolume = x;
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(changedVolume);

	//FileUtils::getInstance()->addSearchPath("SystemFile");
	if (musicVolumeControl == 0) {
		//cocos2d::experimental::AudioEngine::setVolume(track, 0.0f);
	}
	else if (musicVolumeControl>0 && musicVolumeControl<10) {
		//cocos2d::experimental::AudioEngine::setVolume(track, 0.1f);
	}
	else if (musicVolumeControl >= 10 && musicVolumeControl<20) {
		//cocos2d::experimental::AudioEngine::setVolume(track, 0.2f);
	}
	else if (musicVolumeControl >= 20 && musicVolumeControl<30) {
		//cocos2d::experimental::AudioEngine::setVolume(track, 0.3f);
	}
	else if (musicVolumeControl >= 30 && musicVolumeControl<40) {
		//cocos2d::experimental::AudioEngine::setVolume(track, 0.4f);
	}
	else if (musicVolumeControl >= 40 && musicVolumeControl<50) {
		//cocos2d::experimental::AudioEngine::setVolume(track, 0.5f);
	}
	else if (musicVolumeControl >= 50 && musicVolumeControl<60) {
		//cocos2d::experimental::AudioEngine::setVolume(track, 0.6f);
	}
	else if (musicVolumeControl >= 60 && musicVolumeControl<70) {
		//cocos2d::experimental::AudioEngine::setVolume(track, 0.7f);
	}
	else if (musicVolumeControl >= 70 && musicVolumeControl<80) {
		//cocos2d::experimental::AudioEngine::setVolume(track, 0.8f);
	}
	else if (musicVolumeControl >= 80 && musicVolumeControl<90) {
		//cocos2d::experimental::AudioEngine::setVolume(track, 0.9f);
	}
	else if (musicVolumeControl >= 90 && musicVolumeControl <= 100) {
		//cocos2d::experimental::AudioEngine::setVolume(track, 1.0f);
	}


	//FileUtils::getInstance()->addSearchPath("SystemFile");
	string DataFileName = "System_File.txt";
	std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(DataFileName.c_str());
	//CCLOG("%s", fullpath);
	//std::ofstream ReadFile(fullpath);
	std::ofstream ReadFile;
	ReadFile.open(fullpath);
	string text;
	if (!ReadFile)
	{
		CCLOG("SetMusicVolume FILE NOT FOUND");
	}
	else
	{
		CCLOG("CHANGING FILE CONTENTS");
		std::string MV = std::to_string(musicVolumeControl);
		std::string SEV = std::to_string(changedVolume);
		std::string SEM = std::to_string(EffectsMute);
		std::string MM = std::to_string(MusicMute);

		ReadFile << MV << "\n";
		ReadFile << SEV << "\n";
		ReadFile << SEM << "\n";
		ReadFile << MM << "\n";
		ReadFile.close();
	}

	CCLOG("SET SE VOLUME %f", changedVolume);

}

void Options::SetSoundEffectMute(int x) {
	int changedState = x;

	//FileUtils::getInstance()->addSearchPath("SystemFile");
	string DataFileName = "System_File.txt";
	std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(DataFileName.c_str());
	//CCLOG("%s", fullpath);
	//std::ofstream ReadFile(fullpath);
	std::ofstream ReadFile;
	ReadFile.open(fullpath);
	string text;
	if (!ReadFile)
	{
		CCLOG("SetMusicVolume FILE NOT FOUND");
	}
	else
	{
		CCLOG("CHANGING FILE CONTENTS");
		std::string MV = std::to_string(musicVolumeControl);
		std::string SEV = std::to_string(SoundEffectsVolumeControl);
		std::string SEM = std::to_string(changedState);
		std::string MM = std::to_string(MusicMute);

		ReadFile << MV << "\n";
		ReadFile << SEV << "\n";
		ReadFile << SEM << "\n";
		ReadFile << MM << "\n";
		ReadFile.close();
	}

	CCLOG("SET SE VOLUME %d", changedState);

}

void Options::setMusicMute(int x) {
	int changedState = x;

	//FileUtils::getInstance()->addSearchPath("SystemFile");
	string DataFileName = "System_File.txt";
	std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(DataFileName.c_str());
	//CCLOG("%s", fullpath);
	//std::ofstream ReadFile(fullpath);
	std::ofstream ReadFile;
	ReadFile.open(fullpath);
	string text;
	if (!ReadFile)
	{
		CCLOG("SetMusicVolume FILE NOT FOUND");
	}
	else
	{
		CCLOG("CHANGING FILE CONTENTS");
		std::string MV = std::to_string(musicVolumeControl);
		std::string SEV = std::to_string(SoundEffectsVolumeControl);
		std::string SEM = std::to_string(EffectsMute);
		std::string MM = std::to_string(changedState);

		ReadFile << MV << "\n";
		ReadFile << SEV << "\n";
		ReadFile << SEM << "\n";
		ReadFile << MM << "\n";
		ReadFile.close();
	}

	CCLOG("SET SE VOLUME %d", changedState);

}

int getmusicVolume() 
{
	return musicVolumeControl;
}
*/
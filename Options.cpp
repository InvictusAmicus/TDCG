//Worked on by Ciaran Clerkin K00191500 and Declan Cordial K00184439

#include"Options.h"
#include"MainMenu.h"
#include"ui/CocosGUI.h"
#include"SimpleAudioEngine.h"
#include<fstream>
#include<iostream>
#include"AudioEngine.h"

int musicVolumeControl;
int SoundEffectsVolumeControl;
int EffectsMute;
int MusicMute;
char testFile;
int testFileInt;
float VolumeFloat;
int change;

//background music track, needed to store audioId
int GameMenu3 = 0;
//sound effects tracks, needed to store audioId
int SeTrack1 = 0;

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

	FileUtils::getInstance()->addSearchPath("SystemFile");
	string DataFileName = "System_File.txt";
	std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(DataFileName.c_str());
	std::ifstream ReadFile(fullpath);
	string text;
	if (!ReadFile) 
	{
		CCLOG("FILE NOT FOUND");
	}
	else 
	{
		for (int x = 0; x<4; x++)
		{
			if (x==0) 
			{
			    getline(ReadFile, text);
                int testFileInt = atoi(text.c_str());
				std::string::size_type sz;     
				musicVolumeControl = std::stof(text, &sz);
				CCLOG("MVC %d", musicVolumeControl);
			}
			if (x == 1)
			{
				getline(ReadFile, text);
				int testFileInt = atoi(text.c_str());
				std::string::size_type sz;     
				SoundEffectsVolumeControl = std::stof(text, &sz);
				CCLOG("SEVC %d", SoundEffectsVolumeControl);
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
	
	if (MusicMute != 1)
	{
		cocos2d::experimental::AudioEngine::stopAll();
		GameMenu3 = cocos2d::experimental::AudioEngine::play2d("MainMenu.mp3", true, getMusicFloatVolume(musicVolumeControl), nullptr);
	}
	
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
	
	if (MusicMute == 1)
	{
		MusicCheckBox->setSelectedState(true);
	}
	else
	{
		MusicCheckBox->setSelectedState(false);
	}
	
	MusicCheckBox->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) 
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("CHECKBOX");
			//////////////////////////////////
			
			if(MusicMute==0)
			{
				MusicCheckBox->setSelectedState(true);
				MusicMute++;
			}
			else 
			{
				MusicCheckBox->setSelectedState(false);
				MusicMute = 0;
			}
			Options::setMusicMute(MusicMute);
		
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
	
	if (EffectsMute == 1) 
	{
	    SoundEffectCheckBox->setSelectedState(true);
	}
	else 
	{
		SoundEffectCheckBox->setSelectedState(false);
	}
	
	SoundEffectCheckBox->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) 
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("Sound EFFECT CHECKBOX");
			
			if (EffectsMute==0) 
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
				EffectsMute++;
				SoundEffectCheckBox->setSelectedState(true);
				CCLOG("First IF");
			}
			else 
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();			
				EffectsMute = 0;
				SoundEffectCheckBox->setSelectedState(false);
				CCLOG("Else STATEMENT");
			}
			Options::SetSoundEffectMute(EffectsMute);

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

	MusicSlider->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) 
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("Slider Moved");
			CCLOG("SLIDER %d", MusicSlider->getPercent());
			change = MusicSlider->getPercent();
			
			CCLOG("SLIDER %d", change);
			
			if (MusicSlider == 0) 
			{
				cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.0f);
			}
			else if (MusicSlider->getPercent()>0&& MusicSlider->getPercent()<10) 
			{
				cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.1f);
			}
			else if (MusicSlider->getPercent()>=10 && MusicSlider->getPercent()<20) 
			{
				cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.2f);
			}
			else if (MusicSlider->getPercent()>=20 && MusicSlider->getPercent()<30) 
			{
				cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.3f);
			}
			else if (MusicSlider->getPercent()>=30 && MusicSlider->getPercent()<40) 
			{
				cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.4f);
			}
			else if (MusicSlider->getPercent()>=40 && MusicSlider->getPercent()<50) 
			{
				cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.5f);
			}
			else if (MusicSlider->getPercent() >= 50 && MusicSlider->getPercent()<60) 
			{
				cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.6f);
			}
			else if (MusicSlider->getPercent() >= 60 && MusicSlider->getPercent()<70) 
			{
				cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.7f);
			}
			else if (MusicSlider->getPercent() >= 70 && MusicSlider->getPercent()<80) 
			{
				cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.8f);
			}
			else if (MusicSlider->getPercent() >= 80 && MusicSlider->getPercent()<90) 
			{
				cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.9f);
			}
			else if (MusicSlider->getPercent() >= 90 && MusicSlider->getPercent()<100) 
			{
				cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 1.0f);
			}
			else if (MusicSlider->getPercent() == 100) {}
			
			Options::SetMusicVolume(change);
			
			CCLOG("PASSED POSTION");
			break;
		default:
			break;
		}
	});

	this->addChild(MusicSlider,1);
	
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

	SoundEffectSlider->setPercent(SoundEffectsVolumeControl);
	SoundEffectsVolumeControl = SoundEffectSlider->getPercent();
	SoundEffectSlider->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) 
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("Sound Effect Slider Moved");

			if (SoundEffectSlider == 0) 
			{
				cocos2d::experimental::AudioEngine::setVolume(SeTrack1, 0.0f);
			}
			else if (SoundEffectSlider->getPercent()>0 && SoundEffectSlider->getPercent()<10) 
			{
				cocos2d::experimental::AudioEngine::setVolume(SeTrack1, 0.1f);
			}
			else if (SoundEffectSlider->getPercent() >= 10 && SoundEffectSlider->getPercent()<20) 
			{
				cocos2d::experimental::AudioEngine::setVolume(SeTrack1, 0.2f);
			}
			else if (SoundEffectSlider->getPercent() >= 20 && SoundEffectSlider->getPercent()<30) 
			{
				cocos2d::experimental::AudioEngine::setVolume(SeTrack1, 0.3f);
			}
			else if (SoundEffectSlider->getPercent() >= 30 && SoundEffectSlider->getPercent()<40) 
			{
				cocos2d::experimental::AudioEngine::setVolume(SeTrack1, 0.4f);
			}
			else if (SoundEffectSlider->getPercent() >= 40 && SoundEffectSlider->getPercent()<50) 
			{
				cocos2d::experimental::AudioEngine::setVolume(SeTrack1, 0.5f);
			}
			else if (SoundEffectSlider->getPercent() >= 50 && SoundEffectSlider->getPercent()<60) 
			{
				cocos2d::experimental::AudioEngine::setVolume(SeTrack1, 0.6f);
			}
			else if (SoundEffectSlider->getPercent() >= 60 && SoundEffectSlider->getPercent()<70) 
			{
				cocos2d::experimental::AudioEngine::setVolume(SeTrack1, 0.7f);
			}
			else if (SoundEffectSlider->getPercent() >= 70 && SoundEffectSlider->getPercent()<80) 
			{
				cocos2d::experimental::AudioEngine::setVolume(SeTrack1, 0.8f);
			}
			else if (SoundEffectSlider->getPercent() >= 80 && SoundEffectSlider->getPercent()<90) 
			{
				cocos2d::experimental::AudioEngine::setVolume(SeTrack1, 0.9f);
			}
			else if (SoundEffectSlider->getPercent() >= 90 && SoundEffectSlider->getPercent()<100) 
			{
				cocos2d::experimental::AudioEngine::setVolume(SeTrack1, 1.0f);
			}
			Options::SetSoundEffectVolume(SoundEffectSlider->getPercent());
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
	cocos2d::experimental::AudioEngine::stopAll();
	if (MusicMute != 1)
	{
		GameMenu3 = cocos2d::experimental::AudioEngine::play2d("MainMenu.mp3", true, getMusicFloatVolume(musicVolumeControl), nullptr);
	}
	Director::getInstance()->popScene();
}

void Options::setMV(int x) 
{
	musicVolumeControl = x;
}

void Options::setSEV(int x) 
{
	SoundEffectsVolumeControl = x;
}

void Options::setMute(int x) 
{
	MusicMute = x;
}

void Options::setMusicMute(int x) {
	int changedState = x;

	string DataFileName = "System_File.txt";
	std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(DataFileName.c_str());
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
	if (changedState!=0) 
	{
		cocos2d::experimental::AudioEngine::stopAll();
	}
	if (changedState!=1) 
	{
		GameMenu3 = cocos2d::experimental::AudioEngine::play2d("MainMenu.mp3", true, getMusicFloatVolume(musicVolumeControl), nullptr);
	}

}

void Options::setSEVMute(int x)
{
	EffectsMute = x;
}

void Options::SetSoundEffectMute(int x) {
	int changedState = x;

	string DataFileName = "System_File.txt";
	std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(DataFileName.c_str());
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

void Options::SetMusicVolume(int x)
{
	musicVolumeControl = x;
    int changedVolume = x;

	if (musicVolumeControl == 0) 
	{
		cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.0f);
	}
	else if (musicVolumeControl>0 && musicVolumeControl<10) 
	{
		cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.1f);
	}
	else if (musicVolumeControl >= 10 && musicVolumeControl<20) 
	{
		cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.2f);
	}
	else if (musicVolumeControl >= 20 && musicVolumeControl<30) 
	{
		cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.3f);
	}
	else if (musicVolumeControl >= 30 && musicVolumeControl<40) 
	{
		cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.4f);
	}
	else if (musicVolumeControl >= 40 && musicVolumeControl<50) 
	{
		cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.5f);
	}
	else if (musicVolumeControl >= 50 && musicVolumeControl<60) 
	{
		cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.6f);
	}
	else if (musicVolumeControl >= 60 && musicVolumeControl<70) 
	{
		cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.7f);
	}
	else if (musicVolumeControl >= 70 && musicVolumeControl<80) 
	{
		cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.8f);
	}
	else if (musicVolumeControl >= 80 && musicVolumeControl<90) 
	{
		cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 0.9f);
	}
	else if (musicVolumeControl >= 90 && musicVolumeControl <=100) 
	{
		cocos2d::experimental::AudioEngine::setVolume(GameMenu3, 1.0f);
	}

	string DataFileName = "System_File.txt";
	std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(DataFileName.c_str());
	std::ofstream ReadFile;
    ReadFile.open(fullpath);
	string text;
	if (!ReadFile)
	{
		CCLOG("SetMusicVolume FILE NOT FOUND");
	}
	else
	{
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
}

void Options::SetSoundEffectVolume(int x)
{
	SoundEffectsVolumeControl = x;

	int changedVolume = x;

	if (musicVolumeControl == 0) {
		//cocos2d::experimental::AudioEngine::setVolume(SeTrack, 0.0f);
	}
	else if (musicVolumeControl>0 && musicVolumeControl<10) 
	{
		//cocos2d::experimental::AudioEngine::setVolume(SeTrack, 0.1f);
	}
	else if (musicVolumeControl >= 10 && musicVolumeControl<20) 
	{
		//cocos2d::experimental::AudioEngine::setVolume(SeTrack, 0.2f);
	}
	else if (musicVolumeControl >= 20 && musicVolumeControl<30) 
	{
		//cocos2d::experimental::AudioEngine::setVolume(SeTrack, 0.3f);
	}
	else if (musicVolumeControl >= 30 && musicVolumeControl<40) 
	{
		//cocos2d::experimental::AudioEngine::setVolume(SeTrack, 0.4f);
	}
	else if (musicVolumeControl >= 40 && musicVolumeControl<50) 
	{
		//cocos2d::experimental::AudioEngine::setVolume(SeTrack, 0.5f);
	}
	else if (musicVolumeControl >= 50 && musicVolumeControl<60) 
	{
		//cocos2d::experimental::AudioEngine::setVolume(SeTrack, 0.6f);
	}
	else if (musicVolumeControl >= 60 && musicVolumeControl<70) 
	{
		//cocos2d::experimental::AudioEngine::setVolume(SeTrack, 0.7f);
	}
	else if (musicVolumeControl >= 70 && musicVolumeControl<80) 
	{
		//cocos2d::experimental::AudioEngine::setVolume(SeTrack, 0.8f);
	}
	else if (musicVolumeControl >= 80 && musicVolumeControl<90) 
	{
		//cocos2d::experimental::AudioEngine::setVolume(SeTrack, 0.9f);
	}
	else if (musicVolumeControl >= 90 && musicVolumeControl <= 100) 
	{
		//cocos2d::experimental::AudioEngine::setVolume(SeTrack, 1.0f);
	}

	string DataFileName = "System_File.txt";
	std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(DataFileName.c_str());
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

	CCLOG("SET SE VOLUME %d", changedVolume);

}

int Options::getmusicVolume() 
{
	return musicVolumeControl;
}

int Options::EffectsVolume() 
{
	return SoundEffectsVolumeControl;
}

int Options::getMusicMute() 
{
	return MusicMute;
}

int Options::getEffectsMute() 
{
	return EffectsMute;
}

float Options::getMusicFloatVolume(int x) 
{
	CCLOG("Start");
	int CheckVolume = x;
	CCLOG("X, %d",x);

	if (CheckVolume == 0) 
	{
		CCLOG("Start 0.0");
		return 0.0f;
	}
	else if (CheckVolume>0 && CheckVolume<10) 
	{
		CCLOG("Start 0.1");
		return 0.1f;
	}
	else if (CheckVolume >= 10 && CheckVolume<20) 
	{
		CCLOG("Test");
		return 0.2f;
	}
	else if (CheckVolume >= 20 && CheckVolume<30) 
	{
		CCLOG("Test .3");
		return 0.3f;
	}
	else if (CheckVolume >= 30 && CheckVolume<40) 
	{
		return 0.4f;
	}
	else if (CheckVolume >= 40 && CheckVolume<50) 
	{
		return 0.5f;
	}
	else if (CheckVolume >= 50 && CheckVolume<60) 
	{
		return 0.6f;
	}
	else if (CheckVolume >= 60 && CheckVolume<70) 
	{
		return 0.7f;
	}
	else if (CheckVolume >= 70 && CheckVolume<80) 
	{
		return 0.8f;
	}
	else if (CheckVolume >= 80 && CheckVolume<90) 
	{
		return 0.9f;
	}
	else if (CheckVolume >= 90 && CheckVolume <= 100) 
	{
		return 1.0f;
	}
}
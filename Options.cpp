#include"Options.h"
#include"MainMenu.h"
#include"ui/CocosGUI.h"

USING_NS_CC;

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
	//MusicSlider->addEventListener(CC_CALLBACK_2(UISliderTest::sliderEvent, this));
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
	//SoundEffectSlider->addEventListener(CC_CALLBACK_2(UISliderTest::sliderEvent, this));
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

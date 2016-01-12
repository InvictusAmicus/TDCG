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

// on "init" you need to initialize your instance
bool Options::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Options", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	//Simple background added
	auto sprite = Sprite::create("Background.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	
	auto checkBox = cocos2d::ui::CheckBox::create("check_box_normal.png",
		"check_box_normal_press.png",
		"check_box_active.png",
		"check_box_normal_disable.png",
		"check_box_active_disable.png");
	checkBox->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - checkBox->getContentSize().height * 14));
	//checkBox->addEventListener(CC_CALLBACK_2(UICheckBoxTest::selectedEvent, this));
	this->addChild(checkBox,1);


	//auto b = cocos2d::ui::CheckBox::create();
	auto MusicSlider = cocos2d::ui::Slider::create();
	MusicSlider->loadBarTexture("sliderTrack.png");
	MusicSlider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	MusicSlider->loadProgressBarTexture("sliderProgress.png");
	MusicSlider->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - MusicSlider->getContentSize().height * 4));
	//MusicSlider->addEventListener(CC_CALLBACK_2(UISliderTest::sliderEvent, this));
	this->addChild(MusicSlider,1);
	
	auto SoundEffectSlider = cocos2d::ui::Slider::create();
	SoundEffectSlider->loadBarTexture("sliderTrack.png");
	SoundEffectSlider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	SoundEffectSlider->loadProgressBarTexture("sliderProgress.png");
	SoundEffectSlider->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - MusicSlider->getContentSize().height * 6));
	//SoundEffectSlider->addEventListener(CC_CALLBACK_2(UISliderTest::sliderEvent, this));
	this->addChild(SoundEffectSlider,1);

	//Original Back to menu
	//auto BackToMain = MenuItemImage::create("Options.png", "Continue.png", CC_CALLBACK_1(Options::menuReturn, this));
	//BackToMain->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - BackToMain->getContentSize().height * 7));

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

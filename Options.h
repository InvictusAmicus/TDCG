#ifndef __OPTIONS_H__
#define __OPTIONS_H_

#include "cocos2d.h"
#include "ui\UISlider.h"

class Options : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	

	virtual bool init();

	// a selector callback
	void menuReturn(cocos2d::Ref* pSender);
	//void MusicVolume(cocos2d::ui::Slider, cocos2d::Event* event);
	double MusicVolume();
	void SetMusicVolume(int x);
	void SetSoundEffectVolume(float x);
	void SetSoundEffectMute(int x);
	void setMusicMute(int x);
	int getmusicVolume();
	//float SoundEffectsVolumeControl;
	//int EffectsMute;
	//int MusicMute;

	CREATE_FUNC(Options);
};

#endif // __OPTIONS_H__

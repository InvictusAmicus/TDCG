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
	void SetMusicVolume(float x);
	void SetSoundEffectVolume(float x);
	void SetSoundEffectMute(int x);

	CREATE_FUNC(Options);
};

#endif // __OPTIONS_H__

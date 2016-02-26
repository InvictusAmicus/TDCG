#ifndef __OPTIONS_H__
#define __OPTIONS_H_

#include "cocos2d.h"
#include "ui\UISlider.h"

class Options : public cocos2d::Layer
{
public:
	/*!
	*Creates the scene for the options menu
	*/
	static cocos2d::Scene* createScene();
	
	/*!
	*Called to initialize the scene
	*/
	virtual bool init();

	/*!
	*Returns the user to the Main Menu when clicked
	*/
	void menuReturn(cocos2d::Ref* pSender);
    
	/*!
	*MV - Music Volume, set the current background music volume
	*/
	void setMV(int x);
	
	/*!
	*SEV - Sound Effect Volume, set the sound effect volume
	*/
	void setSEV(int x);

	/*!
	*Takes in a value of 0 or 1 and and sets it too a variable
	*/
    void setMute(int x);

	/*!
	*Gets the state of the mute button and sets it in the system file. 
	*If background music is running it will be stopped
	*/
    void setMusicMute(int x);
    
	/*!
	*Takes in a value of 0 or 1 and and sets it too a variable
	*/
	void setSEVMute(int x);

	/*!
	*Gets the state of the mute button and sets it in the system file.
	*/
    void SetSoundEffectMute(int x);
    
	/*!
	*For setting the background music volume by taking in an int value and setting the volume of the music.
	*Any changes made are then saved to the system file
	*/
	void SetMusicVolume(int x);
	
	/*!
	*For setting the effects music volume.
	*Any changes made are then saved to the system file
	*/
    void SetSoundEffectVolume(int x);
	
	/*!
	*For getting the current value of the music volume,
	*Returns an int value
	*/
    int getmusicVolume();

	/*!
	*For getting the current value of the effects volume,
	*Returns an int value
	*/
    int EffectsVolume();

	/*!
	*For getting the value if the background music is muted,
	*Returns an int value
	*/
	int getMusicMute();

	/*!
	*For getting the value if the effects music is muted,
	*Returns an int value
	*/
	int getEffectsMute();
	
	/*!
	*For getting the float value of the volume based on the slider current position,
	*Returns an float value
	*/
    float getMusicFloatVolume(int x);	

	CREATE_FUNC(Options);
};

#endif // __OPTIONS_H__

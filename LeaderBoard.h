#ifndef __LeaderBoard_H__
#define __LeaderBoard_H__

#include "cocos2d.h"

class LeaderBoard : public cocos2d::Layer
{
private:
	std::string G1;
	std::string G2;
	std::string G3;
	std::string G4;
	std::string G5;

	std::string L1;
	std::string L2;
	std::string L3;
	std::string L4;
	std::string L5;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void returnToTitle(cocos2d::Ref* pSender);
	void Next(cocos2d::Ref* pSender);

	CREATE_FUNC(LeaderBoard);
};

#endif // __LeaderBoard_H__

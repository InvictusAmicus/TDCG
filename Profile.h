#ifndef _PROFILE_H_
#define _PROFILE_H_

#include <iostream>
#include <string>

class Profile
{
public:

	Profile();
	Profile(std::string, int);
	~Profile();

	std::string name;
	int score;
};

#endif
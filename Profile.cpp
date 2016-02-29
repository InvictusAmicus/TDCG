#include "Profile.h"

Profile::Profile(std::string n, int s)
{
	name = n;
	score = s;
}

Profile::Profile()
{
	name = "";
	score = 0;
}

Profile::~Profile()
{
}
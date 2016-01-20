#ifndef __COLLISIONDETECTION_H__
#define __COLLISIONDETECTION_H__

class CollisionDetection
{
	CollisionDetection();
	~CollisionDetection();
	bool init();
public:
	void registerObject(int x, int y, char c);
	int enemyCollisionDetect(int x, int y, char c);
	int loop = 0;
};

#endif // __COLLISIONDETECTION_H__
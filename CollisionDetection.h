#ifndef __COLLISIONDETECTION_H__
#define __COLLISIONDETECTION_H__

class CollisionDetection
{
public:
	CollisionDetection();
	~CollisionDetection();
	bool init();

	void registerObject(int x, int y, char c);
	int enemyCollisionDetect(int x, int y, char c);
	int registerTower(int x, int y, char c);
	void CreateGrids();

};

#endif // __COLLISIONDETECTION_H__
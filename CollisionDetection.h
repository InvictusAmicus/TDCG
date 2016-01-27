#ifndef __COLLISIONDETECTION_H__
#define __COLLISIONDETECTION_H__

class CollisionDetection
{
public:
	CollisionDetection();
	~CollisionDetection();
	bool init();

	int registerObject(int x, int y, char c);
	int enemyCollisionDetect(int x, int y, char c);
	int playerCollisionDetect(int x, int y, char c);
	int registerTower(int x, int y, char c);
	int CheckTower(int x, int y);
	void registerEnemyTower(int x, int y, char c);
	void CreateGrids();
};

#endif // __COLLISIONDETECTION_H__
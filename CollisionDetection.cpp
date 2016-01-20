#include"CollisionDetection.h"
#include"SinglePlayGame.h"
#include"MultiPlayer.h"

char ColGrid[10][5];
int loop = 0;

void CollisionDetection::registerObject() {}

void CollisionDetection::CollisionDetect(int x, int y, char c) {

	//creates the grid if it is not made
	if (loop == 0) {
		for (int i = 0;i < 8;i++) {
			for (int j = 0;j < 8;j++) {
				ColGrid[i][j] = 'N';
			}
		}
		this->loop = 1;
	}

	//can register with the colision manager if the grid is available
	if (ColGrid[x][y] == 'N') {
		ColGrid[x][y] = c;
	}
	else {
		std::cout << "Postion already took" << std::endl;
	}
	std::cout << "WORKED" << std::endl;

}
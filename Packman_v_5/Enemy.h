#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
#include <map>
using std::map;

#include <vector>
using std::vector;

enum baseDirection
{
	dirUp,
	dirRigth,
	dirDown,
	dirLeft

};




class Enemy :public Sprite
{
public:
	Enemy(DravEngine * dravEngineEnemy, Level *levelEnemy, float x, float y, int index);
	~Enemy() override;

	void SpriteUpdate(void) override;

	

private:
	void createBaseDirectionMove(void);

	Coordinates Simulation(const int targetX, const int targetY);

	void modeContinueGame(void);
	void modeFrightenedEnemy(void);
	void modeChaseCharacter(void);

	void checkRigthMap(void);
	void checkLeftMap(void);
private:

	const int nextX[4] = { -1, 0, 1, 0 };
	const int nextY[4] = { 0, 1, 0, -1 };
	const int targetScatterX[4] = { 3,17,3,17 };
	const int targetScatterY[4] = { 1,1,25,25 };

	

	bool isAhouse;

	int direction;
	


	map<int, int > baseDirectionMove;

	Coordinates posScatter;
};



#endif
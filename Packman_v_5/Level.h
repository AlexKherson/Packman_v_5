#ifndef LEVEL_H
#define LEVEL_H

#include "DravEngine.h"
//#include "Sprite.h"

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <algorithm>
//using std::algorithm;
#include <stack>
using std::stack;

class Enemy;
class Character;
class Point;
struct Coordinates;

enum BaseModeLevel
{
	waitEnemy,
	continueGame,
	frightenedEnemy,
	chaseCharacter,
	restartGame,
	gameOver
};

class Level
{
public:


	Level(DravEngine *drav_engine, int sizeHeigth, int sizeWidth);
	~Level();

	void DrawLevel(void) const;

	void DrawMenu(void) const;

	void createSprite(void);

	void restartSprite(void);

	void levelPressKey(char key);

	void DrawBufer(void);

	void UpdateLevel(void) ;

	int getModeLevel(void) const;
	
	Coordinates getPosPlayer(void) const;
	char**  get_levelMap(void) const;

	bool isValiedErase(const Coordinates &pos);

	friend class Sprite;
	
private:
	bool read_file();

	int convertCharToInt(const char simvol);

	bool update_PlayerPoint(void);

	bool update_Enemy(void);

	bool update_PointEnemy(void);

	bool update_EnemyPlayer(void);

	void changeMode(void);

	bool saveProgress(void);

	bool readProgress(void);

private:
	DravEngine *dravEngine;
	int sizeWidth;
	int sizeHeigth;
	char **levelMap;

	list<Sprite*> baseSprite;
	list<Sprite*> ::iterator IterSprite;

	Character *player;
	int modeLevel;
	int score;
	double startTimeLevel;

	int livesPlayer;

	vector<Coordinates> coordEnemy;

	stack<int>  prevMode;
};

#endif


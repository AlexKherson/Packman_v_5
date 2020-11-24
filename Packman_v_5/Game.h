#ifndef GAME_H
#define GAME_H

#include "DravEngine.h"

#include "Level.h"


//enum BaseModeGame
//{
//	continueGame,
//	restartGame,
//	gameOver
//};

class Game
{
public:
	bool Game_run(void);

private:
	void timeUpdate(void);

private:
	int frameCount;
	double startTime;
	double lastTime;

	DravEngine DravArea; //конструктор ????? вроде как бы и без него не плохо но если довавлять класы 
						 //
						 //
						 // Time Input ......



	Level *levelGame;
};

#endif


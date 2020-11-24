#include "Game.h"


#include <windows.h>



#define GAME_SPEED 333.3333333 //не могу подобрать правильно время 


#include <iostream>
using std::cout;

bool Game::Game_run(void)
{
	
	levelGame = new Level(&DravArea, DravArea.get_screenHeigth(), DravArea.get_screenWidth());

	levelGame->DrawLevel();

	levelGame->createSprite();

	levelGame->DrawBufer();

	

	char key = ' ';
	startTime = timeGetTime();
	frameCount = 0;
	lastTime = 0;
	while (key != 'q')
	{
		key = getch();

		if (levelGame->getModeLevel() == restartGame)
		{
			delete levelGame;

			DravArea.clearBufer();

			levelGame = new Level(&DravArea, DravArea.get_screenHeigth(), DravArea.get_screenWidth());

			levelGame->DrawLevel();				

			levelGame->restartSprite();					

			levelGame->DrawBufer();

			levelGame->DrawMenu();
		}

		if (levelGame->getModeLevel() == gameOver)
		{
			cout << "Game Over\n";
			delete levelGame;
			return true;
		}

		if (key != ERR && key != 'q')
		{
			levelGame->levelPressKey(key);
		}

		timeUpdate();
	}
	delete levelGame;
	return true;
}


void Game::timeUpdate(void)
{
	double currentTime = timeGetTime() - lastTime;
	if (currentTime < GAME_SPEED)
	{
		return;
	}

	levelGame->UpdateLevel();
	frameCount++;
	lastTime = timeGetTime();
}






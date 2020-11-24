#include "Level.h"


#include "Enemy.h"
#include "Character.h"
#include "Point.h"

#include <string>
#include <fstream>
#include <exception>
#include <Windows.h>

#include <iostream>
using std::cout;

Level::Level(DravEngine * drav_engine, int sizeHeigth, int sizeWidth)
{
	this->dravEngine = drav_engine;
	this->sizeWidth = sizeWidth;
	this->sizeHeigth = sizeHeigth;

	levelMap = new char *[sizeHeigth];
	for (int i = 0; i < sizeHeigth; i++)
		levelMap[i] = new char[sizeWidth];

	

	player = nullptr;
	this->modeLevel = waitEnemy;
	this->score = 0;
	this->startTimeLevel= timeGetTime();
	this->livesPlayer = 3;
	
	read_file();

}

Level::~Level()
{
	for (int i = 0; i < sizeHeigth; i++)
		delete[] levelMap[i];
	delete[]levelMap;

	delete player;

	for (auto IterSprite = baseSprite.begin(); IterSprite != baseSprite.end(); IterSprite++)
		delete *IterSprite;
}

void Level::DrawLevel(void) const
{
	dravEngine->DravBackGround(levelMap);
}

void Level::DrawMenu(void) const
{
	dravEngine->drawScoreAndLive(score, player->getLives());
}

int Level::convertCharToInt(const char simvol)
{
	return simvol-'0';
}

bool Level::update_PlayerPoint(void)
{
	Sprite *tmp = nullptr;
	for (auto IterSprite = baseSprite.begin(); IterSprite != baseSprite.end(); IterSprite++)
	{

		if (player->getPos() == (*IterSprite)->getPos() 
			&&
			dynamic_cast<Point*> (*IterSprite))
		{

			switch ((*IterSprite)->getClassId())
			{
			case 2:
				prevMode.push(modeLevel);
				modeLevel = frightenedEnemy;
				startTimeLevel = timeGetTime();
				score += 50;
				break;
			case 7:
				score += 10;
				break;
			}
				tmp = *IterSprite;
				Coordinates posObj = (*IterSprite)->getPos();
				if (IterSprite == baseSprite.begin())
					IterSprite++;
				else
					IterSprite--;

				baseSprite.remove_if(
					[posObj](const Sprite *tmp)
				{
					return (tmp->getPos() == posObj
						&& (tmp->getClassId()==2 || 
						tmp->getClassId()==7));
				});

				delete tmp;
		}
	}
	return false;
}

bool Level::update_Enemy(void)
{
	for (auto IterSprite = baseSprite.begin(); IterSprite != baseSprite.end(); IterSprite++)
	{
		if (dynamic_cast<Enemy*>(*IterSprite))
		{
			(*IterSprite)->SpriteUpdate();
			coordEnemy.push_back((*IterSprite)->getPos());
		}
	}
	return false;
}

bool Level::update_PointEnemy(void)
{
	for (auto IterSprite = baseSprite.begin(); IterSprite != baseSprite.end(); IterSprite++)
	{
		bool isCoinsender = true;
		if (dynamic_cast<Point*>(*IterSprite))
		{
			for (int i = 0; i < coordEnemy.size(); i++)
			{
				if (coordEnemy[i] == (*IterSprite)->getPos())
				{
					isCoinsender = false;
				}
			}
			if (isCoinsender)
				(*IterSprite)->SpriteUpdate();
		}
	}
	coordEnemy.clear();
	return false;
}

bool Level::update_EnemyPlayer(void)
{
	for (auto IterSprite = baseSprite.begin(); IterSprite != baseSprite.end(); IterSprite++)
		if (dynamic_cast<Enemy*>(*IterSprite) && player->getPos() == (*IterSprite)->getPos())
		{
			if (modeLevel == frightenedEnemy)
			{
				score += 200;
				int tmpClassId = (*IterSprite)->getClassId();
				int indexSprite = 0;
				Sprite *tmpSprite=(*IterSprite);
				Coordinates posObj = (*IterSprite)->getPos();
				baseSprite.remove_if(
					[posObj](const Sprite *tmp)
				{
					return tmp->getPos() == posObj;
				});
				delete tmpSprite;
				for (int i = 0; i < sizeHeigth; i++)
					for (int j = 0; j < sizeWidth; j++)
					{
						indexSprite = convertCharToInt(levelMap[i][j]);
						if (indexSprite == tmpClassId)
						{
							baseSprite.push_back(new Enemy(dravEngine, this, (float)i, (float)j, indexSprite));
							(*(--baseSprite.end()))->addSpriteBufer();
						}
					}
			}
			else
			{
				if (player->isAlives())
					modeLevel = gameOver;
				else
				{
					modeLevel = restartGame;
					saveProgress();
				}
			}
			break;
		}
	return false;
}

void Level::changeMode(void)
{
	if (timeGetTime() - startTimeLevel < 5000)
		return;

	startTimeLevel = timeGetTime();
	switch (modeLevel)
	{
	case waitEnemy:
		modeLevel = continueGame;
		break;
	case continueGame:
		modeLevel = chaseCharacter;
		break;
	case frightenedEnemy:
		modeLevel= prevMode.top();
		break;
	case chaseCharacter:
		modeLevel = continueGame;
		break;
	}
}

bool Level::saveProgress(void)
{
	std::fstream file;
	file.open("temp.txt",std::fstream:: binary | std::fstream::out);

	if (!file.is_open())
		throw std::exception();
	int countLives=player->getLives();
	int tmpScore = score;
	file.write((char*)&countLives, sizeof(int));
	file.write((char*)&tmpScore, sizeof(int));
	Coordinates tmp;
	int tmpClassId;
	for (auto IterSprite=baseSprite.begin();IterSprite!=baseSprite.end();IterSprite++)
		if (dynamic_cast<Point*>(*IterSprite))
		{
			tmp = (*IterSprite)->getPos();
			file.write((char*) &tmp.x, sizeof(float));
			file.write((char*) &tmp.y, sizeof(float));

			tmpClassId = (*IterSprite)->getClassId();
			file.write((char*) &tmpClassId, sizeof(int));
		}
	file.close();
	return false;
}

bool Level::readProgress(void)
{
	int tmpClassId=0;
	float x=0;
	float y=0;

	int tmpLives;
	std::fstream file;
	file.open("temp.txt", std::fstream::in );

	

	if (!file.is_open())
		throw std::exception();


	file.read((char*)&tmpLives, sizeof(int));
	livesPlayer = tmpLives;

	file.read((char*)&score, sizeof(int));
	while (!file.eof())
	{		
		file.read((char*)&x, sizeof(float));
		file.read((char*)&y, sizeof(float));
		file.read((char*)&tmpClassId, sizeof(int));
		baseSprite.push_back(new Point(dravEngine, this, x, y, tmpClassId));
	}

	file.close();
	return false;
}

void Level::DrawBufer(void)
{
	
	dravEngine->DrawChange();
}

void Level::UpdateLevel(void) 
{
	
	DrawLevel();
	
	changeMode();

	update_PlayerPoint();	
		
	update_Enemy();

	update_PointEnemy();

	update_EnemyPlayer();

	DrawBufer();

	DrawMenu();
}

int Level::getModeLevel(void) const
{
	return modeLevel;
}

Coordinates Level::getPosPlayer(void) const
{
	return player->getPos();
}

char ** Level::get_levelMap(void) const
{
	return  levelMap;;
}

bool Level::isValiedErase(const Coordinates & pos)
{
	for (auto IterSprite = baseSprite.begin(); IterSprite != baseSprite.end(); IterSprite++)
		if (dynamic_cast<Enemy*>(*IterSprite) && (*IterSprite)->getPos() == pos)
			return true;
	return false;
}

void Level::createSprite(void)
{
	int indexSprite = 0;
	for (int i = 0; i < sizeHeigth; i++)
		for (int j = 0; j < sizeWidth; j++)
		{
			indexSprite = convertCharToInt(levelMap[i][j]);
			if (levelMap[i][j] > '2' && levelMap[i][j] < '7')
			{
				baseSprite.push_back(new Enemy(dravEngine, this, (float)i, (float)j, indexSprite));
			}

			if (levelMap[i][j] == '8')
			{
				player = new Character(dravEngine, this, (float)i, (float)j,indexSprite,3);
				player->addSpriteBufer();
			}
				

			if (levelMap[i][j] =='2' || levelMap[i][j] == '7')
			{
				baseSprite.push_back(new Point(dravEngine, this, (float)i, (float)j, indexSprite));
			}
		}

	for (IterSprite = baseSprite.begin(); IterSprite != baseSprite.end(); IterSprite++)
		(*IterSprite)->addSpriteBufer();

}

void Level::restartSprite(void)
{
	int indexSprite = 0;

	readProgress();
	cout << livesPlayer << "\n";
	for (int i = 0; i < sizeHeigth; i++)
		for (int j = 0; j < sizeWidth; j++)
		{
			indexSprite = convertCharToInt(levelMap[i][j]);
			if (levelMap[i][j] > '2' && levelMap[i][j] < '7')
			{
				baseSprite.push_back(new Enemy(dravEngine, this, (float)i, (float)j, indexSprite));
			}

			if (levelMap[i][j] == '8')
			{
				player = new Character(dravEngine, this, (float)i, (float)j, indexSprite,livesPlayer);
				player->addSpriteBufer();
			}					   		
		}
	
	for (IterSprite = baseSprite.begin(); IterSprite != baseSprite.end(); IterSprite++)
		(*IterSprite)->addSpriteBufer();
	}

void Level::levelPressKey(char key)
{
	
	player->pressKey(key);
}

bool Level::read_file()
{
	std::string line;
	std::fstream file;
	file.open("level_1.txt", std::fstream::in);

	if (!file.is_open())
		throw std::exception();

	int  i = 0;
	while (!file.eof())
	{
		file >> line;

		for (int j = 0; j < sizeWidth; j++)
			levelMap[i][j] = line[j];
		i++;
	}

	file.close();

	return true;
}


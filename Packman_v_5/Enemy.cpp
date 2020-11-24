#include "Enemy.h"

Enemy::Enemy(DravEngine *dravEngineEnemy,Level *levelEnemy, float x, float y,int index):
	Sprite (dravEngineEnemy,levelEnemy, x,y,index)
{
	
	isAhouse = true;
	if (index % 2 == 0)
		direction = dirLeft;
	else
		direction = dirRigth;

	posScatter.set(targetScatterX[index-3], targetScatterY[index-3]);

	createBaseDirectionMove();
}


Enemy::~Enemy()
{
	
}

void Enemy::SpriteUpdate(void)
{
	if (levelSprite->getModeLevel() == waitEnemy)
		return;

	if (isAhouse)
	{
		Coordinates tmp;
		tmp = Simulation(9, 13);
		prevPos = pos;
		moveSprite(tmp.x, tmp.y);
		tmp = getPos();
		if (tmp.x == 9 && tmp.y == 13)
			isAhouse = false;
	}
	else
	{
		switch (levelSprite->getModeLevel())
		{
		case continueGame:
			modeContinueGame();
			break;
		case frightenedEnemy:
			modeFrightenedEnemy();
			break;
		case chaseCharacter:
			modeChaseCharacter();
			break;
		default:
			throw std::exception();
		}
	}
}



void Enemy::createBaseDirectionMove(void)
{
	baseDirectionMove.emplace(dirUp, dirDown);
	baseDirectionMove.emplace(dirRigth, dirLeft);
	baseDirectionMove.emplace(dirDown, dirUp);
	baseDirectionMove.emplace(dirLeft, dirRigth);
}

Coordinates Enemy::Simulation(const int targetX, const int targetY)
{
	vector<int> direction_next_coord;

	auto it = baseDirectionMove.find(direction);
	for (int i = 0; i < 4; i++)
	{
		if (!isAhouse && pos.x + nextX[i] == 10 && pos.y + nextY[i] == 13)
			continue ;

		if (isValiedLevelMove(pos.x + nextX[i], pos.y + nextY[i]) &&
			i != it->second)
				direction_next_coord.push_back(i);
	}

	if (direction_next_coord.size() == 0)
		throw std::exception();

	if (direction_next_coord.size() == 1)
	{
		Coordinates new_pos(nextX[direction_next_coord[0]], nextY[direction_next_coord[0]]);
		direction = direction_next_coord[0];
		direction_next_coord.clear();
		return new_pos;
	}

	int shift_posX;
	int shift_posY;



	double distance = 10000;
	int index_next_coordinate;

	for (int i = 0; i < direction_next_coord.size(); i++)
	{
		shift_posX = targetX - (pos.x + nextX[direction_next_coord[i]]);
		shift_posY = targetY - (pos.y + nextY[direction_next_coord[i]]);



		if (distance > sqrt(shift_posX*shift_posX + shift_posY * shift_posY))
		{
			distance = sqrt(shift_posX*shift_posX + shift_posY * shift_posY);
			index_next_coordinate = direction_next_coord[i];

		}
	}

	direction = index_next_coordinate;
	Coordinates new_pos(nextX[index_next_coordinate], nextY[index_next_coordinate]);
	direction_next_coord.clear();
	return new_pos;
}

void Enemy::modeContinueGame(void)
{
	Coordinates tmp;
	tmp = Simulation(posScatter.x, posScatter.y);
	prevPos = pos;
	checkRigthMap();
	checkLeftMap();
	moveSprite(tmp.x, tmp.y);
	
}

void Enemy::modeFrightenedEnemy(void)
{
	direction = rand() % 4;
	Coordinates tmp = 
		Simulation(rand()%dravEngineSprite->get_screenHeigth(),rand()%dravEngineSprite->get_screenWidth());
	prevPos = pos;
	checkRigthMap();
	checkLeftMap();
	moveSprite(tmp.x, tmp.y);
}

void Enemy::modeChaseCharacter(void)
{
	Coordinates tmp;
	switch (getClassId())
	{
	case 3:
		tmp=Simulation(levelSprite->getPosPlayer().x, levelSprite->getPosPlayer().y);
		break;
	case 4:
		tmp = Simulation(levelSprite->getPosPlayer().x+4, levelSprite->getPosPlayer().y);
		break;
	case 5:
		tmp = Simulation(levelSprite->getPosPlayer().x, levelSprite->getPosPlayer().y-4);
		break;
	case 6:
		tmp = Simulation(levelSprite->getPosPlayer().x-4, levelSprite->getPosPlayer().y);
		break;
	}
	prevPos = pos;
	checkRigthMap();
	checkLeftMap();
	moveSprite(tmp.x, tmp.y);
}

void Enemy::checkRigthMap(void)
{
	if (pos.x == 11 && pos.y == dravEngineSprite->get_screenWidth() - 1
		&&
		direction == dirRigth)
		pos.y = -1;
}

void Enemy::checkLeftMap(void)
{
	if (pos.x == 11 && pos.y == 0 && direction == dirLeft)
		pos.y = dravEngineSprite->get_screenWidth();
}



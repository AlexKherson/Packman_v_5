#ifndef SPRITE_H
#define SPRITE_H


#include "Level.h"
#include "DravEngine.h"


#include <iostream>
using std::cout;

enum colorSprite
{
	white=2,
	red ,
	green,
	blue,
	magenta,
	yellow
};

struct Coordinates
{
	float x;
	float y;

	Coordinates(float x = 0, float y = 0) { this->x = x; this->y = y; };
	void set(float x, float y) { this->x = x; this->y = y; };
	
	Coordinates & operator=(const Coordinates & obj)
	{
		this->x = obj.x;
		this->y = obj.y;
		return *this;
	}
	bool operator ==(const Coordinates &obj) { return ((int)this->x ==(int) obj.x && (int)this->y == (int)obj.y); }
	
};



class Sprite
{
public:
	Sprite(DravEngine *dravEngineSprite,Level *levelSprite,float x,float y,int index/*,int classId*/);
	virtual ~Sprite();
	void addSpriteBufer(void) const;
	int getClassId(void) const;

	Coordinates getPos(void) const;

	virtual void SpriteUpdate(void);

protected:
	bool isValiedLevelMove(const int x, const int y);
	void moveSprite(const int shiftX, const int shiftY);
	void eraseSprite(const int x, const int y);

protected:
	DravEngine *dravEngineSprite;
	Level *levelSprite;

	Coordinates pos;
	Coordinates prevPos;
	

	char image;
	int color;

	int classId;

private:
	const char baseImage[9] = { ' ',' ','@','M','M','M','M','*','<' };
	const int baseColor[9] = { 0,0,white,red,green,blue,magenta,white,yellow };
};

#endif
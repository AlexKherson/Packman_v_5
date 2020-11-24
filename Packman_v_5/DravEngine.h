#ifndef DRAVENGINE_H
#define DRAVENGINE_H


#include "curses.h"

#include "Bufer.hpp"
//#include "Enemy.h"
#include <string>

#include <iostream>
using std::cout;

class DravEngine
{
public:
	DravEngine(int screenWidth = 27, int screenHeigth = 23);
	~DravEngine();
	int get_screenWidth(void)const;
	int get_screenHeigth(void)const;
	void DravBackGround(char **date) const;

	void changeBufer(const int x, const int y, const char image, const char color) const;

	void clearBufer(void);

	void DrawChange(void) ;

	void drawScoreAndLive(const int score, const int lives) const;
private:
	void set_color(void) const;

	void Draw(const int x, const int y, const char image, const int  color) const;
private:
	int screenWidth;
	int screenHeigth;
	char **map;

	Bufer <int > *oldBufer;
	Bufer <int > *newBufer;
	Bufer <char> *imageBufer;
};


#endif

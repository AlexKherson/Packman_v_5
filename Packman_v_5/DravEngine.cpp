#include "DravEngine.h"



DravEngine::DravEngine(int screenWidth, int screenHeigth)
{
	this->screenWidth = screenWidth;
	this->screenHeigth = screenHeigth;
	map = nullptr;

	oldBufer=new Bufer <int>(this->screenHeigth, this->screenWidth);
	newBufer=new Bufer <int>(this->screenHeigth, this->screenWidth);
	imageBufer =new Bufer<char>(this->screenHeigth, this->screenWidth);

	initscr();
	nodelay(stdscr, true);
	noecho();
	raw();
	curs_set(false);
	set_color();


}

DravEngine::~DravEngine()
{
	delete oldBufer;
	delete newBufer;
	delete imageBufer;

	curs_set(true);
	endwin();
}

int DravEngine::get_screenWidth(void) const
{
	return screenWidth;
}

int DravEngine::get_screenHeigth(void) const
{
	return screenHeigth;
}

void DravEngine::DravBackGround(char **date) const
{
	for (int i = 0; i < screenHeigth; i++)
		for (int j = 0; j < screenWidth; j++)
		{
			if (date[i][j] == '0')
			{
				attron(COLOR_PAIR(1));
				mvprintw(i, j, " ");
				attroff(COLOR_PAIR(1));
			}
		}
}

void DravEngine::changeBufer(const int x, const int y, const char image, const char color) const
{
	newBufer->setBufer(x, y, color);
	imageBufer->setBufer(x, y, image);
	
}

void DravEngine::clearBufer(void)
{
	oldBufer->clear();
	newBufer->clear();
	imageBufer->clear();
	for (int i=0;i<screenHeigth;i++)
		for (int j = 0; j < screenWidth; j++)
		{
			attron(COLOR_PAIR(8));
			mvprintw(i, j, " ");
			attroff(COLOR_PAIR(8));
		}
	for (int j = 0; j < screenWidth; j++)
	{
		attron(COLOR_PAIR(8));
		mvprintw(screenHeigth+2, j, " ");
		attroff(COLOR_PAIR(8));
	}
		

}

void DravEngine::DrawChange(void)
{
 	for (int i=0;i<screenHeigth;i++)
		for (int j = 0; j < screenWidth; j++)
		{
			
			if (newBufer->getElement(i, j) != oldBufer->getElement(i, j))
			{
				Draw(i, j, imageBufer->getElement(i, j), newBufer->getElement(i, j));
				oldBufer->setBufer(i, j, newBufer->getElement(i, j));
			}
				
		}
}

void DravEngine::drawScoreAndLive(const int score, const int lives) const
{
	attron(COLOR_PAIR(7));
	mvprintw(screenHeigth + 2, 0, "SCORE  ");
	mvprintw(screenHeigth + 2, 5,"%d",score);
	mvprintw(screenHeigth + 2, 10, "LIVES  ");
	for (int i=0;i<lives;i++)
		mvprintw(screenHeigth + 2, 15+i, "<");

	attroff(COLOR_PAIR(7));
}

void DravEngine::set_color(void) const
{
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_YELLOW, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_BLACK);
}

void DravEngine::Draw(const int x, const int y, const char image, const int color)const
{
	attron(COLOR_PAIR(color));
	mvprintw(x, y, &image);
	attroff(COLOR_PAIR(color));
	refresh();
}

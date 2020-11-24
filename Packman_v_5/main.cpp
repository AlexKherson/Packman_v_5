#include "Game.h"

#include <iostream>
#include <exception>

using std::cout;


int main()
{
	setlocale(LC_ALL, ".1251");
	try
	{
		Game Packmen;
		Packmen.Game_run();
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what();
	}



	return 0;
}
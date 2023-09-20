#include"Sourse/Render/Render.h"
#include "Sourse/Game/Game.h"
#include <iostream>
int main()
{
	try
	{
		Game::init();
		Render::run();
		Game::terminate();
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
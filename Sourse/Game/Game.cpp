#include "Game.h"
#include <iostream>
Game::Cell** Game::area = nullptr;
bool Game::filledWithMines = false;
void Game::init()
{
	area = new Cell*[AREA_HEIGHT];
	for (size_t i = 0; i < AREA_HEIGHT; i++)
	{
		area[i] = new Cell[AREA_WIDTH]{};
	}
}
void Game::terminate()
{
	for (size_t i = 0; i < AREA_HEIGHT; i++)
	{
		delete area[i];
	}
	delete[] area;
}
void Game::fillMines(int x, int y)
{
	std::cout << "Game: start" << std::endl;
	srand(time(nullptr));
	for (size_t i = 0; i < COUNT_MINES;)
	{
		int rx = rand() % AREA_WIDTH;
		int ry = rand() % AREA_HEIGHT;
		if (!area[ry][rx].mine&&!isÑlosely(rx,ry,x,y))
		{
			area[ry][rx].mine = true;
			countMines(rx, ry);
			++i;
		}
	}
}
void Game::countMines(int x, int y)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (isInArea(x+j,y+i))
			{
				area[y + i][x + j].minesNearby++;
			}
		}
	}
}
bool Game::isInArea(int x, int y)
{
	return (x >= 0) && (x < AREA_WIDTH) && (y >= 0) && (y < AREA_HEIGHT);
}
bool Game::isÑlosely(int rx, int ry, int x, int y)
{
	return (rx-1<=x)&&(x<=rx+1)&&(ry - 1 <= y) && (y <= ry + 1);
}
bool Game::openCells(int x, int y)
{
	if (!isInArea(x, y) || area[y][x].open || area[y][x].flag)
	{
		return true;
	}
	area[y][x].open = true;
	if (area[y][x].mine)
	{
		return false;
	}
	if (area[y][x].minesNearby == 0)
	{
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				openCells(x + j, y + i);
			}
		}
	}
	return true;
}
void Game::restart()
{
	for (size_t i = 0; i < AREA_HEIGHT; i++)
	{
		for (size_t j = 0; j < AREA_WIDTH; j++)
		{
			area[j][i].open = false;
			area[j][i].flag = false;
			area[j][i].mine = false;
			area[j][i].minesNearby = 0;
		}
	}
	filledWithMines = false;
}
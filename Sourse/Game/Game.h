#pragma once
#define AREA_WIDTH 10
#define AREA_HEIGHT 10
#define COUNT_MINES 10
class Game
{
public:
	struct Cell 
	{
		bool open;
		bool mine;
		bool flag;
		unsigned char minesNearby;
	};
	static bool filledWithMines;
	static void init();
	static void terminate();
	static void fillMines(int x, int y);
	static void restart();
	static bool isInArea(int x, int y);
	static bool is—losely(int rx, int ry, int x, int y);
	static bool openCells(int x, int y);
	static Cell** area;
	static void countMines(int x, int y);
private:
};
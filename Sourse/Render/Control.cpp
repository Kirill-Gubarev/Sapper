#include "Render.h"
#include "../Game/Game.h"
#include <iostream>
#include <thread>
#include <chrono>

bool Render::lock = false;
double Render::mouseX = 0;
double Render::mouseY = 0;
void Render::controlling()
{
	glfwGetCursorPos(window, &mouseX, &mouseY);
	glfwSetMouseButtonCallback(window, mouseCallback);
}
void Render::mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (!lock)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			if (action == GLFW_RELEASE)
			{
				openCell();
			}
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			if (action == GLFW_RELEASE)
			{
				setFlag();
			}
			break;

		}
	}
}
int Render::getMouseX()
{
	return (int)(mouseX / CELL_WIDTH);
}
int Render::getMouseY()
{
	return (int)(AREA_HEIGHT - mouseY / CELL_HEIGHT);
}
void Render::openCell()
{
	int x = getMouseX();
	int y = getMouseY();
	if (!Game::filledWithMines)
	{
		Game::fillMines(x, y);
		Game::filledWithMines = true;
	}
	if (!Game::area[y][x].open)
		if (Game::openCells(x, y))
		{
			victory();
		}
		else
		{
			lock = true;
			std::thread t(gameOver);
			t.detach();
		}
}
void Render::setFlag()
{
	int x = getMouseX();
	int y = getMouseY();
	if (Game::area[y][x].flag)
	{
		Game::area[y][x].flag = false;
	}
	else
	{
		Game::area[y][x].flag = true;
	}
	victory();
}
void Render::gameOver()
{
	for (int i = 0; i < AREA_HEIGHT; i++)
	{
		for (int j = 0; j < AREA_WIDTH; j++)
		{
			if (Game::area[i][j].mine)
			{
				Game::area[i][j].open = true;
			}
		}
	}
	std::cout << "Game: Game over" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	for (int i = AREA_HEIGHT - 1; i >= 0; i--)
	{
		for (int j = 0; j < AREA_WIDTH; j++)
		{
			if (!Game::area[i][j].open)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(70));
				Game::area[i][j].open = true;
				drawCell(j, i);
			}
		}
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
	Game::restart();
	lock = false;
}
void Render::victory()
{
	for (int i = 0; i < AREA_HEIGHT; i++)
		for (int j = 0; j < AREA_WIDTH; j++)
			if (!Game::area[j][i].open && !Game::area[j][i].mine)
			{
				return;
			}
			else if (Game::area[j][i].mine)
			{
				if (!Game::area[j][i].flag)
				{
					return;
				}
			}
			else if (Game::area[j][i].flag)
			{
				return;
			}
	std::cout << "Game: Victory" << std::endl;
	lock = true;
	std::thread t([]()
		{
			std::this_thread::sleep_for(std::chrono::seconds(3));
			Game::restart();
			lock = false;
		});
	t.detach();
}
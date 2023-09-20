#include "Render.h"
#include "../Game/Game.h"
#include <iostream>

GLFWwindow* Render::window = nullptr;
void Render::init()
{
	if (!glfwInit())
	{
		throw std::exception("Console: Failed to initialize glfw");
	}
	window = glfwCreateWindow(CELL_WIDTH*AREA_WIDTH, CELL_HEIGHT*AREA_HEIGHT, "Sapper", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		throw std::exception("Console: Failed to create window");
	}
	glfwMakeContextCurrent(window);
}
void Render::terminate()
{
	glfwTerminate();
}

void Render::run()
{
	init();
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glLoadIdentity();
		glTranslatef(-1, -1, 0);
		glScalef((float)2/AREA_WIDTH, (float)2 / AREA_HEIGHT, 0);


		controlling();
		drawArea();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	terminate();
}
void Render::drawArea()
{
	for (size_t i = 0; i < AREA_HEIGHT; i++)
	{
		for (size_t j = 0; j < AREA_WIDTH; j++)
		{
			drawCell(j, i);
		}
	}
	highLight();
}
void Render::drawCell(int x, int y)
{
	if (Game::area[y][x].open)
	{
		drawSquare(Point(x, y), RGB(0.3f));
		if (Game::area[y][x].mine)
		{
			drawMine(Point(x + 0.5f, y + 0.5f));
		}
		else
		{
			writeNumber(Point(x, y), Game::area[y][x].minesNearby);
		}
	}
	else
	{
		drawSquare(Point(x, y), RGB(0.6f));
		if (Game::area[y][x].flag)
		{
			drawFlag(Point(x, y));
		}
	}
}
void Render::highLight()
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		int x = getMouseX();
		int y = getMouseY();
		if (!Game::area[y][x].open)
		{
			drawSquare(Point(x, y), RGB(0.1f, 0.1f, 0.9f));
			if (Game::area[y][x].flag)
			{
				drawFlag(Point(x, y));
			}
		}
	}
}
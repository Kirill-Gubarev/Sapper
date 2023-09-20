#pragma once
#include <GLFW/glfw3.h>
#define CNT 30
#define CELL_WIDTH 60
#define CELL_HEIGHT 60
#define _USE_MATH_DEFINES
static class Render
{
private://basic
	static GLFWwindow* window;
	struct Point
	{
		Point(float x, float y)
		{
			this->x = x;
			this->y = y;
		}
		Point operator++()
		{
			return Point(++x,++y);
		}
		Point operator+(Point p)
		{
			return Point(this->x+p.x, this->y + p.y);
		}
		float x;
		float y;
	};
	struct RGB
	{
		RGB(float R,float G,float B)
		{
			this->R = R;
			this->G = G;
			this->B = B;
		}
		RGB(float value)
		{
			this->R = value;
			this->G = value;
			this->B = value;
		}
		RGB operator +(float value)
		{
			return RGB(this->R+value, this->G + value, this->B + value);
		}
		RGB operator -(float value)
		{
			return RGB(this->R - value, this->G - value, this->B - value);
		}
		float R, G, B;
	};

	inline static void drawCell(int x,int y);
	inline static void drawArea();
	static void highLight();

private://Objects
	static void setColor(RGB color);

	static void drawSquare(Point p, RGB color);
	static void drawSquare(Point p1, Point p2);
	static void drawSquare(Point p1, Point p2, Point p3, Point p4);
	static void drawCircle(Point p, float rad);
	static void drawFlag(Point p);
	static void drawMine(Point p);

	static void writeNumber(Point p,int number);
	static void drawIndicator(Point p, int line);
	static void drawLine(Point p1, Point p2);
private://control
	static bool lock;
	static double mouseX;
	static double mouseY;
	static void controlling();
	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	static int getMouseX();
	static int getMouseY();
	static void openCell();
	static void setFlag();
	static void gameOver();
	static void victory();
public:
	static void init();
	static void terminate();
	static void run();
};
#include "Render.h"
#include <math.h>
void  Render::setColor(RGB color)
{
	glColor3f(color.R, color.G, color.B);
}

void Render::drawSquare(Point p, RGB color)
{
	glBegin(GL_TRIANGLE_STRIP);

	setColor(color + 0.1f);
	glVertex2f(p.x, p.y + 1);
	setColor(color);
	glVertex2f(p.x + 1, p.y + 1);
	glVertex2f(p.x, p.y);
	setColor(color - 0.1f);
	glVertex2f(p.x + 1, p.y);

	glEnd();
}
void Render::drawSquare(Point p1, Point p2)
{
	glBegin(GL_TRIANGLE_STRIP);

	glVertex2f(p1.x, p1.y);
	glVertex2f(p1.x, p2.y);
	glVertex2f(p2.x, p1.y);
	glVertex2f(p2.x, p2.y);

	glEnd();
}
void Render::drawSquare(Point p1, Point p2, Point p3, Point p4)
{
	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glVertex2f(p3.x, p3.y);
	glVertex2f(p4.x, p4.y);

	glEnd();
}
void Render::drawCircle(Point p, float rad)
{
	glBegin(GL_TRIANGLE_FAN);
	float x = 0;
	float y = 0;
	float a = M_PI * 2 / CNT;
	glVertex2f(p.x, p.y);
	for (int i = 0; i <= CNT; ++i)
	{
		x = sinf(a * (float)i) * rad;
		y = cosf(a * (float)i) * rad;
		glVertex2f(x + p.x, y + p.y);
	}
	glEnd();
}
void Render::drawFlag(Point p)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(4);
	drawLine(Point(0.66f, 0.5f) + p, Point(0.66f, 0.2f) + p);

	glBegin(GL_TRIANGLES);

	glColor3f(0.95f, 0.05f, 0.05f);

	glVertex2f(p.x + 0.25f, p.y + 0.625f);
	glVertex2f(p.x + 0.7f, p.y + 0.85f);
	glVertex2f(p.x + 0.7f, p.y + 0.4f);


	glEnd();


}
void Render::drawMine(Point p)
{
	glColor3f(0, 0, 0);
	drawCircle(p, 0.25f);
	float p1 = 0.35f, p2 = 0.25f;
	drawSquare(Point(-p1, -p2) + p, Point(-p2, -p1) + p, Point(p1, p2) + p, Point(p2, p1) + p);
	drawSquare(Point(p1, -p2) + p, Point(p2, -p1) + p, Point(-p1, p2) + p, Point(-p2, p1) + p);
}

void Render::writeNumber(Point p, int number)
{
	glColor3f(0.0f, 0.55f, 0.85f);
	glLineWidth(4);
	switch (number)
	{
	case 0:
	case 9:
		return;
	case 3:
		drawIndicator(p, 3);
		drawIndicator(p, 6);
	case 7:
		drawIndicator(p, 0);
	case 1:
		drawIndicator(p, 2);
		drawIndicator(p, 5);
		break;
	case 2:
		drawIndicator(p, 0);
		drawIndicator(p, 2);
		drawIndicator(p, 3);
		drawIndicator(p, 4);
		drawIndicator(p, 6);
		break;
	case 4:
		drawIndicator(p, 1);
		drawIndicator(p, 2);
		drawIndicator(p, 3);
		drawIndicator(p, 5);
		break;
	case 8:
		drawIndicator(p, 2);
	case 6:
		drawIndicator(p, 4);
	case 5:
		drawIndicator(p, 0);
		drawIndicator(p, 1);
		drawIndicator(p, 3);
		drawIndicator(p, 5);
		drawIndicator(p, 6);
		break;
	}
}
void Render::drawIndicator(Point p, int line)
{
	switch (line)
	{
	case 0:
		drawLine(Point(0.33f, 0.75f) + p, Point(0.66f, 0.75f) + p);
		break;
	case 1:
		drawLine(Point(0.33f, 0.75f) + p, Point(0.33f, 0.5f) + p);
		break;
	case 2:
		drawLine(Point(0.66f, 0.75f) + p, Point(0.66f, 0.5f) + p);
		break;
	case 3:
		drawLine(Point(0.33f, 0.5f) + p, Point(0.66f, 0.5f) + p);
		break;
	case 4:
		drawLine(Point(0.33f, 0.5f) + p, Point(0.33f, 0.25f) + p);
		break;
	case 5:
		drawLine(Point(0.66f, 0.5f) + p, Point(0.66f, 0.25f) + p);
		break;
	case 6:
		drawLine(Point(0.33f, 0.25f) + p, Point(0.66f, 0.25f) + p);
		break;
	}
}
void Render::drawLine(Point p1, Point p2)
{
	glBegin(GL_LINES);

	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);

	glEnd();
}
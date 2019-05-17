#include "Driver.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

//#define PI ( M_PI )
#define PI (3.14)

void Driver::drawPixel(Point point, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX = point.x * width();
	int pixelY = point.y * height();

	if (thickness <= 1)
	{
		// use raw drawing service
		drawPixel(pixelX, pixelY, color);
	}
	else
	{
		// draw using circle as a "brush"
		fillCircle(pixelX, pixelY, round(thickness / 2.0), color);
	}
}

void Driver::drawLine(Line line, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = line.begin.x * width();
	int pixelY0 = line.begin.y * height();
	int pixelX1 = line.end.x * width();
	int pixelY1 = line.end.y * height();

	if (thickness <= 1)
	{
		// use raw drawing service
		drawLine(pixelX0, pixelY0, pixelX1, pixelY1, color);
	}
	else
	{

		Color c = {50, 50, 50};
		fillCircle(pixelX0, pixelY0, thickness / 2, c);
		fillCircle(pixelX1, pixelY1, thickness / 2, c);

		drawLine(pixelX0, pixelY0, pixelX1, pixelY1, color);

		// compute line angle
		float angle = atan2(pixelY1 - pixelY0, pixelX1 - pixelX0);

		// compute point on line perpendicular to start and end ad distance thickness/2
		// float dx = (pixelX1 - pixelX0);
		// float dy = (pixelY1 - pixelY0);

		// float angle = atan(dy / dx);

		float angle1 = angle - (3.14 / 2);
		float angle2 = angle + (3.14 / 2);

		float bottomLeftX = pixelX0 + cos(angle1) * (thickness / 2);
		float bottomLeftY = pixelY0 + sin(angle1) * (thickness / 2);

		drawPixel(bottomLeftX, bottomLeftY, color);

		float bottomRightX = pixelX1 + cos(angle1) * (thickness / 2);
		float bottomRightY = pixelY1 + sin(angle1) * (thickness / 2);
		drawPixel(bottomRightX, bottomRightY, color);

		float topLeftX = pixelX0 + cos(angle2) * (thickness / 2);
		float topLeftY = pixelY0 + sin(angle2) * (thickness / 2);
		drawPixel(topLeftX, topLeftY, color);

		float topRightX = pixelX1 + cos(angle2) * (thickness / 2);
		float topRightY = pixelY1 + sin(angle2) * (thickness / 2);
		drawPixel(topRightX, topRightY, color);

		// float step;

		// if (abs(dx) >= abs(dy))
		// 	step = abs(dx);
		// else
		// 	step = abs(dy);

		// dx /= step;
		// dy /= step;

		// float x = -dy;
		// float y = dx;
		// float distance = sqrt( x*x + y*y);

		// for (int i = 0; i < step; i++)
		// {
		// 	// drawLine(pixelX0+x, pixelY0+y,pixelX1+x, pixelY1+y, color);
		// 	// drawLine(pixelX0-x, pixelY0-y,pixelX1-x, pixelY1-y, color);
		// 	x -= dy;
		// 	y += dx;
		// 	distance = sqrt( x*x + y*y);
		// }
	}
}

void Driver::drawCircle(Circle circle, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = circle.center.x * width();
	int pixelY0 = circle.center.y * height();
	int pixelR;

	// compute radius using the smalles tft dimension. This way, a radius of 1.0 can be fully visualized
	if (height() < width())
		pixelR = circle.outerRadius * height();
	else
		pixelR = circle.outerRadius * width();

	if (thickness <= 1)
	{
		drawCircle(pixelX0, pixelY0, pixelR, color);
	}
	else
	{
		for (int t = 0; t < thickness; t++)
			drawCircle(pixelX0, pixelY0, (pixelR - t / 2) + t, color);
	}
}

void Driver::drawRectangle(Rectangle rectangle, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = rectangle.topLeft.x * width();
	int pixelY0 = rectangle.topLeft.y * height();
	int pixelX1 = rectangle.bottomRight.x * width();
	int pixelY1 = rectangle.bottomRight.y * height();

	if (thickness <= 1)
	{
		// use raw drawing service
		drawRectangle(pixelX0, pixelY0, pixelX1, pixelY1, color);
	}
	else
	{
		// draw using circle as a "brush"
		Line line;
		line.begin = rectangle.topLeft;
		line.begin = rectangle.topRight;
		drawLine(line, thickness, color);

		line.begin = rectangle.topRight;
		line.begin = rectangle.bottomRight;
		drawLine(line, thickness, color);

		line.begin = rectangle.bottomRight;
		line.begin = rectangle.bottomLeft;
		drawLine(line, thickness, color);

		line.begin = rectangle.bottomLeft;
		line.begin = rectangle.topLeft;
		drawLine(line, thickness, color);
	}
}

void Driver::fillRectangle(Rectangle rectangle, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = rectangle.topLeft.x * width();
	int pixelY0 = rectangle.topLeft.y * height();
	int pixelX1 = rectangle.bottomRight.x * width();
	int pixelY1 = rectangle.bottomRight.y * height();

	fillRectangle(pixelX0, pixelY0, pixelX1, pixelY1, color);
	drawRectangle(rectangle, thickness, color);
}

void Driver::fillCircle(Circle circle, int thickness, Color color)
{
	//compute pixel coordinates
	int pixelX0 = circle.center.x * width();
	int pixelY0 = circle.center.y * height();
	int pixelR;

	// compute radius using the smalles tft dimension. This way, a radius of 1.0 can be fully visualized
	if (height() < width())
	{
		int pixelR = circle.outerRadius * height();
	}
	else
	{
		int pixelR = circle.outerRadius * width();
	}

	fillCircle(pixelX0, pixelY0, pixelR, color);
	drawCircle(circle, thickness, color);
}

void Driver::fillCircle(int xc, int yc, int radius, Color color)
{
	/* Function for circle-generation using Bresenham's algorithm from 
	https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/ */

	int x = 0;
	int y = radius;
	int d = 3 - (2 * radius);
	BresenhamFillCircle(xc, yc, x, y, color);
	while (y >= x)
	{
		// for each pixel we will draw all eight pixels
		x++;
		// check for decision parameter and correspondingly update d, x, y
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		BresenhamFillCircle(xc, yc, x, y, color);
	}
}

/* local helper function */
void Driver::BresenhamFillCircle(int xc, int yc, int x, int y, Color color)
{
	/* Function for circle-generation using Bresenham's algorithm from 
	https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/ */

	drawLine(xc - x, yc + y, xc + x, yc + y, color);
	drawLine(xc - x, yc - y, xc + x, yc - y, color);
	drawLine(xc - y, yc + x, xc + y, yc + x, color);
	drawLine(xc - y, yc - x, xc + y, yc - x, color);
}

void Driver::fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color)
{
	// from http://www-users.mat.uni.torun.pl/~wrona/3d_tutor/tri_fillers.html

	// 	the coordinates of vertices are (A.x,A.y), (B.x,B.y), (C.x,C.y); we assume that A.y<=B.y<=C.y (you should sort them first)
	// dx1,dx2,dx3 are deltas used in interpolation
	// horizline draws horizontal segment with coordinates (S.x,Y), (E.x,Y)
	// S.x, E.x are left and right x-coordinates of the segment we have to draw
	// S=A means that S.x=A.x; S.y=A.y;
	// *** begin triangle filler ***

	Point A, B, C, S, E;
	float dx1, dx2, dx3;

	//TODO order points
	A.x = x0;
	A.y = y0;
	B.x = x1;
	B.y = y1;
	C.x = x2;
	C.y = y2;

	if (B.y - A.y > 0)
		dx1 = (B.x - A.x) / (B.y - A.y);
	else
		dx1 = 0;

	if (C.y - A.y > 0)
		dx2 = (C.x - A.x) / (C.y - A.y);
	else
		dx2 = 0;

	if (C.y - B.y > 0)
		dx3 = (C.x - B.x) / (C.y - B.y);
	else
		dx3 = 0;

	S=E=A;
	
	// 	if(dx1 > dx2) {
	// 		for(;S.y<=B.y;S.y++,E.y++,S.x+=dx2,E.x+=dx1)
	// 			horizline(S.x,E.x,S.y,color);
	// 		E=B;
	// 		for(;S.y<=C.y;S.y++,E.y++,S.x+=dx2,E.x+=dx3)
	// 			horizline(S.x,E.x,S.y,color);
	// 	} else {
	// 		for(;S.y<=B.y;S.y++,E.y++,S.x+=dx1,E.x+=dx2)
	// 			horizline(S.x,E.x,S.y,color);
	// 		S=B;
	// 		for(;S.y<=C.y;S.y++,E.y++,S.x+=dx3,E.x+=dx2)
	// 			horizline(S.x,E.x,S.y,color);
	// 	}

	// *** end triangle filler ***
}
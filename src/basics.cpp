#include <fstream>
#include <cstdio>
#include <iostream>
#include <list>
#include <cmath>
#include <algorithm>

struct myEvent
{
	float time;
	int thing;
};

using namespace std;

constexpr auto dimx = 512u, dimy = 512u;

unsigned char imageBuff[dimx][dimy][3];

#define RED 0
#define GREEN 1
#define BLUE 2

void drawPoint(int p1[], int color[])
{
	if (p1[0] >= 0 && p1[0] < dimx && p1[1] >= 0 && p1[1] < dimy)
	{
		imageBuff[p1[0]][p1[1]][RED] = color[0];
		imageBuff[p1[0]][p1[1]][GREEN] = color[1];
		imageBuff[p1[0]][p1[1]][BLUE] = color[2];
	}
}

void drawLine(int p1[], int p2[], int color[])
{
	int x1 = p1[0];
	int y1 = p1[1];
	int x2 = p2[0];
	int y2 = p2[1];

	const bool steep = abs(y2 - y1) > abs(x2 - x1);
	if (steep)
	{
		swap(x1, y1);
		swap(x2, y2);
	}

	if (x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}

	const int dx = x2 - x1;
	const int dy = abs(y2 - y1);
	int error = dx / 2;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = y1;

	for (int x = x1; x <= x2; x++)
	{
		int point[2];
		if (steep)
		{
			point[0] = y;
			point[1] = x;
		}
		else
		{
			point[0] = x;
			point[1] = y;
		}
		drawPoint(point, color);
		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void drawCurve(int p1[], int p2[], int p3[], int p4[], int color[])
{
	for (float t = 0.0; t <= 1.0; t += 0.001)
	{
		float u = 1.0 - t;
		float tt = t * t;
		float uu = u * u;
		float uuu = uu * u;
		float ttt = tt * t;

		float x = uuu * p1[0] + 3 * uu * t * p2[0] + 3 * u * tt * p3[0] + ttt * p4[0];
		float y = uuu * p1[1] + 3 * uu * t * p2[1] + 3 * u * tt * p3[1] + ttt * p4[1];

		int point[2] = {(int)x, (int)y};
		drawPoint(point, color);
	}
}

void drawCircle(int p1[], int radius, int color[])
{
	int x0 = p1[0];
	int y0 = p1[1];
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		int p[2];

		p[0] = x0 + x;
		p[1] = y0 + y;
		drawPoint(p, color);
		p[0] = x0 + y;
		p[1] = y0 + x;
		drawPoint(p, color);
		p[0] = x0 - y;
		p[1] = y0 + x;
		drawPoint(p, color);
		p[0] = x0 - x;
		p[1] = y0 + y;
		drawPoint(p, color);
		p[0] = x0 - x;
		p[1] = y0 - y;
		drawPoint(p, color);
		p[0] = x0 - y;
		p[1] = y0 - x;
		drawPoint(p, color);
		p[0] = x0 + y;
		p[1] = y0 - x;
		drawPoint(p, color);
		p[0] = x0 + x;
		p[1] = y0 - y;
		drawPoint(p, color);

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

int myTexture()
{
	memset(imageBuff, 0, sizeof(imageBuff));

	// Draw lines
	int red[] = {255, 0, 0};
	int p1_line1[] = {1, 1};
	int p2_line1[] = {510, 510};
	drawLine(p1_line1, p2_line1, red);

	int blue[] = {0, 0, 255};
	int p1_line2[] = {1, 510};
	int p2_line2[] = {510, 1};
	drawLine(p1_line2, p2_line2, blue);

	// Draw circle
	int white[] = {255, 255, 255};
	int center[] = {256, 256};
	drawCircle(center, 64, white);

	// Draw Bezier curve
	int green[] = {0, 255, 0};
	int p1_curve[] = {50, 240};
	int p2_curve[] = {160, 50};
	int p3_curve[] = {240, 50};
	int p4_curve[] = {320, 320};
	drawCurve(p1_curve, p2_curve, p3_curve, p4_curve, green);

	return 0;
}

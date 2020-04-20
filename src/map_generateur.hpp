
#ifndef MAP_GENERATOR
/////////////////////////////////////////////////////////////////////////// Constants
#define MAP_GENERATOR 1

#define RESTRICTED -1
#define ALLOWED 1
#define RETURN 1

/////////////////////////////////////////////////////////////////////////// Preprocessors
#include <bits/stdc++.h>
using namespace std;
/////////////////////////////////////////////////////////////////////////// Structs
typedef struct pt
{
	int x, y;
	struct pt *next;
} Point;

/////////////////////////////////////////////////////////////////////////// Prototypes
int **generateLevel(int lvl, int mapW, int mapH);

static float distance(int x0, int y0, int x, int y);
static float uniformGenerator(long *seed);
static bool in(Point *pt, int x, int y);
static Point *shortestPath(int x0, int y0, int x1, int y1);


int **generateLevel(int lvl, int mapW, int mapH)
{
	int **map = (int **) malloc(sizeof(int *)*mapH);
	srand(lvl);
	long seed = rand();

	int start_x = mapW * uniformGenerator(&seed) / 2, start_y = mapH * uniformGenerator(&seed) / 2;
	int stop_x = mapW - 1, stop_y = mapH - 1;


	float n;
	int x = start_x, y = start_y;		// Start Position
	float left, right, down;				// Directions Proba
	Point *pt;							// Shortest Path next point
	for (int i = 0; i < mapH; ++i)
	{
		map[i] = (int *) calloc(mapW, sizeof(int));
	}
	map[start_y][start_x] = 2;

	while(1)
	{
		pt = shortestPath(x, y, stop_x, stop_y);
		if(pt == NULL)
		{
			map[y][x] = 1;
			break;
		}

		n = uniformGenerator(&seed);

		if(pt->x == x)
		{
			if(pt->y < y)
			{
				left = 0.2;
				right = 0.4;
				down = 0.5;
			}
			else
			{
				left = 0.2;
				right = 0.4;
				down = 0.9;
			}
		}
		else
		{
			if(pt->x < x)
			{
				left = 0.1;
				right = 0.6;
				down = 0.8;
			}
			else
			{
				left = 0.5;
				right = 0.6;
				down = 0.8;
			}
		}

		if(n < left && x - 1 >= 0  && map[y][x - 1] == 0)
		{
			map[y][x - 1] = 1;
			x -= 1;
		}
		else if(n < right && x + 1 < mapW && map[y][x + 1] == 0)
		{
			map[y][x + 1] = 1;
			x += 1;
		}
		else if(n < down && y - 1 >= 0 && map[y - 1][x] == 0)
		{
			map[y - 1][x] = 1;
			y -= 1;
		}
		else if( y + 1 < mapH && map[y + 1][x] == 0)
		{
			map[y + 1][x] = 1;
			y += 1;
		}
		else
		{
			map[pt->y][pt->x] = 1;
			x = pt->x;
			y = pt->y;
		}

		free(pt);
	}

	// Symetry-combined Map
	int **maps = (int **) malloc(sizeof(int *)*mapH);

	for (int i = 0; i < mapH; ++i)
	{
		maps[i] = (int *) malloc(2 * mapW * sizeof(int));
		for (int j = 0; j < mapW; ++j)
		{
			maps[i][j] = map[i][j];
			maps[i][j + mapW] = map[i][mapW - j - 1];
		}
	}
	free(map);

	// Border-combined Map
	int **mapss = (int **) malloc(sizeof(int *) * (2 + mapH));
	for (int i = 0; i < 2 + mapH; ++i)
	{
		mapss[i] = (int *) malloc(2 * (mapW + 1) * sizeof(int));
		for (int j = 0; j < 2 * (mapW + 1); ++j)
		{
			if(i == 0 || i == mapH + 1 || j == 0 || j == 2 * mapW + 1 )
			{
				mapss[i][j] = 0;
				continue;
			}
			mapss[i][j] = maps[i - 1][j - 1];
		}
	}
	free(maps);
	return mapss;
}



static Point *shortestPath(int x0, int y0, int x1, int y1)
{
	if (x0 == x1 && y0 == y1)
		return NULL;
	Point *pt = (Point *) malloc(sizeof(Point));
	//// Determine the nearest point to (x1,y1) starting from (x0,y0)
	int d1 = distance(x0 + 1, y0, x1, y1);
	int d2 = distance(x0 - 1, y0, x1, y1);
	int d3 = distance(x0, y0 + 1, x1, y1);
	int d4 = distance(x0, y0 - 1, x1, y1);
	if(d1 > d2)
	{
		if(d2 > d3)
		{
			if(d3 > d4)
			{
				pt->x = x0;
				pt->y = y0 - 1;
			}
			else
			{
				pt->x = x0;
				pt->y = y0 + 1;
			}
		}
		else
		{
			if(d2 > d4)
			{
				pt->x = x0;
				pt->y = y0 - 1;
			}
			else
			{
				pt->x = x0 - 1;
				pt->y = y0;
			}
		}

	}
	else
	{
		if(d1 > d3)
		{
			if(d3 > d4)
			{
				pt->x = x0;
				pt->y = y0 - 1;
			}
			else
			{
				pt->x = x0;
				pt->y = y0 + 1;
			}
		}
		else
		{
			if(d1 > d4)
			{
				pt->x = x0;
				pt->y = y0 - 1;
			}
			else
			{
				pt->x = x0 + 1;
				pt->y = y0;
			}
		}
	}

	return pt;
}

static float distance(int x0, int y0, int x, int y)
{
	return sqrt(pow(x - x0, 2) + pow(y - y0, 2));
}

static float uniformGenerator(long *seed)
{
	long a = 75, b = 596145, m = 2147483647;
	*seed = (a * *seed + b) % m;
	return 1.0 * *seed / m;
}



#endif

#ifndef MAP_GENERATOR
/////////////////////////////////////////////////////////////////////////// Constants
#define MAP_GENERATOR 1

#define RESTRICTED -1
#define ALLOWED 1
#define RETURN 1

/////////////////////////////////////////////////////////////////////////// Preprocessors

typedef int data;

typedef struct _
{
	int x, y;
	struct _ *next;
} Point;

/////////////////////////////////////////////////////////////////////////// Prototypes
vector<vector<data>> generateLevel(int lvl, int mapW, int mapH);

static float distance(int x0, int y0, int x, int y);
static float uniformGenerator(long *seed);
static Point *shortestPath(int x0, int y0, int x1, int y1);
int nbreNeighboors(data value, int x, int y, vector<vector<data>> const &map);
void caveGeneration(vector<vector<data>> &map);

/////////////////////////////////////////////////////////////////////////// Functions


void caveGeneration(vector<vector<data>> &map)
{
	bool stop = false;
	while(stop == false )
	{
		stop = true;
		for (int y = 1; y < map.size() - 1; ++y)
			for (int x = 1; x < map[y].size() - 1; ++x)
				if(map[y][x] == RESTRICTED && ( nbreNeighboors(RESTRICTED,  x,  y, map) < 3 ||
												((map[y + 1][x] == RESTRICTED) + (map[y - 1][x] == RESTRICTED) +
												 (map[y][x + 1] == RESTRICTED) + (map[y][x - 1] == RESTRICTED)) < 2))
				{
					stop = false;
					map[y][x] = ALLOWED;
				}
				else if(map[y][x] == ALLOWED && (map[y + 1][x] == RESTRICTED) && (map[y - 1][x] == RESTRICTED))
				{
					map[y + 1][x] = ALLOWED ;
					map[y - 1][x] = ALLOWED;
				}
	}
}

int nbreNeighboors(data value, int x, int y, vector<vector<data>> const &map)
{
	return (map[y - 1][x] == value ) + (map[y - 1][x - 1] == value ) + (map[y - 1][x + 1] == value ) +
		   (map[y][x - 1] == value ) + (map[y][x + 1] == value ) +
		   (map[y + 1][x] == value ) + (map[y + 1][x - 1] == value ) + (map[y + 1][x + 1] == value);
}


vector<vector<data>> generateLevel(int lvl, int mapW, int mapH)
{
	vector<vector<data>> map(mapH, vector<data>());
	srand(lvl);
	long seed = rand();

	// mapW=mapW/2-1;
	// mapH-=2;

	int start_x = mapW * uniformGenerator(&seed) / 2, start_y = mapH * uniformGenerator(&seed) / 2;
	int stop_x = mapW - 1, stop_y = mapH * (1 + uniformGenerator(&seed)) / 2;


	float n;
	int x = start_x, y = start_y;		// Start Position
	float left, right, down;				// Directions Proba
	Point *pt;							// Shortest Path next point
	for (int i = 0; i < mapH; ++i)
		map[i] = vector<data>(mapW, RESTRICTED);

	while(1)
	{
		pt = shortestPath(x, y, stop_x, stop_y);
		if(pt == NULL)
		{
			// map[y][x] = RETURN;
			map[y][x] = ALLOWED;
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
			map[y][x - 1] = ALLOWED;
			x -= 1;
		}
		else if(n < right && x + 1 < mapW && map[y][x + 1] == 0)
		{
			map[y][x + 1] = ALLOWED;
			x += 1;
		}
		else if(n < down && y - 1 >= 0 && map[y - 1][x] == 0)
		{
			map[y - 1][x] = ALLOWED;
			y -= 1;
		}
		else if( y + 1 < mapH && map[y + 1][x] == 0)
		{
			map[y + 1][x] = ALLOWED;
			y += 1;
		}
		else
		{
			map[pt->y][pt->x] = ALLOWED;
			x = pt->x;
			y = pt->y;
		}

		free(pt);
	}

	vector<data> tobo(mapW, RESTRICTED);
	map.insert(map.begin(), tobo);
	map.insert(map.end(), tobo);

	// for (int y = 0; y < map.size() ; ++y)
	// {
	// 	map[y].insert(map[y].begin(), RESTRICTED);
	// 	int len = map[y].size();
	// 	for (int x = 0 ; x < len ; ++x)
	// 		map[y].push_back(map[y][len - x - 1]);

	// }

	caveGeneration(map);
	// addGreenZone(map);

	return map;
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

	//pt->next = shortestPath(pt->x, pt->y, x1, y1);
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
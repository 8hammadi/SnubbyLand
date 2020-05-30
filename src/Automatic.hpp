

///////////////////////////////////////////////////////////////////////
void directSnubby(bool T[4], Player &s)
{
	static int i = 0;
	level.commandSnubby(T, s);
	if(i == 150)
	{
		cout << "START dijkstra" << endl;
		for(auto pai : dijkstra(level.map, make_pair(level.player.x, level.player.y)
								, level.getCoins())
		   )
		{
			level.coins.push_back(Coin(pai.first, pai.second));
			level.coins[level.coins.size() - 1].is_virtual = true;
			level.n_coins++;
		}
		cout << "END dijkstra" << endl;

		i = 0;
	}
	i++;
}


///////////////////////////////////////////////////////////////////////////////////////////

int n = 12, m = 20;
bool done[1000][1000];

bool isOk(int x, int y)
{
	if (-1 < x && x < n && -1 < y && y < m)
		return 1;
	return 0;
}

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};


//////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\\\ \  \\\\\\\\\\\\ 

vector<pair<int, int>> dijkstra(int map[12][20], pair<int, int> snubby, vector<pair<int, int>> coins)
{
	int p, q, r, s, x, y, a, b;
	string st[n] = {"....................",
					"....................",
					"....................",
					"....................",
					"....................",
					"....................",
					"....................",
					"....................",
					"....................",
					"....................",
					"....................",
					"...................."
				   };
	for(int i = 0; i < 12; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			if(map[i][j] == -1)
			{
				st[i][j] = '#';
			}
		}
	}
	for(auto c : coins)
	{
		st[(int)(c.second - cy ) / 40][(int)(c.first - cx) / 40] = 'B';
	}
	int dist[n][m];
	p = (snubby.second - cy) / 40;
	q = (snubby.first - cx) / 40;
	done[p][q] = 1;
	dist[p][q] = 0;
	queue<pair<int, int>> qu;
	pair<int, int> pa;
	qu.push({p, q});
	bool end = 0;
	while (!qu.empty() and !end)
	{
		pa = qu.front();
		qu.pop();
		for (int i = 0; i < 4; ++i)
		{
			x = pa.first + dx[i];
			y = pa.second + dy[i];
			if (isOk(x, y) && !done[x][y] && st[x][y] != '#')
			{
				done[x][y] = 1;
				dist[x][y] = dist[pa.first][pa.second] + 1;
				qu.push({x, y});
				if(st[x][y] == 'B')
				{
					end = 1;
					break;
				}
			}
		}
	}
	string ans = "";
	while (!(x == p && y == q))
	{
		for (int i = 0; i < 4; ++i)
		{
			a = x + dx[i];
			b = y + dy[i];
			if (isOk(a, b) && done[a][b] && dist[a][b] < dist[x][y])
			{
				x = a;
				y = b;
				if (i == 0)
					ans += 'L';
				else if (i == 1)
					ans += 'U';
				else if (i == 2)
					ans += 'R';
				else
					ans += 'D';
				break;
			}
		}
	}
	vector<pair<int, int>> path = {snubby};

	while ((int)(ans).size())
	{
		switch(ans.back())
		{
		case 'R':
			path.push_back(make_pair(path.back().first + 40, path.back().second));
			break;
		case 'L':
			path.push_back(make_pair(path.back().first - 40, path.back().second));
			break;
		case 'U':
			path.push_back(make_pair(path.back().first, path.back().second - 40));
			break;
		case 'D':
			path.push_back(make_pair(path.back().first, path.back().second + 40));
			break;
		}

		ans.pop_back();
	}
	return path;
}


//////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\\\ \  \\\\\\\\\\\\ 

int getWhere(Player &s, vector<pair<int, int>> r, int obs)
{
	return step(gothere(s, r, obs));
}

int step(pair<double, double> b)
{
	int i = 0;
	// go right
	if(b.first > 0)
		i = i | 1;
	// go left
	else if(b.first < 0)
		i = i | 2;
	// go down
	if(b.second > 0)
		i = i | 4;
	// go up
	else if(b.second < 0)
		i = i | 8;
	return i;
}

pair<double, double> gothere(Player &s, vector<pair<int, int>> r, int obs)
{
	pair<double, double> a(0, 0);
	pair<double, double> b(0, 0);

	int i;
	for (i = 0; i < obs; ++i)
	{
		a = force(0, s.sim.q1, s.sim.q4, r[i]);
		b.first += a.first;
		b.second += a.second;
	}
	for(; i < obs + 4; i++)
	{
		a = force(0, s.sim.q1, s.sim.q3, r[i]);
		b.first += a.first;
		b.second += a.second;
	}

	for(; i < r.size(); i++)
	{
		a = force(10, s.sim.q1, s.sim.q2, r[i]);
		b.first += a.first;
		b.second += a.second;
	}

	return b;
}

pair<double, double> force(int radius, double q1, double q2, pair<int, int> r)
{
	double dist = Distance(r.first, r.second, 0, 0) + radius ;
	if(dist <= 57)
		dist = dist * pow(10, -40);
	if(dist == 0)
		dist = pow(10, -30);
	double norm = -9 * pow(10, 9) * q1 * q2 / pow(dist, 3);
	return make_pair(r.first * norm, r.second * norm);
}

double Distance( int x0, int y0, int x1, int y1)
{
	return sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2)) ;
}

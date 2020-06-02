

///////////////////////////////////////////////////////////////////////
void directSnubby(bool T[4], Player &s)
{
	static int i = 0;
	level.commandSnubby(T, s);

	if(i == 200)
	{
		cout << "START dijkstra" << endl;

		vector<vector<int>> map;
		for (int i = 0; i < 12; ++i)
		{
			vector<int> tmp;
			for (int j = 0; j < 20; ++j)
				tmp.push_back(level.map[i][j]);
			map.push_back(tmp);
		}
		cout << "Do it" << endl;
		int added = whenBlocked(map, level.coins, s.x, s.y);
		level.n_coins += added;
		level.virtuals += added;

		cout << "END dijkstra" << endl;

		i = 0;
	}
	i++;
}

int whenBlocked(vector<vector<int>> map, vector<Coin> &coins, int x, int y)
{
	pair<int, int> nearest = getNearest(coins, x, y);
	nearest = {nearest.first - cx, nearest.second - cy};
	nearest.first /= 40;
	nearest.second /= 40;
	x -= cx;
	y -= cy;
	if(nearest.first < 0)
		return 0;
	cout << "Here" << endl;
	aitHammadi(map, nearest, make_pair(x / 40, y / 40));
	cout << "Here 2" << endl;

	vector<pair<int, int>> paths = path(map, nearest, make_pair(x / 40, y / 40));
	cout << "Here 3" << endl;

	for(auto &p : paths)
	{
		coins.push_back(Coin(cx + p.first * 40 + (rand() % 40),
							 cy + p.second * 40 + (rand() % 40)));
		coins[coins.size() - 1].is_virtual = true;
	}
	return paths.size();
}

vector<pair<int, int>> path(vector<vector<int>> &map, pair<int, int> coin, pair<int, int> snubby)
{
	vector<pair<int, int>> paths{snubby};
	while(coin != snubby)
	{
		paths.push_back(coin);
		switch(map[coin.second][coin.first])
		{
		case 6:
			coin = make_pair( coin.first + 1, coin.second);
			break;
		case 7:
			coin = make_pair( coin.first - 1, coin.second);
			break;
		case 8:
			coin = make_pair( coin.first, coin.second + 1);
			break;
		case 9:
			coin = make_pair( coin.first, coin.second - 1 );
			break;
		}
	}
	return paths;
}

void aitHammadi(vector<vector<int>> &map, pair<int, int> coin, pair<int, int> snubby)
{
	vector<pair<int, int>> queue;
	map[snubby.second][snubby.first] = -1;
	queue.push_back(snubby);

	while(queue.size() >= 1)
	{
		snubby = queue[0];
		queue.erase(queue.begin());
		if(snubby == coin)
			break;

		// we went left
		if(snubby.first - 1 >= 0 && (map[snubby.second][snubby.first - 1] == ALLOWED ||
									 map[snubby.second][snubby.first - 1] == 2 ||
									 map[snubby.second][snubby.first - 1] == 0) )
		{
			queue.push_back(make_pair(snubby.first - 1, snubby.second));
			map[snubby.second][snubby.first - 1] = 6;
		}

		// we went right
		if(snubby.first + 1 < map[0].size() && (map[snubby.second][snubby.first + 1] == ALLOWED ||
												map[snubby.second][snubby.first + 1] == 2 ||
												map[snubby.second][snubby.first + 1] == 0) )
		{
			queue.push_back(make_pair( snubby.first + 1, snubby.second));
			map[snubby.second][snubby.first + 1] = 7;
		}

		// we went up
		if(snubby.second - 1 >= 0 && (map[snubby.second - 1][snubby.first] == ALLOWED ||
									  map[snubby.second - 1][snubby.first] == 2 ||
									  map[snubby.second - 1][snubby.first] == 0) )
		{
			queue.push_back(make_pair(snubby.first, snubby.second - 1));
			map[snubby.second - 1][snubby.first] = 8;
		}

		// we went down
		if(snubby.second + 1 < map.size() && (map[snubby.second + 1][snubby.first] == ALLOWED ||
											  map[snubby.second + 1][snubby.first] == 2 ||
											  map[snubby.second + 1][snubby.first] == 0) )
		{
			queue.push_back(make_pair( snubby.first, snubby.second + 1));
			map[snubby.second + 1][snubby.first] = 9;
		}
	}
}

pair<int, int> getNearest(vector<Coin> &coins, int x, int y)
{
	pair<int, int> near(-10000, -10000);
	double D = Distance(x, y, near.first, near.second);
	for(auto &c : coins)
		if(!c.is_virtual && D > Distance(x, y, c.x, c.y))
		{
			D = Distance(x, y, c.x, c.y);
			near = {c.x, c.y};
		}
	return near;
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
		a = force(s.sim.radius, s.sim.q1, s.sim.q4, r[i]);
		b.first += a.first;
		b.second += a.second;
	}
	for(; i < obs + 4; i++)
	{
		a = force(s.sim.radius, s.sim.q1, s.sim.q3, r[i]);
		b.first += a.first;
		b.second += a.second;
	}

	for(; i < r.size(); i++)
	{
		a = force(s.sim.radius, s.sim.q1, s.sim.q2, r[i]);
		b.first += a.first;
		b.second += a.second;
	}

	return b;
}

pair<double, double> force(int radius, double q1, double q2, pair<int, int> r)
{
	double dist = Distance(r.first, r.second, 0, 0) ;
	if(dist <= radius)
		dist = dist * pow(10, -10);
	if(dist == 0)
		dist = pow(10, -2);
	double norm = -9 * pow(10, 9) * q1 * q2 / pow(dist, 3);
	return make_pair(r.first * norm, r.second * norm);
}


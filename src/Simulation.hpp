int getWhere(Player &s, vector<pair<int, int>> r, int obs);
int step(pair<double, double> b);
pair<double, double> gothere(Player &s, vector<pair<int, int>> r, int obs);
pair<double, double> force(int radius, double q1, double q2, pair<int, int> r);
double Distance(int r1, int r2, int x0, int y0, int x1, int y1);

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
	// cout << b.first << " - " << b.second << " - " << i << endl;
	return i;
}

pair<double, double> gothere(Player &s, vector<pair<int, int>> r, int obs)
{
	pair<double, double> a(0, 0);
	pair<double, double> b(0, 0);

	// cout << s.sim.q1 << " - " << s.sim.q2 << " - " << s.sim.q3 << " - " << s.sim.q4 << " - " << endl;
	int i;
	for (i = 0; i < obs; ++i)
	{
		a = force(20, s.sim.q1, s.sim.q4, r[i]);
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
	double dist = Distance(radius, 30, r.first, r.second, 0, 0);
	if(dist <= 0)
		dist = pow(10, -30);
	double norm = -9 * pow(10, 9) * q1 * q2 / pow(dist / 20, 3);
	return make_pair(r.first * norm, r.second * norm );
}

double Distance(int r1, int r2, int x0, int y0, int x1, int y1)
{
	return sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2)) - (r1 + r2);
}
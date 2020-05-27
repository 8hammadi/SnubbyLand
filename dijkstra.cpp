#include <bits/stdc++.h>
using namespace std;

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
        st[(int)c.second / 40][(int)c.first / 40] = 'B';
    }
    int dist[n][m];
    p = snubby.second / 40;
    q = snubby.first / 40;
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

int main()
{
    int map[12][20] =
    {
        {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
        {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
        {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
        {-1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
        {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
        {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
        {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
        {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}
    };
    pair<int, int> snubby = {110, 153};
    vector<pair<int, int>> coins = {{200, 255}};
    auto path = dijkstra(map, snubby, coins);
    for(auto e : path)
    {
        cout << e.first << "," << e.second << ">>" ;
    }
    return 0;
}
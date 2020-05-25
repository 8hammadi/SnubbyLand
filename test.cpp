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

int main()
{
    int p, q, r, s, x, y, a, b;
    string st[n] = {"A...................",
                    "....................",
                    "....................",
                    "....................",
                    "#...................",
                    "....................",
                    "....................",
                    "....................",
                    "....................",
                    "....................",
                    "....................",
                    "...................B"
                   };
    int dist[n][m];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (st[i][j] == 'A')
            {
                p = i;
                q = j;
            }
            if (st[i][j] == 'B')
            {
                r = i;
                s = j;
            }
        }
    }
    done[p][q] = 1;
    dist[p][q] = 0;
    queue<pair<int, int>> qu;
    pair<int, int> pa;
    qu.push({p, q});
    while (!qu.empty())
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
            }
        }
    }
    x = r;
    y = s;
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
    cout << "BEST MOVE :" << ans.back() << endl;;
    while ((int)(ans).size())
    {
        cout << ans.back();
        ans.pop_back();
    }
    return 0;
}
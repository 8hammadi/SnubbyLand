
class Player
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &x;
        ar &y;

    }
public:
    int x = 500, y = 500, w = 30, h = 30, p;
    Model brain = Model({2, 4, 4});

    Player(int a, int b)
    {
        x = a;
        y = b;

    }
    bool touche_enemy(pair<int, int> enemy, int r)
    {
        if(     ((enemy.first - r >= x - r) && (enemy.first - r <= x + r ) && (enemy.second - r >= y - r) && ( enemy.second - r <= y + r)) ||
                ((enemy.first + r >= x - r) && (enemy.first + r <= x + r ) && (enemy.second + r >= y - r) && ( enemy.second + r <= y + r)) ||
                ((enemy.first - r >= x - r) && (enemy.first - r <= x + r) && (enemy.second + r >= y - r) && ( enemy.second + r <= y + r))  ||
                ((enemy.first + r >= x - r) && (enemy.first + r <= x + r) && (enemy.second - r >= y - r) && ( enemy.second - r <= y + r))
          )
            return 1;
        return 0;
    };

    void go_to_coin(int a, int b)
    {
        double dx = x - a, dy = y - b;
        dx = dx / sqrt(pow(dx, 2) + pow(dy, 2));
        dy = dy / sqrt(pow(dx, 2) + pow(dy, 2));

        auto r = brain.predict({dx, -dy});
        if(max(r[0], max(r[1], max(r[2], r[3]))) < 0.5)exit(0);
        if(r[0] == max(r[0], max(r[1], max(r[2], r[3]))))y -= 10; //up
        else if(r[1] == max(r[0], max(r[1], max(r[2], r[3]))) )y += 10; //down
        else if(r[2] == max(r[0], max(r[1], max(r[2], r[3]))))x += 10; //R
        else if(r[3] == max(r[0], max(r[1], max(r[2], r[3]))))x -= 10; //L
    }

};


class Spiral_dot
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &n;
        ar &R;
        ar &C;
        ar &enemys;

    }
public:
    vector<pair<int, int>> enemys;
    float ongle = 0;
    pair<int, int> C;
    int n;
    int R;
    Spiral_dot() {};
    Spiral_dot(pair<int, int> C, int n, int R)
    {
        this->C = C;
        this->n = n;
        this->R = R;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                enemys.push_back(make_pair(C.first + R * cos(i * PI / 2)*j / n, C.second + R * sin(i * PI / 2)*j / n));

            }
        }

    }

    void next_move()
    {
        ongle += PI / 100;
        enemys.clear();
        for(int i = 0; i < 4; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                enemys.push_back(make_pair(C.first + R * cos((i * PI / 2) + ongle)*j / n, C.second + R * sin((i * PI / 2) + ongle)*j / n));

            }
        }
    }
    void update()
    {
        enemys.clear();
        for(int i = 0; i < 4; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                enemys.push_back(make_pair(C.first + R * cos(i * PI / 2)*j / n, C.second + R * sin(i * PI / 2)*j / n));

            }
        }
    }

};

class Linear_enemy
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &A;
        ar &B;

    }
public:
    pair<int, int> A, B;
    double t = 0;
    int sens = 1;
    Linear_enemy() {};
    Linear_enemy(pair<int, int> a, pair<int, int> b)
    {
        A = a;
        B = b;
    }

    void next_move()
    {
        t += sens * 0.03;


        if(t > 1 or t < 0)
        {
            sens *= -1;
        }
    }

    pair<int, int> enemy()
    {
        return make_pair(t * A.first + (1 - t) * B.first, t * A.second + (1 - t) * B.second);
    }
};





class Coin
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &is_taked;
        ar &x;
        ar &y;


    }
public:
    bool is_taked = 0;
    int x, y;
    int w = 10, h = 10;
    Coin() {};
    Coin(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void take(Player p)
    {
        if( x - w / 2 >= p.x - p.w / 2 && x - w / 2 <= p.x + p.w / 2 && y - (h / 2) >= p.y - p.h / 2 &&  y - h / 2 <= p.y + p.h / 2
                // (x + r >= p.x - p.w/2) && (x + r <= p.x + pr && (y + (h / 2) >= p.y - p.h / 2) && ( y + h / 2 <= p.y + p.h / 2)) ||
                // (x - r >= p.x - p.w/2) && (x - r <= p.x + pr && (y + (h / 2) >= p.y - p.h / 2) && ( y + h / 2 <= p.y + p.h / 2))  ||
                // (x + r >= p.x - p.w/2) && (x + r <= p.x + pr && (y - (h / 2) >= p.y - p.h / 2) && ( y - h / 2 <= p.y + p.h / 2))
          )
        {
            is_taked = 1;
        }
    }
};
class Level
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &map;
        ar &coins;
        ar &player;
        ar &linear_enemys;
        ar &stable_enemys;
        ar &spiral_dots;

    }
public:
    int map[12][20] = {{1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}
    };
    vector<Coin> coins;
    Player player = Player(500, 500);
    int w_enemy = 20;
    pair<int, int> last_touch_on_green_area = make_pair(500, 500);
    vector<Linear_enemy> linear_enemys;
    vector<pair<int, int>> stable_enemys;
    vector<Spiral_dot> spiral_dots;
    vector<double> input;

    Level() {};
    vector<pair<int, int>> get_enemys()
    {
        vector<pair<int, int>> v;
        for (auto sp : spiral_dots)
        {
            for(auto e : sp.enemys)
            {
                v.push_back(e);
            }

        }
        for( auto e : linear_enemys)
        {
            v.push_back(e.enemy());
        }

        return v;
    };

    vector<double> get_input()
    {
        input.clear();
        
        input.push_back(100-player.x);
        input.push_back(100-player.y);

        input.push_back(12*40-player.x);
        input.push_back(20*40-player.y);

        for(auto e : get_enemys())
        {
            input.push_back(e.first - player.x);
            input.push_back(e.second - player.x);
        }
        return input;
    }

};


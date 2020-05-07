class Game;
class Level;
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
    int x = 100, y = 100, w = 30, h = 30, p;
    vector<double> input;
    int score = 0;
    double fitness = 0;
    Model brain = Model({0, 0, 0});
    bool is_a_life = 1;
    Player() {};
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
        {
            is_a_life = 0;
            return 1;
        }
        return 0;
    };

    void think(Level *level, Game *g);
    vector<Player> breed(Player player)
    {
        /*
            Make 3 children as parts of their parents.

        */
        vector<Player> children(3, Player(player));
        for(auto &ch : children)
        {
            //children.push_back(Player(player));
            ch.brain = brain.breed(player.brain);
        }

        return children;
    }


    void update_input(Level *level);


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


class Squar_enemy
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &A;
        ar &B;
        ar &C;
        ar &D;

    }
public:
    pair<int, int> A, B, C, D;
    double t = 1;
    int r = 1;// 0 A-B 1 B-C 2 C-D 3 D-A
    Squar_enemy() {};
    Squar_enemy(pair<int, int> a, pair<int, int> b, pair<int, int> c, pair<int, int> d)
    {
        A = a;
        B = b;
        C = c;
        D = d;
    }

    void next_move()
    {
        t -= 0.03;


        if(t < 0 )
        {
            r++;
            r %= 4;
            t = 1;
        }
    }

    pair<int, int> enemy()
    {
        switch(r)
        {
        case 0:
            return make_pair(t * A.first + (1 - t) * B.first, t * A.second + (1 - t) * B.second);
        case 1:
            return make_pair(t * B.first + (1 - t) * C.first, t * B.second + (1 - t) * C.second);
        case 2:
            return make_pair(t * C.first + (1 - t) * D.first, t * C.second + (1 - t) * D.second);
        case 3:
            return make_pair(t * D.first + (1 - t) * A.first, t * D.second + (1 - t) * A.second);
        default:
            return make_pair(0, 0);
        }


    }
};


class Big_spiral_dot
{
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &n;
        ar &R;
        ar &C;
    }
public:
    vector<pair<int, int>> enemys;
    float ongle = 2 * PI;
    pair<int, int> C;
    int n;
    int R;
    int next_stop = 1; // 1->0 2->PI/2 3->PI 4->3PI/2
    int pause = 0;
    int sleep = 0;
    Big_spiral_dot() {};
    Big_spiral_dot(pair<int, int> C, int n, int R)
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
    void next_move()
    {
        cout << next_stop << endl;
        if(sleep)
        {
            sleep--;
            return;
        }
        ongle += PI / 50;

        if( (ongle > PI / 2 and next_stop == 2) or (ongle > PI and next_stop == 3) or (ongle > 3 * PI / 2 and next_stop == 4))
        {
            next_stop++;
            sleep = 20;
        }
        if(ongle > 2 * PI)
        {
            sleep = 20;
            ongle = 0;
            next_stop = 2;
        }

        enemys.clear();
        for(int i = 0; i < 4; i++)
        {
            for(int j = 1; j <= n; j++)
            {

                enemys.push_back(make_pair(C.first + (R * cos(ongle + i * PI / 2)*j / n) + 20 * cos(PI / 2 - ongle - i * PI / 2 ), C.second + (R * sin(ongle + i * PI / 2 )*j / n) + 20 * sin(PI / 2 - ongle - i * PI / 2)));
                enemys.push_back(make_pair(C.first + (R * cos(ongle + i * PI / 2)*j / n) - 20 * cos(PI / 2 - ongle - i * PI / 2 ), C.second + (R * sin(ongle + i * PI / 2)*j / n) - 20 * sin(PI / 2 - ongle - i * PI / 2)));


            }
        }
    }

};
class Coin
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
    bool is_taked = 0;
    int x, y;
    int w = 10, h = 10;
    Coin() {};
    Coin(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    bool take(Player p)
    {
        if( x - w / 2 >= p.x - p.w / 2 && x - w / 2 <= p.x + p.w / 2 && y - (h / 2) >= p.y - p.h / 2 &&  y - h / 2 <= p.y + p.h / 2

          )
        {
            is_taked = 1;
            return 1;
        }
        return 0;
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
        ar &big_spiral_dots;
        ar &squar_enemys;
        ar &A;
        ar &B;

    }
public:
    int map[12][20] = {{1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}
    };
    vector<Coin> coins;
    Player player = Player(500, 500);
    vector<Player> Snubbys;
    int w_enemy = 20;
    pair<int, int> last_touch_on_green_area = make_pair(500, 500);
    vector<Linear_enemy> linear_enemys;
    vector<pair<int, int>> stable_enemys;
    vector<Spiral_dot> spiral_dots;
    vector<pair<int, int>> enemys;
    vector<Big_spiral_dot> big_spiral_dots;
    vector<Squar_enemy> squar_enemys;
    int n, last_direction = 1, N_Snubbys_a_life = 0;
    pair<double, double> A = {500, 500}, B = {100, 100} ;
    int generation = 0;
    int n_coins;
    Level()
    {
        for(int i = 0; i < N_POPULATION; i++)
        {
            Snubbys.push_back(Player(player));
        }
    };
    void update_population()
    {
        for(auto &sn : Snubbys)
        {
            sn.brain.init_params({ (int)player.input.size(), 10, 10, 4}
                                );
            sn.x = A.first;
            sn.y =  A.second;
            sn.is_a_life = 1;
        };

        N_Snubbys_a_life = N_POPULATION;
    }
    vector<pair<int, int>> get_enemys()
    {
        enemys.clear();
        vector<pair<int, int>> v;
        for (auto sp : spiral_dots)
        {
            for(auto e : sp.enemys)
            {
                enemys.push_back(e);
                v.push_back(e);
            }

        }

        for (auto sp : big_spiral_dots)
        {
            for(auto e : sp.enemys)
            {
                enemys.push_back(e);
                v.push_back(e);
            }

        }
        for( auto e : linear_enemys)
        {
            enemys.push_back(e.enemy());
            v.push_back(e.enemy());
        }

        for( auto e : squar_enemys)
        {
            enemys.push_back(e.enemy());
            v.push_back(e.enemy());
        }


        return v;
    };
    void random_map()
    {
        int T[3] = {-1, 1, 0};
        int lvl = 10, w = 20, h = 12;
        int **rmap = generateLevel(time(NULL), w, h);

        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                map[i][j] = T[rmap[i][j]];
            }
        }

    }


    void save_population()
    {

        std::ofstream ofs("population");
        boost::archive::text_oarchive ar(ofs);
        ar &Snubbys;
    }
    void load_population()
    {

        std::ifstream ifs("population");
        boost::archive::text_iarchive ar(ifs);

        ar &Snubbys;
    }

    static bool key_of_sort(Player A, Player B)
    {
        return A.fitness < B.fitness;
    }



    void next_generation()
    {
        cout << "Generation : " << generation << endl;
        for(auto &sn : Snubbys)
        {
            sn.x = A.first;
            sn.y = A.second;
            sn.is_a_life = 1;
            sn.fitness = sqrt(pow(sn.x - B.first, 2) + pow(sn.y -  B.second, 2));
        }

        sort(Snubbys.begin(), Snubbys.end(), key_of_sort);
        //stay 20 one from 100
        Snubbys.erase(Snubbys.begin() + Snubbys.size() / 5, Snubbys.end());
        N_Snubbys_a_life = Snubbys.size();

        // breeding
        //+20*3=60
        for(int i = 0; i < N_Snubbys_a_life; i++)
        {

            for(auto &c : Snubbys[i].breed(Snubbys[i + 1])) Snubbys.push_back( c);


        }

        //mutation
        //+40  
        for(int j = 0; j < 2; j++)
        {
            for(int i = 0; i < N_Snubbys_a_life; i++)
            {
                Snubbys.push_back(Snubbys[i]);
                Snubbys[i].brain.mutate();
            }
        }



        N_Snubbys_a_life = Snubbys.size();
    }
};



void Player::update_input(Level *level)
{
    input.clear();
    input.push_back((double)(level->B.first - x) / 800);
    input.push_back((double)(level->B.second - y) / 480);
    for(auto e : level->enemys)
    {

        input.push_back((double)(e.first - x) / 800);
        input.push_back((double)(e.second - y) / 480);

    }

}
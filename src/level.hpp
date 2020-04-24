

class Graphic;
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
        ar &brain;
        ar &fitness;

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
        // brain.init_params();

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

    void think(Level *level, Graphic *g);
    vector<Player> breed(Player player)
    {
        /*
            Make two children as parts of their parents.
            Args:
            mother (dict): Network parameters
            father (dict): Network parameters
        */
        vector<Player> children(1, Player(player));
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
    int n, last_direction = 1, N_Snubbys_a_life = 0;
    pair<double, double> A = {500, 500}, B = {100, 100} ;
    int generation=0;

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
        for( auto e : linear_enemys)
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
        cout << "Next Generation : " <<generation<< endl;
        for(auto &sn : Snubbys)
        {
            sn.x=A.first;
            sn.y=A.second;
            sn.is_a_life = 1;
            sn.fitness = sqrt(pow(sn.x - B.first, 2) + pow(sn.y -  B.second, 2));
        }

        sort(Snubbys.begin(), Snubbys.end(), key_of_sort);
        Snubbys.erase(Snubbys.begin() + Snubbys.size() / 3, Snubbys.end());

        N_Snubbys_a_life = Snubbys.size();

        for(int i=0;i<N_Snubbys_a_life;i++){
            Snubbys.push_back(Snubbys[i]);
            Snubbys[i].brain.mutate();
        }

        for(int i=0;i<N_Snubbys_a_life;i++){
            Snubbys.push_back(Snubbys[i]);
            Snubbys[i].brain.mutate();
        }

        //breeding

        // for(int i = 0; i < Snubbys.size() - 1; i++)
        // {


        //     if(Snubbys[i].is_a_life && Snubbys[i + 1].is_a_life)
        //     {

        //         for(auto &c : Snubbys[i].breed(Snubbys[i + 1])) Snubbys.push_back( c);
        //     }

        // }

        N_Snubbys_a_life = Snubbys.size();
    }


    void test(){
           for(auto &sn : Snubbys)
        {
            sn.x=A.first;
            sn.y=A.second;
            sn.is_a_life = 1;
            sn.fitness = sqrt(pow(sn.x - B.first, 2) + pow(sn.y -  B.second, 2));
        }

        sort(Snubbys.begin(), Snubbys.end(), key_of_sort);
        Snubbys.erase(Snubbys.begin() + 1 ,Snubbys.end());

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
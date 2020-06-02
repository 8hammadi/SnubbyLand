
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
    int c1 = 0, c2 = 0;
    vector<Coin> coins;
    Player player = Player(500, 500);
    Player player2 = Player(500, 500);
    vector<Player> Snubbys;
    int w_enemy = 20;
    pair<int, int> last_touch_on_green_area = make_pair(500, 500);
    pair<int, int> last_touch_on_green_area2 = make_pair(500, 500);
    vector<Linear_enemy> linear_enemys;
    vector<pair<int, int>> stable_enemys;
    vector<Spiral_dot> spiral_dots;
    vector<pair<int, int>> enemys;
    vector<Big_spiral_dot> big_spiral_dots;
    vector<Squar_enemy> squar_enemys;
    int n, last_direction = 1, N_Snubbys_a_life = 0;
    pair<double, double> A = {500, 500}, B = {100, 100} ;
    int generation = 0;
    int n_coins, virtuals;
    Level()
    {
        for(int i = 0; i < N_POPULATION; i++)
        {
            Snubbys.push_back(Player(player));
        }
    };
    void init_population(vector<int>nn)
    {
        for(auto &sn : Snubbys)
        {
            sn.brain.init_params(nn);
            sn.x = A.first;
            sn.y =  A.second;
            sn.is_a_life = 1;
        };

        N_Snubbys_a_life = N_POPULATION;
    }

    vector<pair<int, int>> getCoins()
    {
        vector<pair<int, int>> list;
        for(auto c : coins)
            list.push_back(make_pair(c.x, c.y));
        return list;
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
        cout << "GENERATING " << endl;
        int T[3] = {-1, 1, 0};
        int lvl = 10, w = 20, h = 12;

        vector<vector<int>> rmap = generateLevel(time(NULL), w / 2 - 1, h - 2);

        for(int i = 0; i < h; i++)
            for(int j = 0; j < w; j++)
                map[i][j] = rmap[i][j];
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
        generation++;
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

    vector<pair<int, int>> getEnvironment(Player &s);
    vector<pair<int, int>> wallDirections( int x, int y);
    pair<int, int> getVector( int x, int y, pair<int, int> center);
    void commandSnubby(bool T[4], Player &s);
};

///////////////////////////////////////////////////////////
vector<pair<int, int>> Level::wallDirections( int x, int y)
{

    // if no mobile obstacle is found at top of snubby.
    int w0 = (x / size_squar), w1 = ((x + player.w) / size_squar), h0 = (y / size_squar), h1;

    while(h0 >= 0 && map[h0][w0] != RESTRICTED && map[h0][w1] != RESTRICTED )
        h0--;
    int firstUp = y - (1 + h0) * size_squar;

    // if no mobile obstacle is found at bottom of snubby.
    w0 = (x / size_squar);
    w1 = ((x + player.w) / size_squar);
    h0 = (y + player.w) / size_squar;
    while(h0 < WINDOW_HEIGHT  && map[h0][w0] != RESTRICTED && map[h0][w1] != RESTRICTED )
        h0++;
    int firstDown =  h0 * size_squar - (y + player.w);

    // if no mobile obstacle is found at Left of snubby.
    w0 = (x / size_squar);
    h1 = ((y + player.w) / size_squar);
    h0 = (y / size_squar);
    while(w0 >= 0 && map[h0][w0] != RESTRICTED && map[h1][w0] != RESTRICTED )
        w0--;
    int firstLeft = x - (1 + w0) * size_squar;

    // if no mobile obstacle is found at right of snubby.
    w0 = (x + player.w) / size_squar;
    h1 = ((y + player.w) / size_squar);
    h0 = (y / size_squar);
    while(w0 < WINDOW_WIDTH && map[h0][w0] != RESTRICTED && map[h1][w0] != RESTRICTED )
        w0++;
    int firstRight = w0 * size_squar - (x + player.w );
    return vector<pair<int, int>> {make_pair(0, -firstUp), make_pair(0, firstDown), make_pair(-firstLeft, 0), make_pair(firstRight, 0)};

}

vector<pair<int, int>> Level::getEnvironment(Player &s)
{
    vector<pair<int, int>> env;
    for(auto &ob : get_enemys())
        env.push_back(getVector(s.x, s.y, make_pair(ob.first, ob.second)));
    // for(auto &p : wallDirections(s.x, s.y))
    //     env.push_back(p);
    for(auto &c : coins)
        if(!c.is_taked)
            env.push_back(getVector(s.x, s.y, make_pair(c.x, c.y)));
    return env;
}

pair<int, int> Level::getVector( int x, int y, pair<int, int> center)
{
    return make_pair(center.first - x, center.second - y);
}

void Level::commandSnubby(bool T[4], Player &s)
{
    int cmd = getWhere(s, getEnvironment(s), enemys.size());
    T[0] = (cmd & 2) != 0;
    T[1] = (cmd & 8) != 0;
    T[2] = (cmd & 1) != 0;
    T[3] = (cmd & 4) != 0;
}

void Player::update_input(Level &level)
{
    input.clear();
    input.push_back((double)(level.B.first - x) / 800);
    input.push_back((double)(level.B.second - y) / 480);
    for(auto e : level.enemys)
    {

        input.push_back((double)(e.first - x) / 800);
        input.push_back((double)(e.second - y) / 480);

    }

}

void Player::think(Level &level)
{
    update_input(level);
    vector<double> r = brain.predict( input);
    if(r[0] == max(r[0], max(r[1], max(r[2], r[3]))) && check_it_free_area(x, y - 10) &&
            is_player_inside_after(x, y - 20)
      )y -= 10; //up
    else if(r[1] == max(r[0], max(r[1], max(r[2], r[3]))) && check_it_free_area(x, y + 10) &&
            is_player_inside_after(x, y + 20)
           )y += 10; //down
    else if(r[2] == max(r[0], max(r[1], max(r[2], r[3]))) && check_it_free_area(x + 10, y) &&
            is_player_inside_after(x + 20, y)
           )x += 10; //R
    else if(r[3] == max(r[0], max(r[1], max(r[2], r[3]))) && check_it_free_area(x - 10, y) &&
            is_player_inside_after(x - 20, y)
           )x -= 10;; //L
}



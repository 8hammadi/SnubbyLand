class Simulator
{
public:
    // snubby,coins,walls,obstacles
    double q1, q2, q3, q4;
    int radius;
    vector<int> stop;
    Simulator()
    {
        init();
    }
    void init()
    {
        // radius = SNUBBY_SIZE * 3. / 2;
        q1 = 1;
        q2 = -700;
        q3 = 0.001;
        q4 = 4020;
    }
};

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
    Simulator sim;
    int x = 100, y = 100, w = 20, h = 20, p;
    vector<double> input;
    int score = 0;
    double fitness = 0;
    Model brain = Model({0, 0, 0});
    bool is_a_life = 1;
    Player() {};
    Player(int a, int b)
    {
        x = a + cx;
        y = b + cy;
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

    void think(Level &level);
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


    void update_input(Level &level);
};

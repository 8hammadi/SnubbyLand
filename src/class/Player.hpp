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

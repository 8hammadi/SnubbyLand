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
        t += sens * 0.01;


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

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
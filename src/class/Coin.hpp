
double Distance( int x0, int y0, int x1, int y1)
{
    return sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2)) ;
}

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
    bool is_virtual ;
    int x, y;
    int w = 10, h = 10;
    Coin()
    {
        is_virtual = false;
    }
    Coin(int x, int y): Coin()
    {
        this->x = x;
        this->y = y;
    }
    bool take(Player &p)
    {
        if( Distance(x, y, p.x, p.y) <= (w + p.w) / 2 + 3 )
        {
            is_taked = 1;
            return 1;
        }
        return 0;
    }
};
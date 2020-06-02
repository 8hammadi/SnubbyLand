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
                enemys.push_back(make_pair(cx + C.first + R * cos(i * PI / 2)*j / n, cy + C.second + R * sin(i * PI / 2)*j / n));

            }
        }

    }

    vector<pair<int, int>> getDirection()
    {
        vector<pair<int, int>> pais;
        for(int i = 0; i < 4; i++)
            for(int j = 1; j <= n; j++)
                pais.push_back(make_pair( -R * sin((i * PI / 2) + ongle)*j / n, R * cos((i * PI / 2) + ongle)*j / n));

        return pais;
    }

    void next_move()
    {
        ongle += PI / 140;
        enemys.clear();
        for(int i = 0; i < 4; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                enemys.push_back(make_pair(cx + C.first + R * cos((i * PI / 2) + ongle)*j / n, cy + C.second + R * sin((i * PI / 2) + ongle)*j / n));

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
                enemys.push_back(make_pair(cx + C.first + R * cos(i * PI / 2)*j / n, cy + C.second + R * sin(i * PI / 2)*j / n));

            }
        }
    }

};
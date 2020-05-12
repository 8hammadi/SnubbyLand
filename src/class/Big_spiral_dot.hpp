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

class Snubby
{
private:
       // Allow serialization to access non-public data members.
    friend class boost::serialization::access;

    // Serialize the std::vector member of Info
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &id;
        ar &x;
        ar &y;
        ar &pas;
    }
public:
    int id;
    int x = 0, y = 0, pas = 10;
    string icon;
    Snubby(){}
    void setPosition(int a, int b)
    {
        x = a;
        y = b;
    }


    void up()
    {
        y -= pas;
    }
    void down()
    {
        y += pas;
    }
    void left()
    {
        x -= pas;
    }
    void right()
    {
        x += pas;
    }
};


class Coin
{
private:
       // Allow serialization to access non-public data members.
    friend class boost::serialization::access;

    // Serialize the std::vector member of Info
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &x;
        ar &y;
        ar &isTaken;
    }
public:
    int x, y;
    bool isTaken = 0;
    Coin(){}
    Coin(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

};

class PolarRoad
{
private:
       // Allow serialization to access non-public data members.
    friend class boost::serialization::access;

    // Serialize the std::vector member of Info
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &i;
        ar &j;
        ar &A;
        ar &B;
        ar &P1;
        ar &P2;
        ar &D;
    }
public:
    int i, j;
    pair<int, int> A, B, P1, P2;
    double D;
    PolarRoad(){;};
    PolarRoad(pair<int, int> a, pair<int, int> b, pair<int, int> p1,
              pair<int, int> p2)
    {
        A = a, B = b, P1 = p1, P2 = p2;
        D = 0;
        for(int i = 0; i < 100; i++)
        {
            D += dist(M(i / 100), M((i + 1) / 100));
        }

    };
    pair<int, int> M(double t)
    {
        return make_pair(
                   pow((1 - t), 3) * A.first + 3 * pow((1 - t), 2) * t * P1.first + 3 * (1 - t) * pow(t, 2) * P2.first + pow(t, 3) * B.first,
                   pow((1 - t), 3) * A.second + 3 * pow((1 - t), 2) * t * P1.second + 3 * (1 - t) * pow(t, 2) * P2.second + pow(t, 3) * B.second);
    }
    double Distance(pair<int, int> M0)
    {
        double d = dist(M0, A);
        for(int i = 0; i < 100; i++)
        {
            d = min(d, dist(M0, M((double)i / 100)));
        }
        return d;
    }
};

class LinearRoad
{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &A;
        ar &B;
        ar &D;
    }
public:

    int i, j;
    pair<int, int> A, B;
    double D;
    LinearRoad() {;};
    LinearRoad(pair<int, int> a, pair<int, int> b)
    {
        A = a;
        B = b;
        D = dist(A, B);
    }

    pair<int, int> M(double t)
    {
        return make_pair( t * A.first + (1 - t) * B.first, t * A.second + (1 - t) * B.second );
    }
    double Distance(pair<int, int> M0)
    {
        double d = dist(M0, A);
        for(int i = 0; i < 100; i++)
        {
            d = min(d, dist(M0, M((double)i / 100)));
        }
        return d;
    }

};
class CircularRoad{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &C;
        ar &R;
        ar &D;
        ar &P;
    }
public:
    int i, j;
    pair<int, int> C,P;
    double D,R;
    CircularRoad(){;};
    CircularRoad(pair<int, int> c, pair<int, int> p)
    {
        C = c;
        P = p;
        R = dist(C, P);
        D=2*3.14*R;
    }


    pair<int, int> M(double t)
    {
        return make_pair( C.first + R * cos(2*3.14*t),  C.second + R * cos(2*3.14*t) );
    }
    double Distance(pair<int, int> M0)
    {

        return abs(R-dist(M0,C));
    }
};

class Graph
{
private:
    int i, j;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &nodes;
        ar &n;
        ar &m;
        ar &linearRoads;
        ar &polarRoads;
        //ar &circularRoads;

    }
public :
    vector<pair<int, int>> nodes;
    vector<LinearRoad> linearRoads;
    vector<PolarRoad> polarRoads;
    vector<CircularRoad> circularRoads;
    int n, m;
    void addNode(int a, int b)
    {
        if(iNode(make_pair(a, b)) != -1)return;
        nodes.push_back(make_pair(a, b));
        n++;
    }
    int iNode(pair<int, int> M)
    {
        for(int i = 0; i < nodes.size(); i++)if(nodes[i] == M)
            {
                return i;
            }
        return -1;
    }
    void addLinearRoad(pair<int, int> A, pair<int, int> B)
    {
        linearRoads.push_back(LinearRoad(A, B));
    }
    void addPolarRoad(pair<int, int> A, pair<int, int> B, pair<int, int> P1, pair<int, int> P2)
    {
        polarRoads.push_back(PolarRoad(A, B, P1, P2));
    }
    void addCircularRoad(pair<int, int> A, pair<int, int> B)
    {
        circularRoads.push_back(CircularRoad(A,B));
    }
};


class Enemy
{
private:
    // Allow serialization to access non-public data members.
    friend class boost::serialization::access;

    // Serialize the std::vector member of Info
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & idRoad;
        ar & lambda;
        ar & direction;

    }
public:
    int idRoad;
    bool direction = 1;
    float lambda = 0;
    double x = 10, y = 10;
    Enemy(){};
    Enemy(int idRoad, float lambda)
    {
        this->lambda = lambda;
        this->idRoad = idRoad;
        direction = 1;
    }
    void nextRoad(Graph graph)
    {
        idRoad = (idRoad + 1) % (graph.linearRoads.size() + graph.polarRoads.size());
    }
    void nextMouve(Graph graph)
    {
        double d;
        if(idRoad < graph.linearRoads.size())
        {
            d = graph.linearRoads[idRoad].D;
        }
        else
        {
            d = graph.polarRoads[idRoad - graph.linearRoads.size()].D;
        }
        lambda += 2 / d;

        if(lambda > 1)
        {
            nextRoad(graph);
            lambda = 0;
        }
        if(idRoad < graph.linearRoads.size())
        {
            x = graph.linearRoads[idRoad].M(lambda).first ;
            y = graph.linearRoads[idRoad].M(lambda).second ;
        }
        else
        {
            x = graph.polarRoads[idRoad - graph.linearRoads.size()].M(lambda).first ;
            y = graph.polarRoads[idRoad - graph.linearRoads.size()].M(lambda).second ;
        }
    }
};

class Game
{

private :
    // Allow serialization to access non-public data members.
    friend class boost::serialization::access;

    // Serialize the std::vector member of Info
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &map;
        ar &graph;
        ar &coins;
        ar &player;
        ar &enemys;
    }
    vector<pair<int, int>> v;
    pair<int, int> p;
    int n, m;
    int x, y, nEnemy, nCoin, np, nl, i, j;
public:

    Graph graph;
    vector<Coin> coins;
    Snubby player, player1;
    vector<Enemy> enemys;
    bool gameOver=0;
    int map[20][30] ;
    string name, fileName;

};

class Snubby
{
public:
    int x=0, y=0,pas=10;
    string icon;
    //int up, down, right, left;

    void setPosition(int a, int b)
    {
        x = a;
        y = b;
    }


    void up(){
    	y-=pas;
    }
    void down(){
    	y+=pas;
    }
    void left(){
    	x-=pas;
    }
    void right(){
    	x+=pas;
    }
};

// class Keys{
// private:
// 	int up,left,right,down;
// 	bool upActivated,


// };

// class Map
// {
// public:

//     int n = 20, m = 30, squareSize = 30;
//     int map;
// };

class PolarRoad
{
public:
    int i, j;
    pair<int, int> A, B, P1, P2;
    double D;
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
public:
    int i, j;
    pair<int, int> A, B;
    double D;
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

// class Road:public LinearRoad:public PolarRoad{
// 	public :
// 	bool isPolar=0,isLinear=0,isCirculer=0 ;
// 	//  

// }
class Graph
{
private:
    int i, j;
public :
    vector<pair<int, int>> nodes;
    vector<LinearRoad> linearRoads;
    vector<PolarRoad> polarRoads;
    vector<vector<int>> incidcence;
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
};


class Enemy
{
public:
    int idRoad;
    bool direction = 1;
    float lambda = 0;
    double x = 10, y = 10;
    Enemy(int idRoad, float lambda)
    {
        this->lambda = lambda;
        this->idRoad = idRoad;
        direction = 1;
    }
    void nextRoad(Graph graph)
    {
        //we take randomly a another road
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
/***************
Graph
vector<Coins>
Snubby
vector<Enemy>
vector<vector<char>> map    //array




***************/
    vector<pair<int, int>> v;
    pair<int, int> p;
    int n, m;
    int x, y, nEnemy, nCoin, np, nl, i, j;

public:

    Graph graph;
    vector<Coin> coins;
    Snubby player;
    vector<Enemy> enemys;
    int map[20][30]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    string name, fileName;


    /*
    	->	name of level
    	->	n,m of Graphe

    		n of enumy
    		xi yi of enumy

    		n of coins
    		xi yi of coins

    		x y player

    		xi yi of node

    		np nl number of polar and Linear road

    		np line of:
    		i j xc yc

    		nl lines of:

    		i j


    */
    void loadGame()
    {
        cout << "put name of level:";
        cin >> fileName;
        ifstream ensias("../files/" + fileName);

        ensias >> name;
        ensias >> n >> nEnemy;
        // while(nEnemy--)ensias>>e.idRoad>>e.direction>>e.lambda;
        // ensias>>coins.size();
        // for(auto e:coins)ensias>>e.x>>e.y;
        // ensias>>player.x>>player.y;
        // for(auto e:graph.nodes)ensias>>e.first>>e.second;
        // ensias>>graph.polarRoads.size()>>graph.linearRoads.size();
        // for(auto e:graph.polarRoads)ensias>>e.i>>e.j>>e.C.first>>e.C.second;
        // for(auto e:graph.linearRoads)ensias>>e.i>>e.j;

        ensias.close();
    }
    void saveGame()
    {
        cout << "put file name of level:";
        cin >> fileName;
        cout << "put name of level:";
        cin >> name;

        ofstream ensias("../files/" + name);

        ensias << name << " ";
        ensias << graph.nodes.size() << " " << enemys.size() << " ";
        for(auto e : enemys)ensias << e.idRoad << " " << e.direction << " " << e.lambda << " ";
        ensias << coins.size() << " ";
        for(auto e : coins)ensias << e.x << " " << e.y << " ";
        ensias << player.x << " " << player.y;
        for(auto e : graph.nodes)ensias << " " << e.first << " " << e.second;
        ensias << " " << graph.polarRoads.size() << " " << graph.linearRoads.size();

        //		for(auto e:graph.polarRoads)ensias<<" "<<e.i<<" "<<e.j<<" "<<e.C.first<<" "<<e.C.second<<" ";
        //		for(auto e:graph.linearRoads)ensias<<" "<<e.i<<" "<<e.j;
        ensias.close();
    }

};

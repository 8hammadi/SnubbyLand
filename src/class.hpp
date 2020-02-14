
class Snubby{
public:
	pair<int,int> position;
	string icon;
	int up,down,right,left;

	void setPosition(int a,int b){
		position=make_pair(a,b);
	}


	void setKeys(int n){
		switch(n){
			case 0:up=SDLK_z;down=SDLK_s;
			case 1:break;
		}
	}
};


class Coins{
private:
	pair<int,int> position;
	bool isTaken;
};

class Map{
public:
	int n=20 ,m=30 , squareSize=30;
	vector<string> map;
};


class Road
{
public:

    pair<int, int> first, second;
    Road(int a,int b,int aa,int bb)
    {
    	first=make_pair(a,b);second=make_pair(aa,bb);
    }
    pair<int,int> SpeedFonction(float lambda);

};

class Graph
{
public :
    vector<pair<int, int>> nodes;
    vector<Road> roads;

    void addNode(int a,int b);
};


class Enemy{
public:
	int idRoad;
	bool direction;
	float lambda;

	Enemy(int idRoad,float lambda,Graph G){
		this->lambda=lambda;
		this->idRoad=idRoad;
		direction=1;
	}
	void nextRoad(Graph graph);
};

class Game{
public:

	Graph graph;
	Coins coins;
	Snubby player;
	vector<Enemy> enemys;
	Map map;
	

	void loadGame(string fileName);
	void saveGame(string fileName){
	}
};
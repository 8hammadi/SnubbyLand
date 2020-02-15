
class Snubby{
public:
	int x,y;
	string icon;
	int up,down,right,left;

	void setPosition(int a,int b){
		x=a;y=b;
	}


	void setKeys(int n){
		switch(n){
			case 0:up=SDLK_z;down=SDLK_s;
			case 1:break;
		}
	}
};


class Coins{
public:
	int x,y;
	bool isTaken=0;
};

class Map{
public:

	int n=20 ,m=30 , squareSize=30;
	vector<string> map;
};

class PolarRoad{
public:
	int i,j;
	pair<int,int> A, B, P1, P2,C;
	double a1,a2,b1,b2; 
	int R1,R2;
	double O1,O2;
	PolarRoad(pair<int,int> a,pair<int,int> b,pair<int,int> p1, 	
	pair<int,int> p2)
	{
		A=a, B=b, P1=p1, P2=p2;

		a1=(P1.second-A.second)/(P1.first-A.first);
		a2=(P2.second-B.second)/(P2.first-B.first);
		b1=A.second-A.first*a1 ;
		b2=B.second-B.second*a2 ;

		C=make_pair((b1-b2)/(a2-a1),(a2*b1-a1*b2)/(a2-a1));
		
		R1=dist(A,C);
		R2=dist(B,C);
		O1=teta(A,C);
		O2=teta(B,C);

	};
	pair<int,int> M(double t){
		return make_pair(C.first+ (t*R1+(1-t)*R2)*cos( t*O1+(1-t)*O2) ,C.second+  (t*R1+(1-t)*R2)*sin( t*O1+(1-t)*O2));
	}
};

class LinearRoad{
public:
	int i,j;
	pair<int,int> A, B;

	LinearRoad(pair<int,int> a,pair<int,int> b){
		A=a;B=b;
	}

	pair<int,int> M(double t){
	return make_pair( t*A.first+(1-t)*B.first , t*A.second+(1-t)*B.second );
}

};


class Graph
{
private:
	int i,j;
public :
    vector<pair<int, int>> nodes;
    vector<LinearRoad> linearRoad;
    vector<PolarRoad> polarRoad;

    void addNode(int a,int b){
    	nodes.push_back(make_pair(a,b));
    }
    int iNode(pair<int,int> M){
    	for(int i=0;i<nodes.size();i++)if(nodes[i]==M)return i;
    	return -1;
    }
    void addLinearRoad(pair<int,int> A,pair<int,int> B){
    	i=iNode(A);j=iNode(B);
    	linearRoad.push_back(LinearRoad(A,B));
    }
};


class Enemy{
public:
	int idRoad;
	bool direction=1;
	float lambda=0.5;

	Enemy(int idRoad,float lambda,Graph G){
		this->lambda=lambda;
		this->idRoad=idRoad;
		direction=1;
	}
	void nextRoad(Graph graph);
};

class Game{
private :
vector<pair<int,int>> v;
pair<int,int> p;
int n,m;
int x,y,nEnemy,nCoins,np,nl,i,j;

public:

	Graph graph;
	vector<Coins> coins;
	Snubby player;
	vector<Enemy> enemys;
	Map map;
	string name,fileName;


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
	void loadGame(){
		cout<<"put name of level:";
		cin >>fileName;
		ifstream ensias("../files/"+fileName);

		ensias>>name;

		ensias.close();
	}
	void saveGame(){
		cout<<"put file name of level:";
		cin >>fileName;
		cout<<"put name of level:";
		cin>>name;

		ofstream ensias("../files/"+name);

		ensias<<name<<" ";
		ensias<<graph.nodes.size()<<" "<<enemys.size()<<" ";
		for(auto e:enemys)ensias<<e.idRoad<<" "<<e.direction<<" "<<e.lambda<<" ";
		ensias<<coins.size()<<" ";
		for(auto e:coins)ensias<<e.x<<" "<<e.y<<" ";
		ensias<<player.x<<" "<<player.y;
		for(auto e:graph.nodes)ensias<<" "<<e.first<<" "<<e.second;
		ensias<<" "<<graph.polarRoad.size()<<" "<<graph.linearRoad.size();

		for(auto e:graph.polarRoad)ensias<<" "<<e.i<<" "<<e.j<<" "<<e.C.first<<" "<<e.C.second<<" ";
		for(auto e:graph.linearRoad)ensias<<" "<<e.i<<" "<<e.j;
		ensias.close();
	}
};
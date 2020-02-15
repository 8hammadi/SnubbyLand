int dist(pair<int,int> A,pair<int,int> B){
	return sqrt(pow(A.first-B.first,2)+pow(A.second-B.second,2));
}
double teta(pair<int,int> M,pair<int,int> C);

class PolarRoad{
public:
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
	pair<int,int> PlarFonction(double t){
		return make_pair(C.first+ (t*R1+(1-t)*R2)*cos( t*O1+(1-t)*O2) ,C.second+  (t*R1+(1-t)*R2)*sin( t*O1+(1-t)*O2));
	}
}

class LinearRoad{
public:
	pair<int,int> A, B;

	LinearRoad(pair<int,int> a,pair<int,int> b){
		A=a;B=b;
	}

	pair<int,int> LinearFonction(double lambda){
	return make_pair( lambda*A.first+(1-lambda)*B.first , lambda*A.second+(1-lambda)*B.second );
}

}





#define Pi 3.14159265359
int dist(pair<int,int> A,pair<int,int> B){
	return sqrt(pow(A.first-B.first,2)+pow(A.second-B.second,2));
}

double teta(pair<int,int> M,pair<int,int> C){
	int x = M.first - C.first;
	int y = M.second - C.second;
	if(x > 0)return atan(y / x);
	else if(x < 0 && y >= 0)return atan(y / x) + Pi;
	else if(x < 0 && y < 0)return atan(y / x) - Pi;
	else if(x == 0 && y > 0)return Pi / 2;
	else return -Pi / 2;
}

double Sca(pair<int,int> A,pair<int,int> B){
	return A.first*B.first+A.second*B.second;
}

double Norme(pair<int,int> A,pair<int,int> B){
	return sqrt( pow(B.first-A.first,2)+pow(B.second-A.second));
}

pair<int,int> Projection(pair<int,int> M,A,B){

}
double min(double a,double b){return a<b?a:b;}
double max(double a,double b){return a>b?a:b;}




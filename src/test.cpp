#include "bits/stdc++.h"
using namespace std;


class A{

public:
	int a, b;
	A(int x,int y){
		a=x;b=y;
	}
};


class B{

public:
	int a, b;
	B(int x,int y){
		a=x;b=y;
	}
}
;

int main(int argc, char const *argv[])
{
	A P1(1,2);
	void * data=&P1;
	cout<<((A*)data)->a;
	return 0;
}
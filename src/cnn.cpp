
#include <bits/stdc++.h>
// #include "cnn.hpp"
using namespace std;

double relu(double x)
{
    return x > 0 ? x : 0;
}
double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

vector<double> dot(vector<vector<double>> A, vector<double> x, vector<vector<double>> b, int sig)
{
    vector<double> y;
    double e = 0;
    for(int i = 0; i < A.size(); i++)
    {
        e = b[i][0];
        for(int j = 0; j < A[0].size(); j++)
        {
            e += A[i][j] * x[j];;
        }
        if(sig)
            y.push_back(sigmoid(e));
        else
            y.push_back(relu(e));
    }

    return y;

}


class Model
{

public:
    vector<int> layers = {2, 20, 4};

    vector<vector<vector<double>>> W ;
    vector<vector<vector<double>>> b ;

    Model(vector<int> layers)
    {
        this->layers = layers;



        for(int k = 0; k < layers.size()-1; k++)
        {
            vector<vector<double>> bb;
            vector<vector<double>> v;
            for(int i = 0; i < layers[k+1] ; i++)
            {   vector<double> vv;
                for(int j = 0; j < layers[k]; j++)
                {
                    vv.push_back(sigmoid(rand())) ;
                }
                v.push_back(vv);          }
            W.push_back(v);
            b.push_back(bb);
        }
    }
    vector<double> predict(vector<double> input)²
    {
        for(int k = 0; k < layers.size() - 2; k++)
        {
            input = dot(W[k], input, b[k], 0);
        }
        input = dot(W[layers.size() - 2], input, b[layers.size() - 2], 1);
        return input;
    }
};



int main(int argc, char const *argv[])
{
    Model m = Model({2, 20, 1});
    auto r = m.predict({100, 1020});
    for(auto s : r)
    {
        cout << s << " ";
    }
    return 0;
}

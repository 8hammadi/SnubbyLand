double choice(double a, double b)
{
    return rand() % 2 ? a : b;
}
double relu(double x)
{
    return x > 0 ? x : 0;
}
double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}
vector<double>  dot(vector<vector<double>> A, vector<double> x, vector<vector<double>> b, int sig)
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
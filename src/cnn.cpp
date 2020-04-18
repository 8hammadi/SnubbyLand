
#include <bits/stdc++.h>
#include "cnn.hpp"
using namespace std;



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
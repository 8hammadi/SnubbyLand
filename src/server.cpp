#include <bits/stdc++.h>
#include "HTTPRequest.hpp"
using namespace std;

string POST(map<string, string> parameters)
{
    try
    {
        http::Request request("http://horusnews.herokuapp.com/snubbyland_ensias_projet");
        // http::Request request("http://localhost:8000/snubbyland_ensias_projet");
        const http::Response response = request.send("POST", parameters,
        {
            "Content-Type: application/x-www-form-urlencoded"
        });
        return string(response.body.begin(), response.body.end()) ;
    }catch(...){
        cout<<"your are not connected"<<endl;
    }

}
// map<string, string> parameters = {{"level", to_string(level)}, {"id", id_online}, {"x", to_string(level->player.x)}, {"y", to_string(level->player.y)}};
// stringstream r = stringstream(res) ;

string login(string id)
{
    return POST( {{"what", "login"}, {"id", id}}) ;
}

string logout(string id,string token)
{
    return POST( {{"what", "logout"}, {"id", id},{"token",token}}) ;
}
//find_player return id of player online

string find_player(string id, int level)
{

    return POST( {{"what", "i want to play online ."}, {"id", id}, {"level", to_string(level)}});
}

//when the players playing
//it return "win" or "lose" or "x y"
string send_and_get_status(string token, string id, int x, int y)
{
    return POST({{"what", "status_of_playing"}, {"what", "i want to play online ."}, {"id", id}, {"x", to_string(x)}, {"y", to_string(y)},{"token",token}});
}



int main(int argc, char const *argv[])
{
    string id=string(argv[1]);
    string token=login(id);
    cout <<  token<< endl;
    cout<<"demand of playing online ..."<<endl;
    cout<<find_player(id,1)<<endl;

    cout<<send_and_get_status(token,id,20,20);
    cout << logout(id,token) << endl;
    return 0;
}
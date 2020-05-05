
#include <bits/stdc++.h>
#include "HTTPRequest.hpp"
#include <SDL2/SDL.h>

using namespace std;

http::Request request("http://localhost:8000");
http::Response response;
int A(void *_)
{
    while(1)
    {
    	SDL_Delay(10);
        if(response.body.size() >= 9)
            cout << string(response.body.end() - 10, response.body.end()) << endl ;
        }
}
int main(int argc, char const *argv[])
{
    SDL_CreateThread( A, "EventFonction", (void *)NULL);

    request.stream(response, "POST", "545454",
    {
        "Content-Type: application/x-www-form-urlencoded"
    });


    return 0;
}
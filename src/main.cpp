//g++ -o game main.cpp -lSDL2  -lSDL2_image  -lm -lboost_serialization -lSDL2_ttf -fpermissive -lSDL2_mixer
#include <bits/stdc++.h>
using namespace std;

#define PI 3.141592653589793
#define N_POPULATION 100
#define NEURAL_NETWORK { (int)level->player.input.size(),40,10, 4}
#define RANDOM (double)rand()/RAND_MAX
#define TOKEN_SIZE 10
#define SERVER_URL "http://snubbyland.herokuapp.com/api"
#define SERVER_STREAM "ssnuby.herokuapp.com"
#define SPEED 1
#define FREQUENCE 0.2
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>

namespace beast = boost::beast;
namespace websocket = boost::beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;


#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "HTTPRequest.hpp"
#include "server.hpp"

#include <cmath>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "map_generateur.hpp"
#include "cnn.hpp"
#include "level.hpp"
#include "Game.hpp"


Level level;
Game Game(&level);

int  control_event(void *a)
{
    Game.control_event();
    return 1;
};


int  thread_playing_online(void *a)
{
    Game.thread_playing_online();
    return 1;
};

int thread_update_position(void *a)
{
    Game.thread_update_position();
    return 1;
}
int main(int argc, char const *argv[])
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    if(argc > 1)
    {
        Game.init();
        Game.id = argv[1];
        // Game.id2 = argv[2];
    }
    else
    {
        cout << "add some id like '$./game hello_server'" << endl;
        exit(0);
    }


    SDL_CreateThread( control_event, "", (void *)NULL);
    SDL_CreateThread( thread_playing_online, "", (void *)NULL);
    SDL_CreateThread( thread_update_position, "", (void *)NULL);
    Game.index();


    return 0;
}




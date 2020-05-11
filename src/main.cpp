
#define PI 3.141592653589793
#define N_POPULATION 100
#define NEURAL_NETWORK { (int)level.player.input.size(),40,10, 4}
#define RANDOM (double)rand()/RAND_MAX
#define TOKEN_SIZE 10
#define SERVER_STREAM "ssnuby.herokuapp.com"
#define SPEED 1

#include <bits/stdc++.h>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace beast = boost::beast;
namespace websocket = boost::beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
using namespace std;

#include "map_generateur.hpp"
#include "cnn.hpp"
#include "level.hpp"
#include "Game.hpp"

Game Game;

int  control_event(void *_)
{
    Game.control_event();
    return 1;
};
int  thread_playing_online(void *_)
{
    Game.thread_playing_online();
    return 1;
};
int thread_update_position(void *_)
{
    Game.thread_update_position();
    return 1;
}

int main(int argc, char const *argv[])
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Game.init();
    SDL_CreateThread( control_event, "", (void *)NULL);
    SDL_CreateThread( thread_playing_online, "", (void *)NULL);
    SDL_CreateThread( thread_update_position, "", (void *)NULL);
    Game.index();


    return 0;
}




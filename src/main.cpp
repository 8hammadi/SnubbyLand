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

#include "constant.hpp"
#include "map_generateur.hpp"
#include "global_variable.hpp"
#include "util.hpp"
#include "prototype.hpp"
#include "class/brain.hpp"
#include "class/Player.hpp"
#include "class/Spiral_dot.hpp"
#include "class/Linear_enemy.hpp"
#include "class/Squar_enemy.hpp"
#include "class/Big_spiral_dot.hpp"
#include "class/Coin.hpp"
#include "class/level.hpp"

Level  level,*ll ;

#include "init.hpp"
#include "index.hpp"
#include "get_level.hpp"
#include "model.hpp"
#include "sound.hpp"
#include "view.hpp"
#include "update.hpp"
#include "controller.hpp"
#include "online.hpp"

#include "create/Big_spiral_dot.hpp"
#include "create/Coin.hpp"
#include "create/Green_area.hpp"
#include "create/Linear_enemy.hpp"
#include "create/Player.hpp"
#include "create/Spiral_dot.hpp"
#include "create/Squar_enemy.hpp"
#include "create/Wall.hpp"

#include "creator.hpp"
#include "pause.hpp"
#include "game.hpp"


int main(int argc, char const *argv[])
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    SDL_CreateThread( control_event, "", (void *)NULL);
    SDL_CreateThread( thread_playing_online, "", (void *)NULL);
    SDL_CreateThread( thread_update_position, "", (void *)NULL);
    index();


    return 0;
}




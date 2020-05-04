//g++ -o game main.cpp -lSDL2  -lSDL2_image  -lm -lboost_serialization -lSDL2_ttf -fpermissive -lSDL2_mixer

//22 serialization::archive 16 0


#include <bits/stdc++.h>
using namespace std;

#define PI 3.14
#define N_POPULATION 100
#define AUTO 0
#define NN { (int)level->player.input.size(),40,40,40, 4}
#define RANDOM (double)rand()/RAND_MAX
#define TOKEN_SIZE 5

#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"
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
#include "graphic.hpp"

Level level;
Graphic graphic(&level);

int  control(void *a)
{
    graphic.control();
    return 1;
};


int  online(void *a)
{
    graphic.online();
    return 1;
};


int main(int argc, char const *argv[])
{

  


    graphic.init();
	graphic.id=argv[1];

    SDL_CreateThread( control, "EventFonction", (void *)NULL);
    SDL_CreateThread( online, "EventFonction", (void *)NULL);

    graphic.index();


    return 0;
}




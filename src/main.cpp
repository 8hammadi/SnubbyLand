//g++ -o game main.cpp -lSDL2  -lSDL2_image  -lm -lboost_serialization -lSDL2_ttf -fpermissive
//22 serialization::archive 16 0


#define PI 3.14
#define N_POPULATION 200
#define AUTO 0
#define NN { (int)level->player.input.size(),10,10, 4}
#define RANDOM (double)rand()/RAND_MAX

#include <bits/stdc++.h>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"
#include <SDL2/SDL_ttf.h>

#include <cmath>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

#include "map_generateur.hpp"
#include "cnn.hpp"
#include "level.hpp"
#include "graphic.hpp"

Level level;
Graphic graphic(&level);

int  test(void *a)
{
    graphic.control();
    return 1;
};




int main(int argc, char const *argv[])
{

  



    graphic.init();

    SDL_CreateThread( test, "EventFonction", (void *)NULL);

    graphic.index();


    return 0;
}




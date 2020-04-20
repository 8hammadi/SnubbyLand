// g++ -o game main.cpp -lSDL2 -lpng -lSDL2_image  -lm -lboost_serialization
#define PI 3.14
#define N_OF_NEW_LEVEL 6 // Change this if you want creat new level
#define N_OF_LEVELS 5
#include <bits/stdc++.h>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_mixer.h"
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

int  test(void *a){
     graphic.control();
    return 1;
};


int main(int argc, char const *argv[])
{

    graphic.init();
    
    // SDL_CreateThread( quit,"EventFonction",(void *)NULL);
    SDL_CreateThread( test,"EventFonction",(void *)NULL);

    graphic.index();


    return 0;
}




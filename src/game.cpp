// g++ -o game game.cpp -lSDL2 -lpng -lSDL2_image  -lm -lboost_serialization
#include <bits/stdc++.h>

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

#define MAX_BUF 1024
using namespace std;

#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include "math.hpp"
#include "class.hpp"
#include "Graphic.hpp"

Game game;
Graphic SDL("SnubbyLand",&game);

int threadEvent(void *_){
    SDL.takeEvent();
    return 0;
};

int main(int argc, char const *argv[])
{


    SDL.index();
    SDL.sleep(2000);
    SDL.level();
    SDL.sleep(2000);

    SDL_CreateThread( threadEvent,"EventFonction",(void *)NULL);

    while(SDL.continuer){
            SDL.update();
            SDL.draw();
            SDL.show();
            SDL.sleep(10);
        }

    return 0;
}




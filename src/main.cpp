// g++ -o main main.cpp -lSDL2 -lpng -lSDL2_image  -lm -lboost_serialization
#include <bits/stdc++.h>

#include <bits/stdc++.h>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/utility.hpp> 

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
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
int receive(void *_){
    SDL.receive();
    return 0;
}
int send(void *_){
    SDL.send();
    return 1;
    ;}

int main(int argc, char const *argv[])
{
    // if(argc<2)return 0;
    // game.player.id=atoi(argv[1]) ;  
    SDL_CreateThread( threadEvent,"EventFonction",(void *)NULL);
    // SDL_CreateThread( receive ,"receive",(void *)NULL );
    // SDL_CreateThread( send ,"Send",(void *)NULL );

    while(SDL.continuer){
            SDL.go();
            SDL.update();
            SDL.draw();
            SDL.show();
            SDL.sleep(10);
        }

    return 0;
}




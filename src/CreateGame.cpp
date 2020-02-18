// g++ -o main CreateGame.cpp -lSDL2 -lpng -lSDL2_image  -lm 
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <cmath>
using namespace std;

#include "math.hpp"
#include "class.hpp"
#include "Graphic.hpp"


Game game;
Graphic SDL("SnubbyLand",&game);

int threadEvent(void *_){
    SDL.takeEvent(NULL);
    return 0;
};
int main(){
    
    SDL_CreateThread( threadEvent,"EventFonction",(void *)NULL);
    
    while(SDL.continuer){
            SDL.go();
            SDL.update();
            SDL.draw();
            SDL.show();
            SDL.sleep(10);
        }
    cout<<game.graph.nodes.size();
    return 0;
}




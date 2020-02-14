#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
using namespace std;

#include "variable.hpp"
#include "class.hpp"
#include "Graphic.hpp"

void Main();

int main(){
    Game game;

    Graphic SDL("SnubbyLand",&game);
    
    while(SDL.continuer){
            
            SDL.takeEvent();
            //SDL.draw(0,game);
            SDL.show();
            SDL.sleep(20);
        }
    cout<<game.graph.nodes.size();
    SDL.show();
    return 0;
}




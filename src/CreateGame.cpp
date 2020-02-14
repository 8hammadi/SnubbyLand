#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
using namespace std;
#include "Graphic.hpp"
#include "variable.hpp"
#include "class.hpp"

int continuer=1;

string fileName="leve1";

void takeEvent(){
    SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = SDL_FALSE;
            case SDL_KEYDOWN:
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.motion.x;
                y = event.motion.y;
                printf("%d  %d  \n",x,y);
                break;
         
        }
}
void Main();
int main(){

	Graphic SDL("SnubbyLand");
	
	Game game;

    SDL.drawTable(40,60,2);

	//Main();

    SDL.show();
	SDL.sleep(10000);


	return 0;
}




void Main(){
        while(continuer){

            takeEvent();
            Draw();
            Show();

        }
}

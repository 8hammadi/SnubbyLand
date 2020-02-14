#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

#include "variable.hpp"
#include "class.hpp"
#include "fonction.hpp"

int continuer=0;

int main(){

	init();
	
	Game game;

	control();

	while(continuer){

		update();
		draw();
		show();

	}
	SDL_Delay(500);
	freeMemory();


	return 0;
}
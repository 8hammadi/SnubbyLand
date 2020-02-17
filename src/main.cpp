// g++ -o main main.c -lSDL2 -lpng -lSDL2_image  -lm 
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <cmath>
using namespace std;

#include "math.hpp"
#include "class.hpp"
#include "Graphic.hpp"

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
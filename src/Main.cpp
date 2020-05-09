//g++ -o game main.cpp -lSDL2  -lSDL2_image  -lm -lboost_serialization -lSDL2_ttf -fpermissive -lSDL2_mixer
#include <bits/stdc++.h>
using namespace std;

// #include <boost/serialization/vector.hpp>
// #include <boost/archive/text_oarchive.hpp>
// #include <boost/archive/text_iarchive.hpp>
// #include <boost/serialization/utility.hpp>
#include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
// #include "HTTPRequest.hpp"
// #include "server.hpp"


SDL_Window *window;
SDL_Renderer *render;
SDL_Rect rect;
int main(int argc, char const *argv[])
{

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow("Snubby Land", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 668, SDL_WINDOW_OPENGL);
    render = SDL_CreateRenderer(window, -1, 0);
    SDL_Delay(2000);
    SDL_Quit();

    return 0;
}




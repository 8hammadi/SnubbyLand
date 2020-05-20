#include <bits/stdc++.h>
#include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>

using namespace std;


SDL_Window *window;
SDL_Renderer *render;


int main(int argc, char const *argv[])
{

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow("Snubby Land", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 668, SDL_WINDOW_OPENGL);
    render = SDL_CreateRenderer(window, -1, 0);
    SDL_Delay(2000);

    return 0;
}




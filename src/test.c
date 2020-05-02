#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>
using namespace std;
SDL_Window *window;
SDL_Renderer *render;
SDL_Rect rect;
int continuer = 1, i = 0, j = 0;
SDL_Event event;
TTF_Font *font;
SDL_Texture *texture;
SDL_Surface *s;
int draw(void *_)
{
    while(continuer)
    {
        j++;
        SDL_SetRenderDrawColor(render, 181, 181, 253.98, 255);
        SDL_RenderFillRect(render, NULL );


        printf("%d\n", i);

        rect = { 0, 0, 100, 100};

        s = TTF_RenderText_Solid(font, to_string(i).c_str(), {250, 250, 0, 0});
        texture = SDL_CreateTextureFromSurface(render, s);
        SDL_RenderCopy(render, texture, NULL, &rect);


        rect = { 200, 0, 100, 100};

        s = TTF_RenderText_Solid(font, to_string(j).c_str(), {250, 250, 0, 0});
        texture = SDL_CreateTextureFromSurface(render, s);
        SDL_RenderCopy(render, texture, NULL, &rect);

        SDL_RenderPresent(render);
        SDL_Delay(50);

    }
    return 1;
}

int main(int argc, char const *argv[])
{
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow("Snubby Land", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 668, SDL_WINDOW_OPENGL);
    render = SDL_CreateRenderer(window, -1, 0);

    if (!TTF_Init())
    {
        font = TTF_OpenFont("../images/FreeSans.ttf", 24);
    }

    SDL_CreateThread( draw, "draw-test", (void *)NULL);


    while(continuer)
    {

        SDL_WaitEvent(&event);

        switch (event.type)
        {

        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
                i++;
                break;
            }
        }
    }

    return 0;
}


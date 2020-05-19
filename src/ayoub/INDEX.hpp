#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 668

// logo
#define HOME_logo_width 100
#define HOME_logo_height 50
#define HOME_logo_x (WINDOW_WIDTH-HOME_logo_width)/2
#define HOME_logo_y 50

// buttons
#define HOME_button_width 100
#define HOME_button_height 50
#define HOME_button_x 50
#define HOME_button_margin 20

// offline
#define HOME_automatic_y WINDOW_HEIGHT-HOME_button_height-HOME_button_margin

// online
#define HOME_online_y HOME_automatic_y-HOME_button_height-HOME_button_margin

// offline
#define HOME_offline_y HOME_online_y-HOME_button_height-HOME_button_margin

// normal
#define HOME_normal_y  HOME_offline_y-HOME_button_height-HOME_button_margin

// createLevel
#define HOME_createLevel_width 100
#define HOME_createLevel_height 50
#define HOME_createLevel_x WINDOW_WIDTH-HOME_button_margin-HOME_createLevel_width
#define HOME_createLevel_y WINDOW_HEIGHT-HOME_createLevel_height-HOME_button_margin


void eventHome(int x, int y){
	//ONE PLAYER OFFLIN
            if(HOME_button_x <= x && x <= HOME_button_x + HOME_button_width &&
                    HOME_normal_y <= y && y <= HOME_normal_y + HOME_button_height)
            {
               

            }
            //TWO PLAYER thread_playing_online
            if(HOME_button_x <= x && x <= HOME_button_x + HOME_button_width &&
                    HOME_online_y <= y && y <= HOME_online_y + HOME_button_height)
            {

            }
            //GENETIC ALGORITHM (n'est pas encore terminé)
            if(HOME_button_x <= x && x <= HOME_button_x + HOME_button_width &&
                    HOME_automatic_y <= y && y <= HOME_automatic_y + HOME_button_height)
            {
              

            }
            //2Players Offline
            if(HOME_button_x <= x && x <= HOME_button_x + HOME_button_width &&
                    HOME_offline_y <= y && y <= HOME_offline_y + HOME_button_height)
            {

            }

            //CREATE NEW LEVEL
            if(HOME_createLevel_x <= x && x <= HOME_createLevel_x + HOME_createLevel_width &&
                    HOME_createLevel_y <= y && y <= HOME_createLevel_y + HOME_createLevel_height)
            {
               

            }
}

inline void renderHome(SDL_Renderer *render)
{

    static SDL_Texture *HOME_normal =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/normal.svg"));
    static SDL_Texture *HOME_online =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/online.svg"));
    static SDL_Texture *HOME_offline =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/2Players.svg"));
    static SDL_Texture *HOME_automatic =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/automatic.svg"));
    static SDL_Texture *HOME_createLevel =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/createLevel.svg"));
    static SDL_Texture *HOME_logo =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/index.svg"));
    static SDL_Texture *HOME_background = SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/index.png"));


    SDL_RenderCopy(render, HOME_background, NULL, NULL);

    SDL_Rect rect = {HOME_button_x, HOME_normal_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_normal, NULL, &rect);

    rect = {HOME_button_x, HOME_normal_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_offline, NULL, &rect);

    rect = {HOME_button_x, HOME_offline_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_online, NULL, &rect);

    rect = {HOME_button_x, HOME_online_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_automatic, NULL, &rect);

    rect = {HOME_button_x, HOME_automatic_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_normal, NULL, &rect);

    rect = {HOME_createLevel_x, HOME_createLevel_y, HOME_createLevel_width, HOME_createLevel_height};
    SDL_RenderCopy(render, HOME_createLevel, NULL, &rect);
}
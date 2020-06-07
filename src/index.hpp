// logo
#define HOME_logo_width 170
#define HOME_logo_height 70
#define HOME_logo_x (WINDOW_WIDTH-HOME_logo_width)/2
#define HOME_logo_y 50

// buttons
#define HOME_button_width 170
#define HOME_button_height 70
#define HOME_button_x 51
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
#define HOME_createLevel_width 170
#define HOME_createLevel_height 100
#define HOME_createLevel_x WINDOW_WIDTH-HOME_button_margin-HOME_createLevel_width
#define HOME_createLevel_y WINDOW_HEIGHT-HOME_createLevel_height-HOME_button_margin

inline void renderHome(SDL_Renderer *render);

void index()
{
    cout << "Hello " << id << endl;
    coin_sound();

    interface = INDEX;

    continuer = 1;
    while(1)
    {
        SDL_WaitEvent(&event);
        if(!&event)
            continue;
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            coin_sound();
            x = event.motion.x;
            y = event.motion.y;

            //ONE PLAYER OFFLIN
            if(HOME_button_x <= x && x <= HOME_button_x + HOME_button_width &&
                    HOME_normal_y <= y && y <= HOME_normal_y + HOME_button_height)
            {
                is_online_game = 0;
                automatique = 0;
                offline = 0;
                l = get_level();
                if (play_function_is_run)
                {
                    is_playing = 1;
                    return ;
                }
                else
                {
                    play_function_is_run = 1;
                    return play();
                }
            }
            //TWO PLAYER thread_playing_online
            else if(HOME_button_x <= x && x <= HOME_button_x + HOME_button_width &&
                    HOME_online_y <= y && y <= HOME_online_y + HOME_button_height)
            {
                automatique = 0;
                offline = 0;
                l = get_level();
                is_online_game = 1;
                cout << "level : " << l << endl;
                SDL_RenderCopy(render, texture_wait, NULL, NULL);
                SDL_RenderPresent(render);
                while(id2 == "0")
                {
                    SDL_Delay(50);   //finding a player
                }
                if (play_function_is_run)
                {
                    is_playing = 1;
                    return ;
                }
                else
                {
                    play_function_is_run = 1;
                    return play();
                }
            }
            //Automatic
            else if(HOME_button_x <= x && x <= HOME_button_x + HOME_button_width &&
                    HOME_automatic_y <= y && y <= HOME_automatic_y + HOME_button_height)
            {
                is_online_game = 0;
                automatique = 1;
                offline = 0;
                l = get_level();
                if (play_function_is_run)
                {
                    is_playing = 1;
                    return ;
                }
                else
                {
                    play_function_is_run = 1;
                    play();
                    return;
                }
            }
            //2Players Offline
            else if(HOME_button_x <= x && x <= HOME_button_x + HOME_button_width &&
                    HOME_offline_y <= y && y <= HOME_offline_y + HOME_button_height)
            {
                // TODO 2Players Offline
                offline = 1;
                is_online_game = 0;
                automatique = 0;
                l = get_level();
                if (play_function_is_run)
                {
                    is_playing = 1;
                    return ;
                }
                else
                {
                    play_function_is_run = 1;
                    return play();
                }
            }

            //CREATE NEW LEVEL
            else if(HOME_createLevel_x <= x && x <= HOME_createLevel_x + HOME_createLevel_width &&
                    HOME_createLevel_y <= y && y <= HOME_createLevel_y + HOME_createLevel_height)
            {
                is_online_game = 0;
                automatique = 0;
                offline = 0;
                create_level();
                cout << "le niveau créé avec succès" << endl;
                if (play_function_is_run)
                {
                    is_playing = 1;
                    return ;
                }
                else
                {
                    play_function_is_run = 1;
                    return play();
                }
            }
            break ;
        case SDL_QUIT:
            return free_memory();
            break;
        }
    }
    return;
}

inline void renderHome(SDL_Renderer *render)
{

    static SDL_Texture *HOME_normal =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/normal.png"));
    static SDL_Texture *HOME_online =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/online.png"));
    static SDL_Texture *HOME_offline =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/2Players.png"));
    static SDL_Texture *HOME_automatic =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/automatic.png"));
    static SDL_Texture *HOME_createLevel =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/createLevel.png"));
    static SDL_Texture *HOME_logo =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/index.png"));
    static SDL_Texture *HOME_background = SDL_CreateTextureFromSurface(render, IMG_Load("../images/background.jpg"));

    SDL_RenderCopy(render, HOME_background, NULL, NULL);

    SDL_Rect rect = {HOME_button_x, HOME_normal_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_normal, NULL, &rect);

    rect = {HOME_button_x, HOME_offline_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_offline, NULL, &rect);

    rect = {HOME_button_x, HOME_online_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_online, NULL, &rect);

    rect = {HOME_button_x, HOME_automatic_y, HOME_button_width, HOME_button_height};
    SDL_RenderCopy(render, HOME_automatic, NULL, &rect);

    rect = {HOME_createLevel_x, HOME_createLevel_y, HOME_createLevel_width, HOME_createLevel_height};
    SDL_RenderCopy(render, HOME_createLevel, NULL, &rect);
}

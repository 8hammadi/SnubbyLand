// buttons
#define WIN_LOSE_button_width 100
#define WIN_LOSE_button_height 50
#define WIN_LOSE_button_x (WINDOW_WIDTH-WIN_LOSE_button_width)/2
#define WIN_LOSE_button_margin 20

// WIN LOSE IMAGE
#define WIN_LOSE_image_width 400
#define WIN_LOSE_image_height 270
#define WIN_LOSE_image_x (WINDOW_WIDTH-WIN_LOSE_image_width)/2
#define WIN_LOSE_image_y 30

// restart
#define WIN_LOSE_restart_y WIN_LOSE_button_margin*2+WIN_LOSE_image_height+WIN_LOSE_image_y

// levels
#define WIN_LOSE_levels_y WIN_LOSE_restart_y+WIN_LOSE_button_height+WIN_LOSE_button_margin

// quit
#define WIN_LOSE_quit_y  WIN_LOSE_levels_y+WIN_LOSE_button_height+WIN_LOSE_button_margin

// prev_next
#define WIN_LOSE_prev_next_y  WIN_LOSE_quit_y+WIN_LOSE_button_height+WIN_LOSE_button_margin

// previous
#define WIN_LOSE_previous_x (WINDOW_WIDTH-2*WIN_LOSE_button_width-WIN_LOSE_button_margin)/2

// next
#define WIN_LOSE_next_x WIN_LOSE_previous_x+WIN_LOSE_button_width+WIN_LOSE_button_margin


void play()
{
    interface = GAME;
    cout << "the game began" << endl;
    is_playing = 1;

    while(1)
    {
        if(!is_playing or is_pause )
        {
            SDL_Delay(200);
            continue;
        }
        if(_sync)continue;

        interface = GAME;
        update();
        move(T, level.player);
        move(TT, level.player2);

        if(automatique)
            directSnubby(TT, level.player2);
        

        check_status_of_playing();
        check_status_of_playing2();

        if( level.n_coins == level.virtuals)
        {
            if(!is_online_game)
            {
                if(level.c1 >= level.c2)
                    local_win(true);
                else
                    local_win(false);
            }

        }
        SDL_Delay(13);

    }

}
bool win;

void local_win(bool wi)
{
    cout << "You win  .." << endl;
    is_pause = 1;
    is_playing = 0;
    win = wi;
    interface = LOCAL_WIN;

    while(is_pause)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            coin_sound();
            // restart button
            if(WIN_LOSE_button_x <= x && x <= WIN_LOSE_button_x + WIN_LOSE_button_width &&
                    WIN_LOSE_restart_y <= y && y <= WIN_LOSE_restart_y + WIN_LOSE_button_height)
            {
                cout << "RESTART" << endl;
                load_level(l);
                is_playing = 1;
                is_pause = 0;
            }

            // levels button
            if(WIN_LOSE_button_x <= x && x <= WIN_LOSE_button_x + WIN_LOSE_button_width &&
                    WIN_LOSE_levels_y <= y && y <= WIN_LOSE_levels_y + WIN_LOSE_button_height)
            {
                cout << "LEVELS" << endl;
                is_pause = 0;
                l = get_level();
                if( l != -1)
                {
                    load_level(l);
                    is_playing = 1;
                }
            }
            // Quit button
            if(WIN_LOSE_button_x <= x && x <= WIN_LOSE_button_x + WIN_LOSE_button_width &&
                    WIN_LOSE_quit_y <= y && y <= WIN_LOSE_quit_y + WIN_LOSE_button_height)
            {
                cout << "QUIT" << endl;
                is_pause = 0;
                index();
            }

            // Previous button
            if(WIN_LOSE_previous_x <= x && x <= WIN_LOSE_previous_x + WIN_LOSE_button_width &&
                    WIN_LOSE_prev_next_y <= y && y <= WIN_LOSE_prev_next_y + WIN_LOSE_button_height)
            {
                l--;
                if(l == 0)l = N_LEVELS;
                cout << "Level " << l << endl;
                load_level(l);
                is_playing = 1;
                is_pause = 0;
                cout << "Previous" << endl;
            }

            // Next button
            if(WIN_LOSE_next_x <= x && x <= WIN_LOSE_next_x + WIN_LOSE_button_width &&
                    WIN_LOSE_prev_next_y <= y && y <= WIN_LOSE_prev_next_y + WIN_LOSE_button_height)
            {
                l++;
                if(l == N_LEVELS + 1)l = 1;
                cout << "Level " << l << endl;
                load_level(l);
                is_playing = 1;
                is_pause = 0;
                cout << "NEXT" << endl;
            }
            break;
        case SDL_QUIT:
            free_memory();

        }
    }
}


void free_memory()
{
    is_playing = 0;
    SDL_RenderCopy(render, texture_wait, NULL, NULL);
    SDL_RenderPresent(render);
    cout << "libérer la mémoire ..." << endl;
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(textureEnemy);
    for (int i = 0; i < 10; i++) SDL_DestroyTexture(textures[i]);
    for (int i = 0; i < 20; i++) SDL_DestroyTexture(textureSlides[i]);
    SDL_DestroyTexture(textureCoin);
    SDL_FreeSurface(s);
    for (int i = 0; i < 10; i++)SDL_FreeSurface(ss[i]);
    SDL_DestroyTexture(texture_wait);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(1);
}

inline void renderPause_win_lose(SDL_Renderer *render, bool win)
{

    static SDL_Texture *WIN_LOSE_image_WIN =  IMG_LoadTexture(render, "../images/you win.png" );
    static SDL_Texture *WIN_LOSE_image_LOSE =  IMG_LoadTexture(render, "../images/you lose.png" );
    static SDL_Texture *WIN_LOSE_restart =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/restart.png"));
    static SDL_Texture *WIN_LOSE_levels =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/levels.png"));
    static SDL_Texture *WIN_LOSE_quit =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/quit.png"));
    static SDL_Texture *WIN_LOSE_previous =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/previous.png"));
    static SDL_Texture *WIN_LOSE_next =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/next.png"));

    SDL_SetRenderDrawColor(render, 0, 0, 0, 180);
    SDL_RenderFillRect(render, NULL);

    /////////////////////////////
    SDL_Rect rect;
    if(automatique || offline)
    {
        rect = {WIN_LOSE_image_x - ( WIN_LOSE_image_width / 2 + 50), WIN_LOSE_image_y, WIN_LOSE_image_width, WIN_LOSE_image_height};
        if(win)
            SDL_RenderCopy(render, WIN_LOSE_image_WIN, NULL, &rect);
        else
            SDL_RenderCopy(render, WIN_LOSE_image_LOSE, NULL, &rect);
        rect.y += rect.h;
        rect.h = 70;
        draw_text("Player 1", rect.x, rect.y, rect.w, rect.h);
        //////////////////////////////////////////
        rect = {WIN_LOSE_image_x + ( WIN_LOSE_image_width / 2 + 50), WIN_LOSE_image_y, WIN_LOSE_image_width, WIN_LOSE_image_height};
        if(!win)
            SDL_RenderCopy(render, WIN_LOSE_image_WIN, NULL, &rect);
        else
            SDL_RenderCopy(render, WIN_LOSE_image_LOSE, NULL, &rect);
        rect.y += rect.h;
        rect.h = 70;
        if( automatique)
            draw_text("Computer", rect.x + 30, rect.y, rect.w, rect.h);
        else
            draw_text("Player 2", rect.x + 30, rect.y, rect.w, rect.h);
    }
    else
    {
        rect = {WIN_LOSE_image_x, WIN_LOSE_image_y, WIN_LOSE_image_width, WIN_LOSE_image_height};
        if(win)
            SDL_RenderCopy(render, WIN_LOSE_image_WIN, NULL, &rect);
        else
            SDL_RenderCopy(render, WIN_LOSE_image_LOSE, NULL, &rect);
    }




    rect = {WIN_LOSE_button_x, WIN_LOSE_restart_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
    SDL_RenderCopy(render, WIN_LOSE_restart, NULL, &rect);

    rect = {WIN_LOSE_button_x, WIN_LOSE_levels_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
    SDL_RenderCopy(render, WIN_LOSE_levels, NULL, &rect);

    rect = {WIN_LOSE_button_x, WIN_LOSE_quit_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
    SDL_RenderCopy(render, WIN_LOSE_quit, NULL, &rect);

    rect = {WIN_LOSE_previous_x, WIN_LOSE_prev_next_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
    SDL_RenderCopy(render, WIN_LOSE_previous, NULL, &rect);

    rect = {WIN_LOSE_next_x, WIN_LOSE_prev_next_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
    SDL_RenderCopy(render, WIN_LOSE_next, NULL, &rect);

    // SDL_SetRenderDrawColor(render, 0, 0, 0, 170);
    // SDL_RenderFillRect(render, &rect);
}
#define GAME_pause_x 10
#define GAME_pause_y 10
#define GAME_pause_width 120
#define GAME_pause_height 50

void draw_text(char const *t, int x, int y, int w, int h)
{
    rect = {  x, y, w, h};
    s = TTF_RenderText_Solid(font, t, {0, 0, 0, 0});
    texture = SDL_CreateTextureFromSurface(render, s);
    SDL_RenderCopy(render, texture, NULL, &rect);
}


void draw_wall()
{
    SDL_SetRenderDrawColor(render, 181, 181, 253.98, 255);
    SDL_RenderFillRect(render, NULL );
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            if(level.map[i][j] == -1)continue;
            rect = {cx + j *size_squar - 5, cy + i *size_squar - 5, size_squar + 10, size_squar + 10};
            SDL_RenderFillRect(render, &rect );
        }
    }
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            if(level.map[i][j] == 1)       SDL_SetRenderDrawColor(render, 248.11499999999998, 247.095, 253.98, 255);
            else if(level.map[i][j] == 2)  SDL_SetRenderDrawColor(render, 230.01000000000002, 230.01000000000002, 255, 255);
            else if(level.map[i][j] == 0 or level.map[i][j] == 5)  SDL_SetRenderDrawColor(render, 182.07, 255, 181.04999999999998, 255);
            else continue;
            rect = {cx + j * size_squar, cy + i * size_squar, size_squar, size_squar};
            SDL_RenderFillRect(render, &rect );
        }
    }
}
//affiche les obstacles
void draw_enemys()
{
    for(auto e : level.get_enemys())
    {
        rect = {e.first - level.w_enemy / 2, e.second - level.w_enemy / 2, level.w_enemy, level.w_enemy};
        SDL_RenderCopy(render, textureEnemy, NULL, &rect);
    }
}
//affiche tout le jeux
void draw_game()
{
    draw_wall();
    if(!automatique)
    {
        if(is_online_game)
        {
            rect = {-level.player.w / 2  + player2.first, -level.player.h / 2 + player2.second, level.player.w, level.player.h};
            SDL_RenderCopy(render, texturePlayer2, NULL, &rect);
        }
        rect = {-level.player.w / 2  + level.player.x, -level.player.h / 2 + level.player.y, level.player.w, level.player.h};
        SDL_RenderCopy(render, texturePlayer, NULL, &rect);
    }
    else
    {
        for(auto sn : level.Snubbys)
        {

            if(!sn.is_a_life)   continue;
            rect = {-level.player.w / 2  + sn.x, -level.player.h / 2 + sn.y, level.player.w, level.player.h};
            SDL_RenderCopy(render, texturePlayer, NULL, &rect);
        }
    }
    for(auto e : level.coins)
    {
        if(e.is_taked)continue;
        rect = {e.x - e.w / 2, e.y - e.h / 2, e.w, e.h};
        SDL_RenderCopy(render, textureCoin, NULL, &rect);
    }
    draw_enemys();
    if(!is_pause and is_playing)
    {
        rect = {0, 0, 400, 100};
        SDL_RenderCopy(render, textureSlides[7], NULL, &rect);
    }
    if(automatique)
    {
        rect = {1024 - 400, 0, 400, 100};
        SDL_RenderCopy(render, textureSlides[11], NULL, &rect);

    }

    // Pause Button:
    rect = {GAME_pause_x, GAME_pause_y, GAME_pause_width, GAME_pause_height};
    static SDL_Texture *GAME_pause = SDL_CreateTextureFromSurface(render, IMG_Load("../images/pause.png"));
    SDL_RenderCopy(render, GAME_pause, NULL, &rect);
}


void show()
{
    SDL_RenderPresent(render);
    SDL_Delay(30);
}


void draw_levels()
{
    SDL_RenderClear(render);
    SDL_RenderCopy(render, textures[0], NULL, NULL);
    static SDL_Texture *LEVEL_share = SDL_CreateTextureFromSurface(render, IMG_Load("../images/share.png"));
    static SDL_Texture *LEVEL_download = SDL_CreateTextureFromSurface(render, IMG_Load("../images/download.png"));
    for(int i, j, k = 1; k < N_LEVELS + 1; k++)
    {
        j = (k - 1) / LEVEL_level_row;
        i = (k - 1) % LEVEL_level_row;
        rect = {LEVEL_level_margin *(i + 1) + i * LEVEL_level_width,
                LEVEL_level_margin *(j + 1) + j *LEVEL_level_height - y, LEVEL_level_width, LEVEL_level_height
               } ;
        SDL_RenderCopy(render, textures[k], NULL, &rect);

        if(k > N_OPEN_LEVEL/* and mode == "1OFF"*/)
        {
            SDL_SetRenderDrawColor(render, 0, 0, 0, 200);
            SDL_RenderFillRect(render, &rect);
        }
        //send to server
        rect.w = LEVEL_share_width;
        rect.h = LEVEL_share_height;
        rect.x += LEVEL_share_x;
        rect.y += LEVEL_share_y;
        SDL_RenderCopy(render, LEVEL_share, NULL, &rect);
    }
    //upload new level
    int i, j, k = N_LEVELS + 1;
    j = (k - 1) / LEVEL_level_row;
    i = (k - 1) % LEVEL_level_row;
    rect = {LEVEL_level_margin *(i + 1) + i * LEVEL_level_width,
            LEVEL_level_margin *(j + 1) + j *LEVEL_level_height - y, LEVEL_level_width, LEVEL_level_height
           } ;

    SDL_RenderCopy(render, LEVEL_download, NULL, &rect);

    SDL_RenderPresent(render);
    SDL_Delay(4);
}
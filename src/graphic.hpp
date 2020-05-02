

class Graphic
{

public:
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Rect rect;
    SDL_Surface *s, *ss[10];
    SDL_Texture *texture, *texturePlayer, *textureEnemy, *textures[10], *textureCoin, *textureSlides[20];
    Level  *level;
    int continuer = 1, on = 0, p;
    SDL_Event event, event_quit;
    int x, y, xx, yy, cx = 100, cy = 100, size_squar = 40, b;
    bool is_playing = 0, is_pause = 0, is_index = 0, automatique = AUTO, is_thinking = 0;
    TTF_Font *font;
    bool runNext = 0;
    int N_LEVELS = 0;




    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 *wav_buffer;
    SDL_AudioDeviceID device_coin, device_enemy;
    int result = 0;
    int flags = MIX_INIT_MP3;
    Mix_Music *music;



    Graphic(Level *l)
    {
        level = l;
    }
    void get_online_player();
    void online();
    void help(char *path);
    void get_level();
    void create_level();
    void init();
    void draw_wall();
    void get_wall();
    void get_goal_area();
    void draw_enemys();
    void draw_game();
    void get_position_player();
    void add_coin();
    void add_spiral_dot();
    bool check_it_not_black_area(int x, int y);
    void control();
    void update();
    void index();
    void check_state();
    void play();
    void show();
    void pause();
    void draw_levels();
    void free_memory();
    void screenshot();
    void add_linear_enemy();
    void load_level(int k);
    void save_level();
    void screen_level();
    bool is_player_inside_after(int x, int y);
    void save_n()
    {

        std::ofstream ofs("../levels/N_L");
        boost::archive::text_oarchive ar(ofs);
        ar &N_LEVELS;
    }
    void load_n()
    {

        std::ifstream ifs("../levels/N_L");
        boost::archive::text_iarchive ar(ifs);

        ar &N_LEVELS;
    }

    void text(char *t, int x, int y, int w, int h)
    {
        rect = {  x, y, w, h};

        s = TTF_RenderText_Solid(font, t, {0, 0, 0, 0});
        texture = SDL_CreateTextureFromSurface(render, s);
        SDL_RenderCopy(render, texture, NULL, &rect);
    }
    void coin_sound()
    {
        SDL_QueueAudio(device_coin, wav_buffer, wav_length);
        SDL_PauseAudioDevice(device_coin, 0);
    }

    void hit_sound()
    {
        SDL_QueueAudio(device_enemy, wav_buffer, wav_length);
        SDL_PauseAudioDevice(device_enemy, 0);
    }

};
void Graphic::init()
{
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow("Snubby Land", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 668, SDL_WINDOW_OPENGL);
    render = SDL_CreateRenderer(window, -1, 0);

    if (!TTF_Init())
    {
        font = TTF_OpenFont("../images/FreeSans.ttf", 24);
    }

    /////////////Sound

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("Failed to init SDL\n");
        exit(1);
    }

    if (flags != (result = Mix_Init(flags)))
    {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    music = Mix_LoadMUS("../sound/background.mp3");
    Mix_PlayMusic(music, 1);

    SDL_LoadWAV("../sound/coin.wav", &wav_spec, &wav_buffer, &wav_length);
    device_coin = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);

    SDL_LoadWAV("../sound/hit.wav", &wav_spec, &wav_buffer, &wav_length);
    device_enemy = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);





    textureEnemy = SDL_CreateTextureFromSurface(render, IMG_Load("../images/enemy.png"));
    textures[0] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/level.png"));
    string zzz;
    load_n();
    for(int i = 0; i < N_LEVELS + 1; i++)
    {
        zzz = "../levels/" + to_string(i + 1) + ".png";
        textures[i + 1] = SDL_CreateTextureFromSurface(render, IMG_Load(zzz.c_str()));
    }

    textureCoin = SDL_CreateTextureFromSurface(render, IMG_Load("../images/coin.png"));

    textureSlides[0] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/index.png"));
    textureSlides[1] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/black_area.png"));
    textureSlides[2] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/coin_slide.png"));
    textureSlides[3] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/player_slide.png"));
    textureSlides[4] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/green_area.png"));
    textureSlides[5] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/spiral.png"));
    textureSlides[6] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/playing_slide.png"));
    textureSlides[7] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/pause_slide.png"));


    texturePlayer = SDL_CreateTextureFromSurface(render, IMG_Load("../images/player.png"));


}

void Graphic::index()
{
    rect = {0, 0, 1024, 200};
    SDL_RenderCopy(render, textureSlides[0], NULL, &rect);
    SDL_RenderPresent(render);
    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);


        switch (event.type)
        {

        case SDL_QUIT:
            free_memory();
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_p:
                get_level();
                break;
            case SDLK_c:
                create_level();
            }
        }


    }
}
void Graphic::draw_wall()
{
    SDL_SetRenderDrawColor(render, 181, 181, 253.98, 255);
    SDL_RenderFillRect(render, NULL );

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            if(level->map[i][j] == -1)continue;
            rect = {cx + j *size_squar - 5, cy + i *size_squar - 5, size_squar + 10, size_squar + 10};
            SDL_RenderFillRect(render, &rect );
        }
    }

    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            if(level->map[i][j] == 1)       SDL_SetRenderDrawColor(render, 248.11499999999998, 247.095, 253.98, 255);
            else if(level->map[i][j] == 2)  SDL_SetRenderDrawColor(render, 230.01000000000002, 230.01000000000002, 255, 255);
            else if(level->map[i][j] == 0 or level->map[i][j] == 5)  SDL_SetRenderDrawColor(render, 182.07, 255, 181.04999999999998, 255);
            else continue;
            rect = {cx + j * size_squar, cy + i * size_squar, size_squar, size_squar};
            SDL_RenderFillRect(render, &rect );
        }
    }
}

void Graphic::draw_enemys()
{

    for(auto e : level->get_enemys())
    {
        rect = {e.first - level->w_enemy / 2, e.second - level->w_enemy / 2, level->w_enemy, level->w_enemy};
        SDL_RenderCopy(render, textureEnemy, NULL, &rect);
    }


}
void Graphic::draw_game()
{

    draw_wall();
    if(!automatique)
    {


        rect = {-level->player.w / 2  + level->player.x, -level->player.h / 2 + level->player.y, level->player.w, level->player.h};

        SDL_RenderCopy(render, texturePlayer, NULL, &rect);

    }
    else
    {
        for(auto sn : level->Snubbys)
        {
            if(!sn.is_a_life)   continue;

            rect = {-level->player.w / 2  + sn.x, -level->player.h / 2 + sn.y, level->player.w, level->player.h};

            SDL_RenderCopy(render, texturePlayer, NULL, &rect);


        }

        text("B", level->B.first,  level->B.second, 40, 40);
        text("A", level->A.first, level->A.second, 40, 40);
    }

    for(auto e : level->coins)
    {
        if(e.is_taked)continue;
        rect = {e.x - e.w / 2, e.y - e.h / 2, e.w, e.h};
        SDL_RenderCopy(render, textureCoin, NULL, &rect);
    }
    draw_enemys();

}
void Graphic::get_wall()
{

    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[1], NULL, &rect);
    SDL_RenderPresent(render);

    on = 0;
    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        xx = x;
        yy = y;
        x = event.motion.x;
        y = event.motion.y;

        if(x != xx and y != yy and x >= cx and y >= cy and x < cx + 20 * size_squar and y < cy + 20 * size_squar and on)
        {
            level->map[(int)((y - cx) / size_squar)][(int)((x - cy) / size_squar)] = -1;
            draw_wall();


            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[1], NULL, &rect);

            SDL_RenderPresent(render);
            SDL_Delay(5);
        }
        switch (event.type)
        {

        case SDL_QUIT:
            free_memory();
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
                on = 1 - on;
                break;
            case SDLK_s:
                on = 0;
                break;
            case SDLK_r:
                on = 1;
            case SDLK_n:
                continuer = 0;
                break;
            case SDLK_g:
                level->random_map();
                draw_wall();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[1], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            }
        }
    }
}




void Graphic::get_goal_area()
{
    draw_wall();
    int g = 0;

    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[4], NULL, &rect);

    SDL_RenderPresent(render);
    SDL_Delay(5);

    on = 0;
    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        xx = x;
        yy = y;
        x = event.motion.x;
        y = event.motion.y;

        if(x != xx and y != yy and x >= cx and y >= cy and x < cx + 20 * size_squar and y < cy + 20 * size_squar and on)
        {
            level->map[(int)((y - cx) / size_squar)][(int)((x - cx) / size_squar)] = g;
            draw_wall();

            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[4], NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(5);
        }
        switch (event.type)
        {
        case SDL_QUIT:
            free_memory();
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_s:
                on = 0;
                break;
            case SDLK_a:
                on = 1;
                g = 0;
                break;
            case SDLK_g :
                on = 1;
                g = 5;
                break;
            case SDLK_n:
                continuer = 0;
                break;
            case SDLK_b:

                break;
            }
        }
    }

}


void Graphic::get_position_player()
{

    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[3], NULL, &rect);
    SDL_RenderPresent(render);

    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            free_memory();
            break;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            level->player.x = cx + 40 * (int)(( x - cx) / 40 ) + level->player.w / 2;
            level->player.y = cy + 40 * (int)(((y - cy) / 40)) + level->player.h / 2;

            draw_game();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[3], NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(40);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {

            case SDLK_n:
                continuer = 0;
                break;
            }


        }
    }
}

void Graphic::add_coin()
{

    draw_game();


    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
    SDL_RenderPresent(render);
    SDL_Delay(10);

    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            free_memory();
            break;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            level->coins.push_back(Coin(10 * (int)(x / 10), 10 * (int)(y / 10)));
            draw_game();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(40);
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                level->coins.pop_back();

                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(40);


                break;
            case SDLK_n:
                continuer = 0;
                break;
            }

        }


    }
}



// void Graphic::add_stable_enemys()
// {
//     cout<<"stable enemys"<<endl;
//     draw_game();


//     rect = {0, 100 + 40 * 12, 1024, 100} ;
//     SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
//     SDL_RenderPresent(render);
//     SDL_Delay(10);

//     continuer = 1;
//     while(continuer)
//     {
//         SDL_WaitEvent(&event);
//         switch (event.type)
//         {
//         case SDL_QUIT:
//             free_memory();
//             break;
//         case SDL_MOUSEBUTTONDOWN:
//             x = event.motion.x;
//             y = event.motion.y;
//             level->stable_enemys.push_back(Coin(10 * (int)(x / 10), 10 * (int)(y / 10)));
//             draw_game();
//             rect = {0, 100 + 40 * 12, 1024, 100} ;
//             SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
//             SDL_RenderPresent(render);
//             SDL_Delay(40);
//             break;

//         case SDL_KEYDOWN:
//             switch (event.key.keysym.sym)
//             {
//             case SDLK_LEFT:
//                 level->coins.pop_back();

//                 draw_game();
//                 rect = {0, 100 + 40 * 12, 1024, 100} ;
//                 SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
//                 SDL_RenderPresent(render);
//                 SDL_Delay(40);


//                 break;
//             case SDLK_n:
//                 continuer = 0;
//                 break;
//             }

//         }


//     }
// }
void Graphic::add_spiral_dot()
{
    draw_game();

    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[5], NULL, &rect);

    SDL_RenderPresent(render);
    SDL_Delay(500);

    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            free_memory();
            break;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            level->spiral_dots.push_back(Spiral_dot(make_pair(x, y), 5, 100));
            draw_game();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(5);

            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {

            case SDLK_LEFT:
                // level->spiral_dots.pop_back();
                // draw_game();
                level->spiral_dots[level->spiral_dots.size() - 1].R -= 5;
                level->spiral_dots[level->spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_RIGHT:
                level->spiral_dots[level->spiral_dots.size() - 1].R += 5;
                level->spiral_dots[level->spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_UP:
                level->spiral_dots[level->spiral_dots.size() - 1].n++;
                level->spiral_dots[level->spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_DOWN:
                level->spiral_dots[level->spiral_dots.size() - 1].n--;
                level->spiral_dots[level->spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_n:
                continuer = 0;
                break;
            }

        }
        SDL_Delay(5);
    }

}



bool Graphic::check_it_not_black_area(int x, int y)
{

    if(

        (double)(y - cy - level->player.w / 2 ) / size_squar < 0 || (double)(y - cy -  level->player.w / 4 + level->player.w / 2) / size_squar >= 12 ||
        (double)(x - cx - level->player.w / 2 ) / size_squar < 0 || (double)(x - cx -  level->player.w / 4 + level->player.w / 2) / size_squar >= 20
    )
    {
        return 0;
    }

    return 1;
}


bool Graphic::is_player_inside_after(int x, int y)
{

    if(
        level->map[(int)((y - cy   ) / size_squar)][(int)((x - cx ) / size_squar)] == -1 ||
        level->map[(int)((y - cy  ) / size_squar)][(int)((x - cx ) / size_squar)] == -1 ||
        level->map[(int)((y - cy  ) / size_squar)][(int)((x - cx ) / size_squar)] == -1 ||
        level->map[(int)((y - cy ) / size_squar)][(int)((x - cx ) / size_squar)] == -1
    )
    {
        return 0;
    }

    return 1;
}



void Graphic::control()
{
    continuer = 1;
    while(1)
    {
        if(!is_playing)
        {
            SDL_Delay(10);
            continue;
        }
        SDL_WaitEvent(&event);

        switch (event.type)
        {

        case SDL_QUIT:
            free_memory();
            break;

        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;

            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                if(check_it_not_black_area(level->player.x - 10, level->player.y) && is_player_inside_after(level->player.x - 20, level->player.y))
                    level->player.x -= 10;
                break;
            case SDLK_UP:
                if(check_it_not_black_area(level->player.x, level->player.y - 10 ) && is_player_inside_after(level->player.x, level->player.y - 20))
                    level->player.y -= 10;
                break;
            case SDLK_RIGHT:
                if(check_it_not_black_area(level->player.x + 10, level->player.y) && is_player_inside_after(level->player.x + 20, level->player.y))
                    level->player.x += 10;
                break;
            case SDLK_DOWN:
                if(check_it_not_black_area(level->player.x, level->player.y + 10) && is_player_inside_after(level->player.x, level->player.y + 20))
                    level->player.y += 10;
                break;
            case SDLK_p:
                pause();
                break;
            case SDLK_h:
                continuer = 0;
                is_index = 1;
                break;

            case SDLK_n:
                runNext = 1;
                break;
            case SDLK_a:
                level->A = make_pair(x, y);
                break;
            case SDLK_b:
                level->B = make_pair(x, y);
                break;
            case SDLK_f:
                for(auto sn : level->Snubbys)cout << sn.fitness << " ";
                cout << endl;
                break;
            case SDLK_d:
                break;
            case SDLK_m:
                for(auto &sn : level->Snubbys)
                {
                    if(!sn.is_a_life)
                    {
                        sn.brain.mutate();
                    }
                    sn.is_a_life = 1;
                };
                break;
            case SDLK_g:
                automatique = 1 - automatique;

                if(automatique)

                {
                    for(auto &sn : level->Snubbys)
                    {
                        sn.brain.init_params(NN);
                        sn.x = level->A.first;
                        sn.y =  level->A.second;
                        sn.is_a_life = 1;
                    };
                    level->generation++;
                }

                break;
                //  case SDLK_e:
                // level->test();
                //  break;
            }


        }
        if(level->map[(int)((level->player.y - cx) / size_squar)][(int)((level->player.x - cy) / size_squar)] == 0)level->last_touch_on_green_area = make_pair(level->player.x, level->player.y);
        SDL_Delay(10);
    }
}

void Graphic::update()
{

    if(runNext)
    {
        level->next_generation();
        runNext = 0;
    }
    for(auto &sp : level->spiral_dots)sp.next_move();
    for(auto &e : level->linear_enemys)e.next_move();
    if(automatique)
    {
        for(auto &p : level->Snubbys)
        {
            if(p.is_a_life)
                p.think(level, this);
        }
    }

}



void Graphic::check_state()
{
    for(auto &c : level->coins)
    {
        if(!c.is_taked && c.take(level->player))coin_sound();
    }
    for(auto e : level->get_enemys())
    {
        if(level->player.touche_enemy(e, level->w_enemy / 2))
        {
            hit_sound();
            level->player.x = level->last_touch_on_green_area.first;
            level->player.y = level->last_touch_on_green_area.second;

        };
        if(automatique)
        {
            for(auto &sn : level->Snubbys)
            {
                if(!sn.is_a_life)continue;
                if(sn.touche_enemy(e, level->w_enemy / 2))
                {
                    sn.is_a_life = 0;
                    level->N_Snubbys_a_life--;
                };
            }
        }
    }

    if(level->N_Snubbys_a_life <= 0)
    {
        level->next_generation();
        level->generation++;

        for(auto &sn : level->Snubbys)
        {
            sn.x = level->A.first;
            sn.y = level->A.second;
        }
    }
}

void Graphic::play()
{
    level->get_enemys();
    level->player.update_input(level);
    level->update_population();

    is_playing = 1;
    continuer = 1;
    while(continuer and is_playing)
    {
        if(is_pause)
        {
            SDL_Delay(40);
            continue;
        }


        update();
        check_state();
        draw_game();

        rect = {0, 100 + 40 * 12, 1024, 100} ;
        SDL_RenderCopy(render, textureSlides[6], NULL, &rect);
        show();

        SDL_Delay(20);
    }
    if(is_index)
    {
        is_index = 0;
        return index();
    }
}

void Graphic::show()
{
    SDL_RenderPresent(render);
    SDL_Delay(40);

}
void Graphic::create_level()
{

    N_LEVELS++;

    draw_wall();
    SDL_RenderPresent(render);
    SDL_Delay(5);

WALL:
    get_wall();

GREEN:
    get_goal_area();

COIN:
    add_coin();

SPIRAL:
    add_spiral_dot();

LINEAR:
    add_linear_enemy();

POSITION:
    get_position_player();

    screen_level();
    save_level();
    save_n();
    play();
}


void Graphic::pause()
{
    is_pause = 1;

    rect = {0, 0, 1024, 200} ;
    SDL_RenderCopy(render, textureSlides[7], NULL, &rect);
    show();


    while(is_pause)
    {

        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            free_memory();
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {

            case SDLK_p:
                is_pause = 0;
                break;
            case SDLK_s:
                level->save_population();
                cout << "save_population" << endl;

                break;
            case SDLK_l:
                level->load_population();
                cout << "load_population" << endl;
                break;
            }
        }
        SDL_Delay(10);
    }
}

void Graphic::draw_levels()
{

    rect = {0, y, 1024, 3000} ;
    SDL_RenderCopy(render, textures[0], NULL, &rect);


    for(int i, j, k = 1; k < N_LEVELS + 1; k++)
    {
        j = (k - 1) / 3;
        i = (k - 1) - j * 3;

        rect = {40 * (i + 1) + i * 288 + 5, y + 40 * (j + 1) + j * 150 + 5, 288 - 10, 150 - 10} ;
        SDL_RenderCopy(render, textures[k], NULL, &rect);


    }


    SDL_RenderPresent(render);
    SDL_Delay(4);

}



void Graphic::free_memory()
{

    SDL_Quit();
    Mix_FreeMusic(music);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(textureEnemy);
    for (int i = 0; i < 10; i++) SDL_DestroyTexture(textures[i]);
    for (int i = 0; i < 20; i++) SDL_DestroyTexture(textureSlides[i]);
    SDL_DestroyTexture(textureCoin);
    SDL_FreeSurface(s);
    for (int i = 0; i < 10; i++)SDL_FreeSurface(ss[i]);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    exit(0);
}


void Graphic::help(char *path)
{
    is_pause = 1;
    s = IMG_Load(path);
    texture = SDL_CreateTextureFromSurface(render, s);
    rect = {50, 50, 1024 - 50, 768 - 50} ;
    SDL_RenderCopy(render, texture, NULL, &rect);
    show();


    while(is_pause)
    {
        SDL_WaitEvent(&event_quit);
        switch (event_quit.type)
        {
        case SDL_QUIT:
            free_memory();
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_p:
                is_pause = 0;
                break;

            }
        }
        SDL_Delay(50);
    }
}
void Graphic::get_level()
{


    draw_levels();

    y = 0;
    while(1)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            b = event.motion.y;

            // coin_sound();

            for(int i, j, k = 1; k < N_LEVELS + 1; k++)
            {
                j = (k - 1) / 3;
                i = (k - 1) - j * 3;

                rect = {40 * (i + 1) + i * 288 + 5, y + 40 * (j + 1) + j * 150 + 5, 288 - 10, 150 - 10} ;

                if( x > rect.x and x < rect.x + rect.w and b - y > rect.y and b - y < rect.y + rect.h )
                {
                    load_level(k);
                    play();
                    break;
                }

            }
            break;

        case SDL_MOUSEWHEEL:
            if(event.wheel.y >= 0)
                y -= 10;
            else y += 10;
            draw_levels();
            break;

        case SDL_QUIT:
            free_memory();
            break;
        }
    }
}



void Graphic::screenshot()
{

    int width = 1024, height = 768;
    s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(render, NULL, s->format->format, s->pixels, s->pitch);
    IMG_SavePNG(s, "s.png");

}

void Graphic::screen_level()
{

    int width = 1024, height = 768;
    s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(render, NULL, s->format->format, s->pixels, s->pitch);
    string z = "../levels/" + to_string(N_LEVELS) + ".png";
    IMG_SavePNG(s, z.c_str());

}

void Graphic::add_linear_enemy()
{
    draw_game();

    texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/linear_enemy.png"));
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, texture, NULL, &rect);
    pair<int, int> A, B;
    SDL_RenderPresent(render);
    SDL_Delay(5);

    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            free_memory();
            break;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            draw_game();
            texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/linear_enemy.png"));
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, texture, NULL, &rect);

            rect = {-level->player.w / 2  + x, -level->player.h / 2 + y, level->player.w, level->player.h};
            SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
            SDL_RenderFillRect(render, &rect );


            SDL_RenderPresent(render);
            SDL_Delay(5);

            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {

            case SDLK_n:
                continuer = 0;
                break;
            case SDLK_KP_1:
                A = make_pair(x, y);

                draw_game();
                texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/linear_slide.png"));
                rect = {100, 0, 400, 100} ;
                SDL_RenderCopy(render, texture, NULL, &rect);


                rect = {-level->player.w / 2  + A.first, -level->player.h / 2 + B.second, level->player.w, level->player.h};
                SDL_RenderCopy(render, textureEnemy, NULL, &rect);

                SDL_RenderPresent(render);
                SDL_Delay(5);

                break;
            case SDLK_KP_2:
                B = make_pair(x, y);

                draw_game();
                texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/linear_slide.png"));
                rect = {100, 0, 400, 100} ;
                SDL_RenderCopy(render, texture, NULL, &rect);



                rect = {-level->player.w / 2  + B.first, -level->player.h / 2 + B.second, level->player.w, level->player.h};
                SDL_RenderCopy(render, textureEnemy, NULL, &rect);

                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_KP_3:
                level->linear_enemys.push_back(Linear_enemy(A, B));

                draw_game();
                texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/linear_slide.png"));
                rect = {100, 0, 400, 100} ;
                SDL_RenderCopy(render, texture, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            }

        }
        SDL_Delay(5);
    }

}

void Graphic::save_level()
{

    std::ofstream ofs( "../levels/" + to_string(N_LEVELS));
    boost::archive::text_oarchive ar(ofs);
    ar &level;
}
void Graphic::load_level(int k)
{

    std::ifstream ifs("../levels/" + to_string(k));
    boost::archive::text_iarchive ar(ifs);

    ar &level;
}





void Player::think(Level *level, Graphic *g)
{

    update_input(level);

    vector<double> r = brain.predict( input);

    if(r[0] == max(r[0], max(r[1], max(r[2], r[3]))) && g->check_it_not_black_area(x, y - 10) &&
            g->is_player_inside_after(x, y - 20)
      )y -= 10; //up
    else if(r[1] == max(r[0], max(r[1], max(r[2], r[3]))) && g->check_it_not_black_area(x, y + 10) &&
            g->is_player_inside_after(x, y + 20)
           )y += 10; //down
    else if(r[2] == max(r[0], max(r[1], max(r[2], r[3]))) && g->check_it_not_black_area(x + 10, y) &&
            g->is_player_inside_after(x + 20, y)
           )x += 10; //R
    else if(r[3] == max(r[0], max(r[1], max(r[2], r[3]))) && g->check_it_not_black_area(x - 10, y) &&
            g->is_player_inside_after(x - 20, y)
           )x -= 10;; //L

}


void Graphic::get_online_player()
{
    http::Request request("http://horusnews.herokuapp.com/snubbyland_ensias_projet");
    std::map<std::string, std::string> parameters = {{"foo", "1"}, {"bar", "baz"}};
    const http::Response response = request.send("POST", parameters,
    {
        "Content-Type: application/x-www-form-urlencoded"
    });
    std::cout << std::string(response.body.begin(), response.body.end()) << '\n';

}


void Graphic::online()
{
    continuer = 1;
    while(1)
    {
        try
        {
            get_online_player();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Request failed, error: " << e.what() << '\n';
        }
    }

}
class Game
{
public:
    //SDL
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Rect rect;
    SDL_Surface *s, *ss[10];
    SDL_Texture *texture, *texturePlayer2, *texture_wait, *texturePlayer, *textureEnemy, *textures[10], *textureCoin, *textureSlides[20];    //les variable de jeux

    Level  *level;
    int l;//level
    int continuer = 1, on = 0, p;
    SDL_Event event, event_quit;
    int x, y, xx, yy, cx = 100, cy = 100, size_squar = 40, b;
    bool is_playing = 0, is_pause = 0, is_index = 0, automatique = AUTO, is_thinking = 0, status_thread_playing_online = 0;
    TTF_Font *font;
    bool run_next_generation = 0;
    int N_LEVELS = 0;
    bool  T[4] = {0, 0, 0, 0};
    //les variable de son
    SDL_AudioSpec wav_spec[2];
    Uint32 wav_length[2];
    Uint8 *wav_buffer[2];
    SDL_AudioDeviceID device_coin, device_enemy;
    //int result = 0;
    //int flags = MIX_INIT_MP3;
    //Mix_Music *music;

    //les variable de jeux online
    pair<int, int> player2;
    string id2, token;
    stringstream streams;
    string id;

    //les variable de l algorithm génétique
    pair<int, int> A, B;
    Game(Level *l)
    {
        level = l;
    }
    void init();// Initialise tous les variables de jeux
    void index();//c'est l'index de jeux : la page initial de choix
    //Pour la création de nouveau niveau
    void get_wall();//Créez une carte, par vous ou randomly
    void get_green_area();//Pour ajouter des espaces verts
    void get_position_player();//pour ajauter la position initial de joeur
    void add_coins();//pour ajouter les coins
    void add_spiral_dot();//pour ajauter les spiral dot
    void add_linear_enemy();//ajauter des obstacle lineare
    void add_squar_enemy();
    void add_big_spiral_dot();
    void create_level();//le cœur du creation de nouveau niveau
    //Pour le jeux
    bool check_it_free_area(int x, int y);//vérifier si une position est possible ( check_it_free_area & is_player_inside_after)
    bool is_player_inside_after(int x, int y);
    void control_event();//lorsque le jeux est commencé il change la position de jeux si l utilisateur click sur un botton (up/left/down/Right)
    void update();//Mise à jour du jeu
    void check_status_of_playing();//Vérifiez si le joueur a touché des ennemis ou a terminé toutes les coins
    void play();//le cœur du jeu
    void show();//claire
    void pause();//claire
    void draw_levels();//pour le choix de niveau
    void free_memory();//libérer la mémoire
    int get_level();//obtenir le id(1,2,3 ...) du niveau
    void screen_level();//enregistrer un image du niveau
    void save_level();//claire
    void load_level(int k);//claire

    void thread_playing_online();
    void thread_update_position();
    void draw_wall();//claire
    void draw_enemys();//claire
    void draw_game();//claire
    //Mémorisez le numéro de niveau
    void save_n()
    {
        std::ofstream ofs("../levels/n");
        boost::archive::text_oarchive ar(ofs);
        ar &N_LEVELS;
    }
    //Connaître le numéro du niveau
    void load_n()
    {
        std::ifstream ifs("../levels/n");
        boost::archive::text_iarchive ar(ifs);
        ar &N_LEVELS;
    }    void text(char *t, int x, int y, int w, int h)
    {
        rect = {  x, y, w, h};
        s = TTF_RenderText_Solid(font, t, {0, 0, 0, 0});
        texture = SDL_CreateTextureFromSurface(render, s);
        SDL_RenderCopy(render, texture, NULL, &rect);
    }
    void coin_sound()//claire
    {
        SDL_QueueAudio(device_coin, wav_buffer[1], wav_length[1]);
        SDL_PauseAudioDevice(device_coin, 0);
    }
    void hit_sound()//claire
    {
        SDL_QueueAudio(device_enemy, wav_buffer[0], wav_length[0]);
        SDL_PauseAudioDevice(device_enemy, 0);
    }
};
void Game::init()
{
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow("Snubby Land", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 668, SDL_WINDOW_OPENGL);
    render = SDL_CreateRenderer(window, -1, 0);
    textureSlides[0] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/index.png"));
    SDL_RenderCopy(render, textureSlides[0], NULL, NULL);
    SDL_RenderPresent(render);
    if (!TTF_Init())
    {
        font = TTF_OpenFont("../images/AMA.ttf", 50);
    }

    // if (flags != (result = Mix_Init(flags)))
    //  {
    //     printf("Could not initialize mixer (result: %d).\n", result);
    //     printf("Mix_Init: %s\n", Mix_GetError());
    //     exit(1);
    //  }    // Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    // music = Mix_LoadMUS("../sound/background.mp3");
    // Mix_PlayMusic(music, 1);    SDL_LoadWAV("../sound/hit.wav", &wav_spec[0], &wav_buffer[0], &wav_length[0]);
    device_enemy = SDL_OpenAudioDevice(NULL, 0, &wav_spec[0], NULL, 0);
    SDL_LoadWAV("../sound/coin.wav", &wav_spec[1], &wav_buffer[1], &wav_length[1]);
    device_coin = SDL_OpenAudioDevice(NULL, 0, &wav_spec[1], NULL, 0);
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
    textureSlides[1] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/black_area.png"));
    textureSlides[2] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/coin_slide.png"));
    textureSlides[3] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/player_slide.png"));
    textureSlides[4] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/green_area.png"));
    textureSlides[5] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/spiral.png"));
    textureSlides[6] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/playing_slide.png"));
    textureSlides[7] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/pause.png"));
    textureSlides[8] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/continue.png"));
    textureSlides[9] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/ga_continue.png"));

    texture_wait = SDL_CreateTextureFromSurface(render, IMG_Load("../images/wait.gif"));
    texturePlayer = SDL_CreateTextureFromSurface(render, IMG_Load("../images/player.png"));
    texturePlayer2 = SDL_CreateTextureFromSurface(render, IMG_Load("../images/play2.png"));
}
void Game::index()
{
    SDL_RenderCopy(render, textureSlides[0], NULL, NULL);
    SDL_RenderPresent(render);
    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            coin_sound();
            x = event.motion.x;
            y = event.motion.y;
            //ONE PLAYER OFFLIN
            if(x >= 156 and x <= 156 + 700 and y >= 210 and y <= 210 + 100)
            {
                get_level();
                play();
            }
            //TWO PLAYER thread_playing_online
            if(x >= 156 and x <= 156 + 700 and y >= 320 and y <= 420)
            {
                SDL_RenderCopy(render, texture_wait, NULL, NULL);
                SDL_RenderPresent(render);
                token = login(id);
                cout << "Your token  (clef secrète): " << token << endl;
                if(token.size() != TOKEN_SIZE)
                {
                    cout << "la demande de jouer  en ligne n'est pas valide, réessayez avec un autre id ." << endl;
                    break;
                }
                l = get_level();
                cout << "level : " << l << endl;
                if(token.size() != TOKEN_SIZE)
                {
                    break;
                }
                SDL_RenderCopy(render, texture_wait, NULL, NULL);
                SDL_RenderPresent(render);
                do
                {
                    cout << "demande de jouer en ligne ..." << endl;
                    id2 = find_player(id, l);
                    SDL_Delay(300);
                }
                while(id2.size() >= 50);
                cout << "id de la 2eme joeurs est " << id2 << endl;
                play();
            }
            //GENETIC ALGORITHM (n'est pas encore terminé)
            if(x >= 156 and x <= 156 + 700 and y >= 430 and y <= 430 + 100)
            {
                level->update_population();
                level->next_generation();
                automatique = 1;
                get_level();
                //Les joeurs sont en position inital A et leur objectif est d'atteindre la position B (la position de premier coins) todo(Le plus proche)
                level->A = make_pair(level->player.x, level->player.y);
                level->B = make_pair(level->coins[0].x, level->coins[0].y);
                play();
            }
            //CREATE NEW LEVEL
            if(x >= 156 and x <= 156 + 700 and y >= 540 and y <= 540 + 100)
            {
                create_level();
                cout << "le niveau créé avec succès" << endl;
                play();
            }
            break ;
        case SDL_QUIT:
            free_memory();
            break;
        }
    }
}
void Game::draw_wall()
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
//affiche les obstacles
void Game::draw_enemys()
{
    for(auto e : level->get_enemys())
    {
        rect = {e.first - level->w_enemy / 2, e.second - level->w_enemy / 2, level->w_enemy, level->w_enemy};
        SDL_RenderCopy(render, textureEnemy, NULL, &rect);
    }
}
//affiche tout le jeux
void Game::draw_game()
{
    draw_wall();
    if(!automatique)
    {
        rect = {-level->player.w / 2  + player2.first, -level->player.h / 2 + player2.second, level->player.w, level->player.h};
        SDL_RenderCopy(render, texturePlayer2, NULL, &rect);
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
    }
    for(auto e : level->coins)
    {
        if(e.is_taked)continue;
        rect = {e.x - e.w / 2, e.y - e.h / 2, e.w, e.h};
        SDL_RenderCopy(render, textureCoin, NULL, &rect);
    }
    draw_enemys();
    rect = {0, 0, 400, 100};
    SDL_RenderCopy(render, textureSlides[7], NULL, &rect);
}
//pour creer le tableau de map
void Game::get_wall()
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
void Game::get_green_area()
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
void Game::get_position_player()
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

void Game::add_coins()
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

void Game::add_spiral_dot()
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
            case SDLK_r:
                level->spiral_dots.pop_back();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            }
        }
        SDL_Delay(5);
    }
}

void Game::add_linear_enemy()
{
    draw_game();
    texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/linear_enemy.png"));
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, texture, NULL, &rect);

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
            case SDLK_r:
                level->linear_enemys.pop_back();
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

void Game::add_squar_enemy()
{

}
void Game::add_big_spiral_dot()
{

}
void Game::create_level()
{
    N_LEVELS++;
    // load_level(N_LEVELS);
    draw_wall();
    SDL_RenderPresent(render);
    SDL_Delay(5);
    cout << "wall ..." << endl;
WALL:
    get_wall();

    cout << "grean zone ..." << endl;
GREEN:
    get_green_area();

    cout << "coins ..." << endl;
COIN:
    add_coins();

    cout << "apirals ..." << endl;
SPIRAL:
    add_spiral_dot();
    cout << "";
BIG_SPIRAL:
    add_big_spiral_dot();

    cout << "linear enemy ..." << endl;
LINEAR:
    add_linear_enemy();
    cout << 5;
SQUAR:
    add_squar_enemy();

    cout << "initial position ..." << endl;

POSITION:
    get_position_player();
    cout << "screen ..." << endl;
    screen_level();
    cout << "save level ..." << endl;
    save_level();
    save_n();

}
bool Game::check_it_free_area(int x, int y)
{
    if(        (double)(y - cy - level->player.w / 2 ) / size_squar < 0 || (double)(y - cy -  level->player.w / 4 + level->player.w / 2) / size_squar >= 12 ||
               (double)(x - cx - level->player.w / 2 ) / size_squar < 0 || (double)(x - cx -  level->player.w / 4 + level->player.w / 2) / size_squar >= 20
      )
    {
        return 0;
    }
    return 1;
}
bool Game::is_player_inside_after(int x, int y)
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
void Game::control_event()
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
        if(event.type == SDL_KEYDOWN)
        {
            if( event.key.keysym.sym == SDLK_LEFT)
                T[0] = 1;
            else if( event.key.keysym.sym == SDLK_UP)
                T[1] = 1;
            else if( event.key.keysym.sym == SDLK_RIGHT)
                T[2] = 1;
            else if( event.key.keysym.sym == SDLK_DOWN)
                T[3] = 1;
        }
        switch (event.type)
        {
        case SDL_QUIT:
            free_memory();
            break;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            if(x > 0 and x <= 400 and y > 0 and y <= 100)pause();
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_p:
                pause();
                break;
            }
        }
        if(level->map[(int)((level->player.y - cx) / size_squar)][(int)((level->player.x - cy) / size_squar)] == 0)level->last_touch_on_green_area = make_pair(level->player.x, level->player.y);
        SDL_Delay(10);
    }
}
void Game::update()
{
    if(run_next_generation)
    {
        level->next_generation();
        run_next_generation = 0;
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
void Game::check_status_of_playing()
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
    // if(level->N_Snubbys_a_life <= 0)
    // {
    //     level->next_generation();
    //     level->generation++;
    //     for(auto &sn : level->Snubbys)
    //     {
    //         sn.x = level->A.first;
    //         sn.y = level->A.second;
    //     }
    // }
}
void Game::play()
{
    level->get_enemys();
    level->player.update_input(level);
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
        check_status_of_playing();
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
void Game::show()
{
    SDL_RenderPresent(render);
    SDL_Delay(40);
}

void Game::pause()
{
    is_pause = 1;
    rect = {312, 100, 400, 540} ;
    if(automatique)
        SDL_RenderCopy(render, textureSlides[9], NULL, &rect);
    else
        SDL_RenderCopy(render, textureSlides[8], NULL, &rect);
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
void Game::draw_levels()
{
    y = 0;
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
void Game::free_memory()
{
    cout << "libérer la mémoire ..." << endl;
    SDL_RenderCopy(render, texture_wait, NULL, NULL);
    SDL_RenderPresent(render);
    SDL_Delay(4);
    logout(id, token);
    SDL_Quit();
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
    exit(0);
}
int Game::get_level()
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
            coin_sound();
            for(int i, j, k = 1; k < N_LEVELS + 1; k++)
            {
                j = (k - 1) / 3;
                i = (k - 1) - j * 3;
                rect = {40 * (i + 1) + i * 288 + 5, y + 40 * (j + 1) + j * 150 + 5, 288 - 10, 150 - 10} ;
                if( x > rect.x and x < rect.x + rect.w and b - y > rect.y and b - y < rect.y + rect.h )
                {
                    load_level(k);
                    return k;
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
void Game::screen_level()
{
    int width = 1024, height = 768;
    s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(render, NULL, s->format->format, s->pixels, s->pitch);
    string z = "../levels/" + to_string(N_LEVELS) + ".png";
    IMG_SavePNG(s, z.c_str());
}

void Game::save_level()
{
    std::ofstream ofs( "../levels/" + to_string(N_LEVELS));
    boost::archive::text_oarchive ar(ofs);
    ar &level;
}
void Game::load_level(int k)
{
    std::ifstream ifs("../levels/" + to_string(k));
    boost::archive::text_iarchive ar(ifs);
    ar &level;
}
void Player::think(Level *level, Game *g)
{
    update_input(level);
    vector<double> r = brain.predict( input);
    if(r[0] == max(r[0], max(r[1], max(r[2], r[3]))) && g->check_it_free_area(x, y - 10) &&
            g->is_player_inside_after(x, y - 20)
      )y -= 10; //up
    else if(r[1] == max(r[0], max(r[1], max(r[2], r[3]))) && g->check_it_free_area(x, y + 10) &&
            g->is_player_inside_after(x, y + 20)
           )y += 10; //down
    else if(r[2] == max(r[0], max(r[1], max(r[2], r[3]))) && g->check_it_free_area(x + 10, y) &&
            g->is_player_inside_after(x + 20, y)
           )x += 10; //R
    else if(r[3] == max(r[0], max(r[1], max(r[2], r[3]))) && g->check_it_free_area(x - 10, y) &&
            g->is_player_inside_after(x - 20, y)
           )x -= 10;; //L
}
void Game::thread_playing_online()
{
    continuer = 1;
    while(1)
    {
        while(token.size() != TOKEN_SIZE  and !is_playing)SDL_Delay(100);
        try
        {
            streams = stringstream(send_and_get_status(token, id, level->player.x, level->player.y));
            streams >> player2.first >> player2.second;
            status_thread_playing_online = 1;
        }
        catch (const std::exception &e)
        {
            status_thread_playing_online = 0;
        }
    }
}
void Game::thread_update_position()
{
    while(1)
    {
        if(!is_playing)
        {
            SDL_Delay(10);
            continue;
        }
        if(T[0])
        {
            if(check_it_free_area(level->player.x - 10, level->player.y) && is_player_inside_after(level->player.x - 20, level->player.y))
                level->player.x -= 10;
            T[0] = 0;
        }
        if(T[1])
        {
            if(check_it_free_area(level->player.x, level->player.y - 10 ) && is_player_inside_after(level->player.x, level->player.y - 20))
                level->player.y -= 10;
            T[1] = 0;
        }
        if(T[2])
        {
            if(check_it_free_area(level->player.x + 10, level->player.y) && is_player_inside_after(level->player.x + 20, level->player.y))
                level->player.x += 10;
            T[2] = 0;
        }
        if(T[3])
        {
            if(check_it_free_area(level->player.x, level->player.y + 10) && is_player_inside_after(level->player.x, level->player.y + 20))
                level->player.y += 10;
            T[3] = 0;
        }
    }
}
//todo
//mutation
//     for(auto &sn : level->Snubbys)
//     {
//         if(!sn.is_a_life)
//         {
//             sn.brain.mutate();
//         }
//         sn.is_a_life = 1;
//     };

// next generation
//         for(auto &sn : level->Snubbys)
//         {
//             sn.brain.init_params(NEURAL_NETWORK);
//             sn.x = level->A.first;
//             sn.y =  level->A.second;
//             sn.is_a_life = 1;
//         };
//         level->generation++;

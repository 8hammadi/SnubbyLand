void init()
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
    SDL_LoadWAV("../sound/hit.wav", &wav_spec[0], &wav_buffer[0], &wav_length[0]);
    device_enemy = SDL_OpenAudioDevice(NULL, 0, &wav_spec[0], NULL, 0);

    SDL_LoadWAV("../sound/coin.wav", &wav_spec[1], &wav_buffer[1], &wav_length[1]);
    device_coin = SDL_OpenAudioDevice(NULL, 0, &wav_spec[1], NULL, 0);

    textureEnemy = SDL_CreateTextureFromSurface(render, IMG_Load("../images/enemy.png"));
    textures[0] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/level.png"));
    load_n();
    for(int i = 0; i < N_LEVELS + 1; i++)
    {
        text = "../levels/" + to_string(i + 1) + ".png";
        textures[i + 1] = SDL_CreateTextureFromSurface(render, IMG_Load(text.c_str()));
    }
    textureCoin = SDL_CreateTextureFromSurface(render, IMG_Load("../images/coin.png"));
    textureSlides[1] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/black_area.png"));
    textureSlides[2] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/coin_slide.png"));
    textureSlides[3] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/player_slide.png"));
    textureSlides[4] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/green_area.png"));
    textureSlides[5] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/spiral.png"));
    textureSlides[6] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/playing_slide.png"));
    textureSlides[7] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/pause_game.png"));
    textureSlides[8] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/continue.png"));
    textureSlides[9] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/ga_continue.png"));
    textureSlides[10] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/again.png"));
    textureSlides[11] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/ng.png"));

    texture_wait = SDL_CreateTextureFromSurface(render, IMG_Load("../images/wait.gif"));
    texturePlayer = SDL_CreateTextureFromSurface(render, IMG_Load("../images/player.png"));
    texturePlayer2 = SDL_CreateTextureFromSurface(render, IMG_Load("../images/play2.png"));
}

void play()
{
    cout << "the game begain" << endl;
    level.n_coins = level.coins.size();
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

}



void local_win()
{
    cout << "You win .." << endl;
    is_pause = 1;
    draw_game();
    rect = {312, 100, 400, 540} ;
    SDL_RenderCopy(render, textureSlides[10], NULL, &rect);
    show();
    while(is_pause)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            coin_sound();
            if(x > 312 and x<712 and y>100 and y < 200)
            {

                load_level(l);
                is_pause = 0;
                level.n_coins = level.coins.size();
            }
            if(x > 312 and x<712 and y>210 and y < 310)
            {
                if(!automatique)
                {
                    l++;
                    if(l == N_LEVELS + 1)l = 1;
                    cout << "Level " << l << endl;
                    load_level(l);
                }
            }
            if(x > 312 and x<712 and y>320 and y < 420)
            {
                if(!automatique)
                {
                    l--;
                    if(l == 0)l = N_LEVELS;
                    cout << "Level " << l << endl;
                    load_level(l);
                }
            }
            if(x > 312 and x<712 and y>430 and y < 530)
            {
                is_pause = 0;
                is_playing = 0;
                return index();
            }
            if(x > 312 and x<712 and y>540 and y < 640)
            {
                free_memory();
            }
            draw_game();
            rect = {312, 100, 400, 540} ;
            if(automatique)
                SDL_RenderCopy(render, textureSlides[9], NULL, &rect);
            else
                SDL_RenderCopy(render, textureSlides[8], NULL, &rect);
            break;
            show();
        case SDL_QUIT:
            free_memory();

        }
    }
}


void show()
{
    SDL_RenderPresent(render);
    SDL_Delay(40);
}

void pause_game()
{
    cout << "POUSE" << endl;
    is_pause = 1;
    draw_game();
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
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            coin_sound();
            if(x > 312 and x<712 and y>100 and y < 200)
            {

                is_pause = 0;
            }
            if(x > 312 and x<712 and y>210 and y < 310)
            {
                if(!automatique)
                {
                    l++;
                    if(l == N_LEVELS + 1)l = 1;
                    cout << "Level " << l << endl;
                    load_level(l);
                }
            }
            if(x > 312 and x<712 and y>320 and y < 420)
            {
                if(!automatique)
                {
                    l--;
                    if(l == 0)l = N_LEVELS;
                    cout << "Level " << l << endl;
                    load_level(l);
                }
            }
            if(x > 312 and x<712 and y>430 and y < 530)
            {
                is_pause = 0;
                is_playing = 0;
                return index();
            }
            if(x > 312 and x<712 and y>540 and y < 640)
            {
                free_memory();
            }
            //drawing
            draw_game();
            rect = {312, 100, 400, 540} ;
            if(automatique)
                SDL_RenderCopy(render, textureSlides[9], NULL, &rect);
            else
                SDL_RenderCopy(render, textureSlides[8], NULL, &rect);
            break;
            show();
        case SDL_QUIT:
            free_memory();
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_p:
                is_pause = 0;
                break;
            case SDLK_s:
                level.save_population();
                cout << "save_population" << endl;
                break;
            case SDLK_l:
                level.load_population();
                cout << "load_population" << endl;
                break;
            }
        }
        SDL_Delay(10);
    }
}
void draw_levels()
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
void free_memory()
{
    is_playing = 0;
    SDL_RenderCopy(render, texture_wait, NULL, NULL);
    SDL_RenderPresent(render);
    SDL_Delay(4);
    cout << "libérer la mémoire ..." << endl;
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
    exit(1);
}
int get_level()
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
            cout << "scrolling .." << endl;
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



void init()
{
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow("Snubby Land", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 668, SDL_WINDOW_OPENGL);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);

    if (TTF_Init() != -1)
    {
        cout<<"TTF INITIALIZED"<<endl;
        font = TTF_OpenFont("../images/AMA.ttf", 50);
    }
    SDL_LoadWAV("../sound/hit.wav", &wav_spec[0], &wav_buffer[0], &wav_length[0]);
    device_enemy = SDL_OpenAudioDevice(NULL, 0, &wav_spec[0], NULL, 0);

    SDL_LoadWAV("../sound/coin.wav", &wav_spec[1], &wav_buffer[1], &wav_length[1]);
    device_coin = SDL_OpenAudioDevice(NULL, 0, &wav_spec[1], NULL, 0);

    textureEnemy = SDL_CreateTextureFromSurface(render, IMG_Load("../images/enemy.png"));
    textures[0] = SDL_CreateTextureFromSurface(render, IMG_Load("../images/levelBackground.jpg"));
    load_n();
    load_n_open();
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
    textureblack = SDL_CreateTextureFromSurface(render, IMG_Load("../images/black.png"));
    texture_wait = SDL_CreateTextureFromSurface(render, IMG_Load("../images/wait.gif"));
    texturePlayer = SDL_CreateTextureFromSurface(render, IMG_Load("../images/player.png"));
    texturePlayer2 = SDL_CreateTextureFromSurface(render, IMG_Load("../images/play2.png"));
}

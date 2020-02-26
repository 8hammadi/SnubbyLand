//0 # 1 . 2 G
class Graphic
{
private:
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL ;

    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Rect rect;
    SDL_Surface *s;
    SDL_Texture *texture, *texturePlayer, *textureRoad, *textureEnemy, *textureCoin, *texturePlus, *texturePoint;
    vector<pair<int, int>> sizeTable = {{40, 60}, {20, 30}, {10, 15}}, Points;
    pair<int, int> P1 = {0, 0}, P2 = {100, 100}, A = {200, 0}, B = {300, 100};
    double t;
    int PAS = 30;
    bool showRoadbool = 0;
    int modeMap = 0, xx, yy;
    char *text = (char *)malloc(1024), *path = (char *)"../files/", *String = (char *)malloc(1024);



    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 *wav_buffer;
    SDL_AudioDeviceID deviceId, deviceId1;
public:
    SDL_Event event, eevent;
    Game *game;
    int continuer = 1, i = 0, j = 0, n, m, k, l, sizeOfSquir = 0;
    int SCREEN_WIDTH = 900, SCREEN_HEIGHT = 600;
    vector<vector<int>> Color = { {255, 255, 255}, {0, 0, 255}, {0, 0, 0}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255}};
    int color = 0;
    int x = -100, y = -100, oldx = -100, oldy = -100, ooldx = -100, ooldy = -100;
    
    Graphic(const char *gameName, Game *g)
    {
        game = g;
        SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
        window = SDL_CreateWindow(gameName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
        render = SDL_CreateRenderer(window, -1, 0);

        s = IMG_Load("../images/player.png");
        texturePlayer = SDL_CreateTextureFromSurface(render, s);

        s = IMG_Load("../images/coin.png");
        textureCoin = SDL_CreateTextureFromSurface(render, s);

        s = IMG_Load("../images/enemy.png");
        textureEnemy = SDL_CreateTextureFromSurface(render, s);

        s = IMG_Load("../images/plus.png");
        texturePlus = SDL_CreateTextureFromSurface(render, s);

        s = IMG_Load("../images/road.png");
        textureRoad = SDL_CreateTextureFromSurface(render, s);

    }
    void soundInit()
    {
        // SDL_Init(SDL_INIT_AUDIO);

        // SDL_LoadWAV("../sound/background.mp3", &wav_spec, &wav_buffer, &wav_length);
        // deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);

        // SDL_QueueAudio(deviceId, wav_buffer, wav_length);

        // SDL_LoadWAV(SOUND1, &wav_spec, &wav_buffer, &wav_length);
        // deviceId1 = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
        // SDL_QueueAudio(deviceId1, wav_buffer, wav_length);

        // SDL_PauseAudioDevice(deviceId, 0);
    }
    void save(Game g)
    {
        cout << "Tape the name of file :" << endl;
        getText();
        std::ofstream ofs( (string("../files/") + string(text)).c_str() );
        boost::archive::text_oarchive ar(ofs);
        // Save the data
        ar &g;
        cout << "the game is saved" << endl;
    }
    void load(Game &g)
    {
        cout << "Tape the name of file :" << endl;
        getText();
        std::ifstream ifs((string("../files/") + string(text)).c_str() );
        boost::archive::text_iarchive ar(ifs);

        // Load the data
        ar &g;
        cout << "The game is loaded " << endl;
    }
    void sleep(int s)
    {
        SDL_Delay(s);
    }

    void show()
    {
        SDL_RenderPresent(render);
        SDL_Delay(5);
    }


    void go()
    {
        SDL_GetMouseState(&xx, &yy);
        if(modeMap != 3)
        {
            game->map[yy / PAS][xx / PAS] = modeMap;
        }

    }

    void drawRect(int x, int y, int w, int h)
    {
        SDL_SetRenderDrawColor(render, Color[color][0], Color[color][1], Color[color][2], 255);
        rect = {x, y, w, h};
        SDL_RenderDrawRect(render, &rect );
    }
    void fillRect(int x, int y, int w, int h)
    {
        SDL_SetRenderDrawColor(render, Color[color][0], Color[color][1], Color[color][2], 255);
        rect = {x, y, w, h};
        SDL_RenderFillRect(render, &rect);

    }
    void drawTable(int i, int e)
    {
        e = 0;
        n = sizeTable[i].first;
        m = sizeTable[i].second;
        color = 3;
        SDL_SetRenderDrawColor(render, Color[color][0], Color[color][1], Color[color][2], 255);

        fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        color = 1;

        for(i = 0; i < 20; i++)
        {
            for(j = 0; j < 30; j++)
            {
                color = game->map[i][j];
                SDL_SetRenderDrawColor(render, Color[color][0], Color[color][1], Color[color][2], 255);
                rect = {j * PAS, i * PAS, PAS - 2 * e, PAS - 2 * e};
                SDL_RenderFillRect(render, &rect);
            }
        }

    }

    void draw();
    void update();
    int takeEvent();
    void drawTexture(SDL_Texture *T, int x, int y, int r)
    {
        if(r == 0)
            r = SCREEN_HEIGHT / 40;
        rect = {x, y, r, r};
        SDL_RenderCopy(render, T, NULL, &rect);
    }
    void drawNodes()
    {
        for(auto node : game->graph.nodes)
        {
            drawTexture(textureEnemy, node.first, node.second, 15);
        }
    }

    void addLinrearRoad()
    {
        game->graph.addLinearRoad(A, B);
        cout << "LinearRoad added " << endl;
    }
    void addPolarRoad()
    {
        game->graph.addPolarRoad(A, B, P1, P2);
        cout << "PolarRoad added " << endl;
    }
    void addCircularRoad()
    {
        game->graph.addCircularRoad(A, B);
        cout << "Circular Road added " << endl;
    }
    void drawRoad()
    {
        for(auto r : game->graph.linearRoads)
        {
            for(int i = 0; i < 200; i++)
            {
                t = (double)i / 200;
                drawTexture(textureRoad, r.M(t).first, r.M(t).second, 30 );
            }
        }
        for(auto r : game->graph.polarRoads)
        {
            for(int i = 0; i < 200; i++)
            {
                t = (double)i / 200;
                drawTexture(textureRoad, r.M(t).first, r.M(t).second, 30 );
            }
        }
    }
    void drawEnemys()
    {
        for(auto e : game->enemys)
        {
            drawTexture(textureEnemy, e.x, e.y, 30);
        }
    }
    void addEnemy()
    {
        if(game->graph.linearRoads.size() + game->graph.polarRoads.size())
        {
            game->enemys.push_back(Enemy(0, 0.5));
            cout << "Enemy added " << endl;
        }
    }
    void addCoins()
    {
        game->coins.push_back(Coin(xx, yy));
    }
    void receive()
    {
        int fd;
        char *myfifo = (char *)"myProgram";
        char *buf = (char *)malloc(1024);
        while(1)
        {
            fd = open(myfifo, O_RDONLY);
            read(fd, buf, MAX_BUF);
            sscanf(buf, "%d", &i);
            sscanf(buf, "%d %d %d", &game->player1.id, &game->player1.x, &game->player1.y);
            cout << buf;
            *buf = '\0';
            close(fd);

        }
    }
    void drawRotationTest()
    {
        rect = {100, 100, 100, 100};
        SDL_Point pp = {150, 150};
        SDL_RenderCopyEx(render, texturePlayer, NULL, &rect, 15, &pp, (const SDL_RendererFlip)NULL);
    
    }
    void drawGun(){
        rect = {game->player.x, game->player.y, 10, 10};
        SDL_Point pp = {game->player.x+5, game->player.y+5};

        SDL_RenderCopyEx(render, texturePlayer, NULL, &rect, game->player.ongle, &pp, flip);
    
    }
    void send()
    {
        int fd;
        char *myfifo = (char *)"yourProgram";
        char *buf = (char *)malloc(1024);
        while(1)
        {
            fd = open(myfifo, O_WRONLY);
            sprintf(buf, "%d %d %d", game->player.id, game->player.x, game->player.y);
            write(fd, buf, strlen(buf));
            close(fd);
            *buf = '\0';
            sleep(80);
        }
    }

    void getText()
    {
        bool a = 1;
        *text = '\0';
        while(a)
        {
            SDL_WaitEvent(&event);
            switch (event.type)
            {
            case SDL_TEXTINPUT:
                strcat(text, event.text.text);
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)

                {
                case SDLK_SPACE:
                    a = 0;
                    break;
                }
            }
        }
        text = text + 1;
    }
};

int Graphic::takeEvent()
{

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {

        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            ooldx = oldx;
            ooldy = oldy;
            oldx = x;
            oldy = y;
            x = event.motion.x;
            y = event.motion.y;
            Points.push_back(make_pair(x, y));
            y -= y % ((SCREEN_HEIGHT / 40));
            x -= x % ((SCREEN_WIDTH / 60));


            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {

            case SDLK_SPACE:
                ++modeMap %= 4;
                if(modeMap == 3)cout << "Normal Map" << endl;
                if(modeMap == 0)cout << "Mode Gomm" << endl;
                break;

            case SDLK_KP_9:

                cout << "Node added " << x << " " << y << endl;
                game->graph.addNode(x, y);
                Points.push_back(make_pair(x, y));
                break;
            case SDLK_t:
                getText();
                cout << text << endl;
                break;
            case SDLK_r:
                game->player.initToLastGreen();
                //game->player.ongle++;
                //game->graph.addPoints();
                break;
            case SDLK_KP_1:
                P1 = make_pair(x, y);
                break;
            case SDLK_KP_2:
                P2 = make_pair(x, y);
                break;
            case SDLK_a:
                A = make_pair(x, y);
                break;
            case SDLK_b:
                B = make_pair(x, y);
                break;
            case SDLK_s:
                save(*game);
                break;
            case SDLK_KP_0:
                load(*game);
                break;

            case SDLK_l:
                addLinrearRoad();
                break;
            case SDLK_p:
                addPolarRoad();
                break;
            case SDLK_e:
                addEnemy();
                break;
            case SDLK_o:
                addCircularRoad();
                break;
            case SDLK_LEFT:
                game->player.left(game->map);
                break;
            case SDLK_UP:
                game->player.up(game->map);
                break;
            case SDLK_RIGHT:
                game->player.right(game->map);
                break;
            case SDLK_DOWN:
                game->player.down(game->map);
                break;
            case SDLK_c:
                addCoins();
                break;


            }

        }
    }

    return 1;
}

void Graphic::draw()
{
    drawTable(sizeOfSquir, 1);
    drawNodes();
    drawTexture(texturePlus, P1.first, P1.second, 0);
    drawTexture(texturePlus, P2.first, P2.second, 0);
    drawTexture(textureEnemy, A.first, A.second, 0);
    drawTexture(textureEnemy, B.first, B.second, 0);
    drawTexture(texturePlayer, x, y, 0);
    drawEnemys();
    drawTexture(texturePlayer, game->player.x, game->player.y, 30);
    drawGun();
    //drawTexture(texturePlayer, game->player1.x, game->player1.y, 30);
    for(auto c : game->coins)drawTexture(textureCoin, c.x, c.y, 0);

}

void Graphic::update()
{
    for(auto &e : game->enemys)
    {
        e.nextMouve(game->graph);
    }
    for(int i = 0; i < game->coins.size(); i++)
    {
        if(sqrt( pow(game->player.x - game->coins[i].x, 2) - pow(game->player.y - game->coins[i].y, 2) ) < 10)
            game->coins.erase(game->coins.begin() + i);
    }
}
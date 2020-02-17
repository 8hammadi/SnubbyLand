/*


espace ||| change sizeOfSquir
9      |||add Node in Your Graphe
s      |||save level in level
l      |||load level from input
n      |||show node of graphe
b         show roads
q      |||last click
1   pivot 1
2   pivot 2
w draw every thing

o add linear  road

p add Polar road
*/
class Graphic
{
private:
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Rect rect;
    SDL_Surface *s;
    SDL_Event event;
    SDL_Texture *texture, *texturePlayer, *textureEnemy, *textureCoin, *texturePlus, *texturePoint;
    vector<pair<int, int>> sizeTable = {{40, 60}, {20, 30}, {10, 15}};
    pair<int, int> P1 = {0, 0}, P2 = {100, 100}, A = {200, 0}, B = {300, 100};
    double t;

public:
    Game *game;
    int continuer = 1, i = 0, j = 0, n, m, k, l, sizeOfSquir = 0;
    int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 600;
    vector<vector<int>> Color = {{0, 0, 0}, {255, 255, 255}, {0, 0, 255}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255}};
    int color = 0;
    int x = -100, y = -100, oldx = -100, oldy = -100, ooldx = -100, ooldy = -100;

    Graphic(const char *gameName, Game *g)
    {
        game = g;
        SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
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

    void text(int x, int y, int w, int h);

    string getText(int x, int y, int w, int h);

    void freeMemory();

    void drawRect(int x, int y, int w, int h)
    {
        SDL_SetRenderDrawColor(render, Color[color][0], Color[color][1], Color[color][3], 255);
        rect = {x, y, w, h};
        SDL_RenderDrawRect(render, &rect );
    }
    void fillRect(int x, int y, int w, int h)
    {
        s = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);


        SDL_FillRect(s, NULL, SDL_MapRGB(s->format, Color[color][0], Color[color][1], Color[color][3]));
        drawSurface(s, x, y, w, h);

    }
    void drawSurface(SDL_Surface *s, int x, int y, int w, int h)
    {
        texture = SDL_CreateTextureFromSurface(render,
                                               s);
        rect = {x, y, w, h};


        SDL_RenderCopy(render, texture, NULL, &rect);
    }
    void drawTable(int i, int e)
    {
        n = sizeTable[i].first;
        m = sizeTable[i].second;
        color = 0;
        fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        color = 1;
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
                fillRect((j * SCREEN_WIDTH / m) + e, (i * SCREEN_HEIGHT / n) + e, ( SCREEN_WIDTH / m) - 2 * e, ( SCREEN_HEIGHT / n) - 2 * e);
            }
        }

    }

    void draw();
    void update();
    int takeEvent(void *);

    void drawTexture(SDL_Texture *T, int x, int y, int r)
    {
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
    void drawRoad()
    {
        for(auto r : game->graph.linearRoads)
        {
            for(int i = 0; i < 200; i++)
            {
                t = (double)i / 200;
                drawTexture(textureCoin, r.M(t).first, r.M(t).second, 0 );
                cout << t << " " << r.M(t).first << " " << r.M(t).second << endl;
            }
        }
        for(auto r : game->graph.polarRoads)
        {
            for(int i = 0; i < 200; i++)
            {
                t = (double)i / 200;
                drawTexture(textureCoin, r.M(t).first, r.M(t).second, 0 );
                cout << t << " " << r.M(t).first << " " << r.M(t).second << endl;
            }
        }
    }
    void drawEnemys(){
        for(auto e:game->enemys){
            drawTexture(textureEnemy,e.x,e.y,0);
        }
    }
    void addEnemy(){
        if(game->graph.linearRoads.size()+game->graph.polarRoads.size())
        {game->enemys.push_back(Enemy(0,0.5));
            cout<<"Enemy added "<<endl;
        }
    }
};

int Graphic::takeEvent(void *__)
{
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
        case SDL_MOUSEBUTTONDOWN:
            ooldx = oldx;
            ooldy = oldy;
            oldx = x;
            oldy = y;
            x = event.motion.x;
            y = event.motion.y;

            y -= y % ((SCREEN_HEIGHT / 40));
            x -= x % ((SCREEN_WIDTH / 60));
            cout << "mouse" << x << "  " << y << endl;


            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {

            case SDLK_SPACE:
                sizeOfSquir = (++sizeOfSquir) % 3;
                break;

            case SDLK_KP_9:

                cout << "Node added " << x << " " << y << endl;
                game->graph.addNode(x, y);
                break;

            case SDLK_KP_1:
                P1 = make_pair(x, y);
                break;
            case SDLK_KP_2:
                P2 = make_pair(x, y);
                break;
            case SDLK_KP_4:
                A = make_pair(x, y);
                break;
            case SDLK_KP_5:
                B = make_pair(x, y);
                break;

            // case SDLK_s:

            //     game->saveGame();
            //     cout << "Game saved in level file";
            //     break;
            // case SDLK_l:

            //     cout << "fileName :::";
            //     game->loadGame();
            //     cout << "Done loaded";
            //     break;

            case SDLK_o:
                addLinrearRoad();
                break;
            case SDLK_p:
                addPolarRoad();
                break;
            case SDLK_e:
                addEnemy();

            }

        }
    }

    return 1;
}

void Graphic::draw()
{
    // drawTable(sizeOfSquir, 1);
    fillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
     drawRoad();
    drawNodes();
    drawTexture(texturePlus, P1.first, P1.second, 0);
    drawTexture(texturePlus, P2.first, P2.second, 0);
    drawTexture(textureEnemy, A.first, A.second, 0);
    drawTexture(textureEnemy, B.first, B.second, 0);
    drawTexture(texturePlayer, x, y, 0);
     drawEnemys();
}

void Graphic::update(){
    cout<<"update"<<endl;
    for(auto& e:game->enemys){
        e.nextMouve(game->graph);
    }
}
/*


espace ||| change sizeOfSquir
9      |||add Node in Your Graphe
s      |||save level in level
l      |||load level from input
n      |||show node of graphe
q      |||last click

*/
class Graphic
{
private:
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Rect rect;
    SDL_Surface *s;
    SDL_Event event;
    SDL_Texture *texture,*texturePlayer,*textureEnemy,*textureCoin;
    vector<pair<int,int>> sizeTable={{40,60},{20,30},{10,15}};


public:
    Game* game;
    int continuer=1,i=0,j=0,n,m,k,l,sizeOfSquir=0;
    int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 600;
    vector<vector<int>> Color = {{0,0,0},{255,255,255},{0,0,255},{255, 0, 0}, {0, 255, 0}, {0, 0, 255}};
    int color = 0;
    int x, y,oldx,oldy;

    Graphic(const char *gameName,Game*g)
    {
        game=g;
        SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
        window = SDL_CreateWindow(gameName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
        render = SDL_CreateRenderer(window, -1, 0);

        s=IMG_Load("../images/player.png");
        texturePlayer=SDL_CreateTextureFromSurface(render, s);

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
    void fillRect(int x,int y,int w,int h){
        s = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
        
        
        SDL_FillRect(s, NULL, SDL_MapRGB(s->format, Color[color][0], Color[color][1], Color[color][3]));
        drawSurface(s,x,y,w,h);
        
    }
    void drawSurface(SDL_Surface* s,int x,int y,int w,int h){
        texture=SDL_CreateTextureFromSurface(render,
                                          s);
        rect={x, y, w, h};


        SDL_RenderCopy(render, texture, NULL, &rect); 
    }
    void drawTable(int i,int e)
    {
        n=sizeTable[i].first;
        m=sizeTable[i].second;
        color = 0;
        fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        color = 1;
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
                fillRect((j * SCREEN_WIDTH / m)+e, (i * SCREEN_HEIGHT / n)+e,( SCREEN_WIDTH / m)-2*e, ( SCREEN_HEIGHT / n)-2*e);
            }
        }
    }
    void draw(int i,Game game);

    void takeEvent();

    void drawTexture(SDL_Texture* T,int x,int y,int r){
        rect={x-r,y-r,2*r,2*r};
        SDL_RenderCopy(render,T,NULL,&rect);
    }
    void drawNodes(){
        for(auto node:game->graph.nodes){
            drawTexture(texturePlayer,node.first,node.second,15);
        }
    }


};

void Graphic::takeEvent(){
    SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
            case SDL_MOUSEBUTTONDOWN:
                oldx=x;
                oldy=y;
                x = event.motion.x;
                y = event.motion.y;
                cout<<x<<"  "<<y<<endl;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {

                    case SDLK_SPACE:
                        sizeOfSquir=(++sizeOfSquir)%3;
                        drawTable(sizeOfSquir,1);
                        break;

                    case SDLK_KP_9:

                        cout<<"Node added "<<x<<" "<<y<<endl;
                        game->graph.addNode(x,y);
                        break;
                    case SDLK_s:

                        game->saveGame("level");
                        cout<<"Game saved in level file";
                        break;
                    case SDLK_l:
                        
                        cout<<"fileName :::";
                        cin>>game->name;
                        game->loadGame(game->name);
                        cout<<"Done loaded";
                        break;
                    case SDLK_n:
                        drawNodes();
                        show();
                        break;
                    case SDLK_e:
                        // drawRoad();
                        break;
                    case SDLK_a:
                        //addNode();
                    break;
                }
         
        }
}
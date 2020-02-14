class Graphic
{
private:
	SDL_Window *window;
    SDL_Renderer *render;
    SDL_Rect rect;
    SDL_Surface *s;
	SDL_Event event;
	SDL_Texture *texture;
public:

    int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 600;
    vector<vector<int>> Color = {{255,255,255},{0,0,255},{255, 0, 0}, {0, 255, 0}, {0, 0, 255}};
    int color = 0;
    

    Graphic(const char *gameName)
    {

        SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
        window = SDL_CreateWindow(gameName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
        render = SDL_CreateRenderer(window, -1, 0);

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
    void drawTable(int n, int m,int e)
    {
        color = 0;
        fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        color = 1;
        for(int i = 0; i < n; i++)
        {
            for(int  j = 0; j < m; j++)
            {
                fillRect((j * SCREEN_WIDTH / m)+e, (i * SCREEN_HEIGHT / n)+e,( SCREEN_WIDTH / m)-2*e, ( SCREEN_HEIGHT / n)-2*e);
            }
        }
    }

};
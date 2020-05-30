//guide
#define CREATOR_guide_width WINDOW_WIDTH-200
#define CREATOR_guide_height 90
#define CREATOR_guide_x -(WINDOW_WIDTH-CREATOR_guide_width)/2
#define CREATOR_guide_y WINDOW_HEIGHT-CREATOR_guide_height

//plan
#define CREATOR_plan_width 200
#define CREATOR_plan_height WINDOW_HEIGHT-CREATOR_guide_height-CREATOR_plan_x
#define CREATOR_plan_x 0
#define CREATOR_plan_y 0

//previous
#define CREATOR_previous_width CREATOR_guide_x//40
#define CREATOR_previous_height CREATOR_guide_height//20
#define CREATOR_previous_x (CREATOR_guide_x-CREATOR_previous_width)/2
#define CREATOR_previous_y CREATOR_guide_y+(CREATOR_guide_height-CREATOR_previous_height)/2

//previous
#define CREATOR_next_width CREATOR_previous_width
#define CREATOR_next_height CREATOR_previous_height
#define CREATOR_next_x (WINDOW_WIDTH+CREATOR_guide_width+CREATOR_guide_x-CREATOR_next_width)/2
#define CREATOR_next_y CREATOR_previous_y

int stepp;

void create_level()
{
    N_LEVELS++;
    l = N_LEVELS;
LEVEL0:
    go_back = 0;
    load_level(0);
    renderLevelCreator(render, 0);
    SDL_RenderPresent(render);
    SDL_Delay(5);
WALL:
    stepp = 0;
    go_back = 0;
    cout << "wall ..." << endl;
    get_wall();
    if(go_back)goto LEVEL0;

GREEN:
    stepp = 1;
    go_back = 0;
    cout << "grean zone ..." << endl;
    get_green_area();
    if(go_back)goto WALL;
COIN:
    stepp = 2;
    go_back = 0;
    cout << "coins ..." << endl;
    add_coins();
    if(go_back)goto GREEN;
SPIRAL:
    stepp = 3;
    go_back = 0;
    cout << "apirals ..." << endl;
    add_spiral_dot();
    if(go_back)goto COIN;
BIG_SPIRAL:
    stepp = 4;
    go_back = 0;
    cout << "adding big spiral ..." << endl;
    add_big_spiral_dot();
    if(go_back)goto SPIRAL;
LINEAR:
    stepp = 5;
    go_back = 0;
    cout << "linear enemy ..." << endl;
    add_linear_enemy();
    if(go_back)goto BIG_SPIRAL;
SQUAR:
    stepp = 6;
    go_back = 0;
    cout << "squar enemy ..." << endl;
    add_squar_enemy();
    if(go_back)goto LINEAR;
POSITION:
    stepp = 7;
    go_back = 0;
    cout << "initial position ..." << endl;
    get_position_player();
    if(go_back)goto SQUAR;
    go_back = 0;
    cout << "screen ..." << endl;
    screen_level();
    cout << "save level ..." << endl;
    save_level();
    save_n();

}

void renderLevelCreator(SDL_Renderer *render, int stepp)
{
    if(stepp <= 1)
        draw_wall();
    else
        draw_game();

    SDL_Texture *plan ;
    SDL_Texture *guide ;
    switch(stepp)
    {
    case 0:
        plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/drawzone.png"));;
        guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/wall.png"));
        break;
    case 1:
        plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/safezone.png"));
        guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/greenarea.png"));
        break;
    case 2:
        plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/coins.png"));
        guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/coin.png"));
        break;
    case 3:
        plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/spiral.png"));
        guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/guidespiral.png"));
        break;
    case 4:
        plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/bigspiral.png"));
        guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/guidebigspiral.png"));
        break;
    case 5:
        plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/linear.png"));
        guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/guidelinear.png"));
        break;
    case 6:
        plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/polygon.png"));
        guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/guidepolygon.png"));
        break;
    case 7:
        plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/snubbyposition.png"));
        guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/guidesnubbyposition.png"));
        break;
    }
    rect = {CREATOR_plan_x, CREATOR_plan_y, CREATOR_plan_width, CREATOR_plan_height};
    SDL_RenderCopy(render, plan, NULL, &rect);
    rect = {CREATOR_guide_x, CREATOR_guide_y, CREATOR_guide_width, CREATOR_guide_height};
    SDL_RenderCopy(render, guide, NULL, &rect);

    static SDL_Texture *prev = SDL_CreateTextureFromSurface(render, IMG_Load("../images/previous.png"));
    static SDL_Texture *next = SDL_CreateTextureFromSurface(render, IMG_Load("../images/next.png"));
    rect = {CREATOR_previous_x, CREATOR_previous_y, CREATOR_previous_width, CREATOR_previous_height};
    SDL_RenderCopy(render, prev, NULL, &rect);
    rect = {CREATOR_next_x, CREATOR_next_y, CREATOR_next_width, CREATOR_next_height};
    SDL_RenderCopy(render, next, NULL, &rect);

}

int eventLevelCreator(int x, int y)
{
    if(CREATOR_previous_x <= x && x <= CREATOR_previous_x + CREATOR_previous_width &&
            CREATOR_previous_y <= y && y <= CREATOR_previous_y + CREATOR_previous_height)
    {
        cout << "Get back" << endl;
        go_back = 1;
        return 0;
    }
    else if(CREATOR_next_x <= x && x <= CREATOR_next_x + CREATOR_next_width &&
            CREATOR_next_y <= y && y <= CREATOR_next_y + CREATOR_next_height)
    {
        cout << "move on" << endl;
        continuer = 0;
        return 0;
    }
    return -1;
}
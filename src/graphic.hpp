
// 1 & 2 free area

//0 grean zone

//-1 black area

class Graphic
{

public:
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Rect rect;
    SDL_Surface *s;
    SDL_Texture *texture, *textureEnemy;
    Level  *level;
    int continuer = 1, on = 0, p;
    SDL_Event event, event_quit;
    int x, y, xx, yy, cx = 100, cy = 100, size_squar = 40;
    bool is_playing = 0, is_pause = 0;
    Graphic(Level *l)
    {
        level = l;
    }
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
    void random_control();
    void add_h_enemys();
    void show();
    void pause();

};
void Graphic::init()
{
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow("badr", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 668, SDL_WINDOW_OPENGL);
    render = SDL_CreateRenderer(window, -1, 0);



    s = IMG_Load("../images/enemy.png");
    textureEnemy = SDL_CreateTextureFromSurface(render, s);
    draw_wall();
    SDL_RenderPresent(render);


}

void Graphic::index()
{
    s = IMG_Load("../images/index.png");
    texture = SDL_CreateTextureFromSurface(render, s);
    SDL_RenderCopy(render, texture, NULL, NULL);
    SDL_RenderPresent(render);
    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);


        switch (event.type)
        {

        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_p:
                // get_level();
                break;
            case SDLK_n:
                create_level();
            }
        }


    }
}
void Graphic::draw_wall()
{
    SDL_SetRenderDrawColor(render, 181.04999999999998, 181.04999999999998, 253.98, 255);
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
            else if(level->map[i][j] == 0)  SDL_SetRenderDrawColor(render, 182.07, 255, 181.04999999999998, 255);
            else continue;
            rect = {cx + j * size_squar, cy + i * size_squar, size_squar, size_squar};
            SDL_RenderFillRect(render, &rect );
        }
    }
}

void Graphic::draw_enemys()
{
    for(auto sp : level->spiral_dots)
    {
        for(auto e : sp.enemys)
        {
            rect = {e.first - level->w_enemy / 2, e.second - level->w_enemy / 2, level->w_enemy, level->w_enemy};
            // SDL_RenderFillRect(render, &rect );
            SDL_RenderCopy(render, textureEnemy, NULL, &rect);
        }
    }

    for(auto he : level->h_enemys)
    {
        for(auto e : he.enemys)
        {
            // cout << e.first << " " << e.second << endl;
            rect = {e.first - level->w_enemy / 2, e.second - level->w_enemy / 2, level->w_enemy, level->w_enemy};
            SDL_RenderCopy(render, textureEnemy, NULL, &rect);
        }
    }
}
void Graphic::draw_game()
{

    draw_wall();

    rect = {-level->player.w / 2  + level->player.x, -level->player.h / 2 + level->player.y, level->player.w, level->player.h};
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderFillRect(render, &rect );

    rect = {-level->player.w / 2  + level->player.x + 5, -level->player.h / 2 + level->player.y + 5, level->player.w - 10, level->player.h - 10};

    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    SDL_RenderFillRect(render, &rect );

    SDL_SetRenderDrawColor(render, 0, 0, 250, 255);
    for(auto e : level->coins)
    {
        if(e.is_taked)continue;
        rect = {e.x - e.w / 2, e.y - e.h / 2, e.w, e.h};
        SDL_RenderFillRect(render, &rect );
    }
    draw_enemys();

}
void Graphic::get_wall()
{

    texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/black_area.png"));
    rect = {100, 0, 600, 100} ;
    SDL_RenderCopy(render, texture, NULL, &rect);
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
            // cout << x << " " << y << endl;
            level->map[(int)((y - cx) / size_squar)][(int)((x - cy) / size_squar)] = -1;
            draw_wall();

            texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/black_area.png"));
            rect = {100, 0, 600, 100} ;
            SDL_RenderCopy(render, texture, NULL, &rect);

            SDL_RenderPresent(render);
            SDL_Delay(5);
        }
        switch (event.type)
        {

        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_o:
                on = 1 - on;
                // cout << on << endl;
                break;
            }
        }
    }
}




void Graphic::get_goal_area()
{
    draw_wall();

    texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/green_area.png"));
    rect = {100, 0, 400, 100} ;
    SDL_RenderCopy(render, texture, NULL, &rect);

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
            level->map[(int)((y - cx) / size_squar)][(int)((x - cx) / size_squar)] = 0;
            draw_wall();

            texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/green_area.png"));
            rect = {100, 0, 400, 100} ;
            SDL_RenderCopy(render, texture, NULL, &rect);

            SDL_RenderPresent(render);
            SDL_Delay(5);
        }
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_o:
                on = 1 - on;
                break;
            }
        }
    }

}


void Graphic::get_position_player()
{
    texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/player_slide.png"));
    rect = {100, 0, 400, 100} ;
    SDL_RenderCopy(render, texture, NULL, &rect);
    SDL_RenderPresent(render);

    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            level->player = Player(cx + 10 * (int)(( x - cx) / 10 ), cy + 10 * (int)(((y - cy) / 10)));
            draw_game();

            texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/player_slide.png"));
            rect = {100, 0, 400, 100} ;
            SDL_RenderCopy(render, texture, NULL, &rect);
            SDL_RenderPresent(render);
            break;
        }
        SDL_Delay(40);
    }
}

void Graphic::add_coin()
{

    draw_game();

    texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/coin_slide.png"));
    rect = {100, 0, 400, 100} ;
    SDL_RenderCopy(render, texture, NULL, &rect);
    SDL_RenderPresent(render);
    SDL_Delay(10);

    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            level->coins.push_back(Coin(10 * (int)(x / 10), 10 * (int)(y / 10)));

            draw_game();
            texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/coin_slide.png"));
            rect = {100, 0, 400, 100} ;
            SDL_RenderCopy(render, texture, NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(10);
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                level->coins.pop_back();
                break;
            }

        }


    }
}


void Graphic::add_spiral_dot()
{
    draw_wall();

    texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/spiral.png"));
    rect = {100, 0, 400, 100} ;
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
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            level->spiral_dots.push_back(Spiral_dot(make_pair(x, y), 5, 100));
            draw_game();


            texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/spiral.png"));
            rect = {100, 0, 400, 100} ;
            SDL_RenderCopy(render, texture, NULL, &rect);
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
                break;
            case SDLK_RIGHT:
                level->spiral_dots[level->spiral_dots.size() - 1].R += 5;
                level->spiral_dots[level->spiral_dots.size() - 1].update();
                draw_game();
                break;
            case SDLK_UP:
                level->spiral_dots[level->spiral_dots.size() - 1].n++;
                level->spiral_dots[level->spiral_dots.size() - 1].update();
                draw_game();
                break;
            case SDLK_DOWN:
                level->spiral_dots[level->spiral_dots.size() - 1].n--;
                level->spiral_dots[level->spiral_dots.size() - 1].update();
                draw_game();
                break;
            }

        }
        SDL_Delay(5);
    }

}


void Graphic::add_h_enemys()
{
    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;

            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                level->h_enemys.push_back(H_enemy(make_pair(x, y), -1));

                break;
            case SDLK_RIGHT:
                level->h_enemys.push_back(H_enemy(make_pair(x, y), 1));

                break;
            case SDLK_UP:
                level->h_enemys[ level->h_enemys.size() - 1].h += 10;

                break;
            case SDLK_DOWN:
                level->h_enemys[ level->h_enemys.size() - 1].h -= 10;

                break;
            case SDLK_p:
                level->h_enemys[ level->h_enemys.size() - 1].n++;

                break;
            case SDLK_m:
                level->h_enemys[ level->h_enemys.size() - 1].n--;

                break;

            }

        }
        if(level->h_enemys.size())
            level->h_enemys[ level->h_enemys.size() - 1].update();
        draw_game();
        SDL_Delay(5);
    }
}
bool Graphic::check_it_not_black_area(int x, int y)
{
    if(     level->map[(int)((y - cy   - level->player.w / 2) / size_squar)][(int)((x - cx - level->player.w / 2) / size_squar)] == -1 ||
            level->map[(int)((y - cy   + level->player.w / 2) / size_squar)][(int)((x - cx + level->player.w / 2) / size_squar)] == -1 ||
            level->map[(int)((y - cy   + level->player.w / 2) / size_squar)][(int)((x - cx - level->player.w / 2) / size_squar)] == -1 ||
            level->map[(int)((y - cy   - level->player.w / 2) / size_squar)][(int)((x - cx + level->player.w / 2) / size_squar)] == -1 ||
            ((y - cy - level->player.w / 2 ) / size_squar) < -0.125 || ((y - cy -  level->player.w / 4 + level->player.w / 2) / size_squar) >= 12 ||
            ((x - cx - level->player.w / 2 ) / size_squar) < -0.125 || ((x - cx -  level->player.w / 4 + level->player.w / 2) / size_squar) >= 20
      )
    {
        // cout << ((x - cx -  level->player.w / 4 + level->player.w / 2) / size_squar) << endl;
        return 0;
    }

    return 1;
}

void Graphic::control()
{
    continuer = 1;
    while(1)
    {
        cout << is_playing << endl;
        if(!is_playing)
        {
            SDL_Delay(10);
            continue;
        }
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                if(check_it_not_black_area(level->player.x - 9, level->player.y))
                    level->player.x -= 10;
                break;
            case SDLK_UP:
                if(check_it_not_black_area(level->player.x, level->player.y - 9 ))
                    level->player.y -= 10;
                break;
            case SDLK_RIGHT:
                if(check_it_not_black_area(level->player.x + 9, level->player.y))
                    level->player.x += 10;
                break;
            case SDLK_DOWN:
                if(check_it_not_black_area(level->player.x, level->player.y + 9))
                    level->player.y += 10;
                break;
            case SDLK_p:
                pause();
                break;
            }

        }
        if(level->map[(int)((level->player.y - cx) / size_squar)][(int)((level->player.x - cy) / size_squar)] == 0)level->last_touch_on_green_area = make_pair(level->player.x, level->player.y);
        SDL_Delay(5);
    }
}

void Graphic::update()
{
    for(auto &sp : level->spiral_dots)sp.next_move();
    for(auto &e : level->h_enemys)e.next_move();
}
void Graphic::check_state()
{
    for(auto &c : level->coins)
    {
        if(!c.is_taked)c.take(level->player);
    }
    for(auto e : level->get_enemys())
    {
        if(level->player.touche_enemy(e, level->w_enemy))
        {
            level->player.x = level->last_touch_on_green_area.first;
            level->player.y = level->last_touch_on_green_area.second;
        };
    }
}
void Graphic::random_control()
{
    continuer = 1;
    while(continuer)
    {
        SDL_Delay(100);
        if(!level->coins.empty())
            level->player.go_to_coin(level->coins[0].x, level->coins[0].y);
        if(level->map[(int)((level->player.y - cx) / size_squar)][(int)((level->player.x - cy) / size_squar)] == 0)level->last_touch_on_green_area = make_pair(level->player.x, level->player.y);
    }
}
void Graphic::play()
{
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

        texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/playing_slide.png"));
        rect = {100, 0, 400, 100} ;
        SDL_RenderCopy(render, texture, NULL, &rect);
        show();
    }
}

void Graphic::show()
{
    SDL_RenderPresent(render);
    SDL_Delay(40);

}
void Graphic::create_level()
{
    draw_wall();
    SDL_RenderPresent(render);

    get_wall();

    get_goal_area();

    get_position_player();

    add_coin();

    add_spiral_dot();

    // add_h_enemys();

    play();
}


void Graphic::pause()
{
    is_pause = 1;
    texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/pause_slide.png"));
    rect = {100, 100, 400, 400} ;
    SDL_RenderCopy(render, texture, NULL, &rect);
    show();


    while(is_pause)
    {
        SDL_WaitEvent(&event_quit);
        switch (event_quit.type)
        {
        case SDL_QUIT:
            exit(0);
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
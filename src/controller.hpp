#define GAME_pause_x 10
#define GAME_pause_y 10
#define GAME_pause_width 70
#define GAME_pause_height 30

bool is_player_inside_after(int x, int y)
{
    if(
        level.map[(int)((y - cy ) / size_squar)][(int)((x - cx ) / size_squar)] == -1
        // level.map[(int)((y - cy + level.player.w / 2) / size_squar)][(int)((x - cx + level.player.w / 2 ) / size_squar)] == -1
        // level.map[(int)(((y - cy - 10) / size_squar))][(int)(((x - cx + 10 ) / size_squar))] == -1
        // level.map[(int)((y - cy + level.player.w / 2) / size_squar)][(int)((x - cx - level.player.w / 2 ) / size_squar)] == -1

    )
    {
        return 0;
    }
    return 1;
}

bool check_it_free_area(int x, int y)
{
    if(        (double)(y - cy - level.player.w / 2 ) / size_squar < 0 || (double)(y - cy -  level.player.w / 4 + level.player.w / 2) / size_squar >= 12 ||
               (double)(x - cx - level.player.w / 2 ) / size_squar < 0 || (double)(x - cx -  level.player.w / 4 + level.player.w / 2) / size_squar >= 20

      )
    {
        return 0;
    }
    return 1;
}
int control_event(void *_)
{


    while(1)
    {
        while(SDL_WaitEvent(&event))
        {
            if(event.type == SDL_QUIT)free_memory();
            if(event.type == SDL_KEYDOWN)
            {
                cout << "+" << endl;
                if( event.key.keysym.sym == SDLK_LEFT )
                {
                    T[0] = 1;
                    cout<<"T[0] = 1;"<<endl;
                }
                if( event.key.keysym.sym == SDLK_UP  )
                {
                    T[1] = 1;
                    cout<<"T[1] = 1;" <<endl;
                }
                if( event.key.keysym.sym == SDLK_RIGHT )
                {
                    T[2] = 1;
                    cout<< "T[2] = 1;"<<endl;
                }
                if( event.key.keysym.sym == SDLK_DOWN )
                {
                    T[3] = 1;
                    cout<< "T[3] = 1;"<<endl;
                }
            }

            if(event.type == SDL_KEYUP)
            {
                cout << "-" << endl;
                if( event.key.keysym.sym == SDLK_LEFT )
                {
                    T[0] = 0;
                    cout<< "T[0] = 0;"<<endl;
                }
                if( event.key.keysym.sym == SDLK_UP )
                {
                    T[1] = 0;
                    cout<<"T[1] = 0;" <<endl;

                }
                if( event.key.keysym.sym == SDLK_RIGHT )
                {
                    T[2] = 0;
                    cout<<"T[2] = 0;" <<endl;
                }
                if( event.key.keysym.sym == SDLK_DOWN )
                {
                    T[3] = 0;
                    cout<< "T[3] = 0;"<<endl;
                }
            }
            if(is_playing)
            {

                switch (event.type)
                {
                case SDL_MOUSEBUTTONDOWN:
                    x = event.motion.x;
                    y = event.motion.y;
                    if(x >= GAME_pause_x && x <= GAME_pause_x + GAME_pause_width
                            && y >= GAME_pause_y && y <= GAME_pause_y + GAME_pause_height)
                    {

                        pause_game();

                    }
                    if(x > 1024 - 400 and x <= 1024 and y > 0 and y <= 100 and automatique)
                    {
                        is_pause = 1;
                        level.next_generation();
                        is_pause = 0;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_n:
                        break;
                    case SDLK_KP_PLUS:
                        sensitivity += 0.03;
                        cout << sensitivity << endl;
                        break;
                    case SDLK_KP_MINUS:
                        sensitivity -= 0.03;
                        cout << sensitivity << endl;
                        break;
                    }
                }
                if(!automatique and level.map[(int)((level.player.y - cx) / size_squar)][(int)((level.player.x - cy) / size_squar)] == 0)level.last_touch_on_green_area = make_pair(level.player.x, level.player.y);
            }
        }
    }
}

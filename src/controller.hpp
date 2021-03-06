
bool is_player_inside_after(int x, int y)
{
    if(
        level.map[(int)((y - 10 - cy ) / size_squar)][(int)((x - 10 - cx ) / size_squar)] == -1 ||
        level.map[(int)( (y + 9 - cy ) / size_squar)][(int)((x - 10 - cx ) / size_squar)] == -1 ||
        level.map[(int)((y - 10 - cy ) / size_squar)][(int)( (x + 9 - cx ) / size_squar)] == -1 ||
        level.map[(int)( (y + 9 - cy ) / size_squar)][(int)( (x + 9 - cx ) / size_squar)] == -1
    )
    {
        return 0;
    }
    return 1;
}

bool check_it_free_area(int x, int y)
{
    if(
        // (y - 49 - cy ) / size_squar < 0 || (y +49 - cy ) / size_squar >= 12 ||
        // (y - 49 - cy ) / size_squar < 0 || (y - 49 - cy ) / size_squar >= 12 ||
        // (x - 49 - cx ) / size_squar < 0 || (x +49 - cx ) / size_squar >= 20 ||
        (x - 49 - cx ) / size_squar < 0 || (x + 9 - cx ) / size_squar >= 20 ||
        (y - 49 - cy ) / size_squar < 0 ||  (y + 9 - cy ) / size_squar >= 12 || 0
        // (y + 49 - cy ) / size_squar < 0 ||  (y + 49 - cy ) / size_squar >= 12 ||
        // (x + 49 - cx ) / size_squar < 0 ||  (x + 49 - cx ) / size_squar >= 20 ||
        // (x + 49 - cx ) / size_squar < 0 ||  (x + 49 - cx ) / size_squar >= 20
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
        if(!is_playing)
        {
            SDL_Delay(200);
            continue;
        }
        if(SDL_WaitEvent(&event_control))
        {
            if(event_control.type == SDL_QUIT)free_memory();

            if(event_control.type == SDL_KEYDOWN || event_control.type == SDL_KEYUP)
            {
                // cout << event_control.key.keysym.sym << endl;
                if( event_control.key.keysym.sym == SDLK_KP_4 )
                    TT[0] = event_control.type == SDL_KEYDOWN;
                if( event_control.key.keysym.sym == SDLK_KP_8 )
                    TT[1] = event_control.type == SDL_KEYDOWN;
                if( event_control.key.keysym.sym == SDLK_KP_6 )
                    TT[2] = event_control.type == SDL_KEYDOWN;
                if( event_control.key.keysym.sym == SDLK_KP_2 )
                    TT[3] = event_control.type == SDL_KEYDOWN;

                if( event_control.key.keysym.sym == SDLK_LEFT )
                    T[0] = event_control.type == SDL_KEYDOWN;
                if( event_control.key.keysym.sym == SDLK_UP )
                    T[1] = event_control.type == SDL_KEYDOWN;
                if( event_control.key.keysym.sym == SDLK_RIGHT )
                    T[2] = event_control.type == SDL_KEYDOWN;
                if( event_control.key.keysym.sym == SDLK_DOWN )
                    T[3] = event_control.type == SDL_KEYDOWN;
            }
            else if(event_control.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = event_control.motion.x;
                int y = event_control.motion.y;
                if(x >= GAME_pause_x && x <= GAME_pause_x + GAME_pause_width
                        && y >= GAME_pause_y && y <= GAME_pause_y + GAME_pause_height)
                    pause_game();
            }


        }
    }
}

//pour creer le tableau de map
void get_wall()
{
    interface = LEVEL_CREATOR;

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
            level.map[(int)((y - cx) / size_squar)][(int)((x - cy) / size_squar)] = -1;

            interface = LEVEL_CREATOR;
        }
        switch (event.type)
        {
        case SDL_QUIT:
            free_memory();
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(eventLevelCreator( x, y) == 0)
                return;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_s:
                on = 0;
                break;
            case SDLK_r:
                on = 1;
                break;
            case SDLK_g:
                level.random_map();

                interface = LEVEL_CREATOR;

                SDL_Delay(5);
                break;
            }
        }
    }
}
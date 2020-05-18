int get_level()
{
    draw_levels();
    y = 0;
    while(1)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            b = event.motion.y;
            coin_sound();
            for(int i, j, k = 1; k < N_LEVELS + 1; k++)
            {
                j = (k - 1) / 3;
                i = (k - 1) - j * 3;
                rect = {40 * (i + 1) + i * 288 + 5, y + 40 * (j + 1) + j * 150 + 5, 288 - 10, 150 - 10} ;
                if( x > rect.x and x < rect.x + rect.w and b - y > rect.y and b - y < rect.y + rect.h )
                {
                    if(k > N_OPEN_LEVEL)
                    {
                        break;
                    }
                    load_level(k);
                    return k;
                    break;
                }
            }
            break;
        case SDL_MOUSEWHEEL:
            cout << "scrolling .." << endl;
            if(event.wheel.y >= 0)
                y -= 10;
            else y += 10;
            draw_levels();
            break;
        case SDL_QUIT:
            free_memory();
            break;
        }
    }
}


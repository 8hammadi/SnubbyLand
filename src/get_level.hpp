#define LEVEL_share_x 5
#define LEVEL_share_y 5
#define LEVEL_share_width 40
#define LEVEL_share_height 20

int get_level()
{
    y = 0;
    draw_levels();
    while(1)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            b = event.motion.y;
            if(x <= 20 and y <= 20)
            {
                string k;
                cout << "NAME OF LEVEL :" << endl;
                k = get_text();
                get_level_from_server(k);
                is_playing = 1;
                // play();
            }
            for(int i, j, k = 1; k <= N_LEVELS ; k++)
            {
                j = (k - 1) / LEVEL_level_row;
                i = (k - 1) % LEVEL_level_row;
                rect = {LEVEL_level_margin *(i + 1) + i * LEVEL_level_width,
                        LEVEL_level_margin *(j + 1) + j *LEVEL_level_height - y, LEVEL_level_width, LEVEL_level_height
                       } ;

                /* if( x > rect.x and x < rect.x + 20 and b - y > rect.y and b - y < rect.y + 20 )
                 {
                     send_level_to_server(k);
                     break;
                 }*/

                if( rect.x + LEVEL_share_x <= x && x <= rect.x + LEVEL_share_x + LEVEL_share_width &&
                        rect.y + LEVEL_share_y <= y && y <= rect.y + LEVEL_share_y + LEVEL_share_height)
                {
                    // TODO : send this level Kkkk kkk k k k
                    send_level_to_server(k);
                    break;
                }

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
            if(event.wheel.y >= 1)
            {
                if(y - 10 >= 0)
                {
                    cout << "Y1: " << y << endl;
                    y -= 10;
                }
            }
            else  if(event.wheel.y <= -1)
            {
                int max = (WINDOW_HEIGHT < (N_LEVELS / LEVEL_level_row + (N_LEVELS % LEVEL_level_row != 0)) * (LEVEL_level_height + LEVEL_level_margin)) ?
                          (N_LEVELS / LEVEL_level_row + (N_LEVELS % LEVEL_level_row != 0)) * (LEVEL_level_height + LEVEL_level_margin) : WINDOW_HEIGHT;
                cout << N_LEVELS << endl;
                cout << max << endl;
                if(y + WINDOW_HEIGHT + 10 <= max)
                {
                    cout << "Y2: " << y << endl;
                    y += 10;
                }
            };
            draw_levels();

            break;
        case SDL_QUIT:
            free_memory();
            break;
        }
    }
}
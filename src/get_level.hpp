#define LEVEL_share_x 0
#define LEVEL_share_y 0
#define LEVEL_share_width 60
#define LEVEL_share_height 30

int get_level()
{
    y = 0;
    interface = GET_LEVEL;

    while(1)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            b = event.motion.y;

            for(int i, j, k = 1; k <= N_LEVELS ; k++)
            {
                j = (k - 1) / LEVEL_level_row;
                i = (k - 1) % LEVEL_level_row;
                rect =
                {
                    LEVEL_level_margin *(i + 1) + i * LEVEL_level_width,
                    LEVEL_level_margin *(j + 1) + j *LEVEL_level_height - y,
                    LEVEL_level_width, LEVEL_level_height
                } ;

                if( rect.x + LEVEL_share_x <= x && x <= rect.x + LEVEL_share_x + LEVEL_share_width &&
                        rect.y + LEVEL_share_y <= b  && b  <= rect.y + LEVEL_share_y + LEVEL_share_height)
                {
                    cout << "SENT: " << endl;
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Level Sharing Code",
                                             send_level_to_server(k).c_str(),
                                             window);
                    break;
                }

                if( x > rect.x and x < rect.x + rect.w and b  > rect.y and b  < rect.y + rect.h )
                {
                    cout << i << " FOUND: " << j << endl;
                    load_level(k);
                    return k;
                    break;
                }
            }

            {
                int j = N_LEVELS / LEVEL_level_row;
                int i = N_LEVELS % LEVEL_level_row;
                rect =
                {
                    LEVEL_level_margin *(i + 1) + i * LEVEL_level_width,
                    LEVEL_level_margin *(j + 1) + j *LEVEL_level_height - y,
                    LEVEL_level_width, LEVEL_level_height
                };
                if( x > rect.x and x < rect.x + rect.w and b > rect.y and b < rect.y + rect.h )
                {
                    cout << "Upload" << endl;
                    string k = get_text();
                    if(k == "-1")
                        continue ;
                    
                    if (get_level_from_server(k))
                    {
                        return l;
                    }
                    else
                    {
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR ",
                                                 "Level does not exist",
                                                 window);
                        cout << "Level not exist" << endl;
                        return -1;
                    }
                    break;
                }
            }

            break;
        case SDL_MOUSEWHEEL:
            if(event.wheel.y >= 1)
            {
                if(y - 20 >= 0)
                {
                    y -= 20;
                }
            }
            else  if(event.wheel.y <= -1)
            {
                N_LEVELS++;
                int max = (N_LEVELS / LEVEL_level_row + (N_LEVELS % LEVEL_level_row != 0)) * (LEVEL_level_height + LEVEL_level_margin);
                max = (WINDOW_HEIGHT <  max) ? max : WINDOW_HEIGHT;
                N_LEVELS--;
                if(y + WINDOW_HEIGHT + 20 <= max)
                {
                    y += 20;
                }
            };
            interface = GET_LEVEL;
            break;
        case SDL_QUIT:
            free_memory();
            break;
        }
    }
}
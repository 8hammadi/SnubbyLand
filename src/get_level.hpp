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
            if(x<=20 and y<=20){
                string k;
                cout<<"NAME OF LEVEL :"<<endl;
                cin>>k;
                get_level_from_server(k);
                // is_playing=1;
                // play();
            }
            for(int i, j, k = 1; k <= N_LEVELS ; k++)
            {
                j = (k - 1) / 3;
                i = (k - 1) % 3;
                rect = {40 * (i + 1) + i * 288, y + 40 * (j + 1) + j * 150, 288, 150} ;
                
                  if( x > rect.x and x < rect.x + 20 and b - y > rect.y and b - y < rect.y + 20 )
                {
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
            if(event.wheel.y >= 0)
            {
                if(y - 10 >= 0)
                    y -= 10;
            }
            else
            {
                int max = 2000+(WINDOW_HEIGHT < (N_LEVELS / 3 + (N_LEVELS % 3 != 0)) * 190) ? (N_LEVELS / 3 + (N_LEVELS % 3 != 0)) * 190 : WINDOW_HEIGHT;
                cout<<max<<endl;
                if(y +WINDOW_HEIGHT+10 <= max)
                    y += 10;
            };
            draw_levels();

            break;
        case SDL_QUIT:
            free_memory();
            break;
        }
    }
}


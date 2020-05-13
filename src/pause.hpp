void pause_game()
{
    cout << "POUSE" << endl;
    is_pause = 1;
    draw_game();
    SDL_RenderCopy(render, textureblack, NULL, NULL);
    rect = {312, 100, 400, 540} ;
    if(automatique)
        SDL_RenderCopy(render, textureSlides[9], NULL, &rect);
    else
        SDL_RenderCopy(render, textureSlides[8], NULL, &rect);
    show();
    while(is_pause)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            coin_sound();
            if(x > 312 and x<712 and y>100 and y < 200)
            {

                is_pause = 0;
            }
            if(x > 312 and x<712 and y>210 and y < 310)
            {
                if(!automatique)
                {
                    l++;
                    if(l == N_LEVELS + 1)l = 1;
                    cout << "Level " << l << endl;
                    load_level(l);
                }
            }
            if(x > 312 and x<712 and y>320 and y < 420)
            {
                if(!automatique)
                {
                    l--;
                    if(l == 0)l = N_LEVELS;
                    cout << "Level " << l << endl;
                    load_level(l);
                }
            }
            if(x > 312 and x<712 and y>430 and y < 530)
            {
                is_pause = 0;
                is_playing = 0;
                return index();
            }
            if(x > 312 and x<712 and y>540 and y < 640)
            {
                free_memory();
            }
            //drawing
            draw_game();
            rect = {312, 100, 400, 540} ;
            if(automatique)
                SDL_RenderCopy(render, textureSlides[9], NULL, &rect);
            else
                SDL_RenderCopy(render, textureSlides[8], NULL, &rect);
            break;
            show();
        case SDL_QUIT:
            free_memory();
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_p:
                is_pause = 0;
                break;
            case SDLK_s:
                level.save_population();
                cout << "save_population" << endl;
                break;
            case SDLK_l:
                level.load_population();
                cout << "load_population" << endl;
                break;
            }
        }
        SDL_Delay(10);
    }
}
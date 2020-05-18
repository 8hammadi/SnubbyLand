void get_position_player()
{
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[3], NULL, &rect);
    SDL_RenderPresent(render);
    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            free_memory();
            break;
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            level.player.x = cx + 40 * (int)(( x - cx) / 40 ) + level.player.w / 2;
            level.player.y = cy + 40 * (int)(((y - cy) / 40)) + level.player.h / 2;
            draw_game();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[3], NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(40);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_p:
                go_back = 1;
                return;
                break;
            case SDLK_n:
                continuer = 0;
                break;
            }
        }
    }
}


void add_coins()
{
    draw_game();
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
    SDL_RenderPresent(render);
    SDL_Delay(10);
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
            level.coins.push_back(Coin(10 * (int)(x / 10), 10 * (int)(y / 10)));
            draw_game();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
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
            case SDLK_LEFT:
                level.coins.pop_back();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(40);
                break;
            case SDLK_n:
                continuer = 0;
                break;
            }
        }
    }
}

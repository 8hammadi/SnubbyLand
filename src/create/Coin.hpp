void add_coins()
{

    interface = LEVEL_CREATOR;

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
            x = event.motion.x ;
            y = event.motion.y ;
            if(eventLevelCreator( x,  y ) == 0)
                return;
            _sync=1;
            SDL_Delay(100);
            level.coins.push_back(Coin(x, y));
            _sync=0;
            interface = LEVEL_CREATOR;

            SDL_Delay(40);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                if(level.coins.size())
                {
                    level.coins.pop_back();
                }
                renderLevelCreator(render, 2);
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(40);
                break;
            }
        }
    }
}

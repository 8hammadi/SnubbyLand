void get_position_player()
{
    // rect = {0, 100 + 40 * 12, 1024, 100} ;
    // SDL_RenderCopy(render, textureSlides[3], NULL, &rect);
    // renderLevelCreator(render, 7);
    // SDL_RenderPresent(render);
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
            x = event.motion.x;
            y = event.motion.y;
            if(eventLevelCreator( x,  y) == 0)
                return;
            level.player.x = x + level.player.w / 2;
            level.player.y = y + level.player.h / 2;

            // draw_game();
            // renderLevelCreator(render, 7);
            // rect = {0, 100 + 40 * 12, 1024, 100} ;
            // SDL_RenderCopy(render, textureSlides[3], NULL, &rect);
            // SDL_RenderPresent(render);
            // SDL_Delay(40);
            interface = LEVEL_CREATOR;

            break;
        }
    }
}


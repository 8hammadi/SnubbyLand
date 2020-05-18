//pour creer le tableau de map
void get_wall()
{
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[1], NULL, &rect);
    SDL_RenderPresent(render);
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
            draw_wall();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[1], NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(5);
        }
        switch (event.type)
        {
        case SDL_QUIT:
            free_memory();
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
                on = 1 - on;
                break;
            case SDLK_s:
                on = 0;
                break;
            case SDLK_r:
                on = 1;
            case SDLK_n:
                continuer = 0;
                break;
            case SDLK_p:
                go_back = 1;
                return;
                break;
            case SDLK_g:
                level.random_map();
                draw_wall();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[1], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            }
        }
    }
}
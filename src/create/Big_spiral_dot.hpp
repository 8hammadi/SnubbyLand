void add_big_spiral_dot()
{
    draw_game();
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
    SDL_RenderPresent(render);
    SDL_Delay(500);
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
            level.big_spiral_dots.push_back(Big_spiral_dot(make_pair(x, y), 5, 100));
            draw_game();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(5);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].R -= 5;
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_RIGHT:
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].R += 5;
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_UP:
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].n++;
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_DOWN:
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].n--;
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_n:
                continuer = 0;
                break;
            case SDLK_p:
                go_back = 1;
                return;
                break;
            case SDLK_r:
                level.big_spiral_dots.pop_back();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            }
        }
        SDL_Delay(5);
    }
}
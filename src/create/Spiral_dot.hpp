
void add_spiral_dot()
{
    // draw_game();
    // renderLevelCreator(render, 3);
    // rect = {0, 100 + 40 * 12, 1024, 100} ;
    // SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
    // SDL_RenderPresent(render);
    // SDL_Delay(500);
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
            if(eventLevelCreator( x + cx,  y + cy) == 0)
                return;
            level.spiral_dots.push_back(Spiral_dot(make_pair(x, y), 5, 100));
            // draw_game();
            // renderLevelCreator(render, 3);
            // rect = {0, 100 + 40 * 12, 1024, 100} ;
            // SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
            // SDL_RenderPresent(render);
            // SDL_Delay(5);
            interface = LEVEL_CREATOR;
            break;
        case SDL_KEYDOWN:
            if(level.spiral_dots.size() == 0)
                break;
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                level.spiral_dots[level.spiral_dots.size() - 1].R -= 5;
                level.spiral_dots[level.spiral_dots.size() - 1].update();
                // draw_game();
                // renderLevelCreator(render, 3);
                // rect = {0, 100 + 40 * 12, 1024, 100} ;
                // SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                // SDL_RenderPresent(render);
                // SDL_Delay(5);
                interface = LEVEL_CREATOR;
                break;
            case SDLK_RIGHT:
                level.spiral_dots[level.spiral_dots.size() - 1].R += 5;
                level.spiral_dots[level.spiral_dots.size() - 1].update();
                // draw_game();
                // renderLevelCreator(render, 3);
                // rect = {0, 100 + 40 * 12, 1024, 100} ;
                // SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                // SDL_RenderPresent(render);
                // SDL_Delay(5);
                interface = LEVEL_CREATOR;
                break;
            case SDLK_UP:
                level.spiral_dots[level.spiral_dots.size() - 1].n++;
                level.spiral_dots[level.spiral_dots.size() - 1].update();
                // draw_game();
                // renderLevelCreator(render, 3);
                // rect = {0, 100 + 40 * 12, 1024, 100} ;
                // SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                // SDL_RenderPresent(render);
                // SDL_Delay(5);
                interface = LEVEL_CREATOR;
                break;
            case SDLK_DOWN:
                level.spiral_dots[level.spiral_dots.size() - 1].n--;
                level.spiral_dots[level.spiral_dots.size() - 1].update();
                // draw_game();
                // renderLevelCreator(render, 3);
                // rect = {0, 100 + 40 * 12, 1024, 100} ;
                // SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                // SDL_RenderPresent(render);
                // SDL_Delay(5);
                interface = LEVEL_CREATOR;
                break;
            case SDLK_r:
                level.spiral_dots.pop_back();
                // draw_game();
                // renderLevelCreator(render, 3);
                // rect = {0, 100 + 40 * 12, 1024, 100} ;
                // SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                // SDL_RenderPresent(render);
                // SDL_Delay(5);
                interface = LEVEL_CREATOR;
                break;
            }
        }
    }
}


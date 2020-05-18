void add_linear_enemy()
{
    draw_game();
    texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/linear_enemy.png"));
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, texture, NULL, &rect);

    SDL_RenderPresent(render);
    SDL_Delay(5);
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
            draw_game();
            texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/linear_enemy.png"));
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, texture, NULL, &rect);
            rect = {-level.player.w / 2  + x, -level.player.h / 2 + y, level.player.w, level.player.h};
            SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
            SDL_RenderFillRect(render, &rect );
            SDL_RenderPresent(render);
            SDL_Delay(5);
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
            case SDLK_KP_1:
                A = make_pair(x, y);
                draw_game();
                texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/linear_slide.png"));
                rect = {100, 0, 400, 100} ;
                SDL_RenderCopy(render, texture, NULL, &rect);
                rect = {-level.player.w / 2  + A.first, -level.player.h / 2 + B.second, level.player.w, level.player.h};
                SDL_RenderCopy(render, textureEnemy, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_KP_2:
                B = make_pair(x, y);
                draw_game();
                texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/linear_slide.png"));
                rect = {100, 0, 400, 100} ;
                SDL_RenderCopy(render, texture, NULL, &rect);
                rect = {-level.player.w / 2  + B.first, -level.player.h / 2 + B.second, level.player.w, level.player.h};
                SDL_RenderCopy(render, textureEnemy, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_KP_3:
                level.linear_enemys.push_back(Linear_enemy(A, B));
                draw_game();
                texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/linear_slide.png"));
                rect = {100, 0, 400, 100} ;
                SDL_RenderCopy(render, texture, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_r:
                level.linear_enemys.pop_back();
                draw_game();
                texture = SDL_CreateTextureFromSurface(render, IMG_Load("../images/linear_slide.png"));
                rect = {100, 0, 400, 100} ;
                SDL_RenderCopy(render, texture, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            }
        }
        SDL_Delay(5);
    }
}

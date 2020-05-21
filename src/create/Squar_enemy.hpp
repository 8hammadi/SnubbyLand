void add_squar_enemy()
{
    // draw_game();
    renderLevelCreator(render, 6);
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
            if(eventLevelCreator( x,  y) == 0)
                return;
            // draw_game();
            renderLevelCreator(render, 6);
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
            case SDLK_KP_1:
                cout << "A est ajauter " << endl;
                A = make_pair(x, y);
                // draw_game();
                renderLevelCreator(render, 6);

                rect = {-level.player.w / 2  + A.first, -level.player.h / 2 + B.second, level.player.w, level.player.h};
                SDL_RenderCopy(render, textureEnemy, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_KP_2:
                cout << "B est ajauter " << endl;
                B = make_pair(x, y);
                // draw_game();
                renderLevelCreator(render, 6);
                rect = {-level.player.w / 2  + B.first, -level.player.h / 2 + B.second, level.player.w, level.player.h};
                SDL_RenderCopy(render, textureEnemy, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_KP_3:
                cout << "C est ajauter " << endl;
                C = make_pair(x, y);
                // draw_game();
                renderLevelCreator(render, 6);
                rect = {-level.player.w / 2  + B.first, -level.player.h / 2 + B.second, level.player.w, level.player.h};
                SDL_RenderCopy(render, textureEnemy, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_KP_4:
                cout << "D est ajauter " << endl;
                D = make_pair(x, y);
                // draw_game();
                renderLevelCreator(render, 6);
                rect = {-level.player.w / 2  + B.first, -level.player.h / 2 + B.second, level.player.w, level.player.h};
                SDL_RenderCopy(render, textureEnemy, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_KP_0:
                cout << "la forme est ajauter" << endl;
                level.squar_enemys.push_back(Squar_enemy(A, B, C, D));
                // draw_game();
                renderLevelCreator(render, 6);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_r:
                level.linear_enemys.pop_back();
                // draw_game();
                renderLevelCreator(render, 6);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_n:
                return;
            }
        }
        SDL_Delay(5);
    }
}

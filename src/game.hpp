
void play()
{
    cout << "the game begain" << endl;
    level.n_coins = level.coins.size();
    is_playing = 1;
    continuer = 1;
    while(continuer and is_playing)
    {
        if(is_pause)
        {
            SDL_Delay(40);
            continue;
        }
        update();
        check_status_of_playing();
        draw_game();
        rect = {0, 100 + 40 * 12, 1024, 100} ;
        SDL_RenderCopy(render, textureSlides[6], NULL, &rect);
        show();
        SDL_Delay(20);
    }

}



void local_win()
{
    cout << "You win .." << endl;
    is_pause = 1;
    draw_game();
    rect = {312, 100, 400, 540} ;
    SDL_RenderCopy(render, textureSlides[10], NULL, &rect);
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

                load_level(l);
                is_pause = 0;
                level.n_coins = level.coins.size();
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

        }
    }
}



void free_memory()
{
    is_playing = 0;
    SDL_RenderCopy(render, texture_wait, NULL, NULL);
    SDL_RenderPresent(render);
    SDL_Delay(4);
    cout << "libérer la mémoire ..." << endl;
    SDL_Quit();
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(textureEnemy);
    for (int i = 0; i < 10; i++) SDL_DestroyTexture(textures[i]);
    for (int i = 0; i < 20; i++) SDL_DestroyTexture(textureSlides[i]);
    SDL_DestroyTexture(textureCoin);
    SDL_FreeSurface(s);
    for (int i = 0; i < 10; i++)SDL_FreeSurface(ss[i]);
    SDL_DestroyTexture(texture_wait);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    exit(1);
}


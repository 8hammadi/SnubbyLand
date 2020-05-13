void index()
{
    cout << "Hello " << id << endl;
    coin_sound();
    SDL_RenderCopy(render, textureSlides[0], NULL, NULL);
    SDL_RenderPresent(render);
    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            coin_sound();
            x = event.motion.x;
            y = event.motion.y;
            //ONE PLAYER OFFLIN
            if(x >= 156 and x <= 156 + 700 and y >= 210 and y <= 210 + 100)
            {
                y = 0;
                l = get_level();
                play();
            }
            //TWO PLAYER thread_playing_online
            if(x >= 156 and x <= 156 + 700 and y >= 320 and y <= 420)
            {
                online_game();
            }
            //GENETIC ALGORITHM (n'est pas encore terminé)
            if(x >= 156 and x <= 156 + 700 and y >= 430 and y <= 430 + 100)
            {
                y = 0;
                l = get_level();
                level.get_enemys();
                level.player.update_input(level);
                update();
                automatique = 1;
                //Les joeurs sont en position inital A et leur objectif est d'atteindre la position B (la position de premier coins) todo(Le plus proche)
                level.A = make_pair(level.player.x, level.player.y);
                level.B = make_pair(level.coins[0].x, level.coins[0].y);

                level.init_population(NEURAL_NETWORK);

                play();
            }
            //CREATE NEW LEVEL
            if(x >= 156 and x <= 156 + 700 and y >= 540 and y <= 540 + 100)
            {
                create_level();
                cout << "le niveau créé avec succès" << endl;
                play();
            }
            break ;
        case SDL_QUIT:
            free_memory();
            break;
        }
    }
}

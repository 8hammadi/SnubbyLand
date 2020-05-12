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

bool is_player_inside_after(int x, int y)
{
    if(
        level.map[(int)((y - cy ) / size_squar)][(int)((x - cx ) / size_squar)] == -1
        // level.map[(int)((y - cy + level.player.w / 2) / size_squar)][(int)((x - cx + level.player.w / 2 ) / size_squar)] == -1
        // level.map[(int)(((y - cy - 10) / size_squar))][(int)(((x - cx + 10 ) / size_squar))] == -1
        // level.map[(int)((y - cy + level.player.w / 2) / size_squar)][(int)((x - cx - level.player.w / 2 ) / size_squar)] == -1

    )
    {
        return 0;
    }
    return 1;
}

bool check_it_free_area(int x, int y)
{
    if(        (double)(y - cy - level.player.w / 2 ) / size_squar < 0 || (double)(y - cy -  level.player.w / 4 + level.player.w / 2) / size_squar >= 12 ||
               (double)(x - cx - level.player.w / 2 ) / size_squar < 0 || (double)(x - cx -  level.player.w / 4 + level.player.w / 2) / size_squar >= 20

      )
    {
        return 0;
    }
    return 1;
}
int control_event(void *_)
{


    while(1)
    {
        while(SDL_WaitEvent(&event))
        {
            if(event.type == SDL_QUIT)free_memory();
            if(!is_playing)
            {
                SDL_Delay(50);
                continue;
            }
            if(event.type == SDL_KEYDOWN)
            {
                if( event.key.keysym.sym == SDLK_LEFT and !T[0])
                {
                    T[0] = 1;
                }
                if( event.key.keysym.sym == SDLK_UP and !T[1] )
                {
                    T[1] = 1;
                }
                if( event.key.keysym.sym == SDLK_RIGHT and !T[2])
                {
                    T[2] = 1;
                }
                if( event.key.keysym.sym == SDLK_DOWN and !T[3])
                {
                    T[3] = 1;
                }
            }

            if(event.type == SDL_KEYUP)
            {
                if( event.key.keysym.sym == SDLK_LEFT and T[0])
                {
                    T[0] = 0;
                }
                if( event.key.keysym.sym == SDLK_UP and T[1] )
                {
                    T[1] = 0;
                }
                if( event.key.keysym.sym == SDLK_RIGHT and T[2])
                {
                    T[2] = 0;
                }
                if( event.key.keysym.sym == SDLK_DOWN and T[3])
                {
                    T[3] = 0;
                }
            }
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                x = event.motion.x;
                y = event.motion.y;
                if(x > 0 and x <= 400 and y > 0 and y <= 100)pause_game();
                if(x > 1024 - 400 and x <= 1024 and y > 0 and y <= 100 and automatique)
                {
                    is_pause = 1;
                    level.next_generation();
                    is_pause = 0;
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_n:
                    break;
                case SDLK_KP_PLUS:
                    sensitivity += 0.03;
                    cout << sensitivity << endl;
                    break;
                case SDLK_KP_MINUS:
                    sensitivity -= 0.03;
                    cout << sensitivity << endl;
                    break;
                }
            }
            if(!automatique and level.map[(int)((level.player.y - cx) / size_squar)][(int)((level.player.x - cy) / size_squar)] == 0)level.last_touch_on_green_area = make_pair(level.player.x, level.player.y);
        }
    }
}
void update()
{
    for(auto &sp : level.spiral_dots)sp.next_move();
    for(auto &sp : level.big_spiral_dots)sp.next_move();
    for(auto &e : level.linear_enemys)e.next_move();
    for(auto &e : level.squar_enemys)e.next_move();
    if(automatique)
    {
        for(auto &p : level.Snubbys)
        {
            if(p.is_a_life)
                p.think(level);
        }
    }
}
void check_status_of_playing()
{
    for(auto &c : level.coins)
    {
        if(!c.is_taked && c.take(level.player))
        {
            coin_sound();
            level.n_coins--;
            if( level.n_coins == 0)
            {
                if(!is_online_game)
                    return local_win();
                else
                {
                    //TODO
                }
            }
        }
    }
    for(auto e : level.get_enemys())
    {
        if(level.player.touche_enemy(e, level.w_enemy / 2))
        {
            hit_sound();
            level.player.x = level.last_touch_on_green_area.first;
            level.player.y = level.last_touch_on_green_area.second;
        };
        if(automatique)
        {
            for(auto &sn : level.Snubbys)
            {
                if(!sn.is_a_life)continue;
                if(sn.touche_enemy(e, level.w_enemy / 2))
                {
                    sn.is_a_life = 0;
                    level.N_Snubbys_a_life--;
                };
            }
        }
    }
}


int thread_update_position(void *_)
{
    while(1)
    {
        if(!is_playing)
        {
            SDL_Delay(10);
            continue;
        }
        SDL_Delay(1 / sensitivity);
        if(T[0])
        {
            if(check_it_free_area(level.player.x - 10, level.player.y) && is_player_inside_after(level.player.x - 20, level.player.y))
            {
                level.player.x -= SPEED;
            }

        }
        if(T[1])
        {
            if(check_it_free_area(level.player.x, level.player.y - 10 ) && is_player_inside_after(level.player.x, level.player.y - 20))
            {
                level.player.y -= SPEED;
            }
        }
        if(T[2])
        {
            if(check_it_free_area(level.player.x + 10, level.player.y) && is_player_inside_after(level.player.x + 20, level.player.y))
            {
                level.player.x += SPEED;
            }
        }
        if(T[3])
        {
            if(check_it_free_area(level.player.x, level.player.y + 10) && is_player_inside_after(level.player.x, level.player.y + 20))
            {
                level.player.y += SPEED;
            }
        }
    }
    return 1;
}
void update()
{
    for(auto &sp : level.spiral_dots)sp.next_move();
    for(auto &sp : level.big_spiral_dots)sp.next_move();
    for(auto &e : level.linear_enemys)e.next_move();
    for(auto &e : level.squar_enemys)e.next_move();
}

void check_status_of_playing2()
{
    int i = 0;
    for(auto &c : level.coins)
    {
        if(!c.is_taked && c.take(level.player2))
        {
            if(c.is_virtual)
            {
                level.virtuals--;
                level.coins.erase(level.coins.begin() + i);
            }
            level.c2++;
            coin_sound();
            level.n_coins--;
        }
        i++;
    }
    for(auto e : level.get_enemys())
    {
        if(level.player2.touche_enemy(e, level.w_enemy / 2))
        {
            hit_sound();
            level.player2.x = level.last_touch_on_green_area2.first;
            level.player2.y = level.last_touch_on_green_area2.second;
            again2--;
            if(!again2)
            {
                cout << "loser" << endl;
                //todo
                local_win(false);
            }
        };
    }
}

void check_status_of_playing()
{
    int i = 0;
    for(auto &c : level.coins)
    {
        if(!c.is_taked && c.take(level.player))
        {
            if(c.is_virtual)
            {
                level.virtuals--;
                level.coins.erase(level.coins.begin() + i);
            }
            else
                level.c1++;

            ocoins = i;
            cout << "++" << ocoins << endl;
            coin_sound();
            level.n_coins--;
            cout << level.n_coins << " - ---" << endl;
            if(level.n_coins == level.virtuals)
            {
                i_win = 1;
            }

        }
        i++;
    }
    for(auto e : level.get_enemys())
    {
        if(level.player.touche_enemy(e, level.w_enemy / 2))
        {
            hit_sound();
            level.player.x = level.last_touch_on_green_area.first;
            level.player.y = level.last_touch_on_green_area.second;
            again--;
            cout << again << endl;
            if(!again)
            {
                cout << "loser" << endl;
                //todo
                local_win(false);
            }
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


void move(bool Tt[4], Player &player)
{
    SDL_Delay(1 / sensitivity);

    if(Tt[0])
    {
        if(check_it_free_area(player.x - SPEED, player.y) && is_player_inside_after(player.x - 12, player.y))
        {
            player.x -= SPEED;
        }

    }
    if(Tt[1])
    {
        if(check_it_free_area(player.x, player.y - SPEED ) && is_player_inside_after(player.x, player.y - 12))
        {
            player.y -= SPEED;
        }
    }
    if(Tt[2])
    {
        if(check_it_free_area(player.x + SPEED, player.y) && is_player_inside_after(player.x + 12, player.y))
        {
            player.x += SPEED;
        }
    }
    if(Tt[3])
    {
        if(check_it_free_area(player.x, player.y + SPEED) && is_player_inside_after(player.x, player.y + 12))
        {
            player.y += SPEED;
        }
    }
}

int thread_update_position(void *_)
{
    while(1)
    {
        if(!is_playing)
        {
            SDL_Delay(2);
            continue;
        }
        // SDL_Delay(1 / sensitivity);

        // if(T[0])
        // {
        //     if(check_it_free_area(level.player.x - SPEED, level.player.y) && is_player_inside_after(level.player.x - 12, level.player.y))
        //     {
        //         level.player.x -= SPEED;
        //     }

        // }
        // if(T[1])
        // {
        //     if(check_it_free_area(level.player.x, level.player.y - SPEED ) && is_player_inside_after(level.player.x, level.player.y - 12))
        //     {
        //         level.player.y -= SPEED;
        //     }
        // }
        // if(T[2])
        // {
        //     if(check_it_free_area(level.player.x + SPEED, level.player.y) && is_player_inside_after(level.player.x + 12, level.player.y))
        //     {
        //         level.player.x += SPEED;
        //     }
        // }
        // if(T[3])
        // {
        //     if(check_it_free_area(level.player.x, level.player.y + SPEED) && is_player_inside_after(level.player.x, level.player.y + 12))
        //     {
        //         level.player.y += SPEED;
        //     }
        // }
    }
    return 1;
}
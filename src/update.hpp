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
            SDL_Delay(2);
            continue;
        }
        SDL_Delay(1 / sensitivity);
        if(T[0])
        {
            if(check_it_free_area(level.player.x - SPEED, level.player.y) && is_player_inside_after(level.player.x - 12, level.player.y))
            {
                level.player.x -= SPEED;
            }

        }
        if(T[1])
        {
            if(check_it_free_area(level.player.x, level.player.y - SPEED ) && is_player_inside_after(level.player.x, level.player.y - 12))
            {
                level.player.y -= SPEED;
            }
        }
        if(T[2])
        {
            if(check_it_free_area(level.player.x + SPEED, level.player.y) && is_player_inside_after(level.player.x + 12, level.player.y))
            {
                level.player.x += SPEED;
            }
        }
        if(T[3])
        {
            if(check_it_free_area(level.player.x, level.player.y + SPEED) && is_player_inside_after(level.player.x, level.player.y + 12))
            {
                level.player.y += SPEED;
            }
        }
    }
    return 1;
}
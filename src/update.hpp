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
                cout << "is Virtual 2" << endl;
                level.virtuals--;
                level.coins.erase(level.coins.begin() + i);
            }
            else
            {
                level.c2++;
                coin_sound();
            }
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
                cout << "P2 Loser" << endl;
                //todo
                local_win(true);
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
            level.n_coins--;

            if(c.is_virtual)
            {
                cout << "is Virtual" << endl;
                level.virtuals--;
                level.coins.erase(level.coins.begin() + i);
            }
            else
            {

                level.ocoins = i;
                cout << "++" << level.ocoins << endl;
                coin_sound();
                level.c1++;
                cout << level.n_coins << " - ---" << endl;
            }

        }
        i++;
    }
    if(level.n_coins == level.virtuals)
    {
        i_win = 1;
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
    }
}


void move(bool Tt[4], Player &player)
{
    if(Tt[0])
    {
        if(check_it_free_area(player.x - SPEED, player.y) && is_player_inside_after(player.x - SPEED, player.y))
        {
            player.x -= SPEED;
        }

    }
    if(Tt[1])
    {
        if(check_it_free_area(player.x, player.y - SPEED ) && is_player_inside_after(player.x, player.y - SPEED))
        {
            player.y -= SPEED;
        }
    }
    if(Tt[2])
    {
        if(check_it_free_area(player.x + SPEED, player.y) && is_player_inside_after(player.x + SPEED, player.y))
        {
            player.x += SPEED;
        }
    }
    if(Tt[3])
    {
        if(check_it_free_area(player.x, player.y + SPEED) && is_player_inside_after(player.x, player.y + SPEED))
        {
            player.y += SPEED;
        }
    }
}

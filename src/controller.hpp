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
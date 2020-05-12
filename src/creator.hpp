//pour creer le tableau de map
void get_wall()
{
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[1], NULL, &rect);
    SDL_RenderPresent(render);
    on = 0;
    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        xx = x;
        yy = y;
        x = event.motion.x;
        y = event.motion.y;
        if(x != xx and y != yy and x >= cx and y >= cy and x < cx + 20 * size_squar and y < cy + 20 * size_squar and on)
        {
            level.map[(int)((y - cx) / size_squar)][(int)((x - cy) / size_squar)] = -1;
            draw_wall();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[1], NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(5);
        }
        switch (event.type)
        {
        case SDL_QUIT:
            free_memory();
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
                on = 1 - on;
                break;
            case SDLK_s:
                on = 0;
                break;
            case SDLK_r:
                on = 1;
            case SDLK_n:
                continuer = 0;
                break;
            case SDLK_p:
                go_back = 1;
                return;
                break;
            case SDLK_g:
                level.random_map();
                draw_wall();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[1], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            }
        }
    }
}
void get_green_area()
{
    draw_wall();
    int g = 0;
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[4], NULL, &rect);
    SDL_RenderPresent(render);
    SDL_Delay(5);
    on = 0;
    continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        xx = x;
        yy = y;
        x = event.motion.x;
        y = event.motion.y;
        if(x != xx and y != yy and x >= cx and y >= cy and x < cx + 20 * size_squar and y < cy + 20 * size_squar and on)
        {
            level.map[(int)((y - cx) / size_squar)][(int)((x - cx) / size_squar)] = g;
            draw_wall();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[4], NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(5);
        }
        switch (event.type)
        {
        case SDL_QUIT:
            free_memory();
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_p:
                go_back = 1;
                return;
                break;
            case SDLK_s:
                on = 0;
                break;
            case SDLK_a:
                on = 1;
                g = 0;
                break;
            case SDLK_g :
                on = 1;
                g = 5;
                break;
            case SDLK_n:
                continuer = 0;
                break;
            case SDLK_b:
                break;
            }
        }
    }
}
void get_position_player()
{
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[3], NULL, &rect);
    SDL_RenderPresent(render);
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
            level.player.x = cx + 40 * (int)(( x - cx) / 40 ) + level.player.w / 2;
            level.player.y = cy + 40 * (int)(((y - cy) / 40)) + level.player.h / 2;
            draw_game();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[3], NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(40);
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
            }
        }
    }
}

void add_coins()
{
    draw_game();
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
    SDL_RenderPresent(render);
    SDL_Delay(10);
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
            level.coins.push_back(Coin(10 * (int)(x / 10), 10 * (int)(y / 10)));
            draw_game();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(40);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_p:
                go_back = 1;
                return;
                break;
            case SDLK_LEFT:
                level.coins.pop_back();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[2], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(40);
                break;
            case SDLK_n:
                continuer = 0;
                break;
            }
        }
    }
}

void add_spiral_dot()
{
    draw_game();
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
    SDL_RenderPresent(render);
    SDL_Delay(500);
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
            level.spiral_dots.push_back(Spiral_dot(make_pair(x, y), 5, 100));
            draw_game();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
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
            case SDLK_LEFT:
                level.spiral_dots[level.spiral_dots.size() - 1].R -= 5;
                level.spiral_dots[level.spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_RIGHT:
                level.spiral_dots[level.spiral_dots.size() - 1].R += 5;
                level.spiral_dots[level.spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_UP:
                level.spiral_dots[level.spiral_dots.size() - 1].n++;
                level.spiral_dots[level.spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_DOWN:
                level.spiral_dots[level.spiral_dots.size() - 1].n--;
                level.spiral_dots[level.spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_n:
                continuer = 0;
                break;
            case SDLK_r:
                level.spiral_dots.pop_back();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            }
        }
        SDL_Delay(5);
    }
}

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

void add_squar_enemy()
{
    draw_game();
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
                draw_game();

                rect = {-level.player.w / 2  + A.first, -level.player.h / 2 + B.second, level.player.w, level.player.h};
                SDL_RenderCopy(render, textureEnemy, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_KP_2:
                cout << "B est ajauter " << endl;
                B = make_pair(x, y);
                draw_game();
                rect = {-level.player.w / 2  + B.first, -level.player.h / 2 + B.second, level.player.w, level.player.h};
                SDL_RenderCopy(render, textureEnemy, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_KP_3:
                cout << "C est ajauter " << endl;
                C = make_pair(x, y);
                draw_game();
                rect = {-level.player.w / 2  + B.first, -level.player.h / 2 + B.second, level.player.w, level.player.h};
                SDL_RenderCopy(render, textureEnemy, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_KP_4:
                cout << "D est ajauter " << endl;
                D = make_pair(x, y);
                draw_game();
                rect = {-level.player.w / 2  + B.first, -level.player.h / 2 + B.second, level.player.w, level.player.h};
                SDL_RenderCopy(render, textureEnemy, NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_KP_0:
                cout << "la forme est ajauter" << endl;
                level.squar_enemys.push_back(Squar_enemy(A, B, C, D));
                draw_game();
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_r:
                level.linear_enemys.pop_back();
                draw_game();
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
void add_big_spiral_dot()
{
    draw_game();
    rect = {0, 100 + 40 * 12, 1024, 100} ;
    SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
    SDL_RenderPresent(render);
    SDL_Delay(500);
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
            level.big_spiral_dots.push_back(Big_spiral_dot(make_pair(x, y), 5, 100));
            draw_game();
            rect = {0, 100 + 40 * 12, 1024, 100} ;
            SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
            SDL_RenderPresent(render);
            SDL_Delay(5);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].R -= 5;
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_RIGHT:
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].R += 5;
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_UP:
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].n++;
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_DOWN:
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].n--;
                level.big_spiral_dots[level.big_spiral_dots.size() - 1].update();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            case SDLK_n:
                continuer = 0;
                break;
            case SDLK_p:
                go_back = 1;
                return;
                break;
            case SDLK_r:
                level.big_spiral_dots.pop_back();
                draw_game();
                rect = {0, 100 + 40 * 12, 1024, 100} ;
                SDL_RenderCopy(render, textureSlides[5], NULL, &rect);
                SDL_RenderPresent(render);
                SDL_Delay(5);
                break;
            }
        }
        SDL_Delay(5);
    }
}
void create_level()
{
    N_LEVELS++;
    l = N_LEVELS;
LEVEL0:
    go_back = 0;
    load_level(0);
    draw_wall();
    SDL_RenderPresent(render);
    SDL_Delay(5);
WALL:
    go_back = 0;
    cout << "wall ..." << endl;
    get_wall();
    if(go_back)goto LEVEL0;

GREEN:
    go_back = 0;
    cout << "grean zone ..." << endl;
    get_green_area();
    if(go_back)goto WALL;
COIN:
    go_back = 0;
    cout << "coins ..." << endl;
    add_coins();
    if(go_back)goto GREEN;
SPIRAL:
    go_back = 0;
    cout << "apirals ..." << endl;
    add_spiral_dot();
    if(go_back)goto COIN;
BIG_SPIRAL:
    go_back = 0;
    cout << "adding big spiral ..." << endl;
    add_big_spiral_dot();
    if(go_back)goto SPIRAL;
LINEAR:
    go_back = 0;
    cout << "linear enemy ..." << endl;
    add_linear_enemy();
    if(go_back)goto BIG_SPIRAL;
SQUAR:
    go_back = 0;
    cout << "squar enemy ..." << endl;
    add_squar_enemy();
    if(go_back)goto LINEAR;
POSITION:
    go_back = 0;
    cout << "initial position ..." << endl;
    get_position_player();
    if(go_back)goto SQUAR;
    go_back = 0;
    cout << "screen ..." << endl;
    screen_level();
    cout << "save level ..." << endl;
    save_level();
    save_n();

}
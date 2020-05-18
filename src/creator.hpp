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
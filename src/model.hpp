
//Mémorisez le numéro de niveau
void save_n()
{
    try
    {
        ofstream ofs("../levels/n");
        boost::archive::text_oarchive ar(ofs);
        ar &N_LEVELS;
    }
    catch (const std::exception &e)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR ",
                                 e.what(),
                                 window);
    }

}
//Connaître le numéro du niveau
void load_n()
{
    try
    {
        ifstream ifs("../levels/n");
        boost::archive::text_iarchive ar(ifs);
        ar &N_LEVELS;
    }
    catch (const std::exception &e)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR ",
                                 e.what(),
                                 window);
        free_memory();
    }
}

//Mémorisez le numéro des niveaus ouvert
void save_n_open()
{
    try
    {
        ofstream ofs("../levels/n_open");
        boost::archive::text_oarchive ar(ofs);
        ar &N_OPEN_LEVEL;
    }
    catch (const std::exception &e)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR ",
                                 e.what(),
                                 window);
    }

}
//Connaître le numéro des niveaus overts
void load_n_open()
{

    try
    {
        ifstream ifs("../levels/n_open");
        boost::archive::text_iarchive ar(ifs);
        ar &N_OPEN_LEVEL;
    }
    catch (const std::exception &e)
    {
        N_OPEN_LEVEL = 200;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR ",
                                 e.what(),
                                 window);
    }
}



void screen_level()
{
    int width = 1024, height = 668;
    s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(render, NULL, s->format->format, s->pixels, s->pitch);
    string z = "../levels/" + to_string(l) + ".png";
    IMG_SavePNG(s, z.c_str());
}

void screen()
{
    cout<<"taper s"<<endl;
    string s;
    cin>>s;
    int width = 1024, height = 668;
    s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(render, NULL, s->format->format, s->pixels, s->pitch);
    string z = s+ ".png";
    IMG_SavePNG(s, z.c_str());
}
void save_level()
{
    ofstream ofs( "../levels/" + to_string(N_LEVELS));
    boost::archive::text_oarchive ar(ofs);
    ll = &level;
    ar &ll;

}
void load_level(int k)
{
    try
    {
        ifstream ifs("../levels/" + to_string(k));
        boost::archive::text_iarchive ar(ifs);
        ar &ll;
        level = *ll;
        level.n_coins = level.coins.size();

        again = 5;
        again2 = 5;
        level.c1 = 0;
        level.c2 = 0;
        level.virtuals = 0;
        for (int i = 0; i < 4; ++i)
        {
            T[i] = 0;
            TT[i] = 0;
        }
        if(automatique || offline || is_online_game)
        {
            level.player2.x = level.player.x;
            level.player2.y = level.player.y;
        }
        else
        {
            level.player2.x = 0;
            level.player2.y = 0;
        }

    }
    catch(const std::exception &e)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR ",
                                 e.what(),
                                 window);
        free_memory();
    };
}


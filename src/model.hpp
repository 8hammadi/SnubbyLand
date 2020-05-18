
//Mémorisez le numéro de niveau
void save_n()
{
    ofstream ofs("../levels/n");
    boost::archive::text_oarchive ar(ofs);
    ar &N_LEVELS;
}
//Connaître le numéro du niveau
void load_n()
{
    ifstream ifs("../levels/n");
    boost::archive::text_iarchive ar(ifs);
    ar &N_LEVELS;
}

//Mémorisez le numéro des niveaus ouvert
void save_n_open()
{
    ofstream ofs("../levels/n_open");
    boost::archive::text_oarchive ar(ofs);
    ar &N_OPEN_LEVEL;
}
//Connaître le numéro des niveaus overts
void load_n_open()
{
    ifstream ifs("../levels/n_open");
    boost::archive::text_iarchive ar(ifs);
    ar &N_OPEN_LEVEL;
}



void screen_level()
{
    int width = 1024, height = 668;
    s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(render, NULL, s->format->format, s->pixels, s->pitch);
    string z = "../levels/" + to_string(l) + ".png";
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
    ifstream ifs("../levels/" + to_string(k));
    boost::archive::text_iarchive ar(ifs);
    ar &ll;
    level = *ll;
}


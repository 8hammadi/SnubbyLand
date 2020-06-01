
enum Interface
{
	NOTHING, INDEX, GET_LEVEL, GAME, LOCAL_WIN, PAUSE, LEVEL_CREATOR
};

Interface interface;
class Level;
SDL_Window *window;
SDL_Renderer *render;
SDL_Rect rect;
SDL_Surface *s, *ss[10];
SDL_Texture *texture, *textureblack, *texturePlayer2, *texture_wait, *texturePlayer, *textureEnemy, *textures[10], *textureCoin, *textureSlides[20];   //les variable de jeux

int l;//level
int continuer = 1, on = 0, p;
SDL_Event event, event_control, event2;
<<<<<<< HEAD
int x, y, xx, yy, cx =100, cy = 100, size_squar = 40, b;
=======
int x, y, xx, yy, cx = 100, cy = 100, size_squar = 40, b;
>>>>>>> 3e632433e6de01d023c36fabcf544f5fd499898b
bool go_back = 0, is_playing = 0, is_pause = 0, is_index = 0, automatique,offline, is_thinking = 0, status_thread_playing_online = 0;
TTF_Font *font;
int N_LEVELS = 0, N_OPEN_LEVEL;
double sensitivity = 0.2;
string text;
string mode;// "2ON" :2 players online "1OFF" : 1 player ofline
bool  T[4] = {0, 0, 0, 0};	// for player 1
bool  TT[4] = {0, 0, 0, 0}; // for player 2
//les variable de son
SDL_AudioSpec wav_spec[2];
Uint32 wav_length[2];
Uint8 *wav_buffer[2];
SDL_AudioDeviceID device_coin, device_enemy;

//les variable de jeux online
bool is_online_game = 0;
pair<int, int> player2;
string id2 = "0", token;
stringstream streams;
string id;
bool i_win = 0;
//les variable de l algorithm génétique
pair<int, int> A, B, C, D;
default_random_engine generator;
normal_distribution<double> distribution(0, 1);


string host = SERVER_STREAM;
string port = "80";


int ocoins = -1;
int again = 5, again2 = 5;

bool play_function_is_run=0;
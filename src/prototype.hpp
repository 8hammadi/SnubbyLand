inline void renderPause_win_lose(SDL_Renderer *render, bool win);
void renderLevelCreator(SDL_Renderer *render, int step);
int eventLevelCreator(int x, int y);

void init();// Initialise tous les variables de jeux
void index();//c'est l'index de jeux : la page initial de choix
//Pour la création de nouveau niveau
void get_wall();//Créez une carte, par vous ou randomly
void get_green_area();//Pour ajouter des espaces verts
void get_position_player();//pour ajauter la position initial de joeur
void add_coins();//pour ajouter les coins
void add_spiral_dot();//pour ajauter les spiral dot
void add_linear_enemy();//ajauter des obstacle lineare
void add_squar_enemy();
void add_big_spiral_dot();
int create_level();//le cœur du creation de nouveau niveau
//Pour le jeux
bool check_it_free_area(int x, int y);//vérifier si une position est possible ( check_it_free_area & is_player_inside_after)
bool is_player_inside_after(int x, int y);
void control_event();//lorsque le jeux est commencé il change la position de jeux si l utilisateur click sur un botton (up/left/down/Right)
void update();//Mise à jour du jeu
void check_status_of_playing();//Vérifiez si le joueur a touché des ennemis ou a terminé toutes les coins
void play();//le cœur du jeu
void show();//claire
void pause_game();//claire
void draw_levels();//pour le choix de niveau
void free_memory();//libérer la mémoire
int get_level();//obtenir le id(1,2,3 ...) du niveau
void screen_level();//enregistrer un image du niveau
void save_level();//claire
void load_level(int k);//claire

int thread_playing_online(void *_);
void move(bool T[4], Player &player); // move snubby based on T values
int thread_update_position(void *_);
void draw_wall();//claire
void draw_enemys();//claire
void draw_game();//claire
void online_game();
void save_n();
void load_n();
void local_win(bool win);
void coin_sound();
void hit_sound();
void load_n_open();//les niveau ouverts
void save_n_open();//les niveau ouverts

string send_level_to_server(int k);
bool get_level_from_server(string k	);
string get_text();

/////////////////////////////////   AUTOMATIC FUNCTIONS
void directSnubby(bool T[4], Player &s);

// vector<pair<int, int>> dijkstra(int map[12][20], pair<int, int> snubby, vector<pair<int, int>> coins);
int whenBlocked(vector<vector<int>> map, vector<Coin> &coins, int x, int y);
pair<int, int> getNearest(vector<Coin> &coins, int x, int y);
void aitHammadi(vector<vector<data>> &map, pair<int, int> coin, pair<int, int> snubby);
vector<pair<int, int>> path(vector<vector<data>> &map, pair<int, int> coin, pair<int, int> snubby);
/////////////////
int getWhere(Player &s, vector<pair<int, int>> r, int obs);
int step(pair<double, double> b);
pair<double, double> gothere(Player &s, vector<pair<int, int>> r, int obs);
pair<double, double> force(int radius, double q1, double q2, pair<int, int> r);
double Distance( int x0, int y0, int x1, int y1);
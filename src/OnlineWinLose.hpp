// buttons
#define ONLINEWINLOSE_button_width 100
#define ONLINEWINLOSE_button_height 50
#define ONLINEWINLOSE_button_x (WINDOW_WIDTH-ONLINEWINLOSE_button_width)/2
#define ONLINEWINLOSE_button_margin 20

//status
#define ONLINEWINLOSE_status_width 300 
#define ONLINEWINLOSE_status_height 200
#define ONLINEWINLOSE_status_x (WINDOW_WIDTH-ONLINEWINLOSE_status_width)/2
#define ONLINEWINLOSE_status_y (WINDOW_HEIGHT-ONLINEWINLOSE_status_height-5*ONLINEWINLOSE_button_margin-3*ONLINEWINLOSE_button_height )/2

// restart
#define ONLINEWINLOSE_restart_y  ONLINEWINLOSE_status_y+ONLINEWINLOSE_status_height+2*ONLINEWINLOSE_button_margin

// levels
#define ONLINEWINLOSE_levels_y ONLINEWINLOSE_restart_y+ONLINEWINLOSE_button_height+ONLINEWINLOSE_button_margin

// quit
#define ONLINEWINLOSE_quit_y  ONLINEWINLOSE_levels_y+ONLINEWINLOSE_button_height+ONLINEWINLOSE_button_margin

inline void renderONLINEWINLOSE(SDL_Renderer *render);

void  eventONLINEWINLOSE(int x, int y)
{
	// restart button
	if(ONLINEWINLOSE_button_x <= x && x <= ONLINEWINLOSE_button_x + ONLINEWINLOSE_button_width &&
			ONLINEWINLOSE_restart_y <= y && y <= ONLINEWINLOSE_restart_y + ONLINEWINLOSE_button_height)
	{
		cout << "ONLINE RESTART" << endl;
		is_playing = 0;
		load_level(l);
		is_playing = 1;
		is_pause = 0;
		return;
	}

	// levels button
	if(ONLINEWINLOSE_button_x <= x && x <= ONLINEWINLOSE_button_x + ONLINEWINLOSE_button_width &&
			ONLINEWINLOSE_levels_y <= y && y <= ONLINEWINLOSE_levels_y + ONLINEWINLOSE_button_height)
	{
		cout << "ONLINE LEVELS" << endl;
		is_pause = 0;
		is_playing = 0;
		l = get_level();
		// play();
		load_level(l);
		is_playing = 1;
	}
	// Quit button
	if(ONLINEWINLOSE_button_x <= x && x <= ONLINEWINLOSE_button_x + ONLINEWINLOSE_button_width &&
			ONLINEWINLOSE_quit_y <= y && y <= ONLINEWINLOSE_quit_y + ONLINEWINLOSE_button_height)
	{
		cout << "ONLINE QUIT" << endl;
		is_pause = 0;
		is_playing = 0;
		return index();
	}

}

inline void renderONLINEWINLOSE(SDL_Renderer *render, bool win)
{
	static SDL_Texture *ONLINEWINLOSE_status;
	if(win)
		static SDL_Texture *ONLINEWINLOSE_status =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/previous.png"));
	else
		static SDL_Texture *ONLINEWINLOSE_status =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/next.png"));
	static SDL_Texture *ONLINEWINLOSE_restart =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/restart.png"));
	static SDL_Texture *ONLINEWINLOSE_levels =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/levels.png"));
	static SDL_Texture *ONLINEWINLOSE_quit =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/quit.png"));

	SDL_SetRenderDrawColor(render, 0, 0, 0, 185);
	SDL_RenderFillRect(render, NULL);

	SDL_Rect rect = {ONLINEWINLOSE_status_x, ONLINEWINLOSE_status_y, ONLINEWINLOSE_status_width, ONLINEWINLOSE_status_height};
	SDL_RenderCopy(render, ONLINEWINLOSE_status, NULL, &rect);

	rect = {ONLINEWINLOSE_button_x, ONLINEWINLOSE_restart_y, ONLINEWINLOSE_button_width, ONLINEWINLOSE_button_height};
	SDL_RenderCopy(render, ONLINEWINLOSE_restart, NULL, &rect);

	rect = {ONLINEWINLOSE_button_x, ONLINEWINLOSE_levels_y, ONLINEWINLOSE_button_width, ONLINEWINLOSE_button_height};
	SDL_RenderCopy(render, ONLINEWINLOSE_levels, NULL, &rect);

	rect = {ONLINEWINLOSE_button_x, ONLINEWINLOSE_quit_y, ONLINEWINLOSE_button_width, ONLINEWINLOSE_button_height};
	SDL_RenderCopy(render, ONLINEWINLOSE_quit, NULL, &rect);
}
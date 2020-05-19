#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 668

// buttons
#define WIN_LOSE_button_width 100
#define WIN_LOSE_button_height 50
#define WIN_LOSE_button_x 50
#define WIN_LOSE_button_margin 20

// restart
#define WIN_LOSE_restart_y (WINDOW_HEIGHT-4*WIN_LOSE_button_height-3*WIN_LOSE_button_margin)/2

// levels
#define WIN_LOSE_levels_y WIN_LOSE_restart_y+WIN_LOSE_button_height+WIN_LOSE_button_margin

// quit
#define WIN_LOSE_quit_y  WIN_LOSE_levels_y+WIN_LOSE_button_height+WIN_LOSE_button_margin

// prev_next
#define WIN_LOSE_prev_next_y  WIN_LOSE_quit_y+WIN_LOSE_button_height+WIN_LOSE_button_margin

// previous
#define WIN_LOSE_previous_x (WINDOW_WIDTH -2*WIN_LOSE_button_width-WIN_LOSE_button_margin)/2

// next
#define WIN_LOSE_next_x WIN_LOSE_previous_x+WIN_LOSE_button_width+WIN_LOSE_button_margin



inline void renderPause_win_lose(SDL_Renderer *render)
{

	static SDL_Texture *WIN_LOSE_resume =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/resume.svg"));
	static SDL_Texture *WIN_LOSE_restart =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/restart.svg"));
	static SDL_Texture *WIN_LOSE_levels =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/levels.svg"));
	static SDL_Texture *WIN_LOSE_quit =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/quit.svg"));
	static SDL_Texture *WIN_LOSE_previous =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/previous.svg"));
	static SDL_Texture *WIN_LOSE_next =  SDL_CreateTextureFromSurface(render, IMG_Load("../images/buttons/next.svg"));

	SDL_SetRenderDrawColor(render, 0, 0, 0, 120);
	SDL_RenderFillRect(render, NULL);

	SDL_Rect rect = {WIN_LOSE_button_x, WIN_LOSE_restart_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
	SDL_RenderCopy(render, WIN_LOSE_restart, NULL, &rect);

	rect = {WIN_LOSE_button_x, WIN_LOSE_levels_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
	SDL_RenderCopy(render, WIN_LOSE_levels, NULL, &rect);

	rect = {WIN_LOSE_button_x, WIN_LOSE_quit_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
	SDL_RenderCopy(render, WIN_LOSE_quit, NULL, &rect);

	rect = {WIN_LOSE_previous_x, WIN_LOSE_prev_next_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
	SDL_RenderCopy(render, WIN_LOSE_previous, NULL, &rect);

	rect = {WIN_LOSE_next_x, WIN_LOSE_prev_next_y, WIN_LOSE_button_width, WIN_LOSE_button_height};
	SDL_RenderCopy(render, WIN_LOSE_next, NULL, &rect);
	if(1 == 0)
	{
		// add condition if player loses
		// TODO
		SDL_SetRenderDrawColor(render, 0, 0, 0, 0.50);
		SDL_RenderFillRect(render, &rect);
	}
}

void eventPause_win_lose(int x,int y)
{
	// restart button
	if(WIN_LOSE_button_x <= x && x <= WIN_LOSE_button_x + WIN_LOSE_button_width &&
			WIN_LOSE_restart_y <= y && y <= WIN_LOSE_restart_y + WIN_LOSE_button_height)
	{

	}

	// levels button
	if(WIN_LOSE_button_x <= x && x <= WIN_LOSE_button_x + WIN_LOSE_button_width &&
			WIN_LOSE_levels_y <= y && y <= WIN_LOSE_levels_y + WIN_LOSE_button_height)
	{

	}
	// Quit button
	if(WIN_LOSE_button_x <= x && x <= WIN_LOSE_button_x + WIN_LOSE_button_width &&
			WIN_LOSE_quit_y <= y && y <= WIN_LOSE_quit_y + WIN_LOSE_button_height)
	{

	}

	// Previous button
	if(WIN_LOSE_previous_x <= x && x <= WIN_LOSE_previous_x + WIN_LOSE_button_width &&
			WIN_LOSE_prev_next_y <= y && y <= WIN_LOSE_prev_next_y + WIN_LOSE_button_height)
	{

	}
	// Next button
	if(1 == 0)
	{
		// add condition if player loses
		// TODO
		return;
	}
	if(WIN_LOSE_next_x <= x && x <= WIN_LOSE_next_x + WIN_LOSE_button_width &&
			WIN_LOSE_prev_next_y <= y && y <= WIN_LOSE_prev_next_y + WIN_LOSE_button_height)
	{

	}

}
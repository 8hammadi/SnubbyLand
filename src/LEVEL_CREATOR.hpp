//guide
#define CREATOR_guide_width WINDOW_WIDTH-200
#define CREATOR_guide_height 70
#define CREATOR_guide_x (WINDOW_WIDTH-CREATOR_guide_width)/2
#define CREATOR_guide_y WINDOW_HEIGHT-CREATOR_guide_height


//plan
#define CREATOR_plan_width 30
#define CREATOR_plan_height WINDOW_HEIGHT-CREATOR_guide_height
#define CREATOR_plan_x 0
#define CREATOR_plan_y 0

//previous
#define CREATOR_previous_width 40
#define CREATOR_previous_height 20
#define CREATOR_previous_x (CREATOR_guide_x-CREATOR_previous_width)/2
#define CREATOR_previous_y (CREATOR_guide_y-CREATOR_previous_height)/2

//previous
#define CREATOR_next_width CREATOR_previous_width
#define CREATOR_next_height CREATOR_previous_height
#define CREATOR_next_x (WINDOW_WIDTH+CREATOR_guide_width+CREATOR_guide_x)/2
#define CREATOR_next_y CREATOR_previous_y

void renderLevelCreation(SDL_Renderer *render, int step);
void eventLevelCreator(SDL_Event *event);

void renderLevelCreation(SDL_Renderer *render, int step)
{
	SDL_RenderClear(render);
	static SDL_Texture prev = SDL_CreateTextureFromSurface(render, IMG_Load("../images/previous.png"));
	static SDL_Texture next = SDL_CreateTextureFromSurface(render, IMG_Load("../images/next.png"));
	rect = {CREATOR_previous_x, CREATOR_previous_y, CREATOR_previous_width, CREATOR_previous_height};
	SDL_RenderCopy(render, prev, NULL, &rect);
	rect = {CREATOR_next_x, CREATOR_next_y, CREATOR_next_width, CREATOR_next_height};
	SDL_RenderCopy(render, next, NULL, &rect);

	static SDL_Texture plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/drawzone.png"));
	static SDL_Texture guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/drawzone.png"));

	switch(step)
	{
	case 1:
		plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/safezone.png"));
		guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/drawzone.png"));
		break;
	case 2:
		plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/coins.png"));
		guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/drawzone.png"));
		break;
	case 3:
		plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/spiral.png"));
		guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/drawzone.png"));
		break;
	case 4:
		plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/bigspiral.png"));
		guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/drawzone.png"));
		break;
	case 5:
		plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/linear.png"));
		guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/drawzone.png"));
		break;
	case 6:
		plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/polygon.png"));
		guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/drawzone.png"));
		break;
	case 7:
		plan = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/snubbyposition.png"));
		guide = SDL_CreateTextureFromSurface(render, IMG_Load("../images/creator/drawzone.png"));
		break;
	}
	rect = {CREATOR_plan_x, CREATOR_plan_y, CREATOR_plan_width, CREATOR_plan_height};
	SDL_RenderCopy(render, plan, NULL, &rect);
	rect = {CREATOR_guide_x, CREATOR_guide_y, CREATOR_guide_width, CREATOR_guide_height};
	SDL_RenderCopy(render, guide, NULL, &rect);

	//todo draw level between CREATOR_plan_x<=x<=WINDOW_WIDTH and 0<=y<=CREATOR_guide_y
	draw_wall();

	SDL_RenderPresent(render);
}

rect = {CREATOR_previous_x, CREATOR_previous_y, CREATOR_previous_width, CREATOR_previous_height};

rect = {CREATOR_next_x, CREATOR_next_y, CREATOR_next_width, CREATOR_next_height};

void eventLevelCreator(int x, int y)
{
	if(CREATOR_previous_x <= x && x <= CREATOR_previous_x + CREATOR_previous_width &&
			CREATOR_previous_y <= y && y <= CREATOR_previous_y + CREATOR_previous_height)
	{
		// TODO: get back to previous step OR home if current step is to draw zone/wall

	}
	else if(CREATOR_next_x <= x && x <= CREATOR_next_x + CREATOR_next_width &&
			CREATOR_next_y <= y && y <= CREATOR_next_y + CREATOR_next_height)
	{
		// TODO: go to next step OR save level if current step is to position snubby in map
		// !!!!! P.S: check that snubby initial position is given first
	}
}

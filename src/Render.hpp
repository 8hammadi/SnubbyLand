#define TIME 30
// enum Interface
// {
// 	NOTHING, INDEX, GET_LEVEL, GAME, LOCAL_WIN, PAUSE
// };


int threadRender(void *_)
{

	int i = -1;
	while(1)
	{
		switch(interface)
		{
		case INDEX:
			i = 0;
			renderHome(render);
			SDL_RenderPresent(render);
			cout << "INDEX: " << interface << endl;
			while(interface == INDEX)
				SDL_Delay(TIME);
			break;

		case GET_LEVEL:
			i = 0;
			draw_levels();
			cout << "GET_LEVEL: " << interface << endl;
			interface = NOTHING;
			SDL_Delay(TIME);
			break;

		case LOCAL_WIN:
			i = 0;
			draw_game();
			renderPause_win_lose(render, win);
			show();
			cout << "LOCAL_WIN: " << interface << endl;
			while(interface == LOCAL_WIN)
				SDL_Delay(TIME);
			break;

		case PAUSE:
			draw_game();
			renderPause(render);
			show();
			cout << "PAUSE: " << interface << endl;
			while(interface == PAUSE)
				SDL_Delay(TIME);
			break;

		case GAME:
			draw_game();
			show();
			i++;
			if(i == 4)
				screen_level();
			// cout << "GAME: " << interface << endl;
			SDL_Delay(TIME);
			break;

		case LEVEL_CREATOR:
			i = 0;
			renderLevelCreator(render, stepp);
			SDL_RenderPresent(render);
			cout << stepp << " LEVEL_CREATOR: " << interface << endl;
			interface = NOTHING;
			SDL_Delay(TIME);
			break;

		case NOTHING:
			SDL_Delay(TIME);
			break;
		}
	}
}
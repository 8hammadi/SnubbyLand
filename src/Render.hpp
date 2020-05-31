#define TIME 30
// enum Interface
// {
// 	NOTHING, INDEX, GET_LEVEL, GAME, LOCAL_WIN, PAUSE
// };


int threadRender(void *_)
{
	while(1)
	{
		switch(interface)
		{
		case INDEX:
			renderHome(render);
			SDL_RenderPresent(render);
			cout << "INDEX: " << interface << endl;
			while(interface == INDEX)
				SDL_Delay(TIME);
			break;

		case GET_LEVEL:
			draw_levels();
			cout << "GET_LEVEL: " << interface << endl;
			interface = NOTHING;
			SDL_Delay(TIME);
			break;

		case LOCAL_WIN:
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
			rect = {0, 100 + 40 * 12, 1024, 100} ;
			SDL_RenderCopy(render, textureSlides[6], NULL, &rect);
			show();
			cout << "GAME: " << interface << endl;
			SDL_Delay(TIME);
			break;

		case LEVEL_CREATOR:
			renderLevelCreator(render, stepp);
			SDL_RenderPresent(render);
			cout << stepp << " LEVEL_CREATOR: " << interface << endl;
			interface = NOTHING;
			SDL_Delay(TIME);
			break;
			
		default :
			SDL_Delay(TIME);
			break;
		}
	}
}
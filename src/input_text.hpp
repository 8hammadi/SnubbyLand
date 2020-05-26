#define TMP_WINDOW_WIDTH 300
#define TMP_WINDOW_HEIGHT 200

#define TMP_TEXT_X 30
#define TMP_TEXT_Y 20

void draw_text2( SDL_Renderer *render2, char const *t, int x, int y)
{
    int w, h;
    TTF_SizeText( font, t, &w, &h);
    rect = {  x, y, w, h};
    SDL_Surface *surf = TTF_RenderText_Solid(font, t, {0, 0, 0});
    if(surf == NULL)
        cout << SDL_GetError() << "  SURF. NULL " << TTF_GetError() << endl;

    SDL_Texture *textu = SDL_CreateTextureFromSurface(render2, surf);
    if(textu == NULL)
        cout << TTF_GetError() << "  TEXT. NULL "  << SDL_GetError() << endl;

    SDL_RenderClear(render2);
    SDL_SetRenderDrawColor(render2, 255, 0, 0, 55);
    SDL_RenderFillRect(render2, NULL );
    SDL_RenderCopy(render2, textu, NULL, &rect);
    SDL_RenderPresent(render2);
}

string get_text()
{
    string in = "";
    SDL_Window *window2 = SDL_CreateWindow("Enter Level Code", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TMP_WINDOW_WIDTH, TMP_WINDOW_HEIGHT, 0);
    SDL_Renderer *render2 = SDL_CreateRenderer(window2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(render2, SDL_BLENDMODE_BLEND);

    SDL_SetWindowModalFor(window2, window);

    draw_text2( render2, in.c_str(), TMP_TEXT_X, TMP_TEXT_Y);
    SDL_StartTextInput();

    bool done = false;
    while (!done)
    {
        if (SDL_WaitEvent(&event))
        {
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_CLOSE)
                    ;
                else break;
            case SDL_QUIT:
                cout << 10101010 << endl;
                SDL_DestroyRenderer(render2);
                SDL_DestroyWindow(window2);
                done = true;
                break;
            case SDL_TEXTINPUT:
                if(in.size() < 10)
                    in.push_back(*event.text.text);
                break;
            case SDL_KEYDOWN:
            {
                char keyDown = event.key.keysym.scancode;
                if (keyDown == SDL_SCANCODE_BACKSPACE and in.size() > 0)  in.pop_back();
                else if (keyDown == SDL_SCANCODE_RETURN)
                {
                    SDL_DestroyRenderer(render2);
                    SDL_DestroyWindow(window2);
                    return in;
                }
            }
            break;
            }
            cout << in << endl;
            draw_text2( render2, in.c_str(), TMP_TEXT_X, TMP_TEXT_Y);
        }
        // Redraw();
    }
    return "202";
}
string get_text()
{
    string in="L";
    SDL_bool done = SDL_FALSE;
    while (!done)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                done = SDL_TRUE;
                break;
            case SDL_TEXTINPUT:
                if(in.size() < 10)
                    in.push_back(*event.text.text);
                break;
            case SDL_KEYDOWN:
            {
                char keyDown = event.key.keysym.scancode;
                if (keyDown == SDL_SCANCODE_BACKSPACE and in.size() > 0)  in.pop_back();
                else if (keyDown ==    SDL_SCANCODE_RETURN) return in;
            }
            break;

            }
            cout << in << endl;

            draw_levels();
            draw_text(in.c_str(), 200, 200, 200*in.size(), 200);
            show();
        }
        // Redraw();
    }
    return "202";
}
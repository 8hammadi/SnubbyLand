string get_text()
{
    string in;
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
                in.push_back(*event.text.text);
                break;
            case SDL_KEYDOWN:
            {
                char keyDown = event.key.keysym.scancode;
                if (keyDown == SDL_SCANCODE_BACKSPACE and in.size() > 0)  in.pop_back();
                else if (keyDown ==    SDL_SCANCODE_RETURN) return in;
                // else if (keyDown == SDL_SCANCODE_BACKSPACE)  BackSpaceKeyPressed = true;
                // else if (keyDown == SDL_SCANCODE_SPACE)  SpacebarKeyPressed = true;
                // else if (keyDown == SDL_SCANCODE_ESCAPE)  EscapeKeyPressed = true;
            }
            break;

            }
            cout << in << endl;
        }
        // Redraw();
    }
    return "202";
}
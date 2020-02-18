#ifndef EVENTS
/////////////////////////////////////////////////////////////////////////////////Constants
#define EVENTS 1

/////////////////////////////////////////////////////////////////////////////////Preprocessors
#include <stdio.h>
#include "SDL2/SDL_events.h"
#include "SDL2/SDL.h"
#include "Obstacle.h"
/////////////////////////////////////////////////////////////////////////////////Prototypes
int EventProcess( SDL_Event *event);
void WindowEventProcess(SDL_Event *event);
void KeyboardEventProcess(SDL_Event *event, int x);   //x=1 key down
void MouseEventProcess(SDL_Event *event);

/////////////////////////////////////////////////////////////////////////////////Structs
vector <Snubby> sn;

/////////////////////////////////////////////////////////////////////////////////Functions
// Process AddEventWatch function
int EventProcess( SDL_Event *event)
{
    switch(event->type)
    {
    case SDL_WINDOWEVENT:
        WindowEventProcess(event);
        break;
    case SDL_KEYDOWN:
        KeyboardEventProcess(event,  1);
        break;
    case SDL_KEYUP:
        KeyboardEventProcess(event,  0);
        break;
    case SDL_MOUSEBUTTONDOWN:
        MouseEventProcess(event);
        break;
    case SDL_QUIT:
        return 1;

    case SDL_USEREVENT:
        ;

        //int (*p) (void *) = event->user.data1;
        //p(event->user.data2)

        break;

    }

    return 0;
}

void mouve(int x, int y, int i)
{
    //obs
    Obstacle *obs = obstacles;
    while(i--)
    {
        obs = obs->next;
    }
    obs->x += x;
    obs->y += y;
}
//Process the vents related to the window.
void WindowEventProcess(SDL_Event *event)
{
    switch(event->window.event)
    {

    case SDL_WINDOWEVENT_SHOWN:         //window has been shown

        break;

    case SDL_WINDOWEVENT_HIDDEN:        //window has been hidden

        break;

    case SDL_WINDOWEVENT_MINIMIZED:     //window has been minimized

        break;

    case SDL_WINDOWEVENT_RESTORED:      //window has been restored to normal size and position

        break;

    case SDL_WINDOWEVENT_CLOSE:         //the window manager requests that the window be closed
        event->type = SDL_QUIT;
        SDL_PushEvent(event);
        break;

    }
}

//Process the vents related to the Mouse.
void MouseEventProcess(SDL_Event *event)
{
    switch(event->button.button)
    {

    case SDL_BUTTON_LEFT:
        ;
        int x, y;
        SDL_GetMouseState(&x, &y);

        break;
    case SDL_BUTTON_RIGHT:

        break;
    }
}

//Process the vents related to the Keyboard.
void KeyboardEventProcess(SDL_Event *event, int x)
{

    SDL_Keycode key = event->key.keysym.sym;

    switch (key)    //Switch is used when cases are CONSTANTS
    {
    case SDLK_RETURN:
        cout << "ENTER " << endl;
        break;

    default:
        for(Snubby s : sn)
        {
            if(key == s.getUp())
                s.setUp(x == 1);
            else if(key == s.getDown())
                s.setDown(x == 1);
            else if(key == s.getLeft())
                s.setLeft(x == 1);
            else if(key == s.getRight())
                s.setRight(x == 1);
        }
        break;
    }
}





#endif
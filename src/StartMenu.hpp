#ifndef STARTMENU
/////////////////////////////////////////////////////////////////////////////////Constants
#define STARTMENU 1

//Images Paths
#define LOGO './images/Icons/Logo.png'
#define START_BUTTON './images/Icons/Start.png'
#define SETTINGS_BUTTON './images/Icons/Settings.png'
#define SFX_BUTTON_ON './images/Icons/SoundON.png'
#define SFX_BUTTON_OFF './images/Icons/SoundOFF.png'
#define MUSIC_BUTTON_ON './images/Icons/MusicON.png'
#define MUSIC_BUTTON_OFF './images/Icons/MusicOFF.png'

//Images Dimens
#define LOGO_WIDTH 400
#define LOGO_HEIGHT 170
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 50
#define ICON_SIZE 40

//Images Positions
#define LOGO_START_X (WINDOW_WIDTH-LOGO_WIDTH)/2
#define LOGO_START_Y (WINDOW_HEIGHT/2-LOGO_HEIGHT)/2
#define BUTTON_X (WINDOW_WIDTH-BUTTON_WIDTH)/2
#define START_BUTTON_Y WINDOW_HEIGHT/2
#define BOT_MARGIN 5                       //Bottom Margin between Buttons
#define SETTINGS_BUTTON_Y (START_BUTTON_Y + BUTTON_HEIGHT + BOT_MARGIN)
#define ICON_BUTTON_Y (SETTINGS_BUTTON_Y + BUTTON_HEIGHT + BOT_MARGIN)
#define SFX_START_X BUTTON_X
#define MUSIC_START_X (BUTTON_X+BUTTON_WIDTH-ICON_SIZE)

/////////////////////////////////////////////////////////////////////////////////Preprocessors


/////////////////////////////////////////////////////////////////////////////////Prototypes
void ShowStartMenu(SDL_Renderer *renderer);
void StartMenu_onClick(int x, int y);

/////////////////////////////////////////////////////////////////////////////////Main Function
void ShowStartMenu(SDL_Renderer *renderer)
{
    //Render the Background of the menu
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 70, 70, 255, 255);
    SDL_RenderFillRect(renderer, getRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

    RenderIcon(renderer, LOGO, LOGO_START_X, LOGO_START_Y, LOGO_WIDTH, LOGO_HEIGHT);    //LOGO

    RenderIcon(renderer, START_BUTTON, BUTTON_X, START_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);    //START Btn
//    RenderIcon(renderer, SETTINGS_BUTTON, BUTTON_X, SETTINGS_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);    //Settings Btn

    if(getSettings()->sound)
        RenderIcon(renderer, SFX_BUTTON_ON, SFX_START_X, ICON_BUTTON_Y, ICON_SIZE, ICON_SIZE);    //SFX Btn ON
    else
        RenderIcon(renderer, SFX_BUTTON_OFF, SFX_START_X, ICON_BUTTON_Y, ICON_SIZE, ICON_SIZE);    //SFX Btn OFF

    if(getSettings()->music)
        RenderIcon(renderer, MUSIC_BUTTON_ON, MUSIC_START_X, ICON_BUTTON_Y, ICON_SIZE, ICON_SIZE);    //SFX Btn ON
    else
        RenderIcon(renderer, MUSIC_BUTTON_OFF, MUSIC_START_X, ICON_BUTTON_Y, ICON_SIZE, ICON_SIZE);    //SFX Btn OFF

    SDL_RenderPresent(renderer);
}

void StartMenu_onClick(int x, int y)
{
    printf("StartMenu_onClick!!!!!!!!\n");
    // Start ButtonClicked
    // if( BUTTON_X <= x && x <= BUTTON_X + BUTTON_WIDTH
    //         && START_BUTTON_Y <= y && y <= START_BUTTON_Y + BUTTON_HEIGHT )
    //     showGame(0);
    // // Settings ButtonClicked
    // /*
    // if( BUTTON_X <= x && x <= BUTTON_X + BUTTON_WIDTH
    //         && SETTINGS_BUTTON_Y <= y && y <= SETTINGS_BUTTON_Y + BUTTON_HEIGHT )
    //     showGame(0);
    // */
    // // SFX ButtonClicked
    // if( BUTTON_X <= x && x  <= BUTTON_X + ICON_SIZE
    //         && ICON_BUTTON_Y <= y && y <= ICON_BUTTON_Y + ICON_SIZE )
    // {
    //     switchSound();
    //     showStartMenu();
    // }
    // // Music ButtonClicked
    // if( MUSIC_START_X <= x && x <= MUSIC_START_X + ICON_SIZE
    //         && ICON_BUTTON_Y <= y && y <= ICON_BUTTON_Y + ICON_SIZE )
    // {
    //     switchMusic();
    //     showStartMenu();
    // }
}


#endif
    // Creates a window and gives ScreenSurface it's surface
bool init( SDL_Window** Window , SDL_Surface** ScreenSurface , const int WindowWidth , const int WindowHeight );
    // Gives a SDL_Surface an image
bool LoadMedia(SDL_Surface** Surface , std::string path);
    // Free-s up window and it's surface memory
void close(SDL_Surface* Background , SDL_Window* Window);

bool init( SDL_Window** Window , SDL_Surface** ScreenSurface , const int WindowWidth , const int WindowHeight )
{

    bool check = 1;

    *Window = SDL_CreateWindow( "Schizo Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN );
    if( Window == NULL )
    {
        std::cout << " Window not created " << SDL_GetError();
    }
        else
    {
        *ScreenSurface = SDL_GetWindowSurface( *Window );
    }

    return check;
}

bool LoadMedia(SDL_Surface** Background , std::string path)
{
    bool check = 1;

    *Background = SDL_LoadBMP( path.c_str() );

    return check;
}

void close(SDL_Surface* Background , SDL_Window* Window)
{
        // Free Surface
    SDL_FreeSurface( Background );
    Background = NULL;

        // Free Window
    SDL_DestroyWindow( Window );
    Window = NULL;

    SDL_Quit();
}


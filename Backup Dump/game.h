    // Creates a window and gives ScreenSurface it's surface
bool init( SDL_Window** Window , SDL_Surface** ScreenSurface , SDL_Renderer** Renderer , const int WindowWidth , const int WindowHeight );
    // Gives a SDL_Surface an image
bool LoadMedia(SDL_Surface** Surface , std::string path);
    // Free-s up window and it's surface memory
void close( SDL_Window* Window);

bool init( SDL_Window** Window , SDL_Surface** ScreenSurface , SDL_Renderer** Renderer, const int WindowWidth , const int WindowHeight )
{

    bool check = 1;

    *Window = SDL_CreateWindow( "", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN );

    if( Window == NULL )
    {
        std::cout << " Window not created " << SDL_GetError();
    }
        else
    {
        *Renderer = SDL_CreateRenderer( *Window, -1, SDL_RENDERER_ACCELERATED );
        SDL_SetRenderDrawColor( *Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        *ScreenSurface = SDL_GetWindowSurface( *Window );
    }

    return check;
}

SDL_Texture* LoadTexture( SDL_Renderer** Renderer std::string path )
{
    SDL_Texture* Texture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    Texture = SDL_CreateTextureFromSurface( Renderer, loadedSurface );

    SDL_FreeSurface( loadedSurface );

    return Texture;
}

void close( SDL_Window* Window)
{

    SDL_DestroyWindow( Window );
    Window = NULL;

    SDL_Quit();
}


struct structWindow
{
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Surface* WindowSurface;

    int WindowWidth;
    int WindowHeight;

    structWindow( int , int );
    void init();
};

structWindow::structWindow( int Width , int Height )
{
    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;
    SDL_Surface* WindowSurface = nullptr;

    WindowWidth = Width;
    WindowHeight = Height;

}

void structWindow::init()
{
    Window = SDL_CreateWindow( NULL , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , WindowWidth , WindowHeight , SDL_WINDOW_SHOWN );

    Renderer = SDL_CreateRenderer( Window , -1 , SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    WindowSurface = SDL_GetWindowSurface( Window );

}

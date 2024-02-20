struct structWindow
{
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Surface* WindowSurface;

    int WindowWidth;
    int WindowHeight;

    int LevelWidth;
    int LevelHeight;
};

void initWindow( structWindow& Window , int WWidth , int WHeight , int LWidht , int LHeight )
{
    Window.Window = SDL_CreateWindow( NULL , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , WWidth , WHeight , 0  );
    Window.Renderer = SDL_CreateRenderer( Window.Window , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    Window.WindowSurface = SDL_GetWindowSurface( Window.Window );
}

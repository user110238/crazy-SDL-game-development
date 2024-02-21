struct structWindow
{
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Surface* WindowSurface;
};

void initWindow( structWindow& Window )
{
    Window.Window = SDL_CreateWindow( NULL , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , Resolution::WindowWidth , Resolution::WindowHeight , 0  );
    Window.Renderer = SDL_CreateRenderer( Window.Window , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    Window.WindowSurface = SDL_GetWindowSurface( Window.Window );
}

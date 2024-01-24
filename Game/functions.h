void initialize( SDL_Window** Window , SDL_Surface** ScreenSurface , SDL_Renderer** Renderer, const int WindowWidth , const int WindowHeight )
{
    *Window = SDL_CreateWindow( NULL , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , WindowWidth , WindowHeight , SDL_WINDOW_SHOWN );

    *Renderer = SDL_CreateRenderer( *Window , -1 , SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( *Renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    *ScreenSurface = SDL_GetWindowSurface( *Window );

}

SDL_Texture* loadTexture( SDL_Renderer* Renderer , std::string path )
{
    SDL_Texture* Texture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    Texture = SDL_CreateTextureFromSurface( Renderer, loadedSurface );

    SDL_FreeSurface( loadedSurface );

    return Texture;
}

void loadMedia( SDL_Texture** Texture , SDL_Renderer* Renderer )
{

    *Texture = loadTexture( Renderer , "assets/idk.png" );

}

void renderTexture ( SDL_Renderer* Renderer , SDL_Texture* Texture , SDL_Rect Rect )
{
    SDL_RenderClear( Renderer );

    SDL_RenderCopy( Renderer, Texture, NULL, &Rect );

    SDL_RenderPresent( Renderer );

}

void renderRect ( SDL_Renderer* Renderer , SDL_Rect Rect)
{
    SDL_RenderClear( Renderer );

    SDL_SetRenderDrawColor( Renderer, 255 , 0 , 0 , 255 );
    SDL_RenderFillRect( Renderer, &Rect );

    SDL_RenderPresent(Renderer);

}

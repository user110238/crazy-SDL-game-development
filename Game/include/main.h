
void initialize( SDL_Window** Window , SDL_Surface** ScreenSurface , SDL_Renderer** Renderer , const int WindowWidth , const int WindowHeight )
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

void rendererAdd( SDL_Renderer* Renderer , SDL_Texture* Texture , SDL_Rect Dest )
{
    SDL_RenderCopy( Renderer, Texture , NULL , &Dest );
}

bool collision( SDL_Rect a, SDL_Rect b )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    return true;
}

void scrolling( SDL_Rect& camera , SDL_Rect Player , int WindowWidth , int WindowHeight , int LevelWidth , int LevelHeight )
{
        camera.x = Player.x + Player.w / 2 - WindowWidth / 2;
        camera.y = Player.y + Player.h / 2 - WindowHeight / 2;

            // Keep the camera within the bounds of the level
        if (camera.x < 0)
            camera.x = 0;
        if (camera.y < 0)
            camera.y = 0;
        if (camera.x > LevelWidth - camera.w)
            camera.x = LevelWidth - camera.w;
        if (camera.y > LevelHeight - camera.h)
            camera.y = LevelHeight - camera.h;


}





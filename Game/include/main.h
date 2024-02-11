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

void rendererAdd( SDL_Renderer* Renderer , SDL_Texture* Texture , SDL_Rect Src , SDL_Rect Dest )
{

    SDL_RenderCopy( Renderer, Texture , &Src , &Dest );

}

void scrolling(SDL_Rect& camera, const SDL_Rect& Player, int WindowWidth, int WindowHeight, int LevelWidth, int LevelHeight) {
    // Calculate the desired center of the camera based on the player's position
    int centerX = Player.x + Player.w / 2;
    int centerY = Player.y + Player.h / 2;

    // Adjust camera position to keep the player centered within the window
    camera.x = centerX - WindowWidth / 2;
    camera.y = centerY - WindowHeight / 2;

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

int getRandomNumber(int min, int max) {
    return rand() % (max + 1 - min) + min;
}
float distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}





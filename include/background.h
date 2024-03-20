struct structBackground
{
    SDL_Texture* Texture;
    SDL_Rect Camera;
    SDL_Rect backgroundRect;
};

void initBackground ( structBackground& Background , const SDL_Rect& startCamera )
{
    Background.Camera.x = startCamera.x - Resolution::WindowWidth / 2;
    Background.Camera.y = startCamera.y - Resolution::WindowHeight / 2;
    Background.Camera.w = Resolution::WindowWidth;
    Background.Camera.h = Resolution::WindowHeight;

    Background.backgroundRect.x = 0;
    Background.backgroundRect.y = 0;
    Background.backgroundRect.w = Resolution::LevelWidth;
    Background.backgroundRect.h = Resolution::LevelHeight;
}

void offset( structBackground& Background )
{

        Background.backgroundRect.x = -Background.Camera.x;
        Background.backgroundRect.y = -Background.Camera.y;

}

void scrolling( SDL_Rect& camera , const SDL_Rect& player , int windowWidth , int windowHeight , int levelWidth , int levelHeight )
{
    int destX = player.x + player.w / 2 - windowWidth / 2;
    int desty = player.y + player.h / 2 - windowHeight / 2;

    int distanceX = destX - camera.x;
    int distanceY = desty - camera.y;

    camera.x += static_cast<int>( distanceX * 0.1 );
    camera.y += static_cast<int>( distanceY * 0.1 );

    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > levelWidth - camera.w)
        camera.x = levelWidth - camera.w;
    if (camera.y > levelHeight - camera.h)
        camera.y = levelHeight - camera.h;
}






struct back
{

    SDL_Texture* Texture;
    SDL_Rect Camera;
    SDL_Rect backgroundRect;

    //back( int , int , int , int );
    //void offset();

};

void initBackground ( back& Background , int WWidth , int WHeight , int LWidth , int LHeight )
{

    Background.Camera.x = 0;
    Background.Camera.y = 0;
    Background.Camera.w = WWidth;
    Background.Camera.h = WHeight;

    Background.backgroundRect.x = 0;
    Background.backgroundRect.y = 0;
    Background.backgroundRect.w = LWidth;
    Background.backgroundRect.h = LHeight;

}

void offset( back& Background )
{

        Background.backgroundRect.x = -Background.Camera.x;
        Background.backgroundRect.y = -Background.Camera.y;

}

void scrolling(SDL_Rect& camera, const SDL_Rect& Player, int WindowWidth, int WindowHeight, int LevelWidth, int LevelHeight) {

    int centerX = Player.x + Player.w / 2;
    int centerY = Player.y + Player.h / 2;

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





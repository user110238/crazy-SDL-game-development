struct back
{

    SDL_Texture* Texture;
    SDL_Rect Camera;
    SDL_Rect backgroundRect;

    back( int , int , int , int );
    void offset();

};

back::back( int WindowWidth , int WindowHeight , int LevelWidth , int LevelHeight )
{

    Camera.x = 0;
    Camera.y = 0;
    Camera.w = WindowWidth;
    Camera.h = WindowHeight;

    backgroundRect.x = 0;
    backgroundRect.y = 0;
    backgroundRect.w = LevelWidth;
    backgroundRect.h = LevelHeight;

}

void back::offset()
{

        backgroundRect.x = -Camera.x;
        backgroundRect.y = -Camera.y;

}




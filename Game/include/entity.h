struct Entity
{

    SDL_Rect Rect;
    SDL_Texture* Texture;

};

void pushRandom( std::vector<struct Entity> &Enemy , int x , int LevelWidth , int WindowHeight )
{
    srand(time(NULL));

    for ( int i = 0 ; i < x ; i++ )
    {
        int Randomx = rand()%(LevelWidth);
        int Randomy = rand()%(WindowHeight);

        Enemy.push_back( { Randomx, Randomy, constant::ENTITY_SIZE_X, constant::ENTITY_SIZE_Y, nullptr } );

    }
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

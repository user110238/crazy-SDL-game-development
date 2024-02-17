struct Entity
{

    SDL_Rect Rect;
    SDL_Texture* Texture;

};

/*struct Enemy : public Entity
{

  SDL_Point randomPoint;

};*/


void pushRandom( std::vector<struct Entity> &Entity , int x , int LevelWidth , int WindowHeight )
{

    for ( int i = 0 ; i < x ; i++ )
    {
        int Randomx = rand()%(LevelWidth);
        int Randomy = rand()%(WindowHeight);

        Entity.push_back( { Randomx, Randomy, constant::ENTITY_SIZE_X, constant::ENTITY_SIZE_Y, nullptr } );

    }
}

/*void pushRandom( std::vector<struct Enemy> &Enemy , int x , int LevelWidth , int WindowHeight )
{

    for ( int i = 0 ; i < x ; i++ )
    {
        int Randomx = rand()%(LevelWidth);
        int Randomy = rand()%(WindowHeight);
        
        int RRandomx = rand()%((Randomx + constant::WANDER_DISTANCE) - (Randomx - constant::WANDER_DISTANCE) ) + Randomx - constant::WANDER_DISTANCE;
        int RRandomy = rand()%((Randomy + constant::WANDER_DISTANCE) - (Randomy - constant::WANDER_DISTANCE) ) + Randomy - constant::WANDER_DISTANCE;


        Enemy.push_back( { Randomx, Randomy, constant::ENTITY_SIZE_X, constant::ENTITY_SIZE_Y, nullptr, { RRandomx , RRandomy } } );

    }
}*/

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

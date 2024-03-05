enum EntityType
{
    Enemy,
    FireEnemy,
    Tree,
    Ally
};

struct Entity
{

    SDL_Rect Rect;
    EntityType Type;

};

struct AllEntities
{
    std::vector<struct Entity> Enemy;
    std::vector<struct Entity>::iterator enemyIt = Enemy.begin();

    std::vector<struct Entity> Allies;
    std::vector<struct Entity>::iterator allyIt = Allies.begin();

    std::vector<struct Entity> Tree;
    std::vector<struct Entity>::iterator treeIt = Allies.begin();

};

void pushRandom( std::vector<struct Entity> &Entity , int x , int LevelWidth , int WindowHeight , EntityType Type )
{

    for ( int i = 0 ; i < x ; i++ )
    {
        int Randomx = rand()%(LevelWidth - constant::ENTITY_SIZE_X);
        int Randomy = rand()%(WindowHeight - constant::ENTITY_SIZE_Y);

        Entity.push_back( { Randomx, Randomy, constant::ENTITY_SIZE_X, constant::ENTITY_SIZE_Y, Type } );

    }
}

void pushToPairCoords( std::vector<struct Entity>& Entity , int x , int alliesPerCamp ,std::vector<std::pair< int , int >> Coords, EntityType Type )
{
    for ( int i = 0 ; i < x ; i++ )
    {
        for ( int j = 0 ; j < alliesPerCamp ; j++ )
        {
        int Randomx = rand()%(constant::CAMP_SPAWN_DISTANCE);
        int Randomy = rand()%(constant::CAMP_SPAWN_DISTANCE);

        Entity.push_back( { Coords[i].first*constant::PIXEL_SIZE + Randomx, Coords[i].second*constant::PIXEL_SIZE + Randomy, constant::ENTITY_SIZE_X, constant::ENTITY_SIZE_Y, Type } );
        }
    }
}

Entity* findNearestEntity( SDL_Rect enemy , std::vector<Entity>& entity )
{
    Entity* nearestEntity = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for ( std::vector<Entity>::iterator it = entity.begin() ; it != entity.end() ; ++it )
    {
        float dist = distance( enemy.x , enemy.y , it->Rect.x , it->Rect.y );
        if ( dist < minDistance )
        {
            minDistance = dist;
            nearestEntity = &(*it);
        }
    }

    return nearestEntity;
}

void moveTowards( SDL_Rect& srcRect , SDL_Rect& destRect , int speed )
{
        // distance between rectangles
    int DX = destRect.x - srcRect.x;
    int DY = destRect.y - srcRect.y;

    if ( DX == 0 || DY == 0 )
        return;

        // normalize the vector
        // Pitagorov zakon po slovensko
    double lenght = std::sqrt(DX * DX + DY * DY);
    double normDX = DX / lenght;
    double normDY = DY / lenght;

        // move src rectangle acording to the normalized vector
    srcRect.x += (int)( normDX * speed );
    srcRect.y += (int)( normDY * speed );

}

void moveRandomly( SDL_Rect& srcRect , int distance , int speed )
{
    double randomAngle = static_cast<double>(std::rand()) / RAND_MAX * 2.0 * M_PI;

    int destX = srcRect.x + static_cast<int>(std::cos(randomAngle) * distance);
    int destY = srcRect.y + static_cast<int>(std::sin(randomAngle) * distance);

    destX = std::max( 0, std::min( destX, Resolution::LevelWidth - srcRect.w )  );
    destY = std::max( 0, std::min( destY, Resolution::LevelHeight - srcRect.h ) );

    SDL_Rect destRect;
    destRect.x = destX;
    destRect.y = destY;
    destRect.w = 0;
    destRect.h = 0;

    moveTowards(  srcRect, destRect, speed );
}

bool collision( SDL_Rect a , SDL_Rect b )
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

void moveRectAwayEachother( SDL_Rect &rect1 , SDL_Rect &rect2 , float speed )
{
    int DX = ( rect2.x + rect2.w / 2 ) - ( rect1.x + rect1.w / 2 );
    int DY = ( rect2.y + rect2.h / 2 ) - ( rect1.y + rect1.h / 2 );

    float lenght = sqrt( DX * DX + DY * DY );

    if ( lenght < 100 )
    {
            // Normalize vector
        float normDX = DX / lenght;
        float normDY = DY / lenght;

        rect1.x -= static_cast<int>( speed * normDX );
        rect1.y -= static_cast<int>( speed * normDY );

        rect2.x += static_cast<int>( speed * normDX );
        rect2.y += static_cast<int>( speed * normDY );
    }
}

void moveRectAway( SDL_Rect &rect1 , SDL_Rect &rect2 , float speed )
{
    int DX = ( rect2.x + rect2.w / 2 ) - ( rect1.x + rect1.w / 2 );
    int DY = ( rect2.y + rect2.h / 2 ) - ( rect1.y + rect1.h / 2 );

    float lenght = sqrt( DX * DX + DY * DY );

    if ( lenght < 100 )
    {
            // Normalize vector
        float normDX = DX / lenght;
        float normDY = DY / lenght;

        rect1.x -= static_cast<int>( speed * normDX );
        rect1.y -= static_cast<int>( speed * normDY );
    }
}


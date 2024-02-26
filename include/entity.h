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
        int Randomx = rand()%(LevelWidth);
        int Randomy = rand()%(WindowHeight);

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

Entity* findNearestEntity(SDL_Rect enemy, std::vector<Entity>& entity)
{
    Entity* nearestEntity = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (std::vector<Entity>::iterator it = entity.begin(); it != entity.end(); ++it)
    {
        float dist = distance(enemy.x, enemy.y, it->Rect.x, it->Rect.y);
        if (dist < minDistance)
        {
            minDistance = dist;
            nearestEntity = &(*it);
        }
    }

    return nearestEntity;
}

void moveTowards(SDL_Rect& srcRect, SDL_Rect& destRect, EntityType Type )
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
    if ( Type == EntityType::Enemy )
    {
        srcRect.x += (int)(normDX * constant::ENEMY_VELOCITY);
        srcRect.y += (int)(normDY * constant::ENEMY_VELOCITY);
    }
    else if ( Type = EntityType::Ally )
    {
        srcRect.x += (int)(normDX * constant::ALLY_VELOCITY);
        srcRect.y += (int)(normDY * constant::ALLY_VELOCITY);

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

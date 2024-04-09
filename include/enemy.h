void HandleEnemyMovement( Entity& Enemy , std::vector<Entity>& trees , const std::vector<std::vector<Tile>>& Forest )
{
    Entity* nearestTree = findNearestEntity( Enemy.Rect , trees );
    SDL_Rect targetRect;

        // Calculates the distance to the nearest tree
    if ( nearestTree != nullptr ) {
        targetRect = nearestTree->Rect;
    } else {
        targetRect.x = Enemy.Rect.x;
        targetRect.y = Enemy.Rect.y;
    }

    if ( Enemy.Rect.x > targetRect.x ){
        Enemy.Flip = SDL_FLIP_HORIZONTAL;
    } else if ( Enemy.Rect.x < targetRect.x ) {
        Enemy.Flip = SDL_FLIP_NONE;
    }

    if ( isOnTile( Forest , Enemy.Rect , Tile::Blue ) )
        moveTowards( Enemy.Rect , targetRect , constant::ENEMY_VELOCITY / constant::WATER_SLOWDOWN );
    else
        moveTowards( Enemy.Rect , targetRect , constant::ENEMY_VELOCITY );
}

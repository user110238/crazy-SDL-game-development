void HandleEnemyMovement( SDL_Rect& enemyRect , std::vector<Entity>& trees , const std::vector<std::vector<Tile>>& Forest )
{
    Entity* nearestTree = findNearestEntity(enemyRect, trees);
    SDL_Rect targetRect;

        // Calculates the distance to the nearest tree
    if ( nearestTree != nullptr ) {
        targetRect = nearestTree->Rect;
    } else {
        targetRect.x = enemyRect.x;
        targetRect.y = enemyRect.y;
    }

    if ( isOnTile( Forest , enemyRect , Tile::Blue ) )
        moveTowards( enemyRect , targetRect , constant::ENEMY_VELOCITY / constant::WATER_SLOWDOWN );
    else
        moveTowards( enemyRect , targetRect , constant::ENEMY_VELOCITY );
}

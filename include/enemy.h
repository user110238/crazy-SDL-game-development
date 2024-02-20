void HandleEnemyMovement(SDL_Rect& enemyRect, std::vector<Entity>& trees)
{
    Entity* nearestTree = findNearestEntity(enemyRect, trees);
    SDL_Rect targetRect;

        // Calculates the distance to the nearest tree
    if (nearestTree != nullptr ) {
        targetRect = nearestTree->Rect;
    } else {
        targetRect.x = enemyRect.x;
        targetRect.y = enemyRect.y;
    }

    moveTowards( enemyRect , targetRect , EntityType::Enemy );
}

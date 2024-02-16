void moveTowards(SDL_Rect& srcRect, SDL_Rect& destRect )
{
        // distance between rectangles
    int DX = destRect.x - srcRect.x;
    int DY = destRect.y - srcRect.y;

        // normalize the vector
        // Pitagorov zakon po slovensko
    double lenght = std::sqrt(DX * DX + DY * DY);
    double normDX = DX / lenght;
    double normDY = DY / lenght;

            // move src rectangle acording to the normalized vector
    srcRect.x += (int)(normDX * constant::ENEMY_VELOCITY);
    srcRect.y += (int)(normDY * constant::ENEMY_VELOCITY);

}

void moveTowards(SDL_Rect& srcRect, SDL_Point& destPoint )
{
        // distance between rectangles
    int DX = destPoint.x - srcRect.x;
    int DY = destPoint.y - srcRect.y;

        // normalize the vector
        // Pitagorov zakon po slovensko
    double lenght = std::sqrt(DX * DX + DY * DY);
    double normDX = DX / lenght;
    double normDY = DY / lenght;

            // move src rectangle acording to the normalized vector
    srcRect.x += (int)(normDX * constant::ENEMY_VELOCITY);
    srcRect.y += (int)(normDY * constant::ENEMY_VELOCITY);

}

Entity* findNearestTree(Entity enemy, std::vector<Entity>& trees)
{
    Entity* nearestTree = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (std::vector<Entity>::iterator it = trees.begin(); it != trees.end(); ++it)
    {
        float dist = distance(enemy.Rect.x, enemy.Rect.y, it->Rect.x, it->Rect.y);
        if (dist < minDistance)
        {
            minDistance = dist;
            nearestTree = &(*it);
        }
    }

    return nearestTree;
}

void HandleEnemyMovement(Entity& enemy, SDL_Rect playerRect, std::vector<Entity>& trees, int detectionRange)
{
    Entity* nearestTree = findNearestTree(enemy, trees);
    SDL_Rect targetRect;

        // Calculates the distance to the nearest tree
        // Priority is tree over player
    if (distance(enemy.Rect.x, enemy.Rect.y, playerRect.x, playerRect.y) <= detectionRange) {
        targetRect = playerRect;
        // Calculates if player is in range, if theere are no trees
    } else if (nearestTree != nullptr && distance(enemy.Rect.x, enemy.Rect.y, nearestTree->Rect.x, nearestTree->Rect.y) <= detectionRange) {
        targetRect = nearestTree->Rect;
        // Nothing in range
    } else {
        return;
    }

    moveTowards( enemy.Rect , targetRect );
}

void moveTowards(SDL_Rect& srcRect, SDL_Rect& destRect )
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
    srcRect.x += (int)(normDX * constant::ENEMY_VELOCITY);
    srcRect.y += (int)(normDY * constant::ENEMY_VELOCITY);

}

Entity* findNearestTree(SDL_Rect enemy, std::vector<Entity>& trees)
{
    Entity* nearestTree = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (std::vector<Entity>::iterator it = trees.begin(); it != trees.end(); ++it)
    {
        float dist = distance(enemy.x, enemy.y, it->Rect.x, it->Rect.y);
        if (dist < minDistance)
        {
            minDistance = dist;
            nearestTree = &(*it);
        }
    }

    return nearestTree;
}

void HandleEnemyMovement(SDL_Rect& enemyRect, std::vector<Entity>& trees)
{
    Entity* nearestTree = findNearestTree(enemyRect, trees);
    SDL_Rect targetRect;

        // Calculates the distance to the nearest tree
    if (nearestTree != nullptr ) {
        targetRect = nearestTree->Rect;
    } else {
        targetRect.x = enemyRect.x;
        targetRect.y = enemyRect.y;
    }

    moveTowards( enemyRect , targetRect );
}

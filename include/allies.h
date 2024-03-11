void HandleAllyMovement(SDL_Rect& allyRect, std::vector<Entity>& Enemy, int detection, const std::vector<std::vector<Tile>>& Forest)
{
    Entity* nearestEntity = findNearestEntity(allyRect, Enemy);
    SDL_Rect targetRect;

    std::pair<int, int> nearestRedTile = findNearestRedTile(allyRect, Forest);

    if (nearestEntity != nullptr && distance(allyRect.x, allyRect.y, nearestEntity->Rect.x, nearestEntity->Rect.y) <= detection)
    {
        targetRect = nearestEntity->Rect;
        moveTowards(allyRect, targetRect, constant::ALLY_VELOCITY);
    }
    else if (distance(allyRect.x, allyRect.y, nearestRedTile.first, nearestRedTile.second) <= detection)
    {
        targetRect.x = nearestRedTile.first;
        targetRect.y = nearestRedTile.second;
        moveTowards(allyRect, targetRect, constant::ALLY_VELOCITY);
    }
    else
    {
        moveRandomly(allyRect, 200, constant::ALLY_WANDER_VEL);
    }
}

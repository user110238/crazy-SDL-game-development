void HandleAllyMovement( SDL_Rect& allyRect, std::vector<Entity>& Enemy, int detection )
{
    Entity* nearestEntity = findNearestEntity( allyRect, Enemy );
    SDL_Rect targetRect;

    if ( nearestEntity!=nullptr && distance( allyRect.x , allyRect.y , nearestEntity->Rect.x , nearestEntity->Rect.y ) <= detection ) {
        targetRect = nearestEntity->Rect;
    } else {
        targetRect = allyRect;
    }

    moveTowards( allyRect , targetRect , EntityType::Ally );
}

std::vector<std::pair<int, int>> findCamps(const std::vector<std::vector<Tile>>& vector)
{
    std::vector<std::pair<int, int>> campCoords;

    for (int x = 0; x < vector.size(); ++x)
    {
        for (int y = 0; y < vector.at(0).size(); ++y)
        {
            if (vector[x][y] == Tile::Black)
            {
                // checks if current value is top left
                if (x > 0 && y > 0 && vector[x - 1][y] != Tile::Black && vector[x][y - 1] != Tile::Black)
                {
                    campCoords.push_back(std::make_pair(x, y));
                }
            }
        }
    }

    return campCoords;
}

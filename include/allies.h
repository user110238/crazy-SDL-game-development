void HandleAllyMovement( Entity& Ally , std::vector<Entity>& Enemy , int detection , const std::vector<std::vector<Tile>>& Forest )
{
    Entity* nearestEntity = findNearestEntity( Ally.Rect , Enemy );
    SDL_Rect targetRect;

    std::pair<int, int> nearestRedTile = findNearestRedTile( Ally.Rect , Forest );

    if ( nearestEntity != nullptr && distance( Ally.Rect.x , Ally.Rect.y , nearestEntity->Rect.x , nearestEntity->Rect.y ) <= detection )
    {
        targetRect = nearestEntity->Rect;
        moveTowards( Ally.Rect , targetRect , constant::ALLY_VELOCITY );
    }
    else if ( distance( Ally.Rect.x , Ally.Rect.y , nearestRedTile.first , nearestRedTile.second ) <= detection )
    {
        targetRect.x = nearestRedTile.first;
        targetRect.y = nearestRedTile.second;

        if ( Ally.Rect.x > targetRect.x ){
            Ally.Flip = SDL_FLIP_HORIZONTAL;
        } else if ( Ally.Rect.x < targetRect.x ) {
            Ally.Flip = SDL_FLIP_NONE;
        }

        moveTowards(Ally.Rect, targetRect, constant::ALLY_VELOCITY);
    }
    else
    {
        moveRandomly( Ally, 200, constant::ALLY_WANDER_VEL);
    }
}

void movePlayer ( Entity& player , SDL_Point dest , const std::vector<std::vector<Tile>>& Forest )
{
        // lenght of the vector
        // pitagorov zakon po slovensko
    float lenght = std::sqrt( dest.x * dest.x + dest.y * dest.y );

        // normalize the vector
    float normX = dest.x / lenght;
    float normY = dest.y / lenght;

    float scaledX;
    float scaledY;

        // scale the normalized vector by velocity
    if ( isOnTile( Forest , player.Rect , Tile::Blue ) )
    {
        scaledX = normX * constant::PLAYER_VELOCITY / constant::WATER_SLOWDOWN;
        scaledY = normY * constant::PLAYER_VELOCITY / constant::WATER_SLOWDOWN;
    } else {
        scaledX = normX * constant::PLAYER_VELOCITY;
        scaledY = normY * constant::PLAYER_VELOCITY;

    }
        // create the new postion
    int newX = player.Rect.x + static_cast<int>(scaledX);
    int newY = player.Rect.y + static_cast<int>(scaledY);

    if ( player.Rect.x > newX ){
        player.Flip = SDL_FLIP_HORIZONTAL;
    } else if ( player.Rect.x < newX ) {
        player.Flip = SDL_FLIP_NONE;
    }

        // move back if out of bounds
    if (newX >= 0 && newX + player.Rect.w <= Resolution::LevelWidth)
    {
        player.Rect.x = newX;
    }
    if (newY >= 0 && newY + player.Rect.h <= Resolution::LevelHeight)
    {
        player.Rect.y = newY;
    }

}

void playerGameLogic ( Entity& player , SDL_Point moveBy , std::vector<std::vector<Tile>>& Forest )
{
    movePlayer( player , moveBy , Forest );
    updateForest( Forest , player.Rect , Tile::Red , Tile::Brown , 50 );


    if ( player.Rect.x <= 0 )
    {
        player.Rect.x = 1;
    }
    if ( player.Rect.x + player.Rect.w >= Resolution::LevelWidth )
    {
        player.Rect.x = Resolution::LevelWidth - player.Rect.w;
    }
    if ( player.Rect.y <= 0 )
    {
        player.Rect.y = 1;
    }
    if ( player.Rect.y + player.Rect.h >= Resolution::LevelHeight )
    {
        player.Rect.y = Resolution::LevelHeight - player.Rect.h;
    }
}


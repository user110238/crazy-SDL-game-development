struct structPlayer
{
    SDL_Rect Rect;
    SDL_Point Velocity;
};

void initPlayer ( structPlayer& player , int x , int y  )
{

    player.Rect.x = x;
    player.Rect.y = y;
    player.Rect.w = constant::ENTITY_SIZE_X;
    player.Rect.h = constant::ENTITY_SIZE_Y;

    player.Velocity.x = 0;
    player.Velocity.y = 0;


}

void movePlayer ( structPlayer& player , const std::vector<std::vector<Tile>>& Forest )
{
        // lenght of the vector
        // pitagorov zakon po slovensko
    float lenght = std::sqrt(player.Velocity.x * player.Velocity.x + player.Velocity.y * player.Velocity.y);


        // normalize the vector
    float normX = player.Velocity.x / lenght;
    float normY = player.Velocity.y / lenght;

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

void playerGameLogic ( structPlayer& player , std::vector<std::vector<Tile>>& Forest )
{
    movePlayer( player , Forest );
    updateForest( Forest , player.Rect , Tile::Red , Tile::Brown , 50 );


    if ( player.Rect.x <= 0 )
    {
        player.Rect.x += 10;
    }
    if ( player.Rect.x + player.Rect.w >= Resolution::LevelWidth )
    {
        player.Rect.x -= 10;
    }
    if ( player.Rect.y <= 0 )
    {
        player.Rect.y += 10;
    }
    if ( player.Rect.y + player.Rect.h >= Resolution::LevelHeight )
    {
        player.Rect.y -= 10;
    }
}

